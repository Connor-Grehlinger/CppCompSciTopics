//This file is for Step 2.
//You should do 
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
// 
// Be sure to #include any header files you need!

#include<stdlib.h>
#include<stdio.h>


// Note that the sequence goes +4, +6, +8, +10, +12 ... etc
// This depends on how far x is from -1

int seq2(int x){
  int distance_from_neg_one = x - -1;
  // EXAMPLES:
  // x = 0 -->  0 - -1 = 0 + 1 = 1 --> (1 * 2) + (x = -1) = 1
  // x = 1 --> 1 - -1 = 1 + 1 = 2 --> (2 * 2) + (x = 1) = 5
  // x = 2 --> 2 - -1 = 2 + 1 = 3 --> (3 * 2) + (x = 2) = 8
  // x = -1 --> -1 - -1 = -1 + 1 = 0 --> (0 * 2) + (x = -1) = -1
  // x = -2 --> -2 - -1 = -2 + 1 = -1 --> (-1 * 2) + (x = -2) = -2 + -2 = -4 (! diff)
  // MUST RE-THINK THIS
  
  // Updated algorithm
  if (x == -1){
    return x;
  }
  else if (x >= -1){  // -1 and up works properly 
    return ((distance_from_neg_one * 2) + seq2(x -1));
  }
  else if (x < -2){
    // x = -3 --> dist_from_neg_one = -2 --> dist_from_neg_one * 2 = -4
    // --> seq2(x + 1) = seq2(-2) = -1
    return (seq2(x + 1) - ((distance_from_neg_one +1) * 2));
  }
  else{  // x == -2
    // x = -2 --> dist_from_neg_one = -2 + 1 = -1 --> dist_from_neg_one * 2 = -2
    // -2 - seq(-1) = -2 - -1 = -2 + 1 = -1
    return ((distance_from_neg_one * 2) - seq2(x + 1));
  }
}

int sumSeq2(int low, int high){
  int sum = 0;
  if (low >= high){
    return sum;
  }
  else{
    for (int i = low; i < high; i++){
      sum += seq2(i);
    }
  }
  return sum;
}

int main(void){

  printf("seq2(%d) = %d\n", -8, seq2(-8));
  printf("seq2(%d) = %d\n", -7, seq2(-7));
  printf("seq2(%d) = %d\n", -6, seq2(-6));
  printf("seq2(%d) = %d\n", -5, seq2(-5));
  printf("seq2(%d) = %d\n", -4, seq2(-4));
  printf("seq2(%d) = %d\n", -3, seq2(-3));
  printf("seq2(%d) = %d\n", -2, seq2(-2));
  printf("seq2(%d) = %d\n", -1, seq2(-1));
  printf("seq2(%d) = %d\n", 0, seq2(0));
  printf("seq2(%d) = %d\n", 1, seq2(1));
  printf("seq2(%d) = %d\n", 2, seq2(2));
  printf("seq2(%d) = %d\n", 3, seq2(3));
  printf("seq2(%d) = %d\n", 4, seq2(4));
  printf("seq2(%d) = %d\n", 5, seq2(5));
  printf("seq2(%d) = %d\n", 6, seq2(6));
  printf("seq2(%d) = %d\n", 7, seq2(7));
  printf("seq2(%d) = %d\n", 8, seq2(8));
  printf("seq2(%d) = %d\n", 9, seq2(9));
  printf("seq2(%d) = %d\n", 10, seq2(10));
  printf("seq2(%d) = %d\n", 11, seq2(11));
  printf("seq2(%d) = %d\n", 12, seq2(12));
  printf("seq2(%d) = %d\n", 13, seq2(13));
  printf("seq2(%d) = %d\n", 14, seq2(14));
  printf("seq2(%d) = %d\n", 15, seq2(15));


  printf("sumSeq2(%d, %d) = %d\n", 0,2, sumSeq2(0,2));
  printf("sumSeq2(%d, %d) = %d\n", 3,6, sumSeq2(3,6));
  printf("sumSeq2(%d, %d) = %d\n", 9,7, sumSeq2(9,7));
  printf("sumSeq2(%d, %d) = %d\n", 0,7, sumSeq2(0,7));
  printf("sumSeq2(%d, %d) = %d\n", -1,1, sumSeq2(-1,1));
  printf("sumSeq2(%d, %d) = %d\n", -4,0, sumSeq2(-4,0));
  printf("sumSeq2(%d, %d) = %d\n", -5,3, sumSeq2(-5,3));
  printf("sumSeq2(%d, %d) = %d\n", 6,7, sumSeq2(6,7));
  printf("sumSeq2(%d, %d) = %d\n", 0,15, sumSeq2(0,15));
  printf("sumSeq2(%d, %d) = %d\n", -4,2, sumSeq2(-4,2));
  printf("sumSeq2(%d, %d) = %d\n", -3,-1, sumSeq2(-3,-1));


  return EXIT_SUCCESS;
}
