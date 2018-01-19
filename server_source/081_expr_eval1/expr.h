#include<string>
#include<sstream>


class Expression{
  
 public:
  //Expression(std::string exp): expression(exp) {}
  //Expression(){}
  
  //Expression(long n): number(n){}
  
  virtual std::string toString() const =0;  // abstract method, not implementation 

  virtual long evaluate() =0;
  
  virtual ~Expression(){}
};

// Hilton's advice: have each class contain its actual data (number)
// leave the to_string method to handle the strings for printing 

// use string streams 

class NumExpression : public Expression {
  // turn the long passed to the constructor
  // into a NumExpression
 protected:
  std::stringstream exp;
  long number;
  // in expr.cpp, NumExpression constructed from just a long
  
 public:

  //NumExpression(){}
  
 NumExpression(long arg): number(arg){
    this->exp << arg;
  }

 NumExpression(std::string s){
    this->exp << s;
  }
  
 virtual ~NumExpression(){}

  virtual long evaluate(){
    return this->number;
  }
    
  virtual std::string toString() const{
    return exp.str();
  }


};


class PlusExpression : public Expression {

 protected:
  
  Expression * left;
  Expression * right;

  // need to construct it so it's able to have it's toString print
  // other plusExpression objects 
  
 public:

  /*
 PlusExpression(Expression * lhs, Expression * rhs): left(new NumExpression(lhs->toString())),
    right(new NumExpression(rhs->toString())){}
  */
 PlusExpression(Expression * lhs, Expression * rhs): left(lhs),
    right(rhs){}
  
  //left(lhs->evaluate()), right(rhs->evaluate()){}

  virtual ~PlusExpression(){
    delete left;
    delete right;
  }
  
  virtual long evaluate(){
    return left->evaluate() + right->evaluate();
  }
  
  virtual std::string toString() const{
    
    return "(" + left->toString() + " + " + right->toString() + ")"; 
  }
  
};

