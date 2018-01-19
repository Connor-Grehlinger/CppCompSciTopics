#include<stdlib.h>
#include<stdio.h>


size_t maxSeq(int * array, size_t n){
  // function for determining the maximum number of contiguously
  // increasing integers, if the array is empty return 0
  // if the array has no contiguously increasing ints, return 1
  size_t number_of_increasing = 0;
  if(n == 0){
    return number_of_increasing;
  }
  else{
    size_t maxSeq = 1;
    size_t currentMaxSeq = 1;
    number_of_increasing = 1;
    
    for (size_t i = 0; i < (n - 1); i++){
      if(array[i] < array[i+1]){  // if the next number is greater than the current
	number_of_increasing++; // 4
	currentMaxSeq = number_of_increasing; //4
	if(currentMaxSeq > maxSeq){
	  maxSeq = currentMaxSeq; // 4
	}
      }
      else{
	number_of_increasing = 1;
	currentMaxSeq = number_of_increasing;
      }
    }
    return maxSeq;
  }
}


	
