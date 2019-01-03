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


void qksort(vector<int>& nums, int l_idx, int r_idx)
{
    int pivot, l, r;

    if ((r_idx - l_idx + 1) < 2) {
        return;
    }

    pivot = nums[l_idx];
    l = l_idx;
    r = r_idx;

    while (l < r) {
        if (nums[l] <= pivot) {
            l++;
        }
        else {
            int swap = nums[l];
            nums[l] = nums[r];
            nums[r] = swap;
            r--;
        }
    }
#if 0
    printf("sub: %d_%d %d_%d\n", l_idx, l - 1, l, r_idx);
    for (int j = l_idx; j <= r_idx; j++)
        printf("%d ", nums[j]);
    printf("<=\n");
#endif

    if (nums[l] <= pivot) {
        int swap = nums[l];
        nums[l] = nums[l_idx];
        nums[l_idx] = swap;
        l--;
        r++;
    }
    else {
        int swap = nums[l - 1];
        nums[l - 1] = nums[l_idx];
        nums[l_idx] = swap;
        l -= 2;
    }

    if (l > l_idx) {
        qksort(nums, l_idx, l);
    }
    if (r < r_idx) {
        qksort(nums, r, r_idx);
    }
}

int arrayPairSum(vector<int>& nums)
{
    int sum = 0;

    qksort(nums, 0, nums.size() - 1);
#if 0
    for (int j = 0; j < nums.size(); j++)
        printf("%d ", nums[j]);
    printf("<= final\n");
#endif

    for (int i = 0; i < nums.size(); i += 2) {
        sum += nums[i];
    }

    return sum;
}


int minSubArrayLen(int s, vector<int>& nums)
{
    int head, foot;
    int si, shortest;

    if (nums.size() == 0)
        return 0;

    for (head = 0, foot = 0, si = 0; (si < s) && (head < nums.size()); head++) {
        si += nums[head];
    }
    if (si < s)
        return 0;
    head--;
    while (head < nums.size()) {
        while (si - nums[foot] >= s) {
            si -= nums[foot];
            foot++;
        }
        shortest = head - foot + 1;
        //printf("f_h len: %d_%d %d sum=%d\n", foot, head, shortest, si);

        head++; foot++;
        while ((head < nums.size())) {
            si = si + nums[head] - nums[foot - 1];

            if (si >= s)
                break;
            else {
                head++; foot++;
            }
        }
        //printf("    f_h len: %d_%d %d sum=%d\n", foot, head, shortest, si);
    }
    return shortest;
}


void reverseWords(string &s) {
    int i, j, last_ch_offset;

    if (s.size() < 1) {
        return;
    }

    for (j = s.size() - 1; j >= 0; --j) {
        if (s[j] != ' ')
            break;
    }
    if (j < 0) {
        s = "";
        return;
    }

    last_ch_offset = j;
    i = 0;
    while (i < j) {
        int temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        ++i, --j;
    }

    for (j = last_ch_offset; j >= 0; --j) {
        if (s[j] != ' ')
            break;
    }
    last_ch_offset = j;
    i = 0;
    while (i <= last_ch_offset) {
        //printf("@%d\n", i);
        int next_st;

        j = i;
        while ((j <= last_ch_offset) && (s[j] == ' '))
            j++;
        if (j > last_ch_offset)
            break;
        else if (j > i)
            i++;
        next_st = i;

        while ((j <= last_ch_offset) && (s[j] != ' '))
            j++;

        --j;
        while (i < j) {
            int temp = s[i];
            s[i] = s[j];
            s[j] = temp;
            ++i, --j;
        }

        i = next_st;
        while ((i <= last_ch_offset) && (s[i] != ' '))
            i++;
    }

    j = last_ch_offset;
    while (s[j] == ' ') --j;
    //s[j + 1] = 0;
    s.resize(j + 1);
}

string reverseWords2(string s) {
    int word_beg, word_end;

    if (s.length() < 2) {
        return s;
    }

    word_beg = 0;
    while (word_beg < s.length()) {
        while ((word_beg < s.length()) && (s[word_beg] == ' '))
            ++word_beg;

        word_end = word_beg + 1;
        while ((word_end < s.length()) && (s[word_end] != ' '))
            ++word_end;

        for (int i = word_beg, j = word_end - 1; i < j; ++i, --j) {
            int temp = s[i];
            s[i] = s[j];
            s[j] = temp;
        }
        
        word_beg = word_end + 1;
    }

    return s;
}

void main_reverseWords(void)
{
    string s = "  the sky is blue   ";
    s = " ";
    s = "a";

    printf("original_%d: [%s]\n", s.length(), s.c_str());

    reverseWords(s);
    
    printf("reversed_%d: [%s]\n", s.size(), s.c_str());
}