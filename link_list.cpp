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
