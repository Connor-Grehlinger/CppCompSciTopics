#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h> // for the isprint() function

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

/*
int sanitize(const char * check){
  return 0;
}
*/

// Prof Hilton's advice: sort each file seperately, not all together

char ** readFromFile(char ** fileData, size_t * numStringsPtr, FILE * f){
  char * fileLine = NULL; // for getline
  size_t fileLineSize;
  ssize_t fileLineLength;

  while ( (fileLineLength = getline(&fileLine,&fileLineSize,f)) >= 0){
    fileData = realloc(fileData, (*numStringsPtr + 1) * sizeof(*fileData));
    // re-allocates space for pointers to strings
    fileData[*numStringsPtr] = malloc((fileLineLength + 1) * sizeof(**fileData));
    // allocates space for characters in each string
    strcpy(fileData[*numStringsPtr],fileLine);
    // writes the currnt string into the current index of array of strings
    (*numStringsPtr)++;
  }
  free(fileLine);
  return fileData;
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  /*
  char ** data = malloc(sizeof(*data));
  size_t numStrings = 0;
  size_t * numStringsPtr = &numStrings;

  */
  
  if (argc == 1){
    // read from stdin
    char ** data = malloc(sizeof(*data));
    size_t numStrings = 0;
    size_t * numStringsPtr = &numStrings;

    data = readFromFile(data,numStringsPtr,stdin);
    sortData(data, (*numStringsPtr));
    for (int i = 0; i < (*numStringsPtr); i++){
      char * ptr = data[i]; // ptr points at the first character of the
      // strings at data[i];
      while (*ptr != '\0'){
	fprintf(stdout,"%c",*ptr);
	ptr++;
      }
    }
    // free memory
    for (int i = 0; i < *numStringsPtr; i++){
      free(data[i]);
    }
    free(data);
      
  }
  else if (argc > 1){
    // treat each argv[] as an input file
    for (int i = 1; i < argc; i++){
      // perform file reads, sort, then print
      char ** data = malloc(sizeof(*data));
      size_t numStrings = 0;
      size_t * numStringsPtr = &numStrings;

      FILE * f = fopen(argv[i],"r");
      if (f == NULL){
	fprintf(stderr,"Error: Could not open file\n");
	// free memory
	for (int i = 0; i < *numStringsPtr; i++){
	  free(data[i]);
	}
	free(data);
	exit(EXIT_FAILURE);
      }

      data = readFromFile(data,numStringsPtr,f);
      
      if(fclose(f) != 0){
	fprintf(stderr,"Error: Could not close the file\n");
	// free memory
	for (int i = 0; i < *numStringsPtr; i++){
	  free(data[i]);
	}
	free(data);
	exit(EXIT_FAILURE);
      }

      sortData(data, *numStringsPtr);
      // now print sorted data
      for (int i = 0; i < (*numStringsPtr); i++){
	char * ptr = data[i]; // ptr points at the first character of the
	// strings at data[i];
	while (*ptr != '\0'){
	  fprintf(stdout,"%c",*ptr);
	  ptr++;
	}
      }
      // free memory
      for (int i = 0; i < *numStringsPtr; i++){
	free(data[i]);
      }
      free(data);
      
    }
  }
  else{
    fprintf(stderr,"Error: Improper usage\n");
    exit(EXIT_FAILURE);
  }  
  return EXIT_SUCCESS;
}
