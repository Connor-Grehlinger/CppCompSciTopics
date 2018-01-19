#include <stdio.h>
#include <stdlib.h>
//I've provided "min" and "max" functions in
//case they are useful to you
int min (int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max (int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

//Declare your rectangle structure here!
struct _rectangle{
  int x;
  int y;
  int width;
  int height;
  // think of 'left' as x
  // think of 'right' as x + width
  // think of 'bottom' as y
  // think of 'top' as y + height
};

typedef struct _rectangle rectangle;

rectangle canonicalize(rectangle r) {
  //WRITE THIS FUNCTION
  // insure that the width and height is non-negative
  // then adjust x and y coordinates accordingly
  if (r.width < 0){
    r.x += r.width;
    // if the width is negative you must move the x coordinate
    r.width = -r.width;
    // make the negative width a positive width
  }
  if(r.height < 0){
    r.y += r.height;
    // if the height is negative you must move the y coordinate
    r.height = -r.height;
    // make the negative height a positive height
  }
  return r;
}
  
rectangle intersection(rectangle r1, rectangle r2) {
  //WRITE THIS FUNCTION
  r1 = canonicalize(r1);
  r2 = canonicalize(r2);
  // make sure the input parameteres are valid
  int answers_x = max(r1.x,r2.x);
  int answers_y = max(r1.y,r2.y);
  // determing the answer rectangles x and y coordinates
  // remember that top = y + height and right = x + width
  
  int answers_right = min(r1.x + r1.width, r2.x + r2.width);
  
  int answers_width = answers_right - answers_x;

  int answers_top = min(r1.y + r1.height, r2.y + r2.height);

  int answers_height = answers_top - answers_y;

  if (answers_height == 0){
    rectangle answer1 = {.x = answers_x, .y = answers_y,
		      .width = answers_width, .height = answers_height};
    return answer1;
  }
  else if (answers_width == 0){
    rectangle answer2 = {.x = answers_x, .y = answers_y,
		      .width = answers_width, .height = answers_height};
    return answer2;
  }
  
  else if (answers_width <= 0 || answers_height <= 0){
    answers_width = 0;
    answers_height = 0;
    rectangle empty = {.x = answers_x, .y = answers_y,
		       .width = answers_width, .height = answers_height};
    return empty;
  }
  rectangle answer = {.x = answers_x, .y = answers_y,
		      .width = answers_width, .height = answers_height};
  return answer;
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, 
	                           r.x + r.width, r.y + r.height);
  }
}

int main (void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);
  
  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  rectangle i = intersection(r1,r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1,r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);
  
  i = intersection(r1,r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1,r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2,r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2,r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);
  
  i = intersection(r2,r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2,r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3,r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3,r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);
  
  i = intersection(r3,r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3,r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4,r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4,r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);
  
  i = intersection(r4,r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4,r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);


  return EXIT_SUCCESS;

}
