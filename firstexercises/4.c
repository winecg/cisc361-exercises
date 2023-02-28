#include <stdio.h>
  2 #include <stdlib.h>
  3 #include <time.h>
  4
  5 #define MAX_NO_OF_ELEMENTS 100000000
  6
  7 static long long int sum;
  8 static int arr[MAX_NO_OF_ELEMENTS];
  9
 10 int main() {
 11     for(int i=0; i<MAX_NO_OF_ELEMENTS; i++) {
 12         arr[i] = i + 1;
 13     }
 14
 15     clock_t start, end;
 16     double cpu_time_taken;
 17
 18     start = clock();
 19
 20     sum = 0;
 21     for(int i=0; i<MAX_NO_OF_ELEMENTS; i++) {
 22         sum += arr[i];
 23     }
 24
 25     end = clock();
 26
 27     cpu_time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
 28
 29     printf("Total sum: %lld\n", sum);
 30     printf("Time taken to sum all the numbers are %lf\n", cpu_time_taken);
 31
 32     return 0;
 33 }