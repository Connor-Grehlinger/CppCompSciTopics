#include "Parser.h"
#include <iostream>
#include <sstream>

/* Developed by Connor Grehlinger */

/* The Parser is used for parsing the raw input it gets from the Reader
 * and also for various pasing tasks needed by the shell.
 *
 * Code developed with help from cplusplus.com/reference: stringstream, pair 
 */


/* For parsing the shell's environment */
std::vector<std::pair<std::string, std::string> > Parser::parseEnvironment(char ** envi, char delimiter){
  std::vector<std::pair<std::string, std::string> > environment;
  for (int i = 0; envi[i] != NULL; i++){
    std::string enviVar(envi[i]);
    size_t varNameEnd = enviVar.find_first_of("=");
    std::pair <std::string, std::string> currPair(enviVar.substr(0, varNameEnd),
						  enviVar.substr(varNameEnd + 1));
    environment.push_back(currPair);
  }
  return environment;
}


/* Overall parsing function, returns a pair containing the parses for 
 * usual input and set command and can handle whitespace */
std::pair<std::vector<std::string>,std::vector<std::string> > Parser::parse(std::vector<std::string>& toBeFilled, std::vector<std::string>& toBeFilledVar, char delimiter){
  /* Read input from user */
  std::string input;
  input = this->reader.readInput(input);

  /* Parse the input for setting variable */
  toBeFilledVar = this->getVarAndValue(toBeFilledVar, input);
  
  std::istringstream inputStream(input);
  
  /* Parse input stringstream, one char at a time to handle whitespace */
  char c;
  char previous = ' '; 
  char secondPrevious = ' ';
  std::stringstream currentCommand;

  while (inputStream.get(c)){
    if (c == ' '){ // if whitespace
      if (previous == '\\'){ // if previous char was a '\' add whitespace
	currentCommand << c;
	previous = c;
	secondPrevious = '\\';
      }
      else{
	if (secondPrevious != ' '){
	  toBeFilled.push_back(currentCommand.str());
	  currentCommand.str(std::string()); // clear
	}
	previous = c;
	secondPrevious = c;
      }
    }
    else{  // add until whitespace is reached
      if (c != '\\'){
	currentCommand << c; // add if not '\' character 
      }
      previous = c; // set previous values
      secondPrevious = c; 
    }
  }

  if (previous != ' '){ // get last input from user
    toBeFilled.push_back(currentCommand.str());
  }

  std::pair<std::vector<std::string>,std::vector<std::string> > parseInfo;
  parseInfo = std::make_pair(toBeFilled, toBeFilledVar);
  return parseInfo;
}


/* parseInput function that takes in the shell's PATH variable */
std::vector<std::string>& Parser::parseInput(std::vector<std::string>& toBeFilled,
					     char delimiter, char * shellPath){
  std::string command;
  std::istringstream inputStream(shellPath);
  while (std::getline(inputStream, command, delimiter)){
    toBeFilled.push_back(command);
  }
  return toBeFilled;
}

/* Helper function for getting varible's name and value from raw input on 'set' command */
std::vector<std::string>& Parser::getVarAndValue(std::vector<std::string>& toBeFilled,
						 std::string input){
  size_t start = input.find_first_of(" ");
  size_t varNameEnd = input.find_first_of(" ", start + 1);
  toBeFilled.push_back(input.substr(start + 1, (varNameEnd - start - 1)));  // variable name
  std::string valueCandidate = input.substr(varNameEnd + 1);
  if (varNameEnd == std::string::npos){ // case of 'set a' which should map a to empty string
    valueCandidate.clear();
  }
  toBeFilled.push_back(valueCandidate);  // variable value
  return toBeFilled;
}

/* Helper function for getting path to executable */
std::string Parser::getCommandPath(std::string command){
  size_t subStringEnd = command.find_last_of("/");
  return command.substr(0, subStringEnd);
}

/* Helper function for getting executable from path */
std::string Parser::getCommandExe(std::string command){
  size_t subStringBegin = command.find_last_of("/");
  return command.substr(subStringBegin+1);
}

