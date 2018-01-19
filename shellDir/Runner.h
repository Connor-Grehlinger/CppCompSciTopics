#include <string>

/* Developed by Connor Grehlinger */

/* Runner object which is responsible for creating and runnning new processes.
 * The Runner also handles redirection and pipes
 */

class Runner{
private:
  
public:

  /* I know AOP says 'write a default constructor in every class the you write.' However
   * this runner class is very basic and compiler-provided constructor/destructor are fine
   */
  
  void runCommand(const std::string& command, char * const argv[], char * const envp[]);
  
};
