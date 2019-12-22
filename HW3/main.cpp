/*  @Author
 *  Student Name:  Fatih Altınpınar
 *  Student ID:    150180707
 *  Date:          22/12/2019
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct MobileHost {
    int id;
    MobileHost *next_sibling;
};

struct BaseStation {
    int id;
    BaseStation *child_bs_head;
    BaseStation *next_sibling;
    MobileHost *child_mh_head;

    BaseStation *find_base_station(int id);

    void add_base_station(BaseStation *bs, int parent_id);

    void add_mobile_host(MobileHost *mh, int parent_id);

    BaseStation *find_path(int target_mh, string *path);
};

BaseStation *BaseStation::find_base_station(int id) {
    if (this->id == id)
        return this;

    if (this->child_bs_head != NULL) {
        BaseStation *traverse = this->child_bs_head;
        while (traverse != NULL) {
            BaseStation *tmp = traverse->find_base_station(id);
            if (tmp != NULL)
                return tmp;
            traverse = traverse->next_sibling;
        }
    }
    return NULL;
}

void BaseStation::add_base_station(BaseStation *bs, int parent_id) {
    BaseStation *parent = find_base_station(parent_id);

    BaseStation *tmp = parent->child_bs_head;
    if (tmp == NULL) {
        parent->child_bs_head = bs;
    } else {
        while (tmp->next_sibling != NULL)
            tmp = tmp->next_sibling;
        tmp->next_sibling = bs;
        bs->next_sibling = NULL;
    }
}

void BaseStation::add_mobile_host(MobileHost *mh, int parent_id) {
    BaseStation *parent = find_base_station(parent_id);

    MobileHost *tmp = parent->child_mh_head;
    if (tmp == NULL){
        parent->child_mh_head = mh;
    } else {
        while (tmp->next_sibling != NULL)
            tmp = tmp->next_sibling;
        tmp->next_sibling = mh;
        mh->next_sibling = NULL;
    }

}

BaseStation* BaseStation::find_path(int target_mh, string *path) {
    cout << this->id << " ";
    if (this->child_mh_head != NULL) {
        MobileHost *traverse = this->child_mh_head;
        while (traverse != NULL) {
            if (traverse->id == target_mh)
                return this;
            traverse = traverse->next_sibling;
        }
    }

    if (this->child_bs_head != NULL) {
        BaseStation *traverse = this->child_bs_head;
        while (traverse != NULL) {
            BaseStation *tmp = traverse->find_path(target_mh, path);
            if (tmp != NULL) {
                string text = " " + to_string(tmp->id);
                path->insert(0, text);
                return this;
            }
            traverse = traverse->next_sibling;
        }
    }
    return NULL;
}


int main(int argc, char *argv[]) {
    fstream messages_file;
    fstream network_file;
    if (argc == 3) {
        network_file.open(argv[1]);
        messages_file.open(argv[2]);

        if (!(network_file.is_open() && messages_file.is_open())) {
            cerr << "One of the files cannot be opened!" << endl;
            return 1;
        }

    } else {
        cerr << "Wrong arguments while running the program" << endl;
        return 1;
    }

    BaseStation root = {0, NULL, NULL, NULL};
    string node_type;
    int id, parent_id;
    while (!network_file.eof()) {
        network_file >> node_type >> id >> parent_id;
        if (node_type == "BS") {
            BaseStation *tmp = new BaseStation{id, NULL, NULL, NULL};
            root.add_base_station(tmp, parent_id);
        } else if (node_type == "MH") {
            MobileHost *tmp = new MobileHost{id, NULL};
            root.add_mobile_host(tmp, parent_id);
        } else {
            cerr << "Something went wrong" << endl;
        }
        while (network_file.peek() == '\n' || network_file.peek() == '\r')
            network_file.get();
    }
    string path;
    cout << "Traversing:";
    root.find_path(18, &path);
    path.insert(0, "To:0");
    cout << endl << path << " mh_" << 18 << endl;
    return 0;
}