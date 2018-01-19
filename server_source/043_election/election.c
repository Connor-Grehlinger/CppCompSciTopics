#include "election.h"
//include any other headers you need here...


state_t parseLine(const char * line) {
  //STEP 1: write me
  // fill a state_t struct by parsing the input string
  // <stateName>:<population>:<numberOfElectoralVotes
  // EX: Alabama:4858979:9
  if(line == NULL){
    fprintf(stderr, "Error: Improperly formatted string as input. ParseLine received NULL\n");
    exit(EXIT_FAILURE);
  }
  
  //printf("The contents of line ==>%s\n",line);

  const char * emptyStateNameCheck = line;

  if (*emptyStateNameCheck == '\0'){
    fprintf(stderr,"Error: Empty line passed in to parseLine\n");
    exit(EXIT_FAILURE);
  }
  //int length = strlen(line);
  //printf("The length yo: %d\n",length);
  const char delim[2] = ":";  // delimiter seperating state's name, pop and votes
  char * token;  // the token is the portion of the string (line) equal to
  // its name, pop, or votes; there are 3 tokens per line argument

  char strtokLine[MAX_STATE_NAME_LENGTH];  // initialize to make a copy of the line
  memset(strtokLine,'\0',sizeof(strtokLine)); // put terminating character in line's copy
  
  strcpy(strtokLine, line); // copy in the line argument

  token = strtok(strtokLine, delim); // get the first token (stateName) 
  
  //printf("Token ==>%s\n",token);
  
  if(token == NULL){
    fprintf(stderr, "Error: Improperly formatted string as input\n");
    exit(EXIT_FAILURE);
  }
  
  char stateName[MAX_STATE_NAME_LENGTH];
  uint64_t statePop;
  unsigned int stateVotes;

  memset(stateName,'\0',sizeof(stateName));

  if (*emptyStateNameCheck != ':'){ // if it's not an empty string for state name

    strcpy(stateName,token); // stateName now has the name
    token = strtok(NULL,delim); // get the next token, pop if proper format

    if(token == NULL){ // check it before doing anything
      fprintf(stderr, "Error: Improperly formatted string as input\n");
      exit(EXIT_FAILURE);
    }
    statePop = atoi(token);
    
    token = strtok(NULL,delim); // get the next token, electoral votes if proper format
    if(token == NULL){ // check before using it
      fprintf(stderr, "Error: Improperly formatted string as input\n");
      exit(EXIT_FAILURE);
    }
    stateVotes = atoi(token);
    
    token = strtok(NULL,delim); // check to ensure there are only 2 ':'s
    
    //printf("Token ==>%s\n", token);
  
    if(token != NULL){
      fprintf(stderr, "Error: Improperly formatted string as input\n");
      exit(EXIT_FAILURE);
    }
    
  }
  else {  // state name is an empty string, use one fever token
    // current token is now the population and not the name 

    if(token == NULL){ // check it before doing anything
      fprintf(stderr, "Error: Improperly formatted string as input\n");
      exit(EXIT_FAILURE);
    }
    statePop = atoi(token);
    
    token = strtok(NULL,delim); // get the next token, electoral votes if proper format
    if(token == NULL){ // check before using it
      fprintf(stderr, "Error: Improperly formatted string as input\n");
      exit(EXIT_FAILURE);
    }
    stateVotes = atoi(token);

    token = strtok(NULL,delim); // check to ensure there are only 2 ':'s
  
    //printf("Token ==>%s\n", token);
    
    if(token != NULL){
      fprintf(stderr, "Error: Improperly formatted string as input\n");
      exit(EXIT_FAILURE);
    }
    
  }
  
  state_t state;

  //printf("Name: %s\n", stateName);
  //printf("Pop: %lu\n",statePop);
  //printf("EVotes: %u\n", stateVotes);
  
  strcpy(state.name,stateName);
  state.population = statePop;
  state.electoralVotes = stateVotes;

  return state;
}


