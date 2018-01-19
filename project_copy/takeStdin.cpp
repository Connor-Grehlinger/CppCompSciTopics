#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdlib.h>




int main(int argc, char** argv){


  std::cout << "Now testing stdin redirection \n";
  
  std::string str;
  while(getline(std::cin,str)){
    //if (str != ""){
    std::cout << "string from stdin is : '" <<  str << "'" << std::endl;
      //}
  }




  return EXIT_SUCCESS;
}
