#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

unsigned power(unsigned x, unsigned y){
  // have base case first
  /*
    Old implementation that caused seg fault
  if (y == 0){
    return 1;
  }
  else if (y == 1){
    return x;
  }
  else{
    return x * power(x, y-1);
  }
  */

  // more efficient implementation
  int even_answer;  // will be used for the even powers
  if (y == 0){
    return 1;
  }
  else if(y == 1){
    return x;
  }
  else if(y % 2 == 0){ // if y is an even power
    even_answer = power(x, y/2);
    return even_answer * even_answer;
  }
  else{
    return x * power(x , y-1);
  }
  // hopefully this won't seg fault
}

      
