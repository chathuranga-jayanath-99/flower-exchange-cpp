#include "Order.h"
#include "OrderEntry.h"
#include <arpa/inet.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
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

void publishVector(const std::vector<string> &data, int clientSocket) {
    // Serialize vector into a string
    std::string serializedData;
    for (const auto &element : data) {
        serializedData += element + ',';
    }
    serializedData += MESSAGE_DELIMITER;

    // Send serialized vector to the client
    send(clientSocket, serializedData.c_str(), serializedData.size(), 0);
    std::cout << "Vector published to the socket.\n";
}

class Trader {

  public:
    static Trader &get() { return trader_app; }

    // This function is used to read the file
    void readFile(vector<vector<string>> &lines) {
        string filename;

        cout << "Enter the name of the file you want to read: ";
        cin >> filename;

        string fullFileName = "./testcases/" + filename + ".csv";
        // string fullFileName = "./testcases/example7.csv";

        ifstream file(fullFileName);

        if (!file.is_open()) {
            cerr << "Error opening file.\n";
            return;
        }

        string header;
        getline(file, header);

        string line;
        while (getline(file, line)) {

            cout << line << endl;

            if (!line.empty() && line[line.length() - 1] == '\r') {
                line.erase(line.length() - 1);
            }

            vector<string> tokens = split(line, ',');
            lines.push_back(tokens);
        }

        file.close();
        return;
    }

  private:
    Trader(){};
    ~Trader(){};

    static Trader trader_app;
};

Trader Trader::trader_app;

int main() {
    Trader &trader_app = Trader::get();
    vector<vector<string>> lines;

    trader_app.readFile(lines);

    // for (auto &line : lines) {
    //     for (auto &token : line) {
    //         cout << token << endl;
    //     }
    // }

    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    // Specify the server address and port to connect to
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr =
        inet_addr("127.0.0.1");         // Loopback address (localhost)
    serverAddr.sin_port = htons(12345); // Use the same port as the server

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr,
                sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to server" << std::endl;
        close(clientSocket);
        return -1;
    }

    std::cout << "Connected to the server" << std::endl;

    // Send data to the server
    for (auto &line : lines) {
        // sleep(1);
        publishVector(line, clientSocket);
    }

    // Clean up
    close(clientSocket);
}
