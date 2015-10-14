#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <assert.h>
#include "ListNode.h"

#define REPEAT_NUM 300

extern struct ListNode *detectCycle(struct ListNode *head);
typedef struct ListNode _ListNode;

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
    if(detectCycle(NULL) != NULL) {
        printf("Test Case:\"NULL\" Failed!\n");
        //fclose(fp_record);
        exit(0);
    }


    /*Create test case 2
    *       n6--------n5
    *        |         |
    *  n1---n2---n3---n4
    */
    _ListNode *CreateTestCase_2() {
        _ListNode *n1 = (_ListNode *)malloc(sizeof(_ListNode));
        n1->next = (_ListNode *)malloc(sizeof(_ListNode));
        _ListNode *n2 = n1->next;
        n2->next = (_ListNode *)malloc(sizeof(_ListNode));
        _ListNode *n3 = n2->next;
        n3->next = (_ListNode *)malloc(sizeof(_ListNode));
        _ListNode *n4 = n3->next;
        n4->next = (_ListNode *)malloc(sizeof(_ListNode));
        _ListNode *n5 = n4->next;
        n5->next = (_ListNode *)malloc(sizeof(_ListNode));
        _ListNode *n6 = n5->next;
        n6->next = n2;

        n1->val = 1;
        n2->val = 2;
        n3->val = 3;
        n4->val = 4;
        n5->val = 5;
        n6->val = 6;
        return n1;
    }

    void FreeAll(_ListNode *head) {
        _ListNode *cycle = detectCycle(head);
        int first = 1;
        if( cycle!= NULL) {

            while( head!=NULL) {
                _ListNode *temp = head;


                if( ((temp->next) == cycle)&&(first==0) ) {
                    free(temp);
                    return;
                }

                if(temp == cycle) {
                    first = 0;
                }
                head = head->next;

                free(temp);
            }
        } else {
            while(head!=NULL) {
                _ListNode *temp = head;
                head = head->next;
                free(temp);
            }
        }


        return;
    }


    /*
     *Verify test case 2 result!
     * It should return 2
     */
    _ListNode *head = CreateTestCase_2();
    assert( (head != NULL) && "head should not be NULL\n");
    if( detectCycle(head) == (head->next) ) {
        printf("Correct algorithm!\n");
        FreeAll(head);
    } else {
        printf("Incorrect algorithm!\n");
        FreeAll(head);
        //fclose(fp_record);
        exit(1);
    }


    /*
     *Start test consumed time in test case 2!
     */
    _ListNode *head_ = CreateTestCase_2();
    _ListNode * result = NULL;
    for (int i = 0; i < REPEAT_NUM; ++i) {

        system("./drop_cache.sh");

        clock_gettime(CLOCK_REALTIME, &start);

        result = detectCycle(head_);

        clock_gettime(CLOCK_REALTIME, &end);

        elapsed_time = diff_in_second(start, end);
        total_time += elapsed_time;
        //printf("%lf\n", elapsed_time);
        //fprintf(fp_record,"%lf\n", elapsed_time);

    }
    printf("val at where the cycle happend is %d\n",result->val);
    FreeAll(head_);
    printf("Total time:%lf secs for %d times\n", total_time,REPEAT_NUM);

    //fclose(fp_record);
    return 0;
}