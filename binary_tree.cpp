#include "common.h"

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode * build_tree_recursive(vector<int>& inorder, int in_st, int in_end, vector<int>& postorder, int po_st, int po_end)
{
    int r, offset;
    TreeNode *nptr;

    if (in_st == in_end) {
        return new TreeNode(inorder.at(in_st));
    }

    r = postorder.at(po_end);

    for (int i = in_st; i <= in_end; i++) {
        if (inorder.at(i) == r) {
            offset = i;
            break;
        }
    }

    nptr = new TreeNode(r);

    if (offset > in_st) {
        nptr->left = build_tree_recursive(inorder, in_st, offset - 1, postorder, po_st, po_st + offset - in_st - 1);
    }
    if (offset < in_end) {
        nptr->right = build_tree_recursive(inorder, offset + 1, in_end, postorder, po_st + offset - in_st, po_end - 1);
    }

    return nptr;
}

// in: 9,3,15,20,7
// post: 9,15,7,20,3
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
{
    if (inorder.size() == 0) {
        return 0;
    }
    else {
        return build_tree_recursive(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }
}

TreeNode * build_tree_recursive2(vector<int>& preorder, int pre_st, int pre_end, vector<int>& inorder, int in_st, int in_end)
{
    int r, offset;
    TreeNode *nptr;

    if (in_st == in_end) {
        return new TreeNode(inorder.at(in_st));
    }

    r = preorder.at(pre_st);

    for (int i = in_st; i <= in_end; i++) {
        if (inorder.at(i) == r) {
            offset = i;
            break;
        }
    }

    nptr = new TreeNode(r);

    if (offset > in_st) {
        nptr->left = build_tree_recursive2(preorder, pre_st + 1, pre_st + 1 + offset - in_st - 1, inorder, in_st, offset - 1);
    }
    if (offset < in_end) {
        nptr->right = build_tree_recursive2(preorder, pre_st + 1 + offset - in_st, pre_end, inorder, offset + 1, in_end);
    }

    return nptr;
}

TreeNode* buildTree2(vector<int>& preorder, vector<int>& inorder)
{
    if (inorder.size() == 0) {
        return 0;
    }
    else {
        return build_tree_recursive2(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
}

void main_tree_order_construct(void)
{
    int ary_inorder[] = { 9, 3, 15, 20, 7 };
    int ary_postorder[] = { 9, 15, 7, 20, 3 };
    int ary_preorder[] = { 3, 9, 20, 15, 7 };
    vector<int> in, post, pre;
    TreeNode *root, *root2;

    for (int i = 0; i < sizeof(ary_inorder) / sizeof(ary_postorder[0]); i++) {
        in.push_back(ary_inorder[i]);
    }
    for (int i = 0; i < sizeof(ary_postorder) / sizeof(ary_postorder[0]); i++) {
        post.push_back(ary_postorder[i]);
    }

    for (int i = 0; i < sizeof(ary_preorder) / sizeof(ary_preorder[0]); i++) {
        pre.push_back(ary_preorder[i]);
    }
    
    root = buildTree(in, post);
    root2 = buildTree2(pre, in);

    return;
}


struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
    
};

void connect(TreeLinkNode *root)
{
    list<TreeLinkNode*> lnode_list;
    list<int> lnode_depth;

    if (root == 0) {
        return;
    }

    lnode_list.push_back(root);
    lnode_depth.push_back(0);

    while (lnode_list.size()) {
        int d = *(lnode_depth.begin());
        TreeLinkNode *p = *(lnode_list.begin());

        lnode_list.pop_front();
        lnode_depth.pop_front();

        if (p->left) {
            lnode_list.push_back(p->left);
            lnode_depth.push_back(d + 1);
        }
        if (p->right) {
            lnode_list.push_back(p->right);;
            lnode_depth.push_back(d + 1);
        }

        if (lnode_list.size() == 0) {
            p->next = 0;
        }
        else {
            if (*(lnode_depth.begin()) != d) {
                p->next = 0;
            }
            else {
                p->next = *(lnode_list.begin());
            }
        }
    }
}

void connect_leetcode_version(TreeLinkNode *root) {
    if (!root) { return; }
    TreeLinkNode* beg = root;
    TreeLinkNode* curr = NULL;
    while (true) {
        curr = beg;
        beg = NULL;
        TreeLinkNode* last = NULL;
        while (curr) {
            TreeLinkNode* left = (curr->left ? curr->left : curr->right);
            TreeLinkNode* right = (curr->right ? curr->right : curr->left);

            if (!last && left) {
                beg = left;
            }

            if (last && left) {
                last->next = left;
            }

            if (left && right) {
                left->next = right;
                last = right;
            }
            curr = curr->next;
        }
        if (last) { last->next = NULL; }
        if (!beg) { return; }
    }
}


TreeNode* _lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q, int *count)
{
    TreeNode *lptr = 0, *rptr = 0;
    int cnt = 0, lcnt = 0, rcnt = 0;

    if (root == p) {
        cnt = 1;
    }
    else if (root == q) {
        cnt = 1;
    }

    if (root->left) {
        lptr = _lowestCommonAncestor(root->left, p, q, &lcnt);
    }

    if (root->right) {
        rptr = _lowestCommonAncestor(root->right, p, q, &rcnt);
    }
    
    *count = cnt + lcnt + rcnt;

    if (*count == 2) {
        if (lcnt == 2) {
            return lptr;
        }
        else if (rcnt == 2) {
            return rptr;
        }
        else {
            return root;
        }
    }
    else if (*count == 1) {
        if (lcnt) {
            return lptr;
        }
        if (rcnt) {
            return rptr;
        }
        if (cnt) {
            return root;
        }
    }
    
    return 0;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    int cnt = 0;

    return _lowestCommonAncestor(root, p, q, &cnt);
}

void main_lowestCommonAncestor(void)
{
    //3,5,1,6,2,0,8,null,null,7,4
    TreeNode a3(3);
    TreeNode a5(5);
    TreeNode a1(1);
    TreeNode a6(6);
    TreeNode a2(2);
    TreeNode a0(0);
    TreeNode a8(8);
    TreeNode a7(7);
    TreeNode a4(4);
    TreeNode *ret;

    a3.left = &a5;
    a3.right = &a1;
    a5.left = &a6;
    a5.right = &a2;
    a1.left = &a0;
    a1.right = &a8;
    a2.left = &a7;
    a2.right = &a4;

    ret = lowestCommonAncestor(&a3, &a5, &a1);

    printf("common ancestor: %d\n", ret->val);
}



void bfs_serialize(TreeNode *root, string& serial, int traverse_order)
{
    if (!root) {
        return;
    }

    if (traverse_order == 1) { // pre-order
        serial = serial + to_string(root->val) +" ";
    }

    if (root->left) {
        bfs_serialize(root->left, serial, traverse_order);
    }

    if (traverse_order == 0) { // in-order
        serial = serial + to_string(root->val) + " ";
    }

    if (root->right) {
        bfs_serialize(root->right, serial, traverse_order);
    }

    if (traverse_order == 2) { // post-order
        serial = serial + to_string(root->val) + " ";
    }
}

// Encodes a tree to a single string.
string serialize(TreeNode* root) {
    string data;

    bfs_serialize(root, data, 0);
    bfs_serialize(root, data, 1);

    return data;
}

// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
    int data_len = data.size(), cnt_tok = 0;
    size_t offset = 0;
    vector<int> in_order, pre_order;
    stringstream ss_data(data);
    
    for (cnt_tok = 0, offset = 0; 1; offset++, cnt_tok++) {
        offset = data.find_first_of(' ', offset);
        if (offset == -1) {
            break;
        }
    }
    printf("tok:%d, str:%s\n", cnt_tok, data.c_str());

    for (int i = 0, s = 0; i < cnt_tok; i++) {
        ss_data >> s;
        printf("[%d/%d] s=%d\n", i, cnt_tok, s);
        if (i < (cnt_tok>>1))
            in_order.push_back(s);
        else 
            pre_order.push_back(s);
    }
    
    return buildTree2(pre_order, in_order);
}

