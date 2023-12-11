#include <iostream>
#include "Heap.h"

class BaseOrderBook{
    public:
        void addOrder(const std::string& clientOrderIdPtr, const std::string& instrumentPtr, int side, double price, int quantity) {
            std::cout << "RoseOrderBook::addOrder" << std::endl;
        }
        void modifyOrder(const std::string& clientOrderIdPtr, const std::string& instrumentPtr, int side, double price, int quantity) {
            std::cout << "RoseOrderBook::modifyOrder" << std::endl;
        }
        void cancelOrder(const std::string& clientOrderIdPtr, const std::string& instrumentPtr, int side, double price, int quantity) {
            std::cout << "RoseOrderBook::cancelOrder" << std::endl;
        }
        void printOrderBook() {
            std::cout << "RoseOrderBook::printOrderBook" << std::endl;
        }

        virtual const std::string& getInstrument() = 0;
    
    private:
        MaxHeap* buySide;
        MinHeap* sellSide;
};


class RoseOrderBook : public BaseOrderBook {
    public:
        const std::string& getInstrument() {
            return instrument;
        }
    private:
        std::string instrument;
};

class LavenderOrderBook : public BaseOrderBook {
    public:
        const std::string& getInstrument() {
            return instrument;
        }
    private:
        std::string instrument;
};

class LotusOrderBook : public BaseOrderBook {
    public:
        const std::string& getInstrument() {
            return instrument;
        }
    private:
        std::string instrument;
};

class TulipOrderBook : public BaseOrderBook {
    public:
        const std::string& getInstrument() {
            return instrument;
        }
    private:
        std::string instrument;
};

class OrchidOrderBook : public BaseOrderBook {
    public:
        const std::string& getInstrument() {
            return instrument;
        }
    private:
        std::string instrument;
};

class OrderBookFactory {
    public:
        static BaseOrderBook* createOrderBook(const std::string& instrument) {
            if (instrument == "ROSE") {
                return new RoseOrderBook();
            } else if (instrument == "LAVENDER") {
                return new LavenderOrderBook();
            } else if (instrument == "LOTUS") {
                return new LotusOrderBook();
            } else if (instrument == "TULIP") {
                return new TulipOrderBook();
            } else if (instrument == "ORCHID") {
                return new OrchidOrderBook();
            } else {
                return nullptr;
            }
        }
};