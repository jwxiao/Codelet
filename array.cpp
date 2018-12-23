#include "common.h"

using namespace std;

int pivotIndex(vector<int>& nums)
{
    int sum = 0, cur = 0;

    switch (nums.size()) {
    case 1:
        return 0;
    case 0:
        return -1;
    }

    for (int i = 0; i < (int)nums.size(); ++i) {
        sum += nums.at(i);
    }

    for (int i = 0; i < (int)nums.size(); ++i) {
        if ((sum - cur - nums.at(i)) == cur) {
            return i;
        }
        cur += nums.at(i);
    }
    return -1;
}

void main_pivotIndex(void)
{
    vector<int> n;

    n.push_back(1);
    n.push_back(2);
    n.push_back(3);
    printf("pivot: %d\n", pivotIndex(n));

    //1, 7, 3, 6, 5, 6
    n.clear();
    n.push_back(1);
    n.push_back(7);
    n.push_back(3);
    n.push_back(6);
    n.push_back(5);
    n.push_back(6);
    printf("pivot: %d\n", pivotIndex(n));

    //[-1,-1,-1,0,1,1]
    n.clear();
    n.push_back(-1);
    n.push_back(-1);
    n.push_back(-1);
    n.push_back(0);
    n.push_back(1);
    n.push_back(1);
    printf("pivot: %d\n", pivotIndex(n));

    //[-1,-1,1,0,1,0]
    n.clear();
    n.push_back(-1);
    n.push_back(-1);
    n.push_back(1);
    n.push_back(0);
    n.push_back(1);
    n.push_back(0);
    printf("pivot: %d\n", pivotIndex(n));
}


vector<int> findDiagonalOrder(vector<vector<int>>& matrix)
{
    int w, h, total, x = 0, y = 0, mode = 0;
    vector<int> serialize;

    h = matrix.size();
    if (h == 0)
        return serialize;

    w = matrix.at(0).size();
    total = w * h;

    serialize.reserve(total);

    while ((x < w) && (y < h)) {

        serialize.push_back(matrix[y][x]);
        
        if (mode == 0) {
            if (x == w - 1) {
                if (y < (h - 1))
                    y++;
                else
                    break;
                mode = mode ? 0 : 1;
            }
            else if (y == 0) {
                x++;
                mode = mode ? 0 : 1;
            }
            else {
                x++;
                y--;
            }
        }
        else {
            if (y == h - 1) {
                if (x < (w - 1))
                    x++;
                else
                    break;
                mode = mode ? 0 : 1;
            }
            else if (x == 0) {
                y++;
                mode = mode ? 0 : 1;
            }
            else {
                x--;
                y++;
            }
        }
    }

    return serialize;
}

vector<int> findDiagonalOrder_REFERENCE(vector<vector<int>> &matrix) {
    if (matrix.empty() || matrix[0].empty())
        return{};
    vector<int> traverse(matrix.size() * matrix[0].size());
    for (int k = 0, index = 0; k < matrix.size() + matrix[0].size() - 1; ++k)
        if (k % 2) {
            int i = k < matrix[0].size() ? 0 : k - matrix[0].size() + 1, j = k - i;
            while (i < matrix.size() && j >= 0)
                traverse[index++] = matrix[i++][j--];
        }
        else {
            int i = k < matrix.size() ? k : matrix.size() - 1, j = k - i;
            while (i >= 0 && j < matrix[0].size())
                traverse[index++] = matrix[i--][j++];
        }
    return traverse;
}


vector<int> spiralOrder(vector<vector<int>>& matrix)
{
    int xmin, xmax, ymin, ymax, dir = 0, x, y;
    vector<int> serial;

    if (matrix.size() == 0 || matrix[0].size() == 0) {
        return vector<int>();
    }
    serial.reserve(matrix.size() * matrix[0].size());

    xmin = -1;
    xmax = matrix[0].size();
    ymin = -1;
    ymax = matrix.size();
    x = 0;
    y = 0;
    while ((ymax > (ymin + 1)) && (xmax > (xmin + 1))) {
#if 0
        printf("dir:%d serial_len:%d @%d,%d, %d_%d, %d_%d\n", dir, serial.size(), y, x, ymin, ymax, xmin, xmax);
        for (int g = 0; g < serial.size(); g++) {
            printf(" %d", serial[g]);
        }
        printf("\n");
#endif
        if (dir == 0) {
            while (x < xmax)
                serial.push_back(matrix[y][x++]);
            ymin++;
            y++;
            x--;
        }
        else if (dir == 1) {
            while (y < ymax)
                serial.push_back(matrix[y++][x]);
            xmax--;
            x--;
            y--;
        }
        else if (dir == 2) {
            while (x > xmin)
                serial.push_back(matrix[y][x--]);
            ymax--;
            y--;
            x++;
        }
        else {
            while (y > ymin)
                serial.push_back(matrix[y--][x]);
            xmin++;
            x++;
            y++;
        }

        dir = (dir + 1) % 4;
    }
    return serial;
}



int kmp_strstr(string haystack, string needle)
{
    int h = 0, n = 0;
    vector<int> nmatch;
 
    if (needle.size() == 0) {
        return 0;
    }
    if (haystack.size() < needle.size()) {
        return -1;
    }

    nmatch.resize(needle.size());
    nmatch.assign(nmatch.size(), -1);

    nmatch[0] = -1;
    for (int i = 1, j = 0; i < nmatch.size(); ) {
        if (needle[i] == needle[j]) {
            nmatch[i] = j;
            ++i; ++j;
        }
        else {
            if (j == 0) {
                nmatch[i] = -1;
                ++i;
            }
            else {
                j = nmatch[j - 1] + 1;
            }
        }
    }
    for (; (h < haystack.size()) && (n < needle.size()); ) {
        if (haystack[h] == needle[n]) {
            ++h; ++n;
        }
        else {
            if (n == 0) {
                ++h;
            }
            else {
                n = nmatch[n - 1] + 1;
            }
        }
    }
    if (n == needle.size()) {
        return h - n;
    }
    return -1;
}

void main_kmp_strstr(void)
{
    string s1, s2;
    int r = 0;

    s1 = "aabaaabaaac";
    s2 = "aabaaac";
    r = kmp_strstr(s1, s2);
    printf("r: %d s1=%s s2=%s\n", r, s1.c_str(), s2.c_str());

    s1 = "mississippi";
    s2 = "pi";
    r = kmp_strstr(s1, s2);
    printf("r: %d s1=%s s2=%s\n", r, s1.c_str(), s2.c_str());

    s1 = "mississippi";
    s2 = "issip";
    r = kmp_strstr(s1, s2);
    printf("r: %d s1=%s s2=%s\n", r, s1.c_str(), s2.c_str());

    s1 = "ababcaababcaabc";
    s2 = "ababcaabc";
    r = kmp_strstr(s1, s2);
    printf("r: %d s1=%s s2=%s\n", r, s1.c_str(), s2.c_str());
}