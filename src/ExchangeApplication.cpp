#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream stream(str);
    std::string token;
    while (std::getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

class ExchangeApplication {
    public: 
        static ExchangeApplication& get() { return ex_app;}

        int readFile(){
            std::string filename;

            std::cout << "Enter the name of the file you want to read: ";
            std::cin >> filename;

            std::ifstream file(filename + ".csv");

            if (!file.is_open()) {
                std::cerr << "Error opening file.\n";
                return 1;
            }

            std::string line;
            while (std::getline(file, line)) {

                std::vector<std::string> tokens = split(line, ',');

                for (const auto& token : tokens) {
                    std::cout << token << " ";
                }
                std::cout << '\n';
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