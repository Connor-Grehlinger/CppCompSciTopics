#include "hashmap.h"  // custom templated hash map class like from AOP
// hashmap.h has all other necessary includes




// --- Testing helper functions if there are any ---






// --- Main function for testing ---

int main(int argc, char ** argv){

  for (int i = 1; i < argc; i++){
    // for now:
    std::cout << argv[i] << "\n";
  }
  

  // --- Testing constructor and adding to hash map ---
  HashMap<int, std::string, std::hash<int>> testMap(1); // start with size 1 to test resize
  
  for (int i = 1; i < argc; i++){
    // for now:
    testMap.add(i,argv[i]);
    
  }

  std::cout << "Check if keys are present, should be all true except for last two: \n";
  for (int i = 1; i < argc + 2; i++){
    // for now:
    std::cout <<  testMap.isEmptyBucket(i) << "\n";
    
  }

  /*
  HashMap<int,int,std::hash<int>> largerTest(0);
  for (int k = -10; k < 1000000; k++){
    largerTest.add(k,-k);
  }
  */
  






  return EXIT_SUCCESS;
}

