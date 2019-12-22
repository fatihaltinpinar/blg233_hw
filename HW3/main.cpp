/*  @Author
 *  Student Name:  Fatih Altınpınar
 *  Student ID:    150180707
 *  Date:          22/12/2019
*/

#include <iostream>
#include <string>

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

    BaseStation* find_base_station(int id);
    void add_base_station(BaseStation * bs, int parent_id);
    void add_mobile_host(MobileHost * mh, int parent_id);
    int send_message(int target_mh, string *path)
};

BaseStation* BaseStation::find_base_station(int id) {
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

void BaseStation::add_mobile_host(struct MobileHost * mh, int parent_id) {
    BaseStation *parent = find_base_station(parent_id);

    MobileHost *tmp = parent->child_mh_head;
    while (tmp->next_sibling != NULL)
        tmp = tmp->next_sibling;
    tmp->next_sibling = mh;
    mh->next_sibling = NULL;
}

int BaseStation::send_message(int target_mh, std::string *path) {
    cout << this->id << " ";
    if (this->child_mh_head != NULL){
        MobileHost *traverse = this->child_mh_head;
        while (traverse != NULL){
            if (traverse->id == target_mh)
                return this->id;
            traverse = traverse->next_sibling;
        }
    }

    if (this->child_bs_head != NULL){
        BaseStation *traverse = this->child_bs_head;
        while (traverse != NULL){
            int tmp = traverse->send_message(target_mh, path);
            if (tmp != NULL){
                string text = " " + to_string(tmp);
                path->insert(0, text);
                return this->id;
            }
            traverse = traverse->next_sibling;
        }
    }
    return NULL;
}


int main() {

    cout << "Its time to starth" << endl;
    return 0;
}