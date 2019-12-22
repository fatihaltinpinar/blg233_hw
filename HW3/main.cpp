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



int main() {

    cout << "Its time to starth" << endl;
    return 0;
}