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

  int *filterTokens(vector<string> &tokens) {

    int *result = new int[2]; // result[0] = 1 if valid, 0 if invalid
                              // result[1] = error code

    for (auto &token : tokens) {
      if (token == "") {
        result[0] = 0;
        result[1] = 0;
        return result;
      }
    }

    int side = stoi(tokens[2]);
    int price = stod(tokens[3]);
    int quantity = stoi(tokens[4]);

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

    if (quantity < 10 || quantity > 1000 || quantity % 10 != 0) {
      result[0] = 0;
      result[1] = 3;
      return result;
    }

    result[0] = 1;
    result[1] = 0;
    return result;
  }

  void readFile(vector<vector<string>> &lines) {
    string filename;

    cout << "Enter the name of the file you want to read: ";
    cin >> filename;

    string fullFileName = "./testcases/" + filename + ".csv";
    cout << fullFileName;

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

      int *result = filterTokens(tokens);

      if (result[0] == 0) {
        cout << "Error in line: " << line << endl;
        cout << "Error code: " << result[1] << endl;
        continue;
      } else {
        lines.push_back(tokens);
      }
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

  vector<vector<string>> lines;

  ex_app.readFile(lines);

  for (auto &line : lines) {
    for (auto &token : line) {
      cout << token << " ";
    }
    cout << endl;
  }
}