//This file is for Step 3.
//You should do 
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
// 
// Be sure to #include any header files you need!

#include<stdlib.h>
#include<stdio.h>

// Note: for y = 0, values of seq3(x,y) increase/decrease by 3 according to
// x's distance from 0

// For x = 0, the value of seq3(x,y) increases/decreases by 2 according to
// y's distance from 0

int seq3(int x, int y){
  int x_distance_from_zero = 0 - x;
  int y_distance_from_zero = y;
  int x_distance_from_neg_2 = x - -2;
  int y_distance_from_3 = y - 3;

  if (x == 0){
    return (y_distance_from_zero * 2);
  }
  if (y == 0){
    return (x_distance_from_zero * 3);
  }
  // x == 0 || y == 0 case covered
  if (x == y){
    //printf("Diagonal\n");
    return ((x * y) - x);
  }
  // x == y case covered
  
  int temp_x = x;
  int temp_y = y;
  int difference_from_diagonal_y = 0;
  int difference_from_diagonal_x = 0;

  // x > y || y > x
  if (temp_x > temp_y){  
    while (temp_x > temp_y){
      temp_y++;
      difference_from_diagonal_y++;
    }
  }
  else if (temp_x < temp_y){
    while (temp_x < temp_y){
      temp_x++;
      difference_from_diagonal_x++;
    }
  }
  // now both temp_x and temp_y will be equal
  // and you know how far x or y is from the closest diagonal
  
  int closest_diagonal_point = (temp_x * temp_y) - temp_x;
  if (x < y){
    return (closest_diagonal_point - (difference_from_diagonal_x * y_distance_from_3));
  }
  else{
    return (closest_diagonal_point - (difference_from_diagonal_y * x_distance_from_neg_2));
  }
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi){
  int numberOfEvens = 0;
  if ((xLow >= xHi) || (yLow >= yHi)){
      return numberOfEvens;
  }
  else{
    for (int i = xLow; i < xHi; i++){
      for (int j = yLow; j < yHi; j++){
	if(seq3(i,j) % 2 == 0){  // if the result of seq3 is even
	  numberOfEvens++;
	  // count up the number of evens
	}
      }
    }
    return numberOfEvens;
  }
}


    // MISC NOTES:
    // diagonal_point will have values of 30, 20, 12, 6, 2, 0, 0, 2, 6, 12, 20
    // Note where zeros occur (-1,-3),(0,0),(1,1),(4,2),(-5, 5)

    // y = -5, x changes by -8 for each increment, y is -5 away from 0
    // y = -4, x changes by -7 each increment
    // y = -3, x changes by -6 each increment
    // y = -2, x changes by -5
    // y = -1, x changes by -4
    // y = 0, x changes by -3
    // y = 1, x changes by -2
    // y = 2, x changes by -1
    // y = 3, x does not change
    // y = 4, x changes by + 1
    // y = 5, x changes by + 2
    //------------------------
    // x = -5, y changes by -3
    // x = -4, y changes by -2
    // x = -3, y changes by -1
    // x = -2, y does not change
    // x = -1, y changes by +1
    // x = 0, y changes by +2
    // x = 1, y changes by +3
    // x = 2, y changes by +4
    // x = 3, y changes by +5
    // x = 4, y changes by +6
    // x = 5, y changes by +7


