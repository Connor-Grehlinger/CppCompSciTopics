#include<string>

/* Developed by Connor Grehlinger */

/* Very basic reader object used only for taking raw user input */

class Reader{
private:
  
public:

  /* I realize AOP says to 'write a default constructor in every class that you write.'
   * However I'm going to keep this class trivial as it has no real special behavior or members.
   */
  
  const std::string& readInput(std::string& toBeFilled);

};
