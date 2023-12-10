#include <string>
#include <vector>

using namespace std;

class Heap {
    public:
        void insert(int value);  
        int pop_top();
        virtual bool is_empty() = 0; 
};

class MaxHeap : public Heap {
    private:
        vector<int> heap;

    public:
        MaxHeap(vector<int> values);
        void insert(int value);
        int pop_top();
        bool is_empty();
};

class MinHeap : public Heap {
    private:
        vector<int> heap;
    
    public:
        MinHeap(vector<int> values);
        void insert(int value);
        int pop_top();
        bool is_empty();
};

