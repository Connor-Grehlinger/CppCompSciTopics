#include<math.h>
#include<iostream>
#include"function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high){

  int low_s = low;
  int high_s = high;
  int num_invocations = (log2(high - low)) + 1;
  
  int result = 0;
  int midpoint = ((high_s - low_s) / 2) + low_s;  // guess at x value
  //std::cout << "----------Starting midpoint: " << midpoint << "----------\n";
  while (num_invocations > 0){

    result = f->invoke(midpoint);

    if (result == 0){
      //std::cout << "f(x) = 0 at x = " << midpoint << "\n";
      return midpoint;  // you got lucky and happned to guess right or function is always 0
    }
    /*
    else if ((high_s - low_s == 1) || (high_s == low_s)){
      return midpoint;
    }
    */
    else if (result < 0){  // its to the right of the first midpoint, new interval is [midpoint,high)
      low_s = midpoint;
      //std::cout << "Taking right sub-interval: [" << low_s << "," << high_s << ")\n";
    }
    
    else if (result > 0){
      // result is > 0, its to the left of the first midpoint, new interval is [low, midpoint)
      high_s = midpoint;
      //std::cout << "Taking left sub-interval: [" << low_s << "," << high_s << ")\n";
    }
    
    // now you want to run this again for a finite number of invocations
    midpoint = ((high_s - low_s) / 2) + low_s;

    if ((high_s - low_s == 1) || (high_s == low_s)){
      return midpoint;
    }

    //std::cout << "new midpoint: " << midpoint << "\n";
    num_invocations--;
  }
  // if outside of while loop you have used up all the invocations of the function allowed
  // if the last result is positive, asssume the function is all positive, same for neg
  if (result < 0){  // function always negative
    return high - 1;
  }
  else{
    return low;
  }
}
