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
  virtual ~SinFunction() {}
  
};
// Should return 52359 in fewer than 20 invocations

class AlwaysNeg : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return -5;
  }
  virtual ~AlwaysNeg() {}
};
// should return high -1

class AlwaysPos : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return 5;
  }
  virtual ~AlwaysPos() {}
};
// should return the low range 

class Zero : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return 0;
  }
  virtual ~Zero() {}
};
// more functions can be added here if needed:

class Funct1 : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return arg - 1;
  }
  virtual ~Funct1() {}
};

class Funct2 : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return arg - 0.5;
  }
  virtual ~Funct2() {}
};

class Funct3 : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return arg - 100;
  }
  virtual ~Funct3() {}
};

class Funct4 : public Function<int, int>{
 public:
  virtual int invoke(int arg){
    return -arg - 100;
  }
  virtual ~Funct4() {}
};

#endif
