#include <stdio.h>
#include <stdlib.h>
#include "inversion_count.h"
//Test cases to check correctness of our program
void test()
{
    int array1[] = {1,3,5,2,4,6};
    int array2[] = {1,5,3,2,4};
    int array3[] = {5,4,3,2,1} ;
    int array4[] = {1,6,3,2,4,5};
    int array5[] = {1,2,3,4,5,6};
    int array6[] = { 9, 12, 3, 1, 6, 8, 2, 5, 14, 13, 11, 7, 10, 4, 0 };
    int array7[] = { 37, 7, 2, 14, 35, 47, 10, 24, 44, 17, 34, 11, 16, 48,
                    1, 39, 6, 33, 43, 26, 40, 4, 28, 5, 38, 41, 42, 12, 13, 21, 29, 18,
                    3, 19, 0, 32, 46, 27, 31, 25, 15, 36, 20, 8, 9, 49, 22, 23, 30, 45 };
    int array8[] = { 4, 80, 70, 23, 9, 60, 68, 27, 66, 78, 12, 40, 52, 53,
                    44, 8, 49, 28, 18, 46, 21, 39, 51, 7, 87, 99, 69, 62, 84,
                     6, 79, 67, 14, 98, 83, 0, 96, 5, 82, 10, 26, 48, 3, 2, 15,
                      92, 11, 55, 63, 97, 43, 45, 81, 42, 95, 20, 25, 74, 24, 72,
                       91, 35, 86, 19, 75, 58, 71, 47, 76, 59, 64, 93, 17, 50, 56,
                       94, 90, 89, 32, 37, 34, 65, 1, 73, 41, 36, 57, 77, 30, 22, 13,
                       29, 38, 16, 88, 61, 31, 85, 33, 54 };
    int array9[100000];
    data* result;

    result = sortAndCount( array1, 6);
    printf("# of inversions = %llu \n", result->inversions); //3
    free(result->array);
    free(result);

    result = sortAndCount( array2, 5);
    printf("# of inversions = %llu \n", result->inversions); //4
    free(result->array);
    free(result);

    result = sortAndCount( array3, 5);
    printf("# of inversions = %llu \n", result->inversions); //10
    free(result->array);
    free(result);

    result = sortAndCount( array4, 6);
    printf("# of inversions = %llu \n", result->inversions); //5
    free(result->array);
    free(result);

    result = sortAndCount( array5, 6);
    printf("# of inversions = %llu \n", result->inversions); //0
    free(result->array);
    free(result);

    result = sortAndCount( array6, 15);
    printf("# of inversions = %llu \n", result->inversions); //56
    free(result->array);
    free(result);

    result = sortAndCount( array7, 50);
    printf("# of inversions = %llu \n", result->inversions); //590
    free(result->array);
    free(result);

    result = sortAndCount( array8, 100);
    printf("# of inversions = %llu \n", result->inversions); //2372
    free(result->array);
    free(result);

    for( int j = 0, i = 100000; j<100000; j++,i--)
    {
        array9[j] = i;
    }
    result = sortAndCount( array9, 100000);
    printf("# of inversions = %llu \n", result->inversions); //4999950000
    free(result->array);
    free(result);
    return;
}

int main( int argc, char* argv[])
{
    int array[150000], i;
    data* result;
    FILE* fp;
    char* fileName;

    if( argc < 2)
    {
        printf("Usage is inversions_count file_with_numbers.txt\n");
        return EXIT_FAILURE;
    }

    fileName = argv[1];

    //Opening file
    fp = fopen( fileName, "r" );

    //Failed in opening
    if( fp == NULL )
    {
        printf("Could not open the file %s\n", fileName);
        return EXIT_FAILURE;
    }
    //Succeed in opening that file
    else
    {
        //write all file contents as if they were integers into an array
        i = 0;
        while( !feof(fp) )
        {
            if( fscanf(fp, "%d", &array[i]) != 1)
                break;
            i++;
        }
    }

    //Count # of inversions in that array of numbers from file with our function
    result = sortAndCount( array, i);

    /*//print out sorted array
    for( int j = 0; j < i; j++)
    {
        printf("SortedArray[%d] = %d\n", j, result->array[j]);
    }*/
    printf("%llu \n", result->inversions); //Print # of inversions

    //Close file stream
    fclose( fp );
    free(result->array);
    free(result);

    //test(); //run it to test the correctness

    return EXIT_SUCCESS;
}