int main(void){

  // hold x = 0 constant test
  printf("seq3(%d, %d) = %d\n", 0,0, seq3(0,0));
  printf("seq3(%d, %d) = %d\n", 0,1, seq3(0,1));
  printf("seq3(%d, %d) = %d\n", 0,2, seq3(0,2));
  printf("seq3(%d, %d) = %d\n", 0,3, seq3(0,3));
  printf("seq3(%d, %d) = %d\n", 0,4, seq3(0,4));
  printf("seq3(%d, %d) = %d\n", 0,5, seq3(0,5));
  printf("seq3(%d, %d) = %d\n", 0,6, seq3(0,6));
  printf("seq3(%d, %d) = %d\n", 0,-1, seq3(0,-1));
  printf("seq3(%d, %d) = %d\n", 0,-2, seq3(0,-2));
  printf("seq3(%d, %d) = %d\n", 0,-3, seq3(0,-3));
  printf("seq3(%d, %d) = %d\n", 0,-4, seq3(0,-4));
  printf("seq3(%d, %d) = %d\n", 0,-5, seq3(0,-5));
  // hold y = 0 constant test
  printf("seq3(%d, %d) = %d\n", 1,0, seq3(1,0));
  printf("seq3(%d, %d) = %d\n", 2,0, seq3(2,0));
  printf("seq3(%d, %d) = %d\n", 3,0, seq3(3,0));
  printf("seq3(%d, %d) = %d\n", 4,0, seq3(4,0));
  printf("seq3(%d, %d) = %d\n", 5,0, seq3(5,0));
  printf("seq3(%d, %d) = %d\n", -1,0, seq3(-1,0));
  printf("seq3(%d, %d) = %d\n", -2,0, seq3(-2,0));
  printf("seq3(%d, %d) = %d\n", -3,0, seq3(-3,0));
  printf("seq3(%d, %d) = %d\n", -4,0, seq3(-4,0));
  printf("seq3(%d, %d) = %d\n", -5,0, seq3(-5,0));
  printf("seq3(%d, %d) = %d\n", -6,0, seq3(-6,0));
  // diagonals test (x == y)
  printf("seq3(%d, %d) = %d\n", -5,-5, seq3(-5,-5));
  printf("seq3(%d, %d) = %d\n", -4,-4, seq3(-4,-4));
  printf("seq3(%d, %d) = %d\n", -3,-3, seq3(-3,-3));
  printf("seq3(%d, %d) = %d\n", -2,-2, seq3(-2,-2));
  printf("seq3(%d, %d) = %d\n", -1,-1, seq3(-1,-1));
  printf("seq3(%d, %d) = %d\n", 0,0, seq3(0,0));
  printf("seq3(%d, %d) = %d\n", 1,1, seq3(1,1));
  printf("seq3(%d, %d) = %d\n", 2,2, seq3(2,2));
  printf("seq3(%d, %d) = %d\n", 3,3, seq3(3,3));
  printf("seq3(%d, %d) = %d\n", 4,4, seq3(4,4));
  printf("seq3(%d, %d) = %d\n", 5,5, seq3(5,5));

  // negative y constant combintations test
  //printf("Testing top row (y = -5):\n");
  printf("seq3(%d, %d) = %d\n", -5,-5, seq3(-5,-5));
  printf("seq3(%d, %d) = %d\n", -4,-5, seq3(-4,-5));
  printf("seq3(%d, %d) = %d\n", -3,-5, seq3(-3,-5));
  printf("seq3(%d, %d) = %d\n", -2,-5, seq3(-2,-5));
  printf("seq3(%d, %d) = %d\n", -1,-5, seq3(-1,-5));
  printf("seq3(%d, %d) = %d\n", 0,-5, seq3(0,-5));
  printf("seq3(%d, %d) = %d\n", 1,-5, seq3(1,-5));
  printf("seq3(%d, %d) = %d\n", 2,-5, seq3(2,-5));
  printf("seq3(%d, %d) = %d\n", 3,-5, seq3(3,-5));
  printf("seq3(%d, %d) = %d\n", 4,-5, seq3(4,-5));
  printf("seq3(%d, %d) = %d\n", 5,-5, seq3(5,-5));

  // negative x constant combinations test
  //printf("Testing leftmost column (x = -5):\n");
  printf("seq3(%d, %d) = %d\n", -5,-4, seq3(-5,-4));
  printf("seq3(%d, %d) = %d\n", -5,-3, seq3(-5,-3));
  printf("seq3(%d, %d) = %d\n", -5,-2, seq3(-5,-2));
  printf("seq3(%d, %d) = %d\n", -5,-1, seq3(-5,-1));
  printf("seq3(%d, %d) = %d\n", -5,0, seq3(-5,0));
  printf("seq3(%d, %d) = %d\n", -5,1, seq3(-5,1));
  printf("seq3(%d, %d) = %d\n", -5,2, seq3(-5,2));
  printf("seq3(%d, %d) = %d\n", -5,4, seq3(-5,3));
  printf("seq3(%d, %d) = %d\n", -5,4, seq3(-5,4));
  printf("seq3(%d, %d) = %d\n", -5,5, seq3(-5,5));

  // Note where zeros occur (-1,-3),(0,0),(1,1),(4,2),(-5, 5)
  //printf("Testing for 0's:\n");
  printf("seq3(%d, %d) = %d\n", -1,-3, seq3(-1,-3));
  printf("seq3(%d, %d) = %d\n", 0,0, seq3(0,0));
  printf("seq3(%d, %d) = %d\n", 1,1, seq3(1,1));
  printf("seq3(%d, %d) = %d\n", 4,2, seq3(4,2));
  printf("seq3(%d, %d) = %d\n", -5,5, seq3(-5,5));

  // Note @ y = 3 all seq3 values are 6
  //printf("Testing row y = 3:\n");
  printf("seq3(%d, %d) = %d\n", -5,3, seq3(-5,3));
  printf("seq3(%d, %d) = %d\n", -4,3, seq3(-4,3));
  printf("seq3(%d, %d) = %d\n", -3,3, seq3(-3,3));
  printf("seq3(%d, %d) = %d\n", -2,3, seq3(-2,3));
  printf("seq3(%d, %d) = %d\n", -1,3, seq3(-1,3));
  printf("seq3(%d, %d) = %d\n", 0,3, seq3(0,3));
  printf("seq3(%d, %d) = %d\n", 1,3, seq3(1,3));
  printf("seq3(%d, %d) = %d\n", 2,3, seq3(2,3));
  printf("seq3(%d, %d) = %d\n", 3,3, seq3(3,3));
  printf("seq3(%d, %d) = %d\n", 4,3, seq3(4,3));
  printf("seq3(%d, %d) = %d\n", 5,3, seq3(5,3));

  // MISC test
  printf("seq3(%d, %d) = %d\n", 3,-3, seq3(3,-3));
  printf("seq3(%d, %d) = %d\n", -3,-2, seq3(-3,-2));
  printf("seq3(%d, %d) = %d\n", -1,4, seq3(-1,4));
  printf("seq3(%d, %d) = %d\n", -4,4, seq3(-4,4));
  printf("seq3(%d, %d) = %d\n", 4,5, seq3(4,5));

  // Now for the countEvenInSeq3Range tests:
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0,2,0,3, countEvenInSeq3Range(0,2,0,3));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 2,0,3,0, countEvenInSeq3Range(2,0,3,0));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0,4,0,5, countEvenInSeq3Range(0,4,0,5));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", -4,4,-3,2, countEvenInSeq3Range(-4,4,-3,2));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", -5,5,-5,5, countEvenInSeq3Range(-5,5,-5,5));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", -1,3,-1,1, countEvenInSeq3Range(-1,3,-1,1));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0,0,0,0, countEvenInSeq3Range(0,0,0,0));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0,1,0,2, countEvenInSeq3Range(0,1,0,2));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0,10,0,10, countEvenInSeq3Range(0,10,0,10));

  
  return EXIT_SUCCESS;
}
