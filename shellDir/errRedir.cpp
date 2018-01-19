#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdlib.h>




int main(int argc, char** argv){

  
  std::cout << "In errRedir, this string went to stdout" << std::endl;

  /*
  std::cout << "args passed in:\n";
  for (int i = 0; i < argc; i++){
    std::cout << "'" << argv[i] << "'" <<  std::endl;
  }
  
  std::cout << "Now testing stderr and/or stdin redirection \n";
  */
  
  std::string str;
  std::cerr << "Printing this string and the following input read from stdin to stderr \n";
  while(getline(std::cin,str)){
    //if (str != ""){
    std::cerr << str << std::endl;
      //std::cout << str + " to stdout" << std::endl;
      //}
  }








  return EXIT_SUCCESS;
}
