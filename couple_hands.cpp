#include "common.h"

using namespace std;

int couple_hands(vector<int>& row)
{
#define GET_COUPLE(_a)    (_a ^ 1)

    vector<int> position;
    vector<int> matched;
    int first_unmatched = 0, total_swap = 0, total_couple = 0;

    position.resize(row.size());
    matched.assign(row.size(), 0);

    for (int i = 0; i < row.size(); i++) {
        position.at(row.at(i)) = i;
    }

    first_unmatched = 0;
    while ((total_couple < (row.size() / 2)) && (first_unmatched < row.size())) {
        int updated_unmatched = (first_unmatched | 1) + 1;
        int cur_pos = GET_COUPLE(position.at(GET_COUPLE(row.at(first_unmatched))));

        while ((cur_pos != first_unmatched) && (total_swap < row.size())) {

            matched.at(cur_pos) = 1;
            matched.at(GET_COUPLE(cur_pos)) = 1;
            total_couple++;

            while (updated_unmatched < matched.size()) {
                if (matched.at(updated_unmatched)) {
                    updated_unmatched = (updated_unmatched | 1) + 1;
                }
                else {
                    break;
                }
            }
            
            cur_pos = GET_COUPLE(position.at(GET_COUPLE(row.at(cur_pos))));
            total_swap++;
        }

        if (cur_pos == first_unmatched) {
            matched.at(cur_pos) = 1;
            matched.at(GET_COUPLE(cur_pos)) = 1;
            total_couple++;
        }
        else {
            printf("fatal error, nothing done: cur_pos=%d fist_unmatched=%d total_couple=%d\n",
                cur_pos, first_unmatched, total_couple);
        }

        first_unmatched = updated_unmatched;
    }

    return total_swap;
}

void main_couple_hands(void)
{
    //const int order[] = { 1, 0 };
    //const int order[] = { 1, 3, 0, 2 };
    //const int order[] = { 3, 0, 5, 2, 1, 4 };
    //const int order[] = { 3, 0, 5, 2, 1, 4, 6, 7};
    //const int order[] = { 3, 0, 5, 2, 1, 4, 6, 9, 8, 7 };
    //const int order[] = { 4, 6, 1, 3, 5, 7, 12, 13, 15, 11, 0, 10, 2, 8, 9, 14 };
    const int order[] = { 28, 4, 37, 54, 35, 41, 43, 42, 45, 38, 19, 51, 49, 17, 47, 25, 12,
        53, 57, 20, 2, 1, 9, 27, 31, 55, 32, 48, 59, 15, 14, 8, 3, 7, 58, 23, 10, 52, 22, 30,
        6, 21, 24, 16, 46, 5, 33, 56, 18, 50, 39, 34, 29, 36, 26, 40, 44, 0, 11, 13};

    vector<int> people;

    for (int i = 0; i < sizeof(order) / sizeof(order[0]); i++) {
        people.push_back(order[i]);
    }
    printf("total swaps: %d\n", couple_hands(people));
}