void main_tree_serialization(void)
{
    TreeNode *r, *t;
    string bs1, bs2;

#if 1
    //[1,10,null,9,11,null,8,12,null,7,null,null,13,null,6,14,null,5,null,null,15,null,4,16,null,3,null,null,17,null,2,18,null,1,null,null,19]
    TreeNode a1(1);
    TreeNode a1_2(1);
    TreeNode a2(2);
    TreeNode a3(3);
    TreeNode a4(4);
    TreeNode a5(5);
    TreeNode a6(6);
    TreeNode a7(7);
    TreeNode a8(8);
    TreeNode a9(9);
    TreeNode a10(10);
    TreeNode a11(11);
    TreeNode a12(12);
    TreeNode a13(13);
    TreeNode a14(14);
    TreeNode a15(15);
    TreeNode a16(16);
    TreeNode a17(17);
    TreeNode a18(18);
    TreeNode a19(19);
    r = &a1;
    a1.left = &a10;
    a10.left = &a9;
    a10.right = &a11;
    a9.right = &a8;
    a11.left = &a12;
    a8.left = &a7;
    a12.right = &a13;
    a7.right = &a6;
    a13.left = &a14;
    a6.left = &a5;
    a14.right = &a15;
    a5.right = &a4;
    a15.left = &a16;
    a4.left = &a3;
    a16.right = &a17;
    a3.right = &a2;
    a17.left = &a18;
    a2.left = &a1_2;
    a18.right = &a19;
#endif
#if 0
    //3,5,1,6,2,0,8,null,null,7,4
    TreeNode a3(3);
    TreeNode a5(5);
    TreeNode a1(1);
    TreeNode a6(6);
    TreeNode a2(2);
    TreeNode a0(0);
    TreeNode a8(8);
    TreeNode a7(7);
    TreeNode a4(4);
    r = &a3;
    a3.left = &a5;
    a3.right = &a1;
    a5.left = &a6;
    a5.right = &a2;
    a1.left = &a0;
    a1.right = &a8;
    a2.left = &a7;
    a2.right = &a4;
#endif



    bs1 = serialize(r);
    printf("bitstream: %s\n", bs1.c_str());

    t = deserialize(bs1);

    bs2 = serialize(t);
    printf("bs2: %s\n", bs2.c_str());
}