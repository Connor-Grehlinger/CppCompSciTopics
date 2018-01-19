#include "ll.h"
#include <iostream>
#include <stdio.h>


int main(void){

  // doing LinkedList temp() creates a function named temp that returns a linked list
  // doing LinkedList temp creates a linked list named temp with the default constructor
  
  LinkedList<std::string> temp;  // test default constructor first
  temp.addFront("2");
  temp.addFront("1");
  temp.addFront("0");

  temp.print();
  
  LinkedList<std::string> t2(temp);
  t2.print();

  temp.addFront("-1");
  
  t2.addFront("-1");
  t2.addBack("3");
  std::cout << "Extracting element 0, should be '0': " << t2[0] << "\n";
  std::cout << "'1' :" << t2[1] << "\n";
  std::cout << "'2' :" << t2[2] << "\n";
  
  try{
    std::string notThere(t2[3]);
  }
  catch (std::exception & e){
    std::cout << e.what();
  }
  
  
  t2.addFront("squid");
  t2.addFront("fish");

  std::cout << "Should be 1 : " << t2.find("squid") << "\n";
  std::cout << "Should be 4 : " << t2.find("2") << "\n";

  
  
  //std::cout << "Now printing list copy: \n";  
  //t2.print();

  LinkedList<std::string> t3 = t2;

  t3.print();
  t3.addBack("sponge");
  t3.print();

  std::cout << "Removing fish, should be true: " << t3.remove("fish") << "\n";
  std::cout << "Removing wombo, should be false: " << t3.remove("wombo") << "\n";
  std::cout << "Removing sponge, should be true: " << t3.remove("sponge") << "\n";
  std::cout << "Removing 1, should be true: " << t3.remove("1") << "\n";

  t3.print();
  
  return EXIT_SUCCESS;
}
