#include "circle.h"

Circle::Circle(Point c, double r): center(c), radius(r) {}

void Circle::move(double dx, double dy){
  this->center.move(dx,dy);
}

double Circle::intersectionArea(const Circle & otherCircle){
  // find the distance between the two centers first
  double distance = this->center.distanceFrom(otherCircle.center);
  // determine the special cases of no intersection and of concentric circles
  // use M_PI for the pi constant 
  /*  if (distance <= std::abs(this->radius - otherCircle.radius)){
    if (this->radius <= otherCircle.radius){
      return (M_PI * pow(this->radius,2));
    }
    else{
      return (M_PI * pow(otherCircle.radius,2));
    }
  }
  else if (distance > (this->radius + otherCircle.radius)){
    // no intersection case
    return 0;
  }
  */
  if (distance < this->radius + otherCircle.radius){
    /*double R1 = this->radius * this->radius;
    double R2 = otherCircle.radius * otherCircle.radius;
    double x = (R1 - R2 + distance * distance) / (2 * distance);
    double z = x * x;
    double y = sqrt(R1 - z);
    */

    if (distance <= std::abs(this->radius - otherCircle.radius)){
      // one circle is within the other
      if (this->radius <= otherCircle.radius){
	return (M_PI * pow(this->radius,2));
      }
      else{
	return (M_PI * pow(otherCircle.radius,2));
      }
    }

    double distance_to_center1 = (pow(this->radius,2) - pow(otherCircle.radius,2)
				  + pow(distance,2)) / (2 * distance);
    double distance_to_center2 = distance - distance_to_center1;
    double height = sqrt(pow(this->radius, 2) - pow(distance_to_center1,2));

    double theta1 = fmod(atan2(height, distance_to_center1) * 2.0 + 2 * M_PI, 2 * M_PI);
    double theta2 = fmod(atan2(height, distance_to_center2) * 2.0 + 2 * M_PI, 2 * M_PI);

    double firstArea = pow(this->radius,2) / 2.0 * (theta1 - sin(theta1));
    double secondArea = pow(otherCircle.radius,2) / 2.0 * (theta2 - sin(theta2));

    return firstArea + secondArea;
    
    //return R1 * asin(y / this->radius) + R2 * asin(y / otherCircle.radius) - y
      //* (x + sqrt(z + R2 - R1));
  }

  return 0;
}
