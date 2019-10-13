/*  @Author

Student Name:   Fatih Altınpınar

Student ID:     150180707

Date:           13.10.2019

*/


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