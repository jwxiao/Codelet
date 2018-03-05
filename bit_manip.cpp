#include "common.h"

using namespace std;

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

int is_prime23(int q)
{
    static const int primes23[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23
    };
    int cnt = 9, idx, left = 0, right = 8;

    if (q > 23) {
        return -1;
    }

    while (left <= right) {
        idx = ((left + right + 1) >> 1);

        if (q > primes23[idx]) {
            left = idx + 1;
        }
        else if (q < primes23[idx]) {
            right = idx - 1;
        }
        else {
            return 1;
        }
    }
    return 0;
}

int count_set_bits(int a)
{
    int cnt = 0;

    if (a == 0) {
        return 0;
    }
    else if ((a & (a - 1)) == 0) {
        return 1;
    }

    while (a) {
        if (a & 1) {
            cnt++;
        }
        a >>= 1;
    }

    return cnt;
}


void max_set_bit_distance(void)
{
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
}

int kth_grammar(int N, int K)
{
    int pattern = 0, n = N - 1;

    for (int i = 1; i < N; i++) {
        int bm = (1 << (1 << (i - 1))) - 1;

        pattern = (pattern | ((~pattern & bm) << (1 << (i - 1))));
    }

    return (pattern >> (K - 1)) & 1;
}

int kth_grammar2(int N, int K)
{
    int trans = 0;

    for (int i = N; i > 1; i--) {
        if (K > (1 << (i - 2))) {
            K -= (1 << (i - 2));
            trans++;
        }
    }
    return (trans & 1);
}

void main_is_prime23(void)
{
    for (int i = 0; i < 25; i++) {
        is_prime23(i);
    }
}

void main_count_set_bits(void)
{
    for (int i = 0; i < 25; i++) {
        count_set_bits(i);
    }
}

void main_kth_grammar(void)
{
    printf("1,1 : %d\n", kth_grammar2(1, 1));
    printf("2,1 : %d\n", kth_grammar2(2, 1));
    printf("2,2 : %d\n", kth_grammar2(2, 2));
    printf("4,5 : %d\n", kth_grammar2(4, 5));
    printf("30,417219134 : %d\n", kth_grammar2(30, 417219134));
}


