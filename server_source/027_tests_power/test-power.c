#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>

unsigned power(unsigned x, unsigned y);


// unsigned is just short for unsigned int
// max unsigned int value is 4294967295


void check_power(unsigned x, unsigned y, unsigned answer){
  printf("Testing power(%d, %d) and received answer %d; expected %d\n", x,y,power(x,y),answer);
  if (x > UINT_MAX){
    exit(EXIT_FAILURE);
  }
  else if(y > UINT_MAX){
    exit(EXIT_FAILURE);
  }
  else if(power(x,y) > UINT_MAX){
    exit(EXIT_FAILURE);
  }
  else if(power(x,y) != answer){
    printf("Power function answer did not match expected answer.\n");
    exit(EXIT_FAILURE);
  }
  else if (x < 0 || y < 0 || power(x,y) < 0){
    printf("Arguments and answers must be unsigned (positive) numbers\n");
    exit(EXIT_FAILURE);
  }
  else{
    return;
  }
}


int main(void){
  // to exit after failed test, use 'exit(EXIT_FAILURE)'

  check_power(2,2,4);
  check_power(15,2,225);
  check_power(2,10,1024);
  check_power(5,5,3125);
  check_power(99,0,1);
  check_power(99,1,99);
  check_power(0,0,1);
  check_power(-2,3,-8);
  check_power(-2,4,16);
  check_power(2,5,32);
  check_power(4,0,1);
  check_power(8,2,64);
  check_power(3,3,27);
  check_power(2,-1,0);
  


  return EXIT_SUCCESS;
}
