#include "MyShell.h"
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <sstream>

/* Developed by Connor Grehlinger */

/* MyShell is the main object for the shell, it contains all control
 * logic and has the main 'while(true)' program loop.
 *
 * Code developed with help from:
 * get_current_dir_name, chdir, getenv/setenv and opendir/closedir man pages.
 */

#define NOT_FOUND "_NOT_FOUND_"


typedef struct dirent dirent_t;

MyShell::MyShell():workingDir(NULL/*get_current_dir_name()*/){
  /* Put the environment variables into variableMap at construction */
  /*
  std::vector<std::pair<std::string, std::string> > environment =
    this->parser.parseEnvironment(getenv("PATH"),':');
  for (size_t i = 0; i < environment.size(); i++){
    this->variableMap[environment[i].first] = environment[i].second;
  }
  */
  //std::cout << "Started new shell!" << std::endl;
}

MyShell::MyShell(char ** envi):environ(envi){
  /* Put the environment variables into variableMap at construction */
  std::vector<std::pair<std::string, std::string> > environment =
    this->parser.parseEnvironment(environ,'=');

  for (size_t i = 0; i < environment.size(); i++){
    this->variableMap[environment[i].first] = environment[i].second;
  }
  this->workingDir = new char[256]();
  this->workingDir = getcwd(this->workingDir,256);

  //std::cout << "Started new shell!" << std::endl;                                              
}



MyShell::~MyShell(){
  free(workingDir); // get_current_dir_name() dynamically allocates 
}

/* Copy constructor for Shell object, its non-trivial */
MyShell::MyShell(const MyShell& otherShell):commandToExe(otherShell.commandToExe),
					    variableInfo(otherShell.variableInfo),
					    workingDir(NULL/*get_current_dir_name()*/),
					    variableMap(otherShell.variableMap){}

/* Copy assignment operator */
MyShell& MyShell::operator=(const MyShell& rhs){
  if (this != &rhs){
    MyShell temp(rhs);
    std::swap(temp, *this);
  }
  return *this;
}



/* Start the shell program */
void MyShell::start(){
  this->wait();
}

/* Shell sits idle and collects user input */
void MyShell::wait(){
  while (true){
    /* Clear contents from old command parses */
    this->commandToExe.clear();
    this->variableInfo.clear();

    /* Shell prompt that the user sees */
    std::cout << "myShell:" << workingDir << " $ ";

    /* Collect user input */
    std::pair<std::vector<std::string>, std::vector<std::string> > parses =
      this->parser.parse(this->commandToExe, this->variableInfo, ' '); 

    if (parses.first.size() == 0){ // user just hit enter or multiple spaces only then enter
      continue;  // do nothing, just like bash 
    }
    
    if (!(this->exitCheck(parses.first))){  
      this->commandToExe = parses.first;
      this->variableInfo = parses.second;
      this->dispatch();
    }
    else{
      this->quit();
      /* The member function quit() is just a return statement 
       * in a void function, it is used here mainly for readability.
       * The return statement below actually terminates the shell. */
      return;
    }
  }
}

bool MyShell::exitCheck(std::vector<std::string> command){
  if (command[0] == "exit"){
    return true;
  }
  else{
    return false;
  }
}
    

/* Helper function for finding commands in the shells PATH environment variable */
std::string MyShell::scanDirectory(std::string dirName, std::string command){
  dirName = dirName + "/";
  DIR* currentDirStream = opendir(dirName.c_str());
  if (currentDirStream == NULL){ /* Failed to open directory */
    return NOT_FOUND;
  }
  /* From readdir man page */
  dirent_t * entity;
  while (currentDirStream){ /* While directory stream is still valid */
    if ((entity = readdir(currentDirStream)) != NULL){
      if (entity->d_name[0] == '.'){ /* omit current dir and parent dir */
	continue;
      }
      else if (std::string(entity->d_name) == command){
	/* Return the command appended to the appropriate path */
	closedir(currentDirStream);
	return dirName + command;
      }
    }
    else {
      closedir(currentDirStream);
      return NOT_FOUND;
    }
  }
  return NOT_FOUND;
}

