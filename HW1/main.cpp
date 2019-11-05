/*  @Author

Student Name:   Fatih Altınpınar

Student ID:     150180707

Date:           13.10.2019

*/


#include <iostream>
#include <fstream>

using namespace std;

struct Node {
	int size;
	int quantity;
	Node *next;
};

struct Stock {
	Node *head;
	void create();
	void add_stock(int);
	void sell(int);
	void current_stock();
	void clear();
};

void Stock::create() {
	head = NULL;					//Empty linked list
}

void Stock::add_stock(int size) {
	if (!head) {					//If there is nothing in list, create new node with given shoe size
		head = new Node;
		head->size = size;
		head->quantity = 1;
		head->next = NULL;
	}
	else {
		if (size < head->size) {	//If given shoe size is smaller than first shoe in the list then create new node with given shoe size
			Node *tmp = head;
			head = new Node;		//This new node will be the first of the list.
			head->size = size;
			head->quantity = 1;
			head->next = tmp;
		}
		else {						//If not iterate over every element
			Node *current = head;
			Node *next = current->next;
			while (current) {		//While current != NULL
				if (size == current->size) {		//Check if current shoe is the same as wanted if yes increment quantity of the node
					current->quantity++;
					return;
				}
				else if (!next || size < next->size) {			//Add a new node if
					Node *tmp = current->next;					//!next -> Next node does not exists
					current->next = new Node;					// OR
					current->next->size = size;					//Given shoe size is smaller than next node's shoe size. Which means
					current->next->quantity = 1;				//a new node must be created in between current and next.
					current->next->next = tmp;
					return;
				}
				else {
					current = next;								//otherwise iterate to next current and next pair
					next = current->next;						//This will not cause any error since we check existence of next in upper if statement
				}
			}
		}
	}
}

void Stock::sell(int size) {
	if (!head) {
		cout << "NO_STOCK" << endl;								//If there is nothing in stock print NO_STOCK
	}else if (size < head->size) {
		cout << "NO_STOCK" << endl;								//Since list is in ascending order if given shoe is smaller than first item, it
	}															//does not exists in the list
	else if (size == head->size) {						
		if (head->quantity == 1) {								//If shoe that needs to be selled is in this node and quantity is 1 then remove node
			Node *tmp = head->next;
			delete head;										
			head = tmp;											//Set beginning of the list to next one
		}
		else
			head->quantity--;									//If quantity is bigger than 1 decrease it.
	}
	else {
		Node *tail = head;
		Node *current = tail->next;								//Skip to second element since we already checked first element
		while (current) {										//Iterate over every node
			if (current->size == size) {
				if (current->quantity == 1) {					//Remove node and connect tail to current->next if node's quantity is one
					tail->next = current->next;
					delete current;
					return;
				}
				else {
					current->quantity--;
					return;
				}
			}
			tail = current;
			current = current->next;
		}
		if (!current) {
			cout << "NO_STOCK" << endl;							//If iterated over whole stack and nothing is found, (given shoe size is greater than all shoes' available) print NO_STOCK
		}
	}

}

void Stock::current_stock() {
	Node *current = head;
	/*if (!current) {
		cout << "STOCK_EMPTY" << endl;				//There wasn't a specification about printing stack when there is nothing thus I removed it.
		return;
	}*/
	while (current) {								//Iterate over every item and print their size and quantity as "<size>:<quantity>"
		cout << current->size << ":" << current->quantity << endl;
		current = current->next;
	}
}

void Stock::clear() {
	while (head) {
		Node *tmp = head->next;		// Store next node
		delete head;				// Delete head
		head = tmp;					// Set next node as head
	}								// Repeat
}


int main(int argc, char *argv[]) {

	Stock myStock;
	myStock.create();				//Create stack				

	fstream file;					//Using fstream for reading from files

	if (argc == 1)
		file.open("input.txt");		//If the program is runned without any parameters it looks for "input.txt"
	else
		file.open(argv[1]);			//Otherwise it reads inputs from given file name

	if (file.is_open()) {			//If file can be read
		int input;
		while (!file.eof()) {		//Repeat until end of the file
			file >> input;			//Take next integer
			if (input == 0)						
				myStock.current_stock();			//If input is 0 then print whole stack
			else if (input < 0)
				myStock.sell(-input);				//If input is negative sell that particular shoe with the size given as (input * -1)
			else
				myStock.add_stock(input);			//If input is positive add stock with size = input
			while (file.peek() == '\n' || file.peek() == '\r')
				file.get();							//Skip \n and \r. To find
		}
	}
	else {
		if (argc == 1)								//If input.txt cannot be found print error messages.
			cout << "File input.txt does not exist or cannot be opened." << endl;
		else
			cout << "File " << argv[1] << " does not exist or cannot be opened." << endl;
	}
	myStock.clear();

	return 0;
}