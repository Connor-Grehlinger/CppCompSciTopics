#include "point.h"
//#include <math.h>

Point::Point(): x(0), y(0){}

void Point::move(double dx, double dy){
  this->x += dx;
  this->y += dy;
}

double Point::distanceFrom(const Point & p){
  
  return sqrt( (pow((p.x - this->x),2) + pow((p.y - this->y),2)) );
}
