#include <stdio.h>
#include "main.h"

#define NUM_SIZE 20

int nums[NUM_SIZE][NUM_SIZE];

void testfunc()
{
    for (int i=0; i<NUM_SIZE; i++) {
	int n = i+1;
	nums[0][i] = (2*n)*n;
    }

    for (int i=0; i<NUM_SIZE; i++)
	printf("%d ", nums[0][i]);
    printf("\n");

    for (int i=1; i<NUM_SIZE; i++) {
	if (nums[i-1][0] == 0) break;
	for (int j=0; j<NUM_SIZE-i; j++) {
	    nums[i][j] = nums[i-1][j+1] - nums[i-1][j];
	    printf("%d ", nums[i][j]);
	}
	printf("\n");
    }

    printf("\n");
}