/* Function for replacing variables 
 * This function resides in the shell object because 
 * the shell object has the map of variable names and 
 * values. If time permitted would have abstracted this  
 * task out to the parser. 
 */
bool MyShell::variableParse(){
  for (size_t i = 0; i < this->variableInfo.size(); i++){
    size_t varNameBegin = this->variableInfo[i].find_first_of("$");

    while (varNameBegin != std::string::npos){

      if (varNameBegin != std::string::npos){ // if string is a variable
	size_t varNameEnd = this->variableInfo[i].find_first_of(" ", varNameBegin);

	if (varNameEnd == std::string::npos){ // if no space was found
	  std::string s = this->variableInfo[i].substr(varNameBegin + 1);

	  if (s[s.length() - 1] == '\\'){
	    s.resize(s.length() - 1);
	  }

	  if (varLookupCheck(s)){
	    this->variableInfo[i] = this->variableInfo[i].substr(0,varNameBegin) +
	      this->variableMap[s];
	    
	  }
	  else{
	    std::cerr << "Error: " << s << " is not a declared variable \n";
	    return false;
	  }
	}
	else{
	  std::string str = this->variableInfo[i].substr(varNameBegin + 1, varNameEnd - varNameBegin - 1);
	  if (str[str.length() - 1] == '\\'){
	    str.resize(str.length() - 1);
	  }

	  if (varLookupCheck(str)){
	    this->variableInfo[i] = this->variableInfo[i].substr(0,varNameBegin) +
	      this->variableMap[str] + this->variableInfo[i].substr(varNameEnd);
	  }
	  else{
	    std::cerr << "Error: " << str << " is not a declared variable \n";
	    return false;
	  }
	}
      }
      varNameBegin = this->variableInfo[i].find_first_of("$");
    }
  }
  
  for (size_t i = 0; i < this->commandToExe.size(); i++){  
    size_t varNameBegin = this->commandToExe[i].find_first_of("$");

    while (varNameBegin != std::string::npos){

      if (varNameBegin != std::string::npos){ // contains a variable 
	size_t varNameEnd = this->commandToExe[i].find_first_of(" ", varNameBegin);

	if (varNameEnd == std::string::npos){ // if no space was found	
	  std::string s = this->commandToExe[i].substr(varNameBegin + 1);

	  if (s[s.length() - 1] == '\\'){
	    s.resize(s.length() - 1);
	  }

	  if (varLookupCheck(s)){
	    this->commandToExe[i] = this->commandToExe[i].substr(0,varNameBegin) +
	      this->variableMap[s];
	  }
	  else{
	    std::cerr << "Error: " << s << " is not a declared variable \n";
	    return false;
	  }
	}
	else{
	  std::string str = this->commandToExe[i].substr(varNameBegin + 1, varNameEnd - varNameBegin - 1);
	  if (str[str.length() - 1] == '\\'){
	    str.resize(str.length() - 1);
	  }

	  if (varLookupCheck(str)){
	    this->commandToExe[i] = this->commandToExe[i].substr(0,varNameBegin) +
	      this->variableMap[str] + this->commandToExe[i].substr(varNameEnd);
	  }
	  else{
	    std::cerr << "Error: " << str << " is not a declared variable \n";
	    return false;
	  }
	}
      }
      varNameBegin = this->commandToExe[i].find_first_of("$",varNameBegin + 1);
    }
  }
  return true;
}

/* Helper function which checks whether or not a variable is in the Shell's variable map
 * Used to ensure bad entries are not added to the variable map while variable parsing 
 *
 */
bool MyShell::varLookupCheck(std::string var){
  return this->variableMap.count(var);
}


/* Change the shell's current directory */
void MyShell::changeDir(std::string dirName){
  if (chdir(dirName.c_str()) != 0){
    std::cerr << "cd: " << dirName << ": no such directory \n";
    return;
  }
  free(workingDir);
  this->workingDir = NULL;//get_current_dir_name();
}

