/*  @Author
 *  Student Name:  Fatih Altınpınar
 *  Student ID:    150180707
 *  Date:          22/12/2019
*/

#include <iostream>

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

void BaseStation::add_base_station(struct BaseStation * bs, int parent_id) {
    BaseStation *parent = find_base_station(parent_id);

    BaseStation *tmp = parent->child_bs_head;
    while (tmp->next_sibling != NULL)
        tmp = tmp->next_sibling;
    tmp->next_sibling = bs;
    bs->next_sibling = NULL;
}

int main() {

    cout << "Its time to starth" << endl;
    return 0;
}