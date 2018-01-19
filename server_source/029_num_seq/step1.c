//This file is for Step 1.
//You should do 
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
// 
// Be sure to #include any header files you need!

// compile with gcc -o seq1 -std=gnu99 -Wall -Werror -pedantic
// Recognize the pattern. its how far away you are from 1, * 4 in either direction 

#include<stdlib.h>
#include<stdio.h>

int seq1(int x){
  // sequence increases by 4 each time
  int distance_from_one = x - 1;
  
  if (x == 1){
    return 1;
  }
  else if (x < 0){
    return (distance_from_one * 4) + 1; 
  }
  else{
    return (distance_from_one * 4) + 1;
  }
}

void printSeq1Range(int low, int high){
  if (low >= high){
    printf("\n");
    return;
  }
  for (int i = low; i < (high - 1); i++){
    printf("%d,", seq1(i));
  }
  printf("%d\n", seq1(high - 1));
  return;
}


/*
DO NOT TEST THIS WAY IT WILL CONFUSE GRADER!

void test_seq1(int x, int answer){
  if(seq1(x) != answer){
    printf("seq1(%d) Failed. Expected: %d, Received: %d\n", x, answer, seq1(x)); 
    exit(EXIT_FAILURE);
  }
  else{
    printf("seq1(%d) = %d\n", x, seq1(x));
  }
  return;
}
*/

int main(void){


  printf("seq1(%d) = %d\n", -10, seq1(-10));
  printf("seq1(%d) = %d\n", -9, seq1(-9));
  printf("seq1(%d) = %d\n", -8, seq1(-8));
  printf("seq1(%d) = %d\n", -7, seq1(-7));
  printf("seq1(%d) = %d\n", -6, seq1(-6));
  printf("seq1(%d) = %d\n", -5, seq1(-5));
  printf("seq1(%d) = %d\n", -4, seq1(-4));
  printf("seq1(%d) = %d\n", -3, seq1(-3));
  printf("seq1(%d) = %d\n", -2, seq1(-2));
  printf("seq1(%d) = %d\n", -1, seq1(-1));
  printf("seq1(%d) = %d\n", 0, seq1(0));
  printf("seq1(%d) = %d\n", 1, seq1(1));
  printf("seq1(%d) = %d\n", 2, seq1(2));
  printf("seq1(%d) = %d\n", 3, seq1(3));
  printf("seq1(%d) = %d\n", 4, seq1(4));
  printf("seq1(%d) = %d\n", 5, seq1(5));
  printf("seq1(%d) = %d\n", 6, seq1(6));
  printf("seq1(%d) = %d\n", 7, seq1(7));
  printf("seq1(%d) = %d\n", 8, seq1(8));
  printf("seq1(%d) = %d\n", 9, seq1(9));
  printf("seq1(%d) = %d\n", 10, seq1(10));
  printf("seq1(%d) = %d\n", 11, seq1(11));
  printf("seq1(%d) = %d\n", 12, seq1(12));

  printf("printSeq1Range(%d,%d)\n", 0, 4);
  printSeq1Range(0,4);
  printf("printSeq1Range(%d,%d)\n", -2, 6);
  printSeq1Range(-2,6);
  printf("printSeq1Range(%d,%d)\n", 7, 3);
  printSeq1Range(7,3);
  printf("printSeq1Range(%d,%d)\n", 0, 0);
  printSeq1Range(0,0);
  printf("printSeq1Range(%d,%d)\n", -4, 12);
  printSeq1Range(-4,12);
  printf("printSeq1Range(%d,%d)\n", -10, 10);
  printSeq1Range(-10,10);
  printf("printSeq1Range(%d,%d)\n", -7, -8);
  printSeq1Range(-7,-8);
  printf("printSeq1Range(%d,%d)\n", 1, 2);
  printSeq1Range(1,2);
  
  /*
  Other test method (DO NOT UNCOMMENT)

  test_seq1(-4,-19);
  test_seq1(-1,-7);
  test_seq1(0,-3);
  test_seq1(4,13);
  test_seq1(10,37);
  test_seq1(3,8);
  */

  
  return EXIT_SUCCESS;
}
