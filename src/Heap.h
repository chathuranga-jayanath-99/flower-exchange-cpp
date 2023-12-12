#include "OrderBookItem.h"
#include <string>
#include <vector>

using namespace std;

class Heap {
    public:
        virtual void insert(OrderBookItem orderBookItem) = 0;
        virtual OrderBookItem peek_top() = 0;  
        virtual OrderBookItem pop_top() = 0;
        virtual bool is_empty() = 0; 
        virtual void update_top_item_quantity(int newQuantity) = 0;
};

class MaxHeap : public Heap {
    private:
        vector<OrderBookItem> heap;

    public:
        MaxHeap(vector<OrderBookItem> orderBookItems);
        MaxHeap();
        void insert(OrderBookItem orderBookItem);
        OrderBookItem peek_top();
        OrderBookItem pop_top();
        bool is_empty();
        void update_top_item_quantity(int newQuantity);
};

class MinHeap : public Heap {
    private:
        vector<OrderBookItem> heap;
    
    public:
        MinHeap(vector<OrderBookItem> orderBookItems);
        MinHeap();
        void insert(OrderBookItem orderBookItem);
        OrderBookItem peek_top();
        OrderBookItem pop_top();
        bool is_empty();
        void update_top_item_quantity(int newQuantity);
};
