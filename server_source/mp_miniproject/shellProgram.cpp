#include <cstdlib>
#include <iostream>
#include "MyShell.h"

/* Developed by Connor Grehlinger */

/*
 * This is a very simple main function for starting the shell program. 
 */



int main(void){  

  /* Create myShell object */
  MyShell myShell;

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
