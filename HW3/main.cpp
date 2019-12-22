/*  @Author
 *  Student Name:  Fatih Altınpınar
 *  Student ID:    150180707
 *  Date:          22/12/2019
 *  Used:          C++11
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct MobileHost {             // Struct definition of MobileHost
    int id;
    MobileHost *next_sibling;
};

struct BaseStation {            // Struct definition of BaseStation
    int id;
    BaseStation *child_bs_head;
    BaseStation *next_sibling;
    MobileHost *child_mh_head;

    // This function finds the BaseStation with the given id value in the tree
    // in a recursive manner
    BaseStation *find_base_station(int id);

    // This function adds a BaseStation to tree by connecting it to BaseStation with given parent_id
    void add_base_station(BaseStation *bs, int parent_id);

    // This function adds a MobileHost to tree by connecting it to BaseStation with given parent_id
    void add_mobile_host(MobileHost *mh, int parent_id);

    // This recursive function finds target MobileHost to deliver the message
    // It also returns shortest path to that MobileHost
    // It also prints every BaseStation's id while iterating over them.
    BaseStation *find_path(int target_mh, string *path);

    // Deletes whole (sub)tree.
    void delete_tree();
};

// This function finds the BaseStation with the given id value in the tree
// in a recursive manner
BaseStation *BaseStation::find_base_station(int id) {
    if (this->id == id)                 // Exit condition if current BaseStation's id is what we are
        return this;                    // looking for return address of it

    if (this->child_bs_head != NULL) {                  // If BaseStation has any BS child
        BaseStation *traverse = this->child_bs_head;
        while (traverse != NULL) {
            BaseStation *tmp = traverse->find_base_station(id); // Call find_base_station on every one of them
            if (tmp != NULL)        // If they return a pointer which is not equal to NULL,
                return tmp;         // it means that subtree contains the BaseStation with the given id.
                                    // which means this subtree contains the same BaseStation. Return that BS's address.
            traverse = traverse->next_sibling;  // If target BS is not found, search it under sibling BS
        }
    }
    return NULL;            // If nothing is found under this subtree return NULL
}
// This function adds a BaseStation to tree by connecting it to BaseStation with given parent_id
void BaseStation::add_base_station(BaseStation *bs, int parent_id) {
    BaseStation *parent = find_base_station(parent_id); // Get the address of the BS which'll be the parent

    BaseStation *tmp = parent->child_bs_head;
    if (tmp == NULL) {                      // If parent BS has no child BS, add new BS as first child
        parent->child_bs_head = bs;
    } else {                                // If parent BS has children , add new BS at the end of the
        while (tmp->next_sibling != NULL)   // linked list.
            tmp = tmp->next_sibling;
        tmp->next_sibling = bs;
        bs->next_sibling = NULL;
    }
}

// This function adds a MobileHost to tree by connecting it to BaseStation with given parent_id
void BaseStation::add_mobile_host(MobileHost *mh, int parent_id) {
    BaseStation *parent = find_base_station(parent_id); // Get the address of the BS which'll be the parent

    MobileHost *tmp = parent->child_mh_head;
    if (tmp == NULL){                   // If parent BS has no MH connected to it, add new MH as first child
        parent->child_mh_head = mh;
    } else {
        while (tmp->next_sibling != NULL) // If parent BS has MHs connected to it, add new MH at the end of
            tmp = tmp->next_sibling;      // the linked list.
        tmp->next_sibling = mh;
        mh->next_sibling = NULL;
    }

}

// This recursive function finds target MobileHost to deliver the message
// It also returns shortest path to that MobileHost
// It also prints every BaseStation's id while iterating over them.
BaseStation* BaseStation::find_path(int target_mh, string *path) {
    cout << this->id << " ";                    // Printing current BS to completed traversing output
    if (this->child_mh_head != NULL) {          // First checking MHs connected to this BS
        MobileHost *traverse = this->child_mh_head;
        while (traverse != NULL) {
            if (traverse->id == target_mh)
                return this;                    // If target MH is found return it.
            traverse = traverse->next_sibling;
        }
    }
                                                // If this BS does not contain target
    if (this->child_bs_head != NULL) {          // And if it has BSs connected to it
        BaseStation *traverse = this->child_bs_head;
        while (traverse != NULL) {
            BaseStation *tmp = traverse->find_path(target_mh, path);    // Call find_path for every subtree
            if (tmp != NULL) {          // If it returns a value not equal to NULL, means it has the target MH
                string text = " " + to_string(tmp->id); // Add subtree's root BS's id to path
                path->insert(0, text);
                return this;                  // Return current BS, so it might be added to path in callee
            }
            traverse = traverse->next_sibling;
        }
    }
    return NULL;                  // If this subtree does not contain target MH, return NULL
}

// Deletes whole (sub)tree
void BaseStation::delete_tree() {
    while (this->child_bs_head != NULL) {               // Go over children and delete all of them
        BaseStation *tmp = this->child_bs_head->next_sibling;
        this->child_bs_head->delete_tree();
        this->child_bs_head = tmp;
    }

    while (this->child_mh_head != NULL) {               // Go ever sub BSs and call delete_tree on all of them
        MobileHost *tmp = this->child_mh_head->next_sibling;
        delete this->child_mh_head;
        this->child_mh_head = tmp;
    }

    delete this; // Then delete current BS
}

void send_message(BaseStation* root, const string * message, int target_id){
    string path;    // String to hold shortest path to MH
    cout << "Traversing:";
    BaseStation *tmp = root->find_path(target_id, &path);   // Find path will print out every BS
                                                            // it traverses while searching
    if (tmp != NULL) {
        path.insert(0, "To:0"); // Add To:0 to beginning of the path
                                        // since it'll always start from central station
        cout << endl << "Message:" << *message << " " << path << " mh_" << target_id << endl;
    } else {    // If MH does not exist in the network
        cout << endl << "Can not be reached the mobile host mh_"<< target_id << " at the moment" << endl;
    }
}


int main(int argc, char *argv[]) {
    fstream messages_file;
    fstream network_file;
    if (argc == 3) {    // If three are 3 command line arguments run as intended.
        network_file.open(argv[1]);         // First argument will be network_file name
        messages_file.open(argv[2]);        // Second argument will be messages_file name
                                               // Open both files

        if (!(network_file.is_open() && messages_file.is_open())) {
            // If files cannot be opened for some reason return error
            cerr << "One of the files cannot be opened!" << endl;
            return 1;
        }

    } else {    // Otherwise return an error
        cerr << "Wrong command line arguments while running the program" << endl;
        return 1;
    }

    // Create a root for the tree
    auto *root = new BaseStation{0, NULL, NULL, NULL};

    // Reading network.txt
    string node_type;
    int id, parent_id;
    while (!network_file.eof()) {
        network_file >> node_type >> id >> parent_id;
        if (node_type == "BS") {        // If line contains a BS, add a BS to network
            auto *tmp = new BaseStation{id, NULL, NULL, NULL};
            root->add_base_station(tmp, parent_id);
        } else if (node_type == "MH") { // If line contains a MH, add a MH to network
            auto *tmp = new MobileHost{id, NULL};
            root->add_mobile_host(tmp, parent_id);
        } else {
            cerr << "Something went wrong" << endl;
        }
        // For fixing issues cause by newline and carriage return usages on varying operating systems
        while (network_file.peek() == '\n' || network_file.peek() == '\r')
            network_file.get();
    }

    // Send messages one by one from the messages.txt
    while (!messages_file.eof()) {
        string message;
        int target_id;
        getline(messages_file, message, '>');
        messages_file >> target_id;

        send_message(root, &message, target_id);

        // For fixing issues cause by newline and carriage return usages on varying operating systems
        while (messages_file.peek() == '\n' || messages_file.peek() == '\r')
            messages_file.get();
    }
    root->delete_tree();    // Delete whole tree to prevent memory leak.
    return 0;
}