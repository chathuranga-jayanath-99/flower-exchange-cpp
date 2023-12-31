#include "Order.h"
#include "OrderEntry.h"
#include <arpa/inet.h>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
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

class Trader {

  public:
    static Trader &get() { return trader_app; }

    // This function is used to read the file
    void readFile(vector<string> &lines) {
        string filename;

        cout << "Enter the name of the file you want to read: ";
        cin >> filename;

        string fullFileName = "./inputs/" + filename + ".csv";
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

            if (!line.empty() && line[line.length() - 1] == '\r') {
                line.erase(line.length() - 1);
            }

            lines.push_back(line);
        }

        file.close();
        return;
    }

    void publishVector(string &data, int clientSocket) {
        // Add delimiter to the end of the string
        data += MESSAGE_DELIMITER;

        // Send serialized string to the client
        send(clientSocket, data.c_str(), data.size(), 0);
        cout << "Vector published to the socket.\n";
    }

  private:
    Trader(){};
    ~Trader(){};

    static Trader trader_app;
};

Trader Trader::trader_app;

int main() {
    Trader &trader_app = Trader::get();
    vector<string> lines;

    trader_app.readFile(lines);

    // for (auto &line : lines) {
    //     for (auto &token : line) {
    //         cout << token << endl;
    //     }
    // }

    // Create a socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        cerr << "Error creating socket" << endl;
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
        cerr << "Error connecting to server" << endl;
        close(clientSocket);
        return -1;
    }

    cout << "Connected to the server" << endl;

    int counter = 0;
    for (auto &line : lines) {
        // sleep(1);
        if (counter++ == 1000) {
            this_thread::sleep_for(chrono::milliseconds(100));
            counter = 0;
        }
        trader_app.publishVector(line, clientSocket);
    }

    close(clientSocket);
}
