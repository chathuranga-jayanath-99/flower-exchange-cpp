#include "Order.h"
#include <fstream>
#include <iostream>
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

  int readFile() {
    string filename;

    cout << "Enter the name of the file you want to read: ";
    cin >> filename;

    string fullFileName = "./testcases/" + filename + ".csv";
    cout << fullFileName;

    ifstream file(fullFileName);

    if (!file.is_open()) {
      cerr << "Error opening file.\n";
      return 1;
    }

    string header;
    getline(file, header);

    string line;
    while (getline(file, line)) {

      vector<string> tokens = split(line, ',');

      Order newOrder(tokens[0], tokens[1], stoi(tokens[2]), stod(tokens[3]),
                     stoi(tokens[4]));

      newOrder.printOrder();

      cout << '\n';
    }

    file.close();
    return 0;
  }

private:
  ExchangeApplication(){};
  ~ExchangeApplication(){};

  static ExchangeApplication ex_app;
};

ExchangeApplication ExchangeApplication::ex_app;

int main() {
  ExchangeApplication &ex_app = ExchangeApplication::get();
  ex_app.readFile();
}