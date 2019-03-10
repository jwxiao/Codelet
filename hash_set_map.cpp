#include "common.h"

using namespace std;

void quick_sort_string(string &vec, int beg, int end)
{
    int i = beg, j = end, pivot = beg, tmp;

    if (i >= j)
        return;

    if ((i + 1) == j) {
        if (vec[i] > vec[j]) {
            tmp = vec[i];
            vec[i] = vec[j];
            vec[j] = tmp;
            return;
        }
    }

    if ((i + 7) < j) {
        int v0 = vec[i], v3 = vec[i + 3], v7 = vec[i + 7];
        if (v0 > v3) {
            if (v7 > v0) pivot = i;
            else if (v7 > v3) pivot = i + 7;
            else pivot = i + 3;
        }
        else {
            if (v7 > v3) pivot = i + 3;
            else if (v7 > v0) pivot = i + 7;
            else pivot = i;
        }
        if (pivot != i) {
            tmp = vec[pivot];
            vec[pivot] = vec[i];
            vec[i] = tmp;
            pivot = i;
        }
    }

    while (i <= j) {
        if (vec[i] <= vec[pivot]) {
            ++i;
            continue;
        }

        while (vec[j] > vec[pivot]) --j;

        if (i < j) {
            tmp = vec[i];
            vec[i] = vec[j];
            vec[j] = tmp;
            ++i; --j;
        }
    }

    tmp = vec[pivot];
    vec[pivot] = vec[i - 1];
    vec[i - 1] = tmp;

    quick_sort_string(vec, beg, i - 2);
    quick_sort_string(vec, i, end);

    return;
}

void sort_str(string &str, int beg, int end)
{
    int piv = beg, tmp, i = beg, j = end;

    if (i >= j)
        return;

    if ((i + 1) == j) {
        if (str[i] > str[j]) {
            tmp = str[j];
            str[j] = str[i];
            str[i] = tmp;
        }
        return;
    }

    while (i <= j) {
        if (str[i] > str[piv]) {
            while (str[j] > str[piv])
                --j;

            if (i < j) {
                tmp = str[j];
                str[j] = str[i];
                str[i] = tmp;
                --j;
                ++i;
            }
        }
        else
            ++i;
    }

    tmp = str[i - 1];
    str[i - 1] = str[piv];
    str[piv] = tmp;

    sort_str(str, beg, i - 2);
    sort_str(str, i, end);
}

vector<vector<string>> groupAnagrams(vector<string>& strs)
{
    unordered_map<string, vector<string>> hmap;
    unordered_map<string, vector<string>>::iterator itr;
    vector<vector<string>> result;

    for (size_t i = 0; i < strs.size(); i++) {
        string s = strs[i];
        sort_str(s, 0, s.size() - 1);
        itr = hmap.find(s);
        if (itr != hmap.end()) {
            itr->second.push_back(strs[i]);
        }
        else {
            vector<string> vs;
            vs.push_back(strs[i]);
            hmap.insert(make_pair(s, vs));
        }
    }

    for (itr = hmap.begin(); itr != hmap.end(); itr++)
        result.push_back(itr->second);

    return result;
}

template <class T>
void quick_sort(vector<T> &vec, int beg, int end)
{
    int i = beg, j = end, pivot = beg;
    T tmp;

    if (i >= j)
        return;

    if ((i + 1) == j) {
        if (vec[i] > vec[j]) {
            tmp = vec[i];
            vec[i] = vec[j];
            vec[j] = tmp;
            return;
        }
    }

    if ((i + 7) < j) {
        int v0 = vec[i], v3 = vec[i + 3], v7 = vec[i + 7];
        if (v0 > v3) {
            if (v7 > v0) pivot = i;
            else if (v7 > v3) pivot = i + 7;
            else pivot = i + 3;
        }
        else {
            if (v7 > v3) pivot = i + 3;
            else if (v7 > v0) pivot = i + 7;
            else pivot = i;
        }
        if (pivot != i) {
            tmp = vec[pivot];
            vec[pivot] = vec[i];
            vec[i] = tmp;
            pivot = i;
        }
    }

    while (i <= j) {
        if (vec[i] <= vec[pivot]) {
            ++i;
            continue;
        }

        while (vec[j] > vec[pivot]) --j;

        if (i < j) {
            tmp = vec[i];
            vec[i] = vec[j];
            vec[j] = tmp;
            ++i; --j;
        }
    }

    tmp = vec[pivot];
    vec[pivot] = vec[i - 1];
    vec[i - 1] = tmp;

    quick_sort(vec, beg, i - 2);
    quick_sort(vec, i, end);

    return;
}


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

