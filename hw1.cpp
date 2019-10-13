#include <iostream>

using namespace std;

struct Node{
    int size;
    int quant;
    Node *next;
};

struct Stock{
    Node *head;
    void create();
    void add_stock();
    void sell(int);
    void current_stock();
    void clear();
};

int main(){


    return 0;
}