/* Ensure only valid variables are set by the user */
bool MyShell::variableCheck(){
  std::istringstream variableVal(this->variableInfo[0]);
  char c;
  while (variableVal.get(c)){
    if (!isalnum(c) && c != '_'){
      return false;
    }
  }
  return true;
}

/* Add variable to shell's variable map data structure */
void MyShell::addVariable(){
  if (this->variableCheck()){
    this->variableMap[this->variableInfo[0]] = this->variableInfo[1];
    //this->printVars();  // for debugging, shows the variable map each time variable is set
  }
  else{
    std::cerr << "Invalid variable: please use only letters, numbers, and underscores \n";
  }
  return;
}

/* Modify shell environment */
void MyShell::modifyEnv(std::string var){
  if (setenv(var.c_str(), this->variableMap[var].c_str(), 1) != 0){
    std::cerr << "Environment variable could not be added\n";
  }
  return;
}  

/* Dispatch command */
void MyShell::dispatch(){
  /* Redirect if changing directory */
  if (this->commandToExe[0] == "cd"){
    if (this->variableParse()){
      this->changeDir(this->commandToExe[1]);
    }
  }
  /* Redirect if setting variable */
  else if (this->commandToExe[0] == "set"){
    if (this->variableParse()){
      this->addVariable();
    }
  }
  /* Redirect of adding to environment */
  else if (this->commandToExe[0] == "export"){
    if (this->variableParse()){
      this->modifyEnv(this->commandToExe[1]);
    }
  }
  else if (this->commandToExe[0] == "print_vars"){
    this->printVars();
  }
  /* Other run a standard command */
  else{
    if (this->variableParse()){
      this->run();
    }
  }
  return;
}

/* Function for executing commands */
void MyShell::run(){

  /* Check if command has a specified path */
  std::string searchCommand = "";
  if ((this->commandToExe[0][0] != '.') && (this->commandToExe[0][0] != '/')){
    /* If command doesn't start with a '/' or a '.' */
    
    /* Get the directories to search from the Shell's PATH environment variable */
    std::vector<std::string> paths;
    paths = this->parser.parseInput(paths, ':', getenv("PATH"));

    for (unsigned i = 0; i < paths.size(); i++){
      if ((searchCommand = this->scanDirectory(paths[i], this->commandToExe[0])) != NOT_FOUND){
	this->commandToExe[0] = searchCommand; /* replace with path and appended command */
	break;
      }
    }
  }
  else{
    /* Command starts with '/' or '.' */
    std::string pathToSearch = this->parser.getCommandPath(this->commandToExe[0]);
    
    std::string ExeToFind = this->parser.getCommandExe(this->commandToExe[0]);
    searchCommand = this->scanDirectory(pathToSearch, ExeToFind);
  }

  /* Check if the command was found somewhere in the PATH */
  if (searchCommand == NOT_FOUND){
    std::cout << "Command " << this->commandToExe[0] << " not found\n";
    return;
  }
  
  /* Set the list of arguments for the new process */
  size_t argvSize = this->commandToExe.size();
  char ** argv = new char *[argvSize + 1];
  for (size_t i = 0; i < argvSize; i++){
    argv[i] = strdup(this->commandToExe[i].c_str());
  }
  /* Must be NULL terminated */
  argv[argvSize] = NULL;
  
  /* Pass in command, args and environment for new process */
  this->runner.runCommand(this->commandToExe[0], argv, /*envi environ*/this->environ);
  
  
  /* Delete argv */
  for (size_t i = 0; i < argvSize; i++){
    free(argv[i]); /* strdup uses malloc */
  }
  delete[] argv;
  
  return;
}


/* Terminate shell program */
void MyShell::quit(){
  return;
}


/* Print for debugging */
void MyShell::printVars(){
  for (std::map<std::string,std::string>::iterator it = variableMap.begin();
       it != variableMap.end(); ++it){
    std::cout << "variable: (" << it->first << "), value: (" << it->second << ")" << std::endl;
  }
}
