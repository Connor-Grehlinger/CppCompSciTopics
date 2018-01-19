#include <stdio.h>
#include <stdlib.h>

class MyClass {
private:
  int x;
  int y;
public:
  void setPoints(int newx, int newy) { 
    x = newx;
    y = newy;
  }
  void doStuff(const MyClass & p);
  int computeSomething() const {
    return x *3 + y -2;
  }
};

void printMessage(const MyClass * m1) {
  printf("%p has %d\n", m1, m1->computeSomething());
}
void MyClass::doStuff(const MyClass & p) {
  x = p.y + 3;
  y = p.x - 4;
  printMessage(this);
  printMessage(&p);
}

int main(void) {
  MyClass a;
  MyClass b;
  MyClass c;
  a.setPoints(1,1);
  b.setPoints(22,40);
  c.setPoints(9,3);
  a.doStuff(b); // a.x = 40 + 3 = 43, a.y = 22 - 4 = 18; a has (43 * 3) + (18 - 2) = 129 + 16 = 145
  b.doStuff(c); // b.x = 3 + 3 = 6, b.y = 9 - 4 = 5; b has (6 * 3) + (5 -2) = 21
  c.doStuff(a); // c.x = 18 + 3 = 21, c.y = 43 - 4 = 39; c has (21 * 3) + (39 - 2) = 100
  return EXIT_SUCCESS;
}