unsigned int countElectoralVotes(state_t * stateData, 
				 uint64_t * voteCounts,  
				 size_t nStates) {
  //STEP 2: write me
  // voteCounts = number of votes for candidate A
  // nStates = size of voteCounts array
  // stateData = array of state structs
  // items in the arrays are in the same order
  // stateData[0] = Alabama, voteCounts[0] = Alabama's votes for candidate A

  // Determine the total number of electoral votes for Candidate A
  // A's votes for a state = voteCounts[stateIndex]
  // B's votes for a state = stateData[stateIndex].population - voteCounts[stateIndex]
  // if (candidate A's votes > candidate B's votes) for a given state,
  // candidate A gets all electoral votes,
  // if candidate A receives exaclty 50% (A votes == B votes) then A does not get votes
  // I'm assuming B doesn't either, just discard that state

  if (stateData == NULL){
    fprintf(stderr, "Error: Array of states argument has NULL pointer\n");
    exit(EXIT_FAILURE);
  }
  if (voteCounts == NULL){
    fprintf(stderr, "Error: Array of vote counts argument has NULL pointer\n");
    exit(EXIT_FAILURE);
  }
  unsigned int AsElectoralVotes = 0;
  // go through each state
  for (int i = 0; i < nStates; i++){
    if (voteCounts[i] > stateData[i].population){
      fprintf(stderr,"Error: %lu votes for state %s is greater than population of %lu. Voter fraud has occurred.\n", voteCounts[i], stateData[i].name, stateData[i].population);
      exit(EXIT_FAILURE);
    }
    unsigned int Avotes = voteCounts[i];
    unsigned int Bvotes = stateData[i].population - Avotes;
    if (Avotes > Bvotes){
      AsElectoralVotes += stateData[i].electoralVotes;
    }
  }   
  return AsElectoralVotes;
}

void printRecounts(state_t * stateData, 
		   uint64_t * voteCounts, 
		   size_t nStates) {
  //STEP 3: write me
  // prints a float
  if (stateData == NULL){
    fprintf(stderr, "Error: Array of states argument has NULL pointer\n");
    exit(EXIT_FAILURE);
  }
  if (voteCounts == NULL){
    fprintf(stderr, "Error: Array of vote counts argument has NULL pointer\n");
    exit(EXIT_FAILURE);
  }
  float AsPercentage;
  float Avotes;
  for (int i = 0; i < nStates; i++){
    if (voteCounts[i] > stateData[i].population){
      fprintf(stderr,"Error: %lu votes for state %s is greater than population of %lu. Voter fraud has occurred.\n", voteCounts[i], stateData[i].name, stateData[i].population);
      exit(EXIT_FAILURE);
    }
    Avotes = voteCounts[i];
    AsPercentage = Avotes/stateData[i].population;
    //printf("A's percentage: %.2f%%\n",AsPercentage);
    if ((AsPercentage <= 0.505) && (AsPercentage >= 0.495)){ // if As votes in recount range
      float percentValue = AsPercentage * 100;
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
	     stateData[i].name, percentValue);
    }
  }
}


void printLargestWin(state_t * stateData, 
		     uint64_t * voteCounts, 
		     size_t nStates) {
  //STEP 4: write me
  if (stateData == NULL){
    fprintf(stderr, "Error: Array of states argument has NULL pointer\n");
    exit(EXIT_FAILURE);
  }
  if (voteCounts == NULL){
    fprintf(stderr, "Error: Array of vote counts argument has NULL pointer\n");
    exit(EXIT_FAILURE);
  }
  float AsPercentage;
  float AsPercentageMax = 0;
  char bestStateName[MAX_STATE_NAME_LENGTH];
  memset(bestStateName, '\0', sizeof(bestStateName));
  float Avotes;
  for (int i = 0; i < nStates; i++){
    if (voteCounts[i] > stateData[i].population){
      fprintf(stderr,"Error: %lu votes for state %s is greater than population of %lu. Voter fraud has occurred.\n", voteCounts[i], stateData[i].name, stateData[i].population);
      exit(EXIT_FAILURE);
    }
    Avotes = voteCounts[i];
    AsPercentage = Avotes/stateData[i].population;
    if (AsPercentage > AsPercentageMax){
      AsPercentageMax = AsPercentage;
      strcpy(bestStateName, stateData[i].name);
    }
  }
  float percentValue = AsPercentageMax * 100;
  printf("Candidate A won %s with %.2f%% of the vote\n",
	 bestStateName, percentValue);
}
