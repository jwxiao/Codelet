#include <stdio.h>
#include <vector>
#include <list>
#include <string>

using namespace std;

class sr {
public:
    int val;
    int adr;
    sr() { val = 7; adr = 8; };
};

int max_set_bit_distance(int a)
{
    int i, max = -1, s = -1;

    for (i = 0; a; i++) {
        if (a & 1) {
            if (s > -1) {
                int d = i - s - 1;

                if (d > max) {
                    max = d;
                }
            }
            s = i;
        }
        a >>= 1;
    }

    return max;
}


int main(void)
{
#if 1
    vector<int> vars;

    vars.push_back(0);
    vars.push_back(127);
    vars.push_back(128);
    vars.push_back(132);
    vars.push_back(395188);
    vars.push_back(1972);
    vars.push_back(3664);

    for (int i = 0; i < vars.size(); i++) {
        printf("%d \t distance: %d\n", vars.at(i), max_set_bit_distance(vars.at(i)));
    }
#endif
#if 1
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
#endif
}