unordered_map<int, list<TreeNode*>> hmap;
unordered_map<int, list<TreeNode*>>::iterator itr;

void create_groups(TreeNode* root, int& hashval, int& depth)
{
    int val = 0, ld = 0, rd = 0;

    hashval = root->val;

    if (root->left) {
        create_groups(root->left, val, ld);
        ++ld;
        hashval += (~val);
    }
    if (root->right) {
        create_groups(root->right, val, rd);
        ++rd;
        hashval ^= val;
    }

    depth = (ld > rd) ? ld : rd;
    hashval ^= depth;

    itr = hmap.find(hashval);
    if (itr == hmap.end()) {
        list<TreeNode*> v;
        v.push_back(root);
        hmap.insert(make_pair(hashval, v));
    }
    else {
        itr->second.push_back(root);
    }
}

bool compare_tree(TreeNode *left, TreeNode *right)
{
    bool result = true;
    static int nest_cnt = 0;

    if (left->left && right->left) {
        result = compare_tree(left->left, right->left);
        if (result == false)
            return result;
    }
    else if (left->left != right->left)
        return false;

    if (left->right && right->right) {
        result = compare_tree(left->right, right->right);
        if (result == false)
            return result;
    }
    else if (left->right != right->right)
        return false;

    return left->val == right->val;
}

vector<TreeNode*> findDuplicateSubtrees(TreeNode* root)
{
    int roothv = 0, depth = 0;
    vector<TreeNode*> result;
    list<TreeNode*>::iterator itrL0;
    list<TreeNode*>::iterator itrL1;

    if (!root)
        return result;

    create_groups(root, roothv, depth);

    for (itr = hmap.begin(); itr != hmap.end(); itr++) {
        if (itr->second.size() < 2)
            continue;

#if 0
        printf("group of nodes: \n");
        for (itrL0 = itr->second.begin(); itrL0 != itr->second.end(); itrL0++) {
            printf("    val:%d ptr:%p\n", (*itrL0)->val, *itrL0);
        }
#endif
        for (itrL0 = itr->second.begin(); itrL0 != itr->second.end(); itrL0 = itr->second.erase(itrL0)) {
            int dup_cnt = 1;

            itrL1 = itrL0;
            itrL1++;

            while (itrL1 != itr->second.end()) {
                if (compare_tree((*itrL0), (*itrL1))) {
                    dup_cnt++;
                    itrL1 = itr->second.erase(itrL1);

                    if (dup_cnt == 2)
                        result.push_back(*itrL0);
                }
                else
                    itrL1++;
            }
        }
    }

    return result;
}

vector<vector<int>> threeSum(vector<int>& nums)
{
    unordered_map<int, vector<int>> tuples;
    unordered_map<int, vector<int>> lut;
    unordered_map<int, vector<int>>::iterator itr;
    unordered_map<int, vector<int>>::iterator itr2;
    vector<vector<int>> result;

    for (int i = 0; i < nums.size(); i++) {
        itr = lut.find(nums[i]);
        if (itr != lut.end()) {
            itr->second.push_back(i);
        }
        else {
            vector<int> t;
            t.push_back(i);
            lut.insert(make_pair(nums[i], t));
        }
    }

    for (int i = 0; i < nums.size(); i++) {

        for (int j = i + 1; j < nums.size(); j++) {
            int val = 0 - nums[i] - nums[j];
            int a, b, c;

            itr2 = lut.find(val);
            if (itr2 != lut.end()) {
                if (itr2->second.at(itr2->second.size()-1) > j) {
                    if (nums[i] > nums[j]) {
                        if (nums[i] > val) {
                            if (nums[j] > val) {
                                a = val;
                                b = nums[j];
                            }
                            else {
                                a = nums[j];
                                b = val;
                            }
                            c = nums[i];
                        }
                        else {
                            a = nums[j];
                            b = nums[i];
                            c = val;
                        }
                    }
                    else {
                        if (nums[i] > val) {
                            a = val;
                            b = nums[i];
                            c = nums[j];
                        }
                        else {
                            a = nums[i];
                            if (nums[j] > val) {
                                b = val;
                                c = nums[j];
                            }
                            else {
                                b = nums[j];
                                c = val;
                            }
                        }
                    }
                        
                    itr = tuples.find(a);
                    if (itr != tuples.end()) {
                        int t = 0;
                        for (t = 0; t < itr->second.size(); t++) {
                            if (itr->second.at(t) == b)
                                break;
                        }
                        if (t >= itr->second.size()) {
                            vector<int> newtuple = { a, b, c };

                            itr->second.push_back(b);
                            result.push_back(newtuple);
                        }
                    }
                    else {
                        vector<int> t;
                        vector<int> newtuple = { a, b, c };

                        t.push_back(b);
                        tuples.insert(make_pair(a, t));
                        result.push_back(newtuple);
                    }
                }
            }
        }
    }

    return result;
}

