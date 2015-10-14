#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <assert.h>
#include "BinaryTree.h"

#define REPEAT_NUM 500

extern void flatten(struct TreeNode* node);

_TreeNode *InsertLeftNode(int val, _TreeNode *e)
{
    e->left = (_TreeNode *) malloc(sizeof(_TreeNode));
    e = e->left;
    e->val = val;
    e->left = NULL;
    e->right = NULL;
    return e;
}

_TreeNode *InsertRightNode(int val, _TreeNode *e)
{
    e->right = (_TreeNode *) malloc(sizeof(_TreeNode));
    e = e->right;
    e->val = val;
    e->left = NULL;
    e->right = NULL;
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


    /*Create test case
    *             1
    *            / \
    *           2   5
    *          / \   \
    *         3   4   6
    */
    _TreeNode *CreateTestCase() {
        _TreeNode *node_1 = (_TreeNode*)malloc(sizeof(_TreeNode));
        node_1->val = 1;
        node_1->left = (_TreeNode*)malloc(sizeof(_TreeNode));
        node_1->right = (_TreeNode*)malloc(sizeof(_TreeNode));
        _TreeNode *node_2 = node_1->left;
        node_2->val = 2;
        node_2->left = (_TreeNode*)malloc(sizeof(_TreeNode));
        node_2->right = (_TreeNode*)malloc(sizeof(_TreeNode));
        _TreeNode *node_3 = node_2->left;
        node_3->val = 3;
        node_3->left = NULL;
        node_3->right = NULL;
        _TreeNode *node_4 = node_2->right;
        node_4->val = 4;
        node_4->left = NULL;
        node_4->right = NULL;
        _TreeNode *node_5 = node_1->right;
        node_5->val = 5;
        node_5->left = NULL;
        node_5->right = (_TreeNode*)malloc(sizeof(_TreeNode));
        _TreeNode *node_6 = node_5->right;
        node_6->val = 6;
        node_6->left = NULL;
        node_6->right = NULL;
        return node_1;
    }

    void FreeTestCase(_TreeNode *head) { //recursive free all node
        if(head == NULL)//do nothing
            return;

        //recursive free
        FreeTestCase(head->left);
        FreeTestCase(head->right);

        free(head);
    }


    /*
     *Verify test case result!
     *  1
     *   \
     *    2
     *     \
     *      3
     *       \
     *        4
     *         \
     *          5
     *           \
     *            6
     */
    _TreeNode *head = CreateTestCase();
    assert( (head != NULL) && "head should not be NULL!\n");
    flatten(head);
    if( (head->val == 1)&&(head->right->val == 2)&&(head->right->right->val == 3)&&(head->right->right->right->val == 4)&&(head->right->right->right->right->val == 5)&&(head->right->right->right->right->right->val == 6) ) {
        printf("Correct algorithm!\n");
        FreeTestCase(head);
    } else {
        printf("Incorrect algorithm!\n");
        //fclose(fp_record);
        exit(1);
    }


    /*
     *Start test consumed time in test case 2!
     */
    for (int i = 0; i < REPEAT_NUM; ++i) {
        _TreeNode *head = CreateTestCase();

        system("./drop_cache.sh");

        clock_gettime(CLOCK_REALTIME, &start);

        flatten(head);

        clock_gettime(CLOCK_REALTIME, &end);

        elapsed_time = diff_in_second(start, end);
        total_time += elapsed_time;
        FreeTestCase(head);
        //printf("%lf\n", elapsed_time);
        //fprintf(fp_record,"%lf\n", elapsed_time);
    }

    printf("Total time:%lf secs for %d times\n", total_time,REPEAT_NUM);

    //fclose(fp_record);
    return 0;
}