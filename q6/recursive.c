#include "ListNode.h"
#include <stddef.h>

struct ListNode *recursiveReverseLL(struct ListNode *mNode,struct ListNode *nNode)
{
    struct ListNode *revHead;
    if ( mNode == nNode) {
        return mNode;
    }

    revHead = recursiveReverseLL(mNode->next,nNode);
    mNode->next->next = mNode;
    mNode->next = NULL;

    return revHead;
}

struct ListNode* reverseBetween(struct ListNode* head, int m, int n)
{
    if(m==n) {
        return head;
    }

    struct ListNode* mNode = head;
    struct ListNode* mNodePrev = head;

    for(int i =1; i<m; i++) {
        mNode = mNode->next;
        if(i<m-1) {
            mNodePrev = mNodePrev->next;
        }
    }
    struct ListNode* nNode = mNode;
    struct ListNode* mNodeRear;
    for(int i = m; i < n; i++) {
        nNode = nNode->next;
        if(i == (n-1)) {
            mNodeRear = nNode->next;
        }
    }
    if(m!=1) {
        mNodePrev->next = recursiveReverseLL(mNode,nNode);
    } else {
        head = recursiveReverseLL(mNode,nNode);
    }
    mNode->next = mNodeRear;
    return head;
}
