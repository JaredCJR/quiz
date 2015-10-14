#include "ListNode.h"
#include <stddef.h>

typedef struct ListNode ln;
#define NEXT(x) (x=x->next)
#define NEXT3(x) (x=x->next->next->next)
ln* getIntersectionNode(ln *headA, ln *headB);

ln* detectCycle(ln *head)
{
    /* first use runner chaser to find if cycle exists */
    ln *runner = head, *chaser = head;
    while(runner && chaser->next && chaser->next->next) {
        NEXT(runner);
        NEXT3(chaser);
        if(runner == chaser) break;
    }

    /* return NULL if no cycle being found */
    if(!runner || runner != chaser) return NULL;

    /* find the intersection between two lists
       list-1: head->...->tail
       list-2: tail+1->...->tail*/
    ln* newHeadOfCycle = runner->next;
    runner->next = NULL; /* runner becomes the sentinel node and the tail of the new list */

    chaser = getIntersectionNode(head, newHeadOfCycle);

    /* restore the original linked list */
    runner->next = newHeadOfCycle;

    return chaser;
}

ln* getIntersectionNode(ln *headA, ln *headB)
{
    if(!headA || !headB) return NULL;

    /* first get the len of two lists */
    int lenA = 0, lenB =0;
    ln *pA, *pB;
    for(pA = headA; pA; NEXT(pA)) lenA++;
    for(pB = headB; pB; NEXT(pB)) lenB++;

    /* move the longer one forward to match two lists at the start-line */
    for(int i = 0; i<(lenA-lenB); i++) NEXT(headA);
    for(int i = 0; i<(lenB-lenA); i++) NEXT(headB);

    /* move simultaneously and check the first meet point */
    while(headA!=headB) {
        NEXT(headA);
        NEXT(headB);
    }

    return headA;
}