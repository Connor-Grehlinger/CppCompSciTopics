#include<string>
#include<vector>
#include "Parser.h"
#include "Runner.h"
#include<map>

/* Developed by Connor Grehlinger */

/* MyShell is the main object of the shell miniproject, and where all the 
 * control logic is placed. 
 */

class MyShell{
private:

  Parser parser;

  Runner runner;

  std::vector<std::string> commandToExe;

  std::vector<std::string> variableInfo;

  char * workingDir;

  std::map<std::string,std::string> variableMap;
  
  char ** environ;

public:

  MyShell();
  
  MyShell(char ** envi);

  ~MyShell();

  MyShell(const MyShell& otherShell);

  MyShell& operator= (const MyShell& rhs);
  
  std::string scanDirectory(std::string dirName, std::string command);
  
  bool variableParse();

  bool varLookupCheck(std::string var);

  void changeDir(std::string dirName);

  void addVariable();

  void start();

  bool exitCheck(std::vector<std::string> command);
  
  void quit();

  void wait();

  void dispatch();

  void run();

  void printVars();

  bool variableCheck();

  void modifyEnv(std::string var);
};

