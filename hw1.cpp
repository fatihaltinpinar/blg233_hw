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
	head = NULL;
}

void Stock::add_stock(int size) {
	if (!head) {
		head = new Node;
		head->size = size;
		head->quantity = 1;
		head->next = NULL;
	}
	else {
		if (size < head->size) {
			Node *tmp = head;
			head = new Node;
			head->size = size;
			head->quantity = 1;
			head->next = tmp;
		}
		else {
			Node *current = head;
			Node *next = current->next;
			while (current) {
				if (size == current->size) {
					current->quantity++;
					return;
				}
				else if (!next || size < next->size) {
					Node *tmp = current->next;
					current->next = new Node;
					current->next->size = size;
					current->next->quantity = 1;
					current->next->next = tmp;
					return;
				}
				else {
					current = next;
					next = current->next;
				}
			}
		}
	}
}

void Stock::sell(int size) {
	if (!head) {
		cout << "NO_STOCK" << endl;
		return;
	}
	Node *current = head;
	Node *next = current->next;
	if (size < current->size) {
		cout << "NO_STOCK" << endl;
	}
	else if (size == current->size) {
		if (current->quantity == 1) {
			head = next;
			delete current;
		}
		else
			current->quantity--;
	}
	else {
		while (next) {
			if (next->size == size) {
				if (next->quantity == 1) {
					Node *tmp = next;
					current->next = next->next;
					delete next;
					return;
				}
				else {
					next->quantity--;
					return;
				}
			}
			current = next;
			next = current->next;
		}
		if (!next) {
			cout << "NO_STOCK" << endl;
		}
	}

}

void Stock::current_stock() {
	Node *current = head;
	/*if (!current) {
		cout << "STOCK_EMPTY" << endl;				/There wasn't a specification about printing stack when there is nothing thus I removed it.
		return;
	}*/
	while (current) {
		cout << current->size << ":" << current->quantity << endl;
		current = current->next;
	}
}

void Stock::clear() {
	while (head) {
		Node *tmp = head->next;
		delete head;
		head = tmp;
	}
}


int main(int argc, char *argv[]) {

	Stock myStock;
	myStock.create();

	fstream file;

	if (argc == 1)
		file.open("input.txt");
	else
		file.open(argv[1]);

	if (file.is_open()) {
		int input;
		while (!file.eof()) {
			file >> input;
			if (input == 0)
				myStock.current_stock();
			else if (input < 0)
				myStock.sell(-input);
			else
				myStock.add_stock(input);
			while (file.peek() == '\n' || file.peek() == '\r')
				file.get();
		}
	}
	else {
		if (argc == 1)
			cout << "File input.txt does not exist or cannot be opened." << endl;
		else
			cout << "File " << argv[1] << " does not exist or cannot be opened." << endl;
	}
	myStock.clear();

	return 0;
}