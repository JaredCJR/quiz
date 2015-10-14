#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <assert.h>
#include "ListNode.h"

#define REPEAT_NUM 300

extern struct ListNode* reverseBetween(struct ListNode* head, int m, int n);

_ListNode *InsertNode(int val, _ListNode *e)
{
    e->next = (_ListNode *) malloc(sizeof(_ListNode));
    e = e->next;
    e->val = val;
    e->next = NULL;
    return e;
}

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec - t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{

    double elapsed_time,total_time = 0;
    struct timespec start, end;
    /*
    	FILE *fp_record;
    	fp_record = fopen("./result.txt","a");
    	if( fp_record == NULL ){
            printf("Cannot open the result_file\n");
            return -1;
        }
    */

    /*Create test case 1
    *  NULL
    */
    if(reverseBetween(NULL,0,0) != NULL) {
        printf("Test Case:\"NULL\" Failed!\n");
        //fclose(fp_record);
        exit(0);
    }


    /*Create test case 2
    *  1->2->3->4->5->6->7->8->NULL
    */
    _ListNode *head = (_ListNode *)malloc(sizeof(_ListNode));
    head->val = 1;
    _ListNode *temp = head;
    temp->next = NULL;
    for(int i =2; i<=8; i++) {
        InsertNode(i,temp);
        temp = temp->next;
    }


    /*
     *Verify test case 2 result!
     * 1->2->3->4->5->6->7->8->NULL
     * 1->2->6->5->4->3->7->8->NULL
     */
    int m = 3,n=6;
    assert( (m<n) && "n must larger than m\n");
    reverseBetween(head,m,n);
    if( (head->val ==1)&&(head->next->val ==2)&&(head->next->next->val ==6)&&(head->next->next->next->val ==5)&&(head->next->next->next->next->val ==4)&&(head->next->next->next->next->next->val ==3)&&(head->next->next->next->next->next->next->val ==7)&&(head->next->next->next->next->next->next->next->val ==8) ) {
        printf("Correct algorithm!\n");
    } else {
        printf("Incorrect algorithm!\n");
        //fclose(fp_record);
        exit(1);
    }


    /*
     *Start test consumed time in test case 2!
     */
    for (int i = 0; i < REPEAT_NUM; ++i) {
        reverseBetween(head,m,n);//Go back to its origin.
        system("./drop_cache.sh");

        clock_gettime(CLOCK_REALTIME, &start);

        reverseBetween(head,m,n);

        clock_gettime(CLOCK_REALTIME, &end);

        elapsed_time = diff_in_second(start, end);
        total_time += elapsed_time;
        //printf("%lf\n", elapsed_time);
        //fprintf(fp_record,"%lf\n", elapsed_time);
    }

    printf("Total time:%lf secs for %d times\n", total_time,REPEAT_NUM);
    /*
    *  Free test case 2
    */
    while(head!=NULL) {
        _ListNode *temp = head;
        head = head->next;
        free(temp);
    }

    //fclose(fp_record);
    return 0;
}