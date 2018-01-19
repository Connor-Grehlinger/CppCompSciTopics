#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include<math.h>

template<typename R, typename A> 
class Function {
public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};


class SinFunction : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};
// Should return 52359 in fewer than 20 invocations

class AlwaysNeg : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return -5;
  }
};
// should return high -1

class AlwaysPos : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return 5;
  }
};
// should return the low range 

class Zero : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return 0;
  }
};
// more functions can be added here if needed:

class Funct1 : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return arg - 1;
  }
};

class Funct2 : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return arg - 0.5;
  }
};

class Funct3 : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return arg - 100;
  }
};

class Funct4 : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return -arg - 100;
  }
};

#endif
