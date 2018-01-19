#include "Reader.h"
#include <iostream>

/* Developed by Connor Grehlinger */

/* Very basic functionality for Reader object. 
 * This object is more of a way of abstracting out certain 
 * functionality, in this case reading the raw input from the user. 
 */



const std::string& Reader::readInput(std::string& toBeFilled){
  getline(std::cin, toBeFilled);
  if (std::cin.eof()){ // check for EOF, exit if found
    toBeFilled = "exit";
  }
  return toBeFilled;
}
