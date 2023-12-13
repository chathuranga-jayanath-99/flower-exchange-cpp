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

std::string receivedBuffer; // Shared buffer to store received data
std::mutex bufferMutex;     // Mutex to synchronize access to the shared buffer
std::condition_variable
    bufferCondition; // Condition variable to notify processing thread

atomic<bool> shutDownFlag(false);

vector<string> lines;

vector<string> split(const string &str, char delimiter) {
    vector<string> tokens;
    istringstream stream(str);
    string token;
    while (getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void receiveThread(int clientSocket) {

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
        std::unique_lock<std::mutex> lock(bufferMutex);
        // Wait until new data is available in the buffer
        bufferCondition.wait(lock, [] {
            return !receivedBuffer.empty() || shutDownFlag.load();
            ;
        });

        if (shutDownFlag.load()) {
            break;
        }

        // Process the data in the buffer
        std::istringstream iss(receivedBuffer);
        std::string message;
        while (std::getline(iss, message, MESSAGE_DELIMITER)) {
            // Perform processing tasks here
            std::cout << " Processed message: " << message << std::endl;

            lines.push_back(message);
        }

        // Clear the buffer for new data
        receivedBuffer.clear();

        // Unlock the mutex to allow the receive thread to modify the buffer
        lock.unlock();
    }
}

class ExchangeApplication {
  public:
    static ExchangeApplication &get() { return ex_app; }

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
    void readFile(vector<string> &lines, vector<Order> &validOrders,
                  vector<OrderEntry> &orderEntries,
                  map<string, string> &orderIDMap, int &orderCount) {

        for (string line : lines) {

            vector<string> tokens = split(line, ' ');

            // std::cout << "Tokens: ";
            // for (const auto &token : tokens) {
            //   std::cout << token << " ";
            // }
            // std::cout << std::endl;

            string orderID =
                orderIdGenerator(orderIDMap, tokens[0], orderCount);

            int *result = filterTokens(tokens);

            if (result[0] == 0) {
                if (result[1] != 0) {
                    OrderEntry orderEntry(orderID, tokens[0], tokens[1],
                                          stoi(tokens[2]), 1, stod(tokens[3]),
                                          stoi(tokens[4]), result[1]);
                    orderEntries.push_back(orderEntry);
                    continue;
                } else {
                }
            } else {
                Order order(orderID, tokens[0], tokens[1], stoi(tokens[2]),
                            stod(tokens[3]), stoi(tokens[4]));
                validOrders.push_back(order);
            }
        }

        return;
    }

    void writeFile(vector<OrderEntry> &orderEntries) {

        string fullFileName = "./results/Ravindu_test.csv";

        ofstream file(fullFileName);

        if (!file.is_open()) {
            cerr << "Error opening file.\n";
            return;
        }

        file << "OrderID,ClientOrderID,Instrument,Side,ExecStatus,Price,"
                "Quantity,"
                "Reason\n";

        for (auto &orderEntry : orderEntries) {
            file << orderEntry.getOrderID() << ","
                 << orderEntry.getClientOrderId() << ","
                 << orderEntry.getInstrument() << ","
                 << to_string(orderEntry.getSide()) << ","
                 << orderEntry.getExecStatus() << ","
                 << to_string(orderEntry.getPrice()) << ","
                 << to_string(orderEntry.getQuantity()) << ","
                 << orderEntry.getReason() << "\n";
        }

        file.close();
        return;
    }

  private:
    ExchangeApplication(){};
    ~ExchangeApplication(){};

    static ExchangeApplication ex_app;
};

ExchangeApplication ExchangeApplication::ex_app;

int main() {
    ExchangeApplication &ex_app = ExchangeApplication::get();

    vector<Order> validOrders;
    vector<OrderEntry> orderEntries;
    map<string, string> orderIDMap;
    int orderCount = 0;

    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
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
        std::cerr << "Error binding socket" << std::endl;
        close(serverSocket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening for connections" << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Server listening for connections..." << std::endl;

    // Accept a connection
    sockaddr_in clientAddr{};
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSocket =
        accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket == -1) {
        std::cerr << "Error accepting connection" << std::endl;
        close(serverSocket);
        return -1;
    }

    // Start the receive thread
    std::thread receiveThreadObj(receiveThread, clientSocket);

    // Start the process thread
    std::thread processThreadObj(processThread);

    // Wait for threads to finish
    receiveThreadObj.join();
    shutDownFlag.store(true);
    bufferCondition.notify_one();
    processThreadObj.join();

    // Close the client socket when done
    // close(clientSocket);

    ex_app.readFile(lines, validOrders, orderEntries, orderIDMap, orderCount);

    for (auto &order : validOrders) {
        order.printOrder();
    }

    ex_app.writeFile(orderEntries);

    return 0;
}