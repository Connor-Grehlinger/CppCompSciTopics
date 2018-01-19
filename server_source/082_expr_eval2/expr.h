#include<string>
#include<sstream>


class Expression{
  
 public:
  
  virtual std::string toString() const =0;  // abstract method, not implementation 

  virtual long evaluate() =0;
  
  virtual ~Expression(){}
};

// Hilton's advice: have each class contain its actual data (number)
// leave the to_string method to handle the strings for printing 

// use string streams 

class NumExpression : public Expression {
 protected:
  std::stringstream exp;
  long number;
  // in expr.cpp, NumExpression constructed from just a long
  
 public:
 
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

 public:
  
 PlusExpression(Expression * lhs, Expression * rhs): left(lhs),
    right(rhs){}
  
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

class MinusExpression : public Expression {
 protected:
  Expression * left;
  Expression * right;
 public:
 MinusExpression(Expression * lhs, Expression * rhs): left(lhs), right(rhs){}

  virtual ~MinusExpression(){
    delete left;
    delete right;
  }

  virtual long evaluate(){
    return left->evaluate() - right->evaluate();
  }
  
  virtual std::string toString() const{
    return "(" + left->toString() + " - " + right->toString() + ")"; 
  }
};

class TimesExpression : public Expression {
 protected:
  Expression * left;
  Expression * right;
 public:
 TimesExpression(Expression * lhs, Expression * rhs): left(lhs), right(rhs){}

  virtual ~TimesExpression(){
    delete left;
    delete right;
  }

  virtual long evaluate(){
    return left->evaluate() * right->evaluate();
  }
  
  virtual std::string toString() const{
    return "(" + left->toString() + " * " + right->toString() + ")"; 
  }
};

class DivExpression : public Expression {
 protected:
  Expression * left;
  Expression * right;
 public:
 DivExpression(Expression * lhs, Expression * rhs): left(lhs), right(rhs){}

  virtual ~DivExpression(){
    delete left;
    delete right;
  }

  virtual long evaluate(){
    return left->evaluate() / right->evaluate();
  }
  
  virtual std::string toString() const{
    return "(" + left->toString() + " / " + right->toString() + ")"; 
  }
};
