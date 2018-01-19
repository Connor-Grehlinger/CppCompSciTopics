#include <cstdlib>
#include <iostream>
#include "MyShell.h"
#include <type_traits>

/* Developed by Connor Grehlinger */

/*
 * This is a very simple main function for starting the shell program. 
 */



int main(int argc, char ** argv, char ** envp){  

  
  for (int i = 0; envp[i] != NULL; i++){
    //std::cout << envp[i] << std::endl;
  }
  //Reader reader;
  //Parser parser;
  //Runner runner;
  /*
  std::cout << std::boolalpha;
  std::cout << "Is reader POD? " << std::is_pod<Reader>::value << std::endl;
  std::cout << "Is parser POD? " << std::is_pod<Parser>::value << std::endl;
  std::cout << "Is runner POD? " << std::is_pod<Runner>::value << std::endl;
  std::cout << "Is parser trivial? " << std::is_trivial<Parser>::value << std::endl;
  */

  /* Create myShell object */
  //MyShell myShell;
  MyShell myShell(envp);

  /* Run shell program */
  myShell.start();


  /* // Below was just a test of the 
     // copy constructor and copy assignment operator

  MyShell otherShell(myShell);
  otherShell.start();

  MyShell s = otherShell;
  s.start();
  */
  
  return EXIT_SUCCESS;
}