void main_threeSum(void)
{
    vector<int> newtuple2 = { -1, 0, 1, 2, -1, -4 };
    vector<int> newtuple1 = { 0, 1, -1, 2, 1, -1 };
    vector<int> newtuple = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };
    vector<vector<int>> obj;

    obj = threeSum(newtuple);

    for (int j = 0; j < obj.size(); j++) {
        printf("dump set[%d]: ", j);
        for (int i = 0; i < obj[j].size(); i++) {
            printf("%d, ", obj[j][i]);
        }
        printf("\n");
    }

    return;
}


int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
    unordered_map<int, int> o2tab;
    unordered_map<int, int>::iterator it;
    int total = 0;

    for (int c = 0; c < C.size(); c++) {
        for (int d = 0; d < D.size(); d++) {
            int sum = C[c] + D[d];
            it = o2tab.find(sum);
            if (it != o2tab.end())
                it->second++;
            else
                o2tab.insert(make_pair(sum, 1));
        }
    }

    for (int a = 0; a < A.size(); a++) {
        for (int b = 0; b < B.size(); b++) {
            it = o2tab.find(-(A[a] + B[b]));
            if (it != o2tab.end())
                total += it->second;
        }
    }

    return total;
}

#include <algorithm>
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq, invfreq;
    unordered_map<int, int>::iterator it;
    vector<int> spectrum, result;
    int i = 0, f;

    for (int i = 0; i < nums.size(); i++) {
        it = freq.find(nums[i]);
        if (it != freq.end())
            it->second++;
        else
            freq.insert(make_pair(nums[i], 1));
    }
    if (freq.size() == nums.size()) {
        for (i = 0; i < k; i++)
            result.push_back(nums[i]);
        return result;
    }

    spectrum.resize(freq.size());
    for (it = freq.begin(), i = 0; it != freq.end(); it++, i++) {
        spectrum[i] = it->second;
    }
    sort(spectrum.begin(), spectrum.end());
    f = spectrum[spectrum.size() - k];

    for (it = freq.begin(); it != freq.end(); it++) {
        if (it->second > f)
            result.push_back(it->first);
    }

    for (it = freq.begin(); (it != freq.end()) && (result.size() < k); it++) {
        if (it->second == f)
            result.push_back(it->first);
    }

    return result;
}


class RandomizedSet {
public:
    /** Initialize your data structure here. */

    vector<unordered_map<int, int>::iterator> randvec;
    unordered_map<int, int> mainlut;

    RandomizedSet() {
        srand(time(NULL));
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        unordered_map<int, int>::iterator it;
        it = mainlut.find(val);
        if (it == mainlut.end()) {
            mainlut.insert(make_pair(val, randvec.size()));
            it = mainlut.find(val);
            randvec.push_back(it);
            return true;
        }
        else
            return false;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        unordered_map<int, int>::iterator it;
        it = mainlut.find(val);
        if (it == mainlut.end()) {
            return false;
        }
        else {
            randvec[it->second] = randvec[randvec.size() - 1];
            randvec[randvec.size() - 1]->second = it->second;

            randvec.pop_back();
            mainlut.erase(it);
            return true;
        }
    }

    /** Get a random element from the set. */
    int getRandom() {
        int r, k;
        r = rand();
        r %= randvec.size();
        k = randvec[r]->first;
        return k;
    }
};

class RandomizedSetX {
public:
    /** Initialize your data structure here. */
    RandomizedSetX() {

    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        // check exist?
        if (!elementKey.count(val)){
            // insert with new key
            int key = nums.size();
            nums.push_back(val);
            elementKey[val] = key;
            return true;
        }
        else{
            return false;
        }
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        // check exist
        auto it = elementKey.find(val);
        if (it != elementKey.end()){
            int removedKey = it->second;
            elementKey.erase(val);
            // edge case: remove at last
            if (removedKey == nums.size() - 1){
                nums.pop_back();
            }
            else{
                // pick the last element and use its key 
                int lastElement = nums.back();
                nums.pop_back();
                nums[removedKey] = lastElement;
                elementKey[lastElement] = removedKey;
            }
            return true;

        }
        else{
            return false;
        }
    }

    /** Get a random element from the set. */
    int getRandom() {
        return nums[rand() % nums.size()];
    }

private:
    vector<int> nums;
    unordered_map<int, int> elementKey;
};
