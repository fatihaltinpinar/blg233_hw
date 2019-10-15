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
    int quantity;
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
        head->quantity = 1;
        head->next = NULL;
    }else{
        if(size < head->size){
            Node *tmp = head;
            head = new Node;
            head->size = size;
            head->quantity = 1;
            head->next = tmp;
        }else{
            Node *current = head;
            Node *next = current->next;
            while(current){
                if(size == current->size){
                    current->quantity++;
                }else if(size < next->size){
                    current->next = new Node;
                    current->next->size = size;
                    current->next->quantity = 1;
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
    Node *next = current->next;
    if(size < current->size){
        cout << "NO_STOCK" << endl;
    }else if{size == current->size}{
        if(current->quantity == 1){
            head = next;
            delete current;
        }else
            current->quantity--;
    }else{
        while(next){
            if(next->size == size){
                if(next->qauntity == 1){
                    Node *tmp = next;
                    current->next = next->next;
                    delete next;
                    return;
                }else{
                    next->quantity--;
                    return;
                }
            }
            current = next;
            next = current->next;
        }
        if(!next){
            cout << "NO_STOCK" << endl;
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
        cout << current->size << ":" << current->quantity << endl;    
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