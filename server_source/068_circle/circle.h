#include "point.h"
#include <math.h>
#include <cmath>

class Circle{

 private:
  Point center;
  const double radius;
  
 public:
  Circle(Point c, double r);

  void move(double dx, double dy);

  double intersectionArea(const Circle & otherCircle);

};
