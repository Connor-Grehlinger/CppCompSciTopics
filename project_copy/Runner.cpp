#include "Runner.h"
#include <iostream>
#include <unistd.h> 
#include <cstdlib>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

/* Developed by Connor Grehlinger */

/* The Runner is used for creating and running new processes
 * based on commands entered into the shell.
 * The Runner also handles redirection and pipes
 *
 * Code developed using documentation from: 
 * fork, execve, waitpid, open, close and dup2 man pages
 */

void Runner::runCommand(const std::string& command ,char * const argv[],
			char * const envp[]){
  pid_t child;
  int status;
  
  int pipeFileDescriptors[2];
  /* Check pipe creation */
  if (pipe(pipeFileDescriptors) == -1){
    std::cerr << "Error: could not create pipe\n";
  }
  /* Pipe created here so both parents and child have access */

  /* Create new process copy */
  child = fork(); 

  if (child < 0){ 
    std::cerr << "Error forking child process: " << command << "\n";
    /* Not calling exit(EXIT_FAILURE) here or above since the shell can always try to
       run another program or modify the one it was trying to run */
  }
  
  /* Child process code */
  if (child == 0){
    int fileDescriptor;
    
    for (int i = 0; argv[i] != NULL; i++){
      
      if (*argv[i] == '<'){ // redirect stdin
	if (argv[i + 1] != NULL){ // make sure filename exists
	  char * file = argv[i + 1];
	  /* Open file and check for error */
	  if ((fileDescriptor = open(file, O_RDONLY)) == -1){
	    std::cerr << "Error: cannot open input file for stdin redirection\n";
	    exit(EXIT_FAILURE);
	  }
	  else{
	    dup2(fileDescriptor, 0); // redirect stdin to file
	    close(fileDescriptor);
	  }
	}
	else{
	  std::cerr << "Error: must name a file for stdin redirection\n";
	  exit(EXIT_FAILURE);
	}
      }
      else if(*argv[i] == '>'){ //redirect stdout
	if (argv[i + 1] != NULL){
	  char * file = argv[i + 1];
	  if ((fileDescriptor = open(file, O_WRONLY | O_CREAT | O_TRUNC,
				     S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1){
	    std::cerr << "Error: cannot open output file for stdout redirection\n";
	    exit(EXIT_FAILURE);
	  }
	  else{
	    dup2(fileDescriptor, 1); // redirect stdout to file
	    close(fileDescriptor);
	  }
	}
	else{
	  std::cerr << "Error: must name a file for stdout redirection\n";
	  exit(EXIT_FAILURE);
	}
      }
      else if(*argv[i] ==  '2' && argv[i][1] == '>' ){ //redirect stderr
	if (argv[i + 1] != NULL){
	  char * file = argv[i + 1];
	  if ((fileDescriptor = open(file, O_WRONLY | O_CREAT | O_TRUNC,
				     S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1){
	    std::cerr << "Error: cannot open output file for stderr redirection\n";
	    exit(EXIT_FAILURE);
	  }
	  else{
	    dup2(fileDescriptor, 2); // redirect stderr to file
	    close(fileDescriptor);
	  }
	}
	else{
	  std::cerr << "Error: must name a file for stderr redirection\n";
	  exit(EXIT_FAILURE);
	}
      }
      else if(*argv[i] == '|'){
	if (argv[i + 1] != NULL){	  
	  close(pipeFileDescriptors[0]); // close reading end, child only writes
	  dup2(pipeFileDescriptors[1],1); //redirect stdout of child to input of pipe
	  close(pipeFileDescriptors[1]);
	}
      }
    }

    if (execve(command.c_str(), argv, envp) == -1){ 
      std::cerr << "Error running child process: " << command << "\n";
    }
    exit(EXIT_FAILURE);
  }
  /* Parent process code */
  else{   
    do { /* Wait for the child process to complete */

      /* Developed from waitpid man page */
      pid_t parent = waitpid(child, &status, WUNTRACED | WCONTINUED);
      /* status contains info about how the child process terminated */
      if (parent == -1){
	std::cerr << "Error on waitpid call for command: " << command << "\n";
	exit(EXIT_FAILURE);
      }
      // Wait for first process to be over then attempt to read from the pipe

      for (int i = 0; argv[i] != NULL; i++){
	if (*argv[i] == '|'){
	  if (argv[i+1] != NULL){ // if pipe command and process exists to read from it
	    
	    size_t len = 0;	    
	    for (size_t sz = i + 1; argv[sz] != NULL; sz++){ // find remaining size  
	      len++;
	    }
	    
	    int oldArgvIndex = i + 1;
	    // len is the length of the remaining argv (other processes total argv)
	    char ** newArgv = new char *[len + 1]; // + 1 to NULL terminate
	    for (size_t i = 0; i < len; i++){
	      newArgv[i] = argv[oldArgvIndex];
	      oldArgvIndex++;
	    }
	    newArgv[len] = NULL; // NULL terminate

	    /* Create new process copy */
	    child = fork();
	    
	    if (child < 0){ 
	      std::cerr << "Error forking child process: " << command << "\n";
	      exit(EXIT_FAILURE);
	    }
	    
	    /* Child process code */
	    if (child == 0){
	      close(pipeFileDescriptors[1]); // close write pipe
	      dup2(pipeFileDescriptors[0], 0);
	      close(pipeFileDescriptors[0]);
	      
	      if (execve(newArgv[0], newArgv, envp) == -1){ 
		std::cerr << "Error running child process: " << newArgv[0] << "\n";
	      }
	      exit(EXIT_FAILURE);
	    }
	    else{ /* Parent process */

	      close(pipeFileDescriptors[1]);
	      close(pipeFileDescriptors[0]);

	      pid_t parent = waitpid(child, &status, WUNTRACED | WCONTINUED);
	      /* status contains info about how the child process terminated */
	      if (parent == -1){
		std::cerr << "Error on waitpid call for command: " << command << "\n";
		exit(EXIT_FAILURE);
	      }
	      delete[] newArgv;
	    }
	  }
	}
      }
      
      if (WIFEXITED(status)){
	std::cout << "Program exited with status " << WEXITSTATUS(status) << "\n";
      }
      else if (WIFSIGNALED(status)){
	std::cout << "Program was killed by signal " << WTERMSIG(status) << "\n";
      }
      else if (WIFSTOPPED(status)){
	std::cout << "Program was killed by signal "<< WSTOPSIG(status) << "\n";
      }
      else if (WIFCONTINUED(status)){
	std::cout << "Continued.. \n";
      }
    } while(!WIFEXITED(status) && !WIFSIGNALED(status));
  }
}
