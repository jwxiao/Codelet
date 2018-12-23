#include "common.h"

using namespace std;

class MyLinkedList {
public:
    struct junode {
        struct junode *next;
        int value;
    };

    struct junode *pHead;
    struct junode *pTail;

    /** Initialize your data structure here. */
    MyLinkedList() {
        pHead = 0;
        pTail = 0;
    }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        struct junode *ptr = pHead;

        for (int i = 0; (i < index) && (ptr); i++) {
            ptr = ptr->next;
        }
        
        return (ptr)? ptr->value: -1;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        struct junode *ptr = new struct junode;

        ptr->value = val;
        ptr->next = pHead;
        pHead = ptr;

        if (pTail == 0) {
            pTail = pHead;
        }
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        struct junode *ptr = new struct junode;

        ptr->value = val;
        ptr->next = 0;

        if (pTail == 0) {
            pHead = ptr;
            pTail = ptr;
        }
        else  {
            pTail->next = ptr;
            pTail = ptr;
        }
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        struct junode **ptr = &pHead;
        int i;

        for (i = 0; (i < index) && (*ptr); i++) {
            ptr = &((*ptr)->next);
        }

        if ((*ptr) || (i == index)) {
            struct junode *p = new struct junode;
            
            p->value = val;
            p->next = *ptr;

            if ((*ptr) == 0) {
                pTail = p;
            }
            *ptr = p;
        }
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        struct junode **ptr = &pHead, *prev = 0;
        int i;

        for (i = 0; (i < index) && (*ptr); i++) {
            prev = *ptr;
            ptr = &((*ptr)->next);
        }

        if (*ptr) {
            struct junode *p = *ptr;

            if ((*ptr) == pTail) {
                pTail = prev;
            }
            *ptr = (*ptr)->next;
            
            delete p;
        }

    }
};

/*
["MyLinkedList","addAtHead","addAtIndex","addAtIndex","addAtTail","addAtHead","addAtIndex","addAtIndex","addAtIndex","addAtTail","addAtTail","deleteAtIndex"]
[[],             [0],        [1,9],      [1,5],       [7],         [1],        [5,8],       [5,2],       [3,0],      [1],         [0],        [6]]
1,0,5,9,7
1,0,5,0,9,7,5,1,0
*/

/**
* Your MyLinkedList object will be instantiated and called as such:
* MyLinkedList obj = new MyLinkedList();
* int param_1 = obj.get(index);
* obj.addAtHead(val);
* obj.addAtTail(val);
* obj.addAtIndex(index,val);
* obj.deleteAtIndex(index);
*/

void main_my_linked_list(void)
{
    MyLinkedList obj;

    obj.addAtHead(0);
    obj.addAtIndex(1, 9);
    obj.addAtIndex(1, 5);
    obj.addAtTail(7);
    obj.addAtHead(1);
    obj.addAtIndex(5, 8);
    obj.addAtIndex(5, 2);
    obj.addAtIndex(3, 0);
    obj.addAtTail(1);
    obj.addAtTail(0);
    obj.deleteAtIndex(6);
}


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *detectCycle(ListNode *head)
{
    ListNode *fast = head, *slow = head;
    int cycle = 0, T = 0;

    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        T++;

        if (fast == slow) {
            cycle = 1;
            break;
        }
    }
    if (cycle == 0) {
        return 0;
    }

    for (int i = 0; i < T; ++i) {
        slow = slow->next;
    }

    fast = head;

    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }

    return fast;
}


ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    ListNode *pa = headA, *pb = headB;
    int a_num = 1, b_num = 1, diff;

    if ((pa == 0) || (pb == 0))
        return 0;

    while (pa && pa->next) {
        a_num++;
        pa = pa->next;
    }
    while (pb && pb->next) {
        b_num++;
        pb = pb->next;
    }

    if (pa != pb)
        return 0;

    pa = headA;
    pb = headB;
    
    if (a_num > b_num) {
        diff = a_num - b_num;
        for (int i = 0; i < diff; i++)
            pa = pa->next;
    }
    else if (a_num < b_num) {
        diff = b_num - a_num;
        for (int i = 0; i < diff; i++)
            pb = pb->next;
    }

    while (pa != pb) {
        pa = pa->next;
        pb = pb->next;
    }

    return pa;
}


ListNode* reverseList(ListNode* head) {
    ListNode *prev = 0, *succ = 0;
    ListNode *cur = head;

    while (cur) {
        succ = cur->next;
        cur->next = prev;
        prev = cur;
        cur = succ;
    }
    return prev;

#if 0
    if (head == NULL || head->next == NULL) {
        return head; // returns either NULL or last linked list element
    }
    ListNode* reverse = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return reverse;
#endif
}

void main_reverseList(void)
{
    ListNode a1(1), a2(2), a3(3), a4(4), a5(5);
    ListNode *r;

    a1.next = &a2;

    r = reverseList(&a1);

    while (r) {
        printf("node: %d\n", r->val);
        r = r->next;
    }
}

