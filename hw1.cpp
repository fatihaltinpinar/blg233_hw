/*  @Author

Student Name:   Fatih Altınpınar

Student ID:     150180707

Date:           13.10.2019

*/


#include <iostream>
#include <fstream>

using namespace std;

struct Node{
    int size;
    int quant;
    Node *next;
};

struct Stock{
    Node *head;
    void create();
    void add_stock(int);
    void sell(int);
    void current_stock();
    void clear();
};

void Stock::create(){
    head = NULL;
}

void Stock::add_stock(int size){
    if(!head){
        head = new Node;
        head->size = size;
        head->quant = 1;
        head->next = NULL;
    }else{
        if(size < head->size){
            Node *tmp = head;
            head = new Node;
            head->size = size;
            head->quant = 1;
            head->next = tmp;
        }else{
            Node *current = head;
            Node *next = current->next;
            while(current){
                if(size == current->size){
                    current->quant++;
                }else if(size < next->size){
                    current->next = new Node;
                    current->next->size = size;
                    current->next->quant = 1;
                    current->next->next = next;
                    return;
                }else{
                    current = next;
                    next = current->next;
                }
            }
        } 

    }

}

void Stock::sell(int size){
    Node *current = head;   
    while(!(head->next)){
        if(!(current->next))
        if(current->next->size == size){
            
        }

    }

}

void Stock::current_stock(){
    Node *current = head;
    if(!current){
        cout << "NO_STOCK" << endl;    
        return;
    }
    while(current){
        cout << current->size << ":" << current->quant << endl;    
        current = current->next;
    }
}

void Stock::clear(){
    Node *current = head;
    Node *next = current->next;
    while(next){
        delete current;
        current = next;
        next = current->next; 
    }
    delete current;
    head = NULL;
}


int main(){


    return 0;
}