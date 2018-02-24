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

int maxChunksToSortedII(vector<int>& arr)
{
    int chunk_num = 1, min = arr.at(arr.size() - 1);
    int maxL;
    vector<int> minR;

    minR.assign(arr.size(), 0);

    for (int i = arr.size() - 1; i >= 0; i--) {
        if (arr.at(i) < min) {
            min = arr.at(i);
        }
        minR.at(i) = min;
    }

    maxL = arr.at(0);
    for (int i = 0; i < arr.size() - 1; i++) {

        if (maxL > minR.at(i + 1)) {
            if (maxL < arr.at(i + 1)) {
                maxL = arr.at(i + 1);
            }

            continue;
        }
        else {
            maxL = arr.at(i + 1);
        }
        chunk_num++;
    }

    return chunk_num;
}

void main_max_chunks(void)
{
    int ary1[] = { 1, 0, 2, 3, 4 };
    //int ary2[] = { 4, 2, 1, 3, 2, 4, 4, 4, 3 };
    //int ary2[] = { 2, 1, 3, 2, 4, 4, 4, 0 };
    int ary2[] = { 8, 18, 3, 5, 3, 6, 9, 16, 4, 11, 22, 32, 23, 24, 30, 29, 35, 22, 24, 33 };
    //int ary2[] = { 3, 3 , 4, 5, 6, 8, 9, 11, 16, 18, 22, 22, 23, 24, 24, 29, 30, 32, 33, 35 };

    vector<int> vec1, vec2;

    for (int i = 0; i < sizeof(ary1) / sizeof(ary1[0]); i++) {
        vec1.push_back(ary1[i]);
    }
    for (int i = 0; i < sizeof(ary2) / sizeof(ary2[0]); i++) {
        vec2.push_back(ary2[i]);
    }

    printf("max chunk# : %d\n", maxChunksToSorted(vec1));
    printf("max chunk II# : %d\n", maxChunksToSortedII(vec2));
}