bool isPalindrome (ListNode* head)
{
    ListNode *f = head, *s = head, *tmp;

    if (head == 0) {
        return true;
    }
    if (head->next == 0) {
        return true;
    }

    while (f && f->next) {
        f = f->next->next;
        if (f == 0) {
            break;
        }

        tmp = s->next;
        s->next = tmp->next;
        tmp->next = head;
        head = tmp;
    }

    if (f == 0) { //odd edges
        s = s->next;
    }
    else if (f->next == 0) { //even edges
        s = s->next;
        head = head->next;
    }

    while (s) {
        if (s->val != head->val) {
            return false;
        }
        s = s->next;
        head = head->next;
    }

    return true;
}


ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    ListNode *main, *sub, *st, *tmp;

    if (!(l1 && l2)) {
        return (l1) ? l1 : l2;
    }

    if (l1->val < l2->val) {
        main = l1;
        sub = l2;
    }
    else {
        main = l2;
        sub = l1;
    }
    st = main;

    while (main->next && sub) {
        if (sub->val >= main->next->val) {
            main = main->next;
            continue;
        }

        tmp = main->next;
        main->next = sub;
        main = tmp;

        while ((sub->next) && (sub->next->val <= main->val)) {
            sub = sub->next;
        }

        tmp = sub->next;
        sub->next = main;
        sub = tmp;
    }
    
    if (sub) {
        main->next = sub;
    }

    return st;
}

class Node {
public:
    int val = NULL;
    Node* prev = NULL;
    Node* next = NULL;
    Node* child = NULL;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};


Node* getLast_recur(Node* head)
{
    Node *curr = head;

    if (curr == 0)
        return curr;

    while (curr->next) {
        if (curr->child) {
            Node *child_last, *nextp;

            child_last = getLast_recur(curr->child);
            nextp = curr->next;

            curr->next = curr->child;
            curr->child->prev = curr;
            curr->child = 0;

            nextp->prev = child_last;
            child_last->next = nextp;

            curr = nextp;
        }
        else {
            curr = curr->next;
        }
    }

    if (curr->child) {
        Node *child_last = getLast_recur(curr->child);
        curr->child->prev = curr;
        curr->next = curr->child;
        curr->child = 0;

        curr = child_last;
    }

    return curr;
}

Node* flatten(Node* head)
{
    getLast_recur(head);

    return head;
}


struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

struct hash_node {
    int         order;
    void        *key;
    hash_node   *next;

public:
    hash_node(int o, void *k) : order(o), key(k), next(nullptr) {}
};

struct bindptr {
    RandomListNode  *org;
    RandomListNode  *dup;

public:
    bindptr(RandomListNode *o, RandomListNode *d) : org(o), dup(d) {}
};

inline int hash_offset(void *ptr, int range)
{
    unsigned long long c = (unsigned long long)ptr;
    return (c + (c >> 16) + (c >> 32)) % range;
}

RandomListNode *copyRandomList(RandomListNode *head)
{
    int n = 0;
    RandomListNode      **pOrg, **pDup, *dupHead = nullptr;
    vector<bindptr>     bindlut;
    vector<hash_node*>  htbl_org;

    if (head == nullptr)
        return nullptr;

    pOrg = &head;
    pDup = &dupHead;
    while (*pOrg) {
        *pDup = new RandomListNode((*pOrg)->label);

        bindlut.push_back(bindptr(*pOrg, *pDup));

        pOrg = &((*pOrg)->next);
        pDup = &((*pDup)->next);
        n++;
    }

    htbl_org.resize(n);
    htbl_org.assign(n, 0);

    pOrg = &head;
    for (int i = 0; i < n; i++) {
        hash_node **pph = &(htbl_org[hash_offset(*pOrg, n)]);

        while (*pph) {
            pph = &((*pph)->next);
        }
        *pph = new hash_node(i, *pOrg);

        pOrg = &((*pOrg)->next);
    }

    pOrg = &head;
    pDup = &dupHead;
    for (int i = 0; i < n; i++) {
        if ((*pOrg)->random == nullptr) {
            (*pDup)->random = nullptr;
        }
        else {
            RandomListNode *k = (*pOrg)->random;
            hash_node **pph = &(htbl_org[hash_offset(k, n)]);

            while ((*pph)->key != k) {
                pph = &((*pph)->next);
            }

            (*pDup)->random = bindlut[(*pph)->order].dup;
        }

        pOrg = &((*pOrg)->next);
        pDup = &((*pDup)->next);
    }

    return dupHead;
}

void print_list(RandomListNode *p, char *tag)
{
    printf("%s order: ", tag);
    while (p) {
        if (p->random) {
            printf("%d(%d), ", p->random->label, p->label);
        }
        else {
            printf("NULL(%d), ", p->label);
        }
        p = p->next;
    }
    printf("\n");
}

void main_copyRandomList(void)
{
    RandomListNode n0(10);
    RandomListNode n1(11);
    RandomListNode n2(12);
    RandomListNode n3(13);
    RandomListNode *dup, *org;

    n0.next = &n1;
    n1.next = &n2;
    n2.next = &n3;

    n0.random = &n1;
    n1.random = &n2;
    n2.random = &n2;
    n3.random = &n2;

    dup = copyRandomList(&n0);
    org = &n0;

    print_list(org, "org");
    print_list(dup, "dup");
}

ListNode* rotateRight(ListNode* head, int k)
{
    int n, k2 = k, d;
    ListNode *last, *cur;

    if ((head == nullptr) || (head->next == nullptr)) {
        return head;
    }

    for (n = 1, cur = head; cur->next; cur = cur->next, n++);

    last = cur;
    k2 = k % n;
    d = n - k2 - 1;

    cur = head;
    for (int i = 0; i < d; i++) {
        cur = cur->next;
    }

    last->next = head;
    head = cur->next;
    cur->next = nullptr;

    return head;
}

