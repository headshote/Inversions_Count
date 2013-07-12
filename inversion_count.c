#include <stdio.h>
#include <stdlib.h>
#include "inversion_count.h"

data* sortAndCount( int* array, int length)
{
    int lengthLeft, lengthRight;
    int leftArray[length/2], rightArray[length - length/2];
    data *X, *Y, *Z, *processedData;

    processedData = malloc( sizeof(data));

    //Base case for our recursion: 1-element array means no inversions
    if( length <2 )
    {
        processedData->inversions = 0L;
        processedData->array = array;
    }
    //Array has at least 2 elements, process it
    else
    {
        processedData->inversions = 0L;
        lengthLeft = length/2;
        lengthRight = length - length/2;
        //printf("%d %d %d\n", length, lengthLeft, lengthRight );
        X = malloc( sizeof(data));
        Y = malloc( sizeof(data));
        Z = malloc( sizeof(data));

        //Fill in first part of the array
        for( int i = 0; i<lengthLeft; i++ )
        {
            leftArray[i] = array[i];
            //printf( "leftArray[%d] = %d ", i, leftArray[i]);
        }
        //printf("\n");

        //Fill in the second part of the array
        for( int i = 0; i<lengthRight; i++ )
        {
            rightArray[i] = array[i+lengthLeft];
            //printf( "rightArray[%d] = %d ", i, rightArray[i]);
        }
        //printf("\n");

        //Recursively call our fcn on smaller inputs(halves), get these halves sorted
        X = sortAndCount( leftArray, lengthLeft);
        Y = sortAndCount( rightArray, lengthRight);
        //Merge sorted halves into 1 big sorted array, also get # of inversions
        Z = mergeAndCountSplitInv( X->array, Y->array, lengthLeft, lengthRight);

        //mergeAndCountSplitInv returns final sorted array
        processedData->array = Z->array;
        //Total # of inversions
        processedData->inversions = X->inversions + Y->inversions + Z->inversions;
        free(X->array);
        free(Y->array);
        free(X);
        free(Y);
        free(Z);
    }

    return processedData;
}

data* mergeAndCountSplitInv( int* leftArray, int* rightArray, int lengthLeft, int lengthRight)
{
    int i,j,k;
    data* processedData = malloc( sizeof(data));
    processedData->array = malloc((lengthLeft+lengthRight)*sizeof(int));
    processedData->inversions = 0L;

    i = 0;
    j = 0;
    k = 0;
    //Merge halves, depending on values of their elements
    while( (j<lengthLeft) && (k<lengthRight) )
    {
        if( leftArray[j] < rightArray[k] )
        {
            processedData->array[i] = leftArray[j];
            j++;
        }
        else
        {
            processedData->array[i] = rightArray[k];
            /*
             * while merging the two sorted subarrays, keep running total of
             * number of split inversions. When element of 2nd array C
             * gets copied to output D, increment total by number of elements
             * remaining in 1st array B
             */
            processedData->inversions += (lengthLeft - j);
            /*
             * the split inversions involving an element y of the 2nd array C
             * are precisely the numbers left in the 1st array B when y is copied to the output D
             */
            k++;
        }
        i++;
    }
    //In case one half of array was merged fully into output before the other
    //just fill in the rest of the other
    if( j==lengthLeft )
    {
        while(i<lengthLeft+lengthRight)
        {
            processedData->array[i] = rightArray[k];
            i++;
            k++;
        }
    }
    else
    {
       while(i<lengthLeft+lengthRight)
        {
              processedData->array[i] = leftArray[j];
              i++;
              j++;
        }
    }
    //printf("%llu \n", processedData->inversions );
    return processedData;
}
