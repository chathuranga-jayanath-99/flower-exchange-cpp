#include <iostream>
#include <string>

class Order {
    private: 
        std::string clientOrderId;
        std::string instrument;
        int side;
        double price;
        int quantity;

    public: 
        Order(const std::string& clientOrderIdPtr, const std::string& instrumentPtr, int side, double price, int quantity) {
            clientOrderId = *clientOrderIdPtr;
            instrument = *instrumentPtr;
            side = side;
            price = price;
            quantity = quantity;
        }   
        
}