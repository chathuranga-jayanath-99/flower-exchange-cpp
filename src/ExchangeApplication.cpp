#include <iostream>
#include <string>

class ExchangeApplication {
    private: 
        static ExchangeApplication& get() { return ex_app;}
    public: 
        ExchangeApplication() {};
        ~ExchangeApplication() {};

        static ExchangeApplication ex_app;        
}

ExchangeApplication ExchangeApplication::ex_app;