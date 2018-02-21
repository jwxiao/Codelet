#include "common.h"

using namespace std;

int maxChunksToSorted(vector<int>& arr)
{
    int chunk_num = 0;
    int i = 0;

    while (i < arr.size()) {
        int last_i = arr.at(i);
        
        while (i <= last_i) {
            if (arr.at(i) > last_i) {
                last_i = arr.at(i);
            }
            i++;
        }
        chunk_num++;
    }

    return chunk_num;
}

void main_max_chunks(void)
{
    int ary1[] = {1, 0, 2, 3, 4};

    vector<int> ary;

    for (int i = 0; i < sizeof(ary1) / sizeof(ary1[0]); i++) {
        ary.push_back(ary1[i]);
    }

    printf("max chunk# : %d\n", maxChunksToSorted(ary));
}
