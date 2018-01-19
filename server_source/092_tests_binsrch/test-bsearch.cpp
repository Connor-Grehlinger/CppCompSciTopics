#include<iostream>
#include<stdlib.h>
#include"function.h"
#include<string>
#include<math.h>
#include<assert.h>
//#include<search.cpp> // where the binary search is implemented 

int binarySearchForZero(Function<int, int> * f, int low, int high);


class CountedIntFn : public Function<int, int>{
protected:
  unsigned remaining;
  Function<int, int> * f;
  const char *msg;
public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m): remaining(n), f(fn), msg(m){}

  virtual int invoke(int arg){
    if (remaining == 0){
      std::cerr <<  "Too many function invocations in: " << msg << " \n";
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};



// abstracted out testing function:
void check(Function<int,int> * f, int low, int high, int expected_ans, const char * msg){

  // set the remaining invocations field:
  int remaining_function_invocations = (log2(high - low)) + 1;
  if (high <= low){
    remaining_function_invocations = 1;
  }
  
  // make a counting function object from passed in function:
  Function<int, int> * function_tester = new CountedIntFn(remaining_function_invocations, f, msg);

  // call binary search on the count object:
  if (binarySearchForZero(function_tester, low, high) != expected_ans){
    std::cout << binarySearchForZero(function_tester, low, high) << "\n";
    
    std::cerr << "Error, binary search result not equal to expected answer \n";
    exit(EXIT_FAILURE);
  }
  //std::cout << "Made it through checks with: " << msg << "\n";
  return;  
}

int main(void){

  Function<int, int> * sine = new SinFunction;
  
  
  check(sine, 0, 150000, 52359, "Testing SinFunction with valid range");
  check(sine, 0, 0, 0, "Testing SinFunction with no range");
  check(sine, 10, 20, 19, "Testing SinFunction with range less than solution");

 
  Function<int, int> * neg = new AlwaysNeg;
  // should return high - 1
  check(neg,-100,100,99, "Testing always negative function, should be high -1");
  check(neg, 20, -5, 20,"Testing always negative function with invalid range");
  check(neg, 20, 22, 21,"Testing always negative function with invalid range");
  
  
  Function<int, int> * pos = new AlwaysPos;
  // should return low of range
  check(pos,-2,100,-2,"Testing always positive function, should be the low of the range");
  check(pos, 10, 0, 10, "Testing always positive function with invalid range");
  
  Function<int, int> * z = new Zero;
  check(z, -2, 3, 0, "Testing with the zero function, should be the high of the range");
  // fails correct implementation ^ (used to, changing to the greatest val of range

  Function<int, int> * f1 = new Funct1;
  check(f1, -5, 6, 1, "Testing with f(x) = x - 1, should be 1");
  // f(x) = x - 1
  check(f1, -5, 0, -1, "Testing f(x) = x - 1 with solution out of range");
  check(f1, -8, 12, 1,".....");
  

  
  Function<int, int> * f2 = new Funct2;
  check(f2,-5,6,0, "Testing f(x) = x - 0.5 to see if it takes the x values less than 0.5");
  // f(x) = x - 0.5
  //check(f2, -1, 4, 1, "Testing f(x) = x - 0.5 to try to exclude solution");


  
  Function<int, int> * f3 = new Funct3;
  check(f3,-100, -50, -51, "Testing increasing function that does not get to 0");
  // f(x) = x - 100

  // what about decreasing function? should take the low
  Function<int, int> * f4 = new Funct4;
  check(f4, 5, 41, 40, "Testing a decreasing function to see if the result is the low");
  // f(x) = -x - 100

  
  return EXIT_SUCCESS;
}
