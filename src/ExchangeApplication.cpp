#include "./enums/Instrument.h"
#include "Constants.h"
#include "Order.h"
#include "OrderBook.h"
#include "OrderEntry.h"
#include "Utils.h"
#include <arpa/inet.h>
#include <atomic>
#include <condition_variable>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
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

    vector<OrderEntry> orderEntries;
    map<string, string> orderIDMap;
    int orderCount = 1;

    OrderBook roseOrderBook = OrderBook(Instrument::ROSE);
    OrderBook lavenderOrderBook = OrderBook(Instrument::LAVENDER);
    OrderBook lotusOrderBook = OrderBook(Instrument::LOTUS);
    OrderBook tulipOrderBook = OrderBook(Instrument::TULIP);
    OrderBook orchidOrderBook = OrderBook(Instrument::ORCHID);

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
            char chunk[1024 * 32];
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
                readLine(message, orderEntries, orderIDMap, orderCount);
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
    int *filterTokens(string &clientID, string &instrument_str,
                      string &side_str, string &price_str,
                      string &quantity_str) {

        int *result = new int[2]; // result[0] = 1 if valid, 0 if invalid
                                  // result[1] = error code

        if (clientID.empty() || instrument_str.empty() || side_str.empty() ||
            price_str.empty() || quantity_str.empty()) {
            // cout << "Empty" << endl;
            result[0] = 0;
            result[1] = 0;
            return result;
        }

        int side = stoi(side_str);
        int price = stod(price_str);
        int quantity = stoi(quantity_str);

        if (side > 2 || side < 1) {
            result[0] = 0;
            result[1] = 1;
            return result;
        }

        if (price <= 0) {
            result[0] = 0;
            result[1] = 2;
            return result;
        }

        if (quantity <= 10 || quantity >= 1000 || quantity % 10 != 0) {
            result[0] = 0;
            result[1] = 3;
            return result;
        }

        result[0] = 1;
        result[1] = -1;
        return result;
    }

    Instrument getInstrumentFromString(string instrumentString) {
        if (instrumentString == Constants::ROSE) {
            return Instrument::ROSE;
        } else if (instrumentString == Constants::LAVENDER) {
            return Instrument::LAVENDER;
        } else if (instrumentString == Constants::LOTUS) {
            return Instrument::LOTUS;
        } else if (instrumentString == Constants::ORCHID) {
            return Instrument::ORCHID;
        } else if (instrumentString == Constants::TULIP) {
            return Instrument::TULIP;
        } else {
            throw invalid_argument("Invalid Instrument");
        }
    }

    // This function is used to read the file
    void readLine(string &line, vector<OrderEntry> &orderEntries,
                  map<string, string> &orderIDMap, int &orderCount) {

        vector<string> tokens = split(line, ',');

        // cout << "Tokens: ";
        // for (const auto &token : tokens) {
        //     cout << token << " ";
        // }
        // cout << endl;

        string clientOrderId = tokens[0];
        string instrument_str = tokens[1];
        string side = tokens[2];
        string quantity = tokens[3];
        string price = tokens[4];

        string orderID = orderIdGenerator(orderIDMap, tokens[0], orderCount);

        int *result =
            filterTokens(clientOrderId, instrument_str, side, price, quantity);

        if (result[0] == 0) {
            string reasonStr = Utils::getReasonStrFromErrorCode(result[1]);
            OrderEntry orderEntry(orderID, clientOrderId, instrument_str, side,
                                  Constants::REJECTED, price, quantity,
                                  reasonStr);
            orderEntries.push_back(orderEntry);

        } else {
            Instrument instrument = getInstrumentFromString(instrument_str);
            Order order(orderID, clientOrderId, instrument, stoi(side),
                        stod(price), stoi(quantity));
            vector<OrderEntry> orderEntryVector = handleOrder(order);
            orderEntries.insert(orderEntries.end(), orderEntryVector.begin(),
                                orderEntryVector.end());
        }

        return;
    }

    vector<OrderEntry> handleOrder(Order &order) {
        Instrument instrument = order.getInstrument();
        if (instrument == Instrument::ROSE) {
            return roseOrderBook.processOrder(order);
        } else if (instrument == Instrument::LAVENDER) {
            return lavenderOrderBook.processOrder(order);
        } else if (instrument == Instrument::LOTUS) {
            return lotusOrderBook.processOrder(order);
        } else if (instrument == Instrument::TULIP) {
            return tulipOrderBook.processOrder(order);
        } else if (instrument == Instrument::ORCHID) {
            return orchidOrderBook.processOrder(order);
        } else {
            // Return empty vector
            vector<OrderEntry> orderEntryVector;
            return orderEntryVector;
        }
    }

    void writeFile() {

        string filename;

        cout << "Enter the name of the file you want to write: ";
        cin >> filename;

        string fullFileName = "./results/" + filename + ".csv";
        // string fullFileName = "./results/result7.csv";

        ofstream file(fullFileName);

        if (!file.is_open()) {
            cerr << "Error opening file.\n";
            return;
        }

        file << "OrderID,ClientOrderID,Instrument,Side,ExecStatus,Quantity,"
                "Price,"
                "Reason,Timestamp\n";

        for (auto &orderEntry : orderEntries) {
            file << orderEntry.getOrderID() << ","
                 << orderEntry.getClientOrderId() << ","
                 << orderEntry.getInstrument() << "," << orderEntry.getSide()
                 << "," << orderEntry.getQuantity() << ","
                 << orderEntry.getExecStatus() << "," << std::fixed
                 << std::setprecision(2) << orderEntry.getPrice() << ","
                 << orderEntry.getReason() << "," << orderEntry.getTimestamp()
                 << "\n";
        }

        file.close();
        return;
    }

    vector<OrderEntry> getOrderEntries() { return orderEntries; }

    void setOrderEntries(vector<OrderEntry> orderEntries) {
        this->orderEntries = orderEntries;
    }

    void setOrderIDMap(map<string, string> orderIDMap) {
        this->orderIDMap = orderIDMap;
    }

    void setOrderCount(int orderCount) { this->orderCount = orderCount; }
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

    // cout << "Order Entries: " << endl;
    // for (auto &orderEntry : ex_app.getOrderEntries()) {
    //     orderEntry.printOrderEntry();
    // }

    ex_app.writeFile();

    return 0;
}