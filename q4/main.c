#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <assert.h>
#include "ListNode.h"

#define REPEAT_NUM 300

extern int maxSubArray(int* s, int size);


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
    *  [-2,1,-3,4,-1,2,1,-5,4]
    *  [4,-1,2,1] has largest sum = 6
    */
    int test_array[9] =  {-2,1,-3,4,-1,2,1,-5,4};

    /*
     *Verify test case result!
     *[4,-1,2,1] =>6
     */
    assert( (test_array!=NULL) && "Array should not be NULL!\n");
    if( maxSubArray(test_array,9)==6 ) {
        printf("Correct algorithm!\n");
    } else {
        printf("Incorrect algorithm!\n");
        //fclose(fp_record);
        exit(1);
    }


    /*
     *Start test consumed time in test case 2!
     */
    int first = 1;
    for (int i = 0; i < REPEAT_NUM; ++i) {
        int result;
        system("./drop_cache.sh");

        clock_gettime(CLOCK_REALTIME, &start);

        result = maxSubArray(test_array,9);

        clock_gettime(CLOCK_REALTIME, &end);

        elapsed_time = diff_in_second(start, end);
        total_time += elapsed_time;
        if(first) {
            printf("Max = %d\n",result);
            first = 0;
        }
        //printf("%lf\n", elapsed_time);
        //fprintf(fp_record,"%lf\n", elapsed_time);
    }

    printf("Total time:%lf secs for %d times\n", total_time,REPEAT_NUM);

    //fclose(fp_record);
    return 0;
}