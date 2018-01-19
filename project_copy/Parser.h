#include <vector>
#include <string>
#include "Reader.h"

/* Developed by Connor Grehlinger */

/* Parser object, which is responsible for parsing output from the Reader and 
 * other tasks the shell may need performed
 */

class Parser{
private:
  /* Reader is trivial, therfore will keep this class trivial as well and use compiler-provided 
   * constructor and destructor
   */
  
  Reader reader;

public:

  /* For parsing shell's environment variable, can parse with any delimiter */
  std::vector<std::pair<std::string, std::string> > parseEnvironment(char ** envi, char delimiter);

  /* Parse to find the paths in the shell's Path environment variable */ 
  std::vector<std::string>& parseInput(std::vector<std::string>& toBeFilled, char delimiter, char * shellPath);

  std::string getCommandPath(std::string command);

  std::string getCommandExe(std::string command);

  
  std::vector<std::string>& getVarAndValue(std::vector<std::string>& toBeFilled, std::string input);

  /* Main parsing function that does two parses of user input for 
   * reading different types of commands */
  std::pair<std::vector<std::string>, std::vector<std::string> > parse(std::vector<std::string>& toBeFilled, std::vector<std::string>& toBeFilledVar, char delimiter);

};

  
