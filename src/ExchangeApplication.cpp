#include "Order.h"
#include "OrderEntry.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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
    void readFile(vector<Order> &validOrders, vector<OrderEntry> &orderEntries,
                  map<string, string> &orderIDMap, int &orderCount) {
        string filename;

        cout << "Enter the name of the file you want to read: ";
        cin >> filename;

        string fullFileName = "./testcases/" + filename + ".csv";

        ifstream file(fullFileName);

        if (!file.is_open()) {
            cerr << "Error opening file.\n";
            return;
        }

        string header;
        getline(file, header);

        string line;
        while (getline(file, line)) {

            vector<string> tokens = split(line, ',');

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

        file.close();
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

    ex_app.readFile(validOrders, orderEntries, orderIDMap, orderCount);

    for (auto &order : validOrders) {
        order.printOrder();
    }

    ex_app.writeFile(orderEntries);
}