#include<iostream>
#include"bstset.h"
#include<stdlib.h>



int main(void){


  
  std::cout << "----------Beginning BstMap tests----------\n";
  
  BstSet<int> test(0);
  test.add(3);
  test.add(-88);
  test.add(20);
  for (int i = 4; i < 20; i++){
    test.add(i+2);
  }
  test.print();

  BstSet<int> copy(test);
  copy.print();

  BstSet<int> copy2 = copy;
  
  /*
  try{
    std::cout << "----------Beginning BstMap tests----------\n";
    
    BstMap<int,int> test(0,1);
    test.add(3,3);
    test.add(-88,90);
    test.add(20,21);
    for (int i = 4; i < 20; i++){
      test.add(i,i+2);
    }
    int s = test.lookup(19);
    std::cout << "lookup for key 19: " << s << "\n";
    int s1 = test.lookup(-2009);
    std::cout << "lookup for key -2009: " << s1 << "\n";
  }
  
  catch (std::invalid_argument &e){
    std::cout << "In the block.\n";
    std::cout << e.what();
  }
  
  */

  /*x/
  
  BstMap<int,std::string> testMap1;
  testMap1.add(7,"seven");
  testMap1.add(2,"two");
  testMap1.add(5,"five");
  testMap1.add(6,"six");
  testMap1.add(1,"one");
  testMap1.add(9,"nine");
  testMap1.add(3,"three");

  BstMap<int, std::string> copy1 = testMap1;
  copy1.print();
  
  //testMap1.print();
  //std::string str = testMap1.lookup(7);
  
  //std::cout << "lookup for key 7: " << str << "\n";
  //std::string str2 = testMap1.lookup(3);
  //std::cout << "lookup for key 3: " << str2 << "\n";
  //testMap1.print();

  testMap1.remove(7);
  std::cout << "Removing 7 (the root) from tree\n";
  //testMap1.print();

  testMap1.remove(1);
  testMap1.remove(9);
  testMap1.remove(3);
  testMap1.remove(5);
  testMap1.remove(2);
  //testMap1.print();
  
  
  testMap1.add(17, "seventeen");
  testMap1.add(-20, "negative twenty");
  for (int i = 90; i < 191; i++){
    testMap1.add(i, "<>");
  }

  BstMap<int, std::string> otherMap = testMap1;
  */
  BstSet<int> src;
  BstSet<int> dest;
  dest = src;

  for (int cuck = 0; cuck < 40; cuck++){
    dest.add(cuck);
  }
  bool result = dest.contains(37);

  dest.remove(20);
  result = dest.contains(20);
  
  std::cout << result << "\n";
  
  

  /*
  BST<int, std::string> testMap;
  testMap.add(7,"seven");
  testMap.add(2,"two");
  testMap.add(5,"five");
  testMap.add(6,"six");
  testMap.add(1,"one");
  testMap.add(9,"nine");
  testMap.add(3,"three");
  testMap.print();

  std::string str1 = testMap.getValueFromKey(2);
  std::cout << "lookup for key 2: " << str1 << "\n";
  */

  return EXIT_SUCCESS;
}
