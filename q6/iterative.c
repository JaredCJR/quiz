#include "ListNode.h"
#include <stddef.h>

struct ListNode* reverseBetween(struct ListNode* head, int m, int n)
{
    if(head == NULL || head->next == NULL || m == n) {
        return head;
    }

    int counter = 1, retimes = n-m+1;
    struct ListNode *cur = head, *sublist_prev = head, *prev = NULL, *next = NULL;

    /*
     * let cur point to the mth node,
     * let sublist_prev point to the (m-1)th node.(the previous node of the head of reversed sublist)
     * eg: 1-> 2 -> 3 -> 4 -> NULL, m = 3, n = 4.
     * when m != 1 you should record the (m-1)th node (eg: 2) let it point to the head of reversed sublist.
     * 1 -> 2 -> 4 -> 3 -> NULL
     *
     * hit: (counter < m) do not add "="
     */

    while(counter < m) {
        cur = cur->next;
        counter++;
        if(counter < m) {
            /*tricky step to record previous node of the head of reversed sublist*/
            sublist_prev = sublist_prev->next;
        }
    }

    /*
     * let prev point to the (n+1)th node.
     * in above example prev should point to NULL
     * hit: (counter <= n) do not missing "=".
     */

    prev = cur;
    while(counter <= n) {
        prev = prev->next;
        counter++;
    }

    /*
     *   reverse the sublist, may be all list
     */
    while(retimes--) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    /*
     * when m == 1 it means to reverse all list.
     * after revese, prev point to the head of the reversed linked list.
     * cur point the (n+1)th node.
     */

    if(m == 1) {
        return prev;
    }


    /*
     *  m != 1 it means to just reverse a sublist.
     *  so, just return head.
     *  But do not forget to change the next of sublist_prev to the head of reversed list
     */
    sublist_prev->next = prev;
    return head;
}