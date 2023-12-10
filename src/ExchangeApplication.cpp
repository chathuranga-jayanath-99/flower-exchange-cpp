#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<string> split(const string& str, char delimiter) {
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
        static ExchangeApplication& get() { return ex_app;}

        int readFile(){
            string filename;

            cout << "Enter the name of the file you want to read: ";
            cin >> filename;

            ifstream file(filename + ".csv");

            if (!file.is_open()) {
                cerr << "Error opening file.\n";
                return 1;
            }

            string line;
            while (getline(file, line)) {

                vector<string> tokens = split(line, ',');

                for (const auto& token : tokens) {
                    cout << token << " ";
                }
                cout << '\n';
            }

            file.close();
            return 0;
        }

    private: 
        ExchangeApplication() {};
        ~ExchangeApplication() {};

        static ExchangeApplication ex_app;   


};

ExchangeApplication ExchangeApplication::ex_app;

int main() {
    ExchangeApplication& ex_app = ExchangeApplication::get();
    ex_app.readFile();
}