#include <stdio.h>
#include <stdlib.h>



int * initArray(int * array, int n){
  for (int i = 0; i < n; i++){
    array[i] = i;
  }
  return array;
}

int * aFunction(int n) {
  int myArray[n];
  
  int * ptr = initArray(myArray, n-1);
  int total = 0;
  for (int i = 0; i <= n; i++) { // index out of bounds
    printf("%d\n", myArray[i]);  // use of unitialized value
    total += ptr[i];   // use of unitialized value
  }
  printf("Total = %d\n", total);
  return myArray;   // return dangling pointer 
}

int main (void) {
  int * ptr = aFunction(8); // use of dangling pointer
  printf("%d\n", ptr[0]); // use of uninitialized value
  return EXIT_SUCCESS;
}
