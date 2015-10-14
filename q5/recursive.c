#include "ListNode.h"
#include <stddef.h>

#define node_NUM 15000

void *addr_array[node_NUM];//record the address of node
int _index = 0;

int findAddr(struct ListNode *temp) //0 for not found;1 for found it!
{
    for(int i =0; i<_index; i++) {
        if( temp == addr_array[i]) {
            _index = 0;
            return 1;
        }
    }
    addr_array[_index] = temp;
    _index++;
    return 0;
}

struct ListNode *detectCycle(struct ListNode *head)
{
    if(head == NULL) {
        return NULL;
    }

    if(head->next != NULL) {
        if(findAddr(head)) {
            return head;
        }
        return detectCycle(head->next);//Recursive
    }
    _index = 0;
    return NULL;
}