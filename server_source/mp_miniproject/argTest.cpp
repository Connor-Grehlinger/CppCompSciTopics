#include <iostream>
#include <stdlib.h>




int main(int argc, char** argv){


  std::cout << "In the argTest program, printing arguments to stdout (cout): \n";
  
  for (int i = 0; i < argc; i++){
    std::cout << "'" << argv[i] << "'" <<  std::endl;
  }


  return EXIT_SUCCESS;
}
