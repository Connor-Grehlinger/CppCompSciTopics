#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL){
    freeKVs(kvPairs);
    fprintf(stderr,"Error: Could not open file\n");
    exit(EXIT_FAILURE);
  }
  // kvPairs has your list of keys
  counts_t * c = createCounts();
  // count the number of values for each key that occurs in the file

  // go throught the file you open
  // extract each key, pass the key into lookupValue
  char * line = NULL;
  size_t sz = 0;
  ssize_t len;
  while ( (len = getline(&line,&sz,f)) >= 0){
    if (line == NULL || (strchr(line,'\n') == NULL)){
      fprintf(stderr,"Error: Improper format\n");
      freeKVs(kvPairs);
      freeCounts(c);
    }
    line[strlen(line) -1] = '\0';
    addCount(c,lookupValue(kvPairs,line));
    
  }
  free(line);
  if (fclose(f) != 0){
    freeKVs(kvPairs);
    freeCounts(c);
    fprintf(stderr,"Error: Could not close file\n");
    exit(EXIT_FAILURE);
  }
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++){
    // count the values that appear in the file named by argv[i],
    // using kv as the key/value pair (call this result c)
    // lookupValue returns a value associated with a key from kv
    counts_t * c = countFile(argv[i],kv);

    // compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    
    //open the file named by outName (call that f)
    FILE * f = fopen(outName,"w");
    if (f == NULL){
      freeKVs(kv);
      freeCounts(c);
      free(outName);
      fprintf(stderr,"Error: Could not create file for writing\n");
      exit(EXIT_FAILURE);
    }
    
    //print the counts from c into the FILE f
    printCounts(c,f);
    
    //close f
    if (fclose(f) != 0){
      freeKVs(kv);
      freeCounts(c);
      free(outName);
      fprintf(stderr,"Error: Could not close file for writing\n");
      exit(EXIT_FAILURE);
    } 
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  freeKVs(kv);
  //free the memory for kv
    
  return EXIT_SUCCESS;
}
