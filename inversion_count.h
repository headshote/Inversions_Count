#include <stdio.h>
#include <stdlib.h>

/* Data structure that will contain array and number of inversions in it
 * Ir will be returned by our routines
 */
typedef struct data
{
    int* array;
    unsigned long long int	 inversions;
}data;

/* Recursive function that splits array into halves,
 * calls itself on these halves to get halves sorted,
 * calls mergeAndCountSplitInv() to get 1 sorted array
 * from sorted halves and get number of split inversions, adds that count
 * with counts from prev recursive calls to left and right halves of
 * the array and returns value( along with sorted array)
 */
data* sortAndCount( int* array, int length);

/* Merges two halves of an array into 1 sorted array and counts split inversions
 */
data* mergeAndCountSplitInv( int* leftArray, int* rightArray, int lengthLeft, int lengthRight);
