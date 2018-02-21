#include "common.h"

using namespace std;

extern void main_is_prime23(void);
extern void main_count_set_bits(void);
extern void max_set_bit_distance(void);
extern void main_partition_labels(void);
extern void main_order_of_largest_plus_sign(void);
extern void main_couple_hands(void);
extern void main_reorganizeString(void);

int main(void)
{
    main_reorganizeString();
    //main_couple_hands();
    //main_order_of_largest_plus_sign();
    //main_partition_labels();
    
    return 0;
}












#if 0
class sr {
public:
    int val;
    int adr;
    sr() { val = 7; adr = 8; };
};

int main(void)
{

    list<sr> lst1;
    vector<int> v1;
    string str;
    sr obj1;
    sr obj2;
    sr tar;

    obj2.val = 55;
    obj2.adr = 66;

    lst1.push_back(obj1);
    lst1.push_back(obj2);

    tar = lst1.front();
    printf("tar @1:%d_%d\n",  tar.val, tar.adr);

    lst1.pop_front();

    tar = *(&(lst1.front()));

    printf("lst1 @2:%d_%d\n", lst1.front().val, lst1.front().adr);
    printf("tar @2:%d_%d\n", tar.val, tar.adr);

    printf("list1 @2:%p_%p\n", &tar, &(lst1.front()));

    return 0;

    printf("v1 size:%d cap:%d\n", v1.size(), v1.capacity());
    v1.resize(5);
    printf("v1 size:%d cap:%d\n", v1.size(), v1.capacity());
    v1.resize(3);
    printf("v1 size:%d cap:%d\n", v1.size(), v1.capacity());
    for (int i = 0; i < v1.size(); i++) {
        printf("v1 at[%d]=%d\n", i, v1.at(i));
    }

    v1.assign(8, 123);
    printf("v1 size:%d cap:%d\n", v1.size(), v1.capacity());
    for (int i = 0; i < v1.size(); i++) {
        printf("v1 at[%d]=%d\n", i, v1.at(i));
    }

    v1.assign(6, 78);
    printf("v1 size:%d cap:%d\n", v1.size(), v1.capacity());
    for (int i = 0; i < v1.size(); i++) {
        printf("v1 at[%d]=%d\n", i, v1.at(i));
    }

    return 0;
}

#endif