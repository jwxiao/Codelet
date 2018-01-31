#include "common.h"

using namespace std;

int count_swap_recursive(int *row, int start, int num, int *loc)
{
#define GET_COUPLE(_a)    (_a ^ 1)
    int swap0 = 0, swap1 = 0, temp = 0, couple_loc = 0, min_swap = 0;

    if (start >= num) {
        //printf("terminate recursion: %d\n", num);
        return 0;
    }

    if (row[start] == GET_COUPLE(row[start + 1])) {
        return count_swap_recursive(row, start + 2, num, loc);
    }

    couple_loc = loc[GET_COUPLE(row[start])];

    temp = row[start + 1];
    row[start + 1] = row[couple_loc];
    row[couple_loc] = temp;

    loc[row[start + 1]] = start + 1;
    loc[row[couple_loc]] = couple_loc;

    swap0 = count_swap_recursive(row, start + 2, num, loc);

    temp = row[start + 1];
    row[start + 1] = row[couple_loc];
    row[couple_loc] = temp;

    loc[row[start + 1]] = start + 1;
    loc[row[couple_loc]] = couple_loc;



    couple_loc = loc[GET_COUPLE(row[start + 1])];

    temp = row[start + 0];
    row[start + 0] = row[couple_loc];
    row[couple_loc] = temp;

    loc[row[start + 0]] = start + 0;
    loc[row[couple_loc]] = couple_loc;

    swap1 = count_swap_recursive(row, start + 2, num, loc);

    temp = row[start + 0];
    row[start + 0] = row[couple_loc];
    row[couple_loc] = temp;

    loc[row[start + 0]] = start + 0;
    loc[row[couple_loc]] = couple_loc;

    min_swap = ((swap0 < swap1) ? swap0 : swap1) + 1;

    //printf("           [%d/%d] swap0=%d swap1=%d min_swap=%d\n", start, num, swap0, swap1, min_swap);

    return min_swap;
}

int couple_hands_2(vector<int>& row)
{
    int total_swap = 0;
    int *row_ary = new int[row.size()];
    int *loc_ary = new int[row.size()];

    for (int i = 0; i < row.size(); i++) {
        row_ary[i] = row.at(i);
        loc_ary[row.at(i)] = i;
    }

    total_swap = count_swap_recursive(row_ary, 0, row.size(), loc_ary);

    if (row_ary) {
        delete row_ary;
    }

    return total_swap;
}

int couple_hands_3(vector<int>& row)
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
        int cur_pos = GET_COUPLE(position.at(GET_COUPLE(row.at(first_unmatched))));

        while ((cur_pos != first_unmatched) && (total_swap < row.size())) {

            matched.at(cur_pos) = 1;
            matched.at(GET_COUPLE(cur_pos)) = 1;
            total_couple++;

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

        for (int i = 0; i < matched.size(); i++) {
            if (matched.at(i) == 0) {
                first_unmatched = i;
                break;
            }
        }
    }

    return total_swap;
}

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
    const int order1[] = { 1, 0 };
    const int order2[] = { 1, 3, 0, 2 };
    const int order3[] = { 3, 0, 5, 2, 1, 4 };
    const int order4[] = { 3, 0, 5, 2, 1, 4, 6, 7};
    const int order5[] = { 3, 0, 5, 2, 1, 4, 6, 9, 8, 7 };
    const int order6[] = { 4, 6, 1, 3, 5, 7, 12, 13, 15, 11, 0, 10, 2, 8, 9, 14 };
    const int order7[] = { 28, 4, 37, 54, 35, 41, 43, 42, 45, 38, 19, 51, 49, 17, 47, 25, 12,
        53, 57, 20, 2, 1, 9, 27, 31, 55, 32, 48, 59, 15, 14, 8, 3, 7, 58, 23, 10, 52, 22, 30,
        6, 21, 24, 16, 46, 5, 33, 56, 18, 50, 39, 34, 29, 36, 26, 40, 44, 0, 11, 13}; // 26 -> 46

    vector<int> people;

#if 0
    for (int i = 0; i < sizeof(order1) / sizeof(order1[0]); i++) {
        people.push_back(order1[i]);
    }
    printf("num: %d total swaps: %d\n", people.size(), couple_hands_2(people));
    people.clear();

    for (int i = 0; i < sizeof(order2) / sizeof(order2[0]); i++) {
        people.push_back(order2[i]);
    }
    printf("num: %d total swaps: %d\n", people.size(), couple_hands_2(people));
    people.clear();

    for (int i = 0; i < sizeof(order3) / sizeof(order3[0]); i++) {
        people.push_back(order3[i]);
    }
    printf("num: %d total swaps: %d_%d\n", people.size(), couple_hands_2(people), couple_hands(people));
    people.clear();

    for (int i = 0; i < sizeof(order4) / sizeof(order4[0]); i++) {
        people.push_back(order4[i]);
    }
    printf("num: %d total swaps: %d_%d\n", people.size(), couple_hands_2(people), couple_hands(people));
    people.clear();

    for (int i = 0; i < sizeof(order5) / sizeof(order5[0]); i++) {
        people.push_back(order5[i]);
    }
    printf("num: %d total swaps: %d_%d\n", people.size(), couple_hands_2(people), couple_hands(people));
    people.clear();

    for (int i = 0; i < sizeof(order6) / sizeof(order6[0]); i++) {
        people.push_back(order6[i]);
    }
    printf("num: %d total swaps: %d_%d\n", people.size(), couple_hands_2(people), couple_hands(people));
    people.clear();
#endif

#if 1
    for (int i = 0; i < sizeof(order7) / sizeof(order7[0]); i++) {
        people.push_back(order7[i]);
    }
    printf("num: %d total swaps: %d_%d\n", people.size(), couple_hands_3(people), couple_hands(people));
    people.clear();
#endif
}
