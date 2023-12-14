#include "Order.h"
#include "OrderEntry.h"
#include <arpa/inet.h>
#include <atomic>
#include <condition_variable>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

using namespace std;

const char MESSAGE_DELIMITER = '\n';

vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    istringstream stream(str);
    string token;
    while (getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

class ExchangeApplication {
  private:
    ExchangeApplication(int clientSocket);
    ~ExchangeApplication(){};
    string receivedBuffer; // Shared buffer to store received data
    mutex bufferMutex;     // Mutex to synchronize access to the shared buffer
    condition_variable
        bufferCondition; // Condition variable to notify processing thread
    atomic<bool> shutDownFlag;

    int clientSocket;

    thread receiveThreadObj;
    thread processThreadObj;

    vector<Order> validOrders;
    vector<OrderEntry> orderEntries;
    map<string, string> orderIDMap;
    int orderCount = 1;

  public:
    static ExchangeApplication &getInstance(int clientSocket);

    void start(int clientSocket) {
        receiveThreadObj =
            std::thread(&ExchangeApplication::receiveThread, this);
        processThreadObj =
            std::thread(&ExchangeApplication::processThread, this);

        receiveThreadObj.join();
        shutDownFlag.store(true);
        bufferCondition.notify_one();
        processThreadObj.join();
    }

    void receiveThread() {

        while (true) {
            char chunk[4096];
            ssize_t bytesRead = recv(clientSocket, chunk, sizeof(chunk), 0);

            if (bytesRead > 0) {
                // Lock the mutex before modifying the shared buffer
                lock_guard<mutex> lock(bufferMutex);
                receivedBuffer.append(chunk, bytesRead);

                // Notify the processing thread that new data is available
                bufferCondition.notify_one();

            } else if (bytesRead == 0) {
                cerr << "Connection closed by the server" << endl;
                break;
            } else if (errno != EWOULDBLOCK) {
                cerr << "Error receiving data" << endl;
                break;
            }
        }

        bufferCondition.notify_one();
    }

    void processThread() {
        while (true) {
            // Lock the mutex before accessing the shared buffer
            unique_lock<mutex> lock(bufferMutex);
            // Wait until new data is available in the buffer
            bufferCondition.wait(lock, [&] {
                return !receivedBuffer.empty() || shutDownFlag.load();
                ;
            });

            if (shutDownFlag.load()) {
                break;
            }

            // Process the data in the buffer
            istringstream iss(receivedBuffer);
            string message;
            while (getline(iss, message, MESSAGE_DELIMITER)) {
                // Perform processing tasks here
                cout << " Processed message: " << message << endl;
                readFile(message, validOrders, orderEntries, orderIDMap,
                         orderCount);
                // lines.push_back(message);
            }

            // Clear the buffer for new data
            receivedBuffer.clear();

            // Unlock the mutex to allow the receive thread to modify the buffer
            lock.unlock();
        }
    }

    // This function is used to generate orderID for each unique order
    string orderIdGenerator(map<string, string> &orderIDMap,
                            string &clientOrderId, int &orderCount) {
        if (orderIDMap.find(clientOrderId) == orderIDMap.end()) {
            orderIDMap[clientOrderId] = "ord" + to_string(orderCount);
            orderCount++;
            return orderIDMap[clientOrderId];
        } else {
            return orderIDMap[clientOrderId];
        }
    }

    // This function is used to filter out invalid orders
    int *filterTokens(vector<string> &tokens) {

        int *result = new int[3]; // result[0] = 1 if valid, 0 if invalid
                                  // result[1] = error code
                                  // result[2] = missing token index

        int token_count = 0;
        for (auto &token : tokens) {
            if (token == "") {
                result[0] = 0;
                result[1] = 0;
                result[2] = token_count;
                return result;
            }
            token_count++;
        }

        int side = stoi(tokens[2]);
        int price = stod(tokens[3]);
        int quantity = stoi(tokens[4]);

        if (side > 2 || side < 1) {
            result[0] = 0;
            result[1] = 1;
            result[2] = -1;
            return result;
        }

        if (price <= 0) {
            result[0] = 0;
            result[1] = 2;
            result[2] = -1;
            return result;
        }

        if (quantity <= 10 || quantity >= 1000 || quantity % 10 != 0) {
            result[0] = 0;
            result[1] = 3;
            result[2] = -1;
            return result;
        }

        result[0] = 1;
        result[1] = -1;
        result[2] = -1;
        return result;
    }

    // This function is used to read the file
    void readFile(string &line, vector<Order> &validOrders,
                  vector<OrderEntry> &orderEntries,
                  map<string, string> &orderIDMap, int &orderCount) {

        vector<string> tokens = split(line, ' ');

        // cout << "Tokens: ";
        // for (const auto &token : tokens) {
        //   cout << token << " ";
        // }
        // cout << endl;

        string orderID = orderIdGenerator(orderIDMap, tokens[0], orderCount);

        int *result = filterTokens(tokens);

        if (result[0] == 0) {
            if (result[1] != 0) {
                OrderEntry orderEntry(orderID, tokens[0], tokens[1],
                                      stoi(tokens[2]), 1, stod(tokens[3]),
                                      stoi(tokens[4]), result[1]);
                orderEntries.push_back(orderEntry);
            } else {
            }
        } else {
            Order order(orderID, tokens[0], tokens[1], stoi(tokens[2]),
                        stod(tokens[3]), stoi(tokens[4]));
            validOrders.push_back(order);
        }

        return;
    }

    vector<Order> getValidOrders() { return validOrders; }
};

ExchangeApplication &ExchangeApplication::getInstance(int clientSocket) {
    static ExchangeApplication instance(clientSocket);
    return instance;
}

ExchangeApplication::ExchangeApplication(int clientSocket)
    : clientSocket(clientSocket), shutDownFlag(false) {}

int main() {
    // ExchangeApplication &ex_app = ExchangeApplication::get();

    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Error creating socket" << endl;
        return -1;
    }

    // Bind the socket to a specific address and port
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr =
        INADDR_ANY; // Listen on any available interface
    serverAddr.sin_port =
        htons(12345); // Use a specific port (you can change this)

    if (bind(serverSocket, (struct sockaddr *)&serverAddr,
             sizeof(serverAddr)) == -1) {
        cerr << "Error binding socket" << endl;
        close(serverSocket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        cerr << "Error listening for connections" << endl;
        close(serverSocket);
        return -1;
    }

    cout << "Server listening for connections..." << endl;

    // Accept a connection
    sockaddr_in clientAddr{};
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSocket =
        accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket == -1) {
        cerr << "Error accepting connection" << endl;
        close(serverSocket);
        return -1;
    }

    ExchangeApplication &ex_app =
        ExchangeApplication::getInstance(clientSocket);
    ex_app.start(clientSocket);

    cout << "Valid Orders: " << endl;
    for (auto &order : ex_app.getValidOrders()) {
        order.printOrder();
    }

    return 0;
}