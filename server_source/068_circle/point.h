#include <math.h>

class Point{

 private:
  double x;
  double y;


 public:

  Point();  // default constructor with initialization list

  void move(double dx, double dy);

  double distanceFrom(const Point & p);

};

