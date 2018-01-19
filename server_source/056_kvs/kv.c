#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t * readAPair(FILE * f, kvarray_t * freeMem){
  kvpair_t * new_pair = malloc(sizeof(*new_pair));

  size_t sz = 0;
  char * pair_line = NULL;
  getline(&pair_line,&sz,f);

  const char delimiter[2] = "=";
  char * key;

  char * value = strchr(pair_line, '=');
  value[strlen(value) - 1] = '\0'; // NULL terminate the value field
  value++; // move past the '=' character, remaing string is the value
  
  key = strtok(pair_line, delimiter);// get the key first
  if (key == NULL){
    fprintf(stderr,"Error: Improperly formatted input file\n");
    freeKVs(freeMem);
    exit(EXIT_FAILURE);
  }
  new_pair->key = calloc((strlen(key) + 1), sizeof(*new_pair->key));
  strcpy(new_pair->key,key);

  new_pair->value = calloc((strlen(value) + 1), sizeof(*new_pair->key));
  strcpy(new_pair->value,value);
  
  free(pair_line);
  return new_pair;
}

int getNumPairs(const char * fname){
  FILE * f = fopen(fname, "r");
  if (f == NULL){
    fprintf(stderr,"Error: could not open file\n");
    exit(EXIT_FAILURE);
  }
  int numPairs = 0;
  char * line = NULL;
  size_t sz = 0;
  ssize_t len;

  while( (len = getline(&line,&sz,f)) >= 0){
    numPairs++;
  }
  free(line);
  if (fclose(f) != 0){
    fprintf(stderr,"Error: could not close file\n");
    exit(EXIT_FAILURE);
  }
  return numPairs;
}
  

kvarray_t * readKVs(const char * fname) {
  int num_pairs = getNumPairs(fname);
  
  FILE * f = fopen(fname, "r");
  if (f == NULL){
    fprintf(stderr,"Error: could not open file\n");
    exit(EXIT_FAILURE);
    // no need to free anything yet
  }
  kvarray_t * new_kv_array = malloc(sizeof(*new_kv_array));
  // created reference to memory block holding the kvarray_t struct
  if (new_kv_array == NULL){
    free(new_kv_array);
    fprintf(stderr,"Error: Could not allocate memory\n");
    exit(EXIT_FAILURE);
  }
  new_kv_array->kv_array = malloc(sizeof(*new_kv_array->kv_array));
  // allocatd memory for structs array of pairs
  if (new_kv_array->kv_array == NULL){
    free(new_kv_array->kv_array);
    free(new_kv_array);
    fprintf(stderr,"Error: Could not allocate memory\n");
    exit(EXIT_FAILURE);
  }
  
  size_t num_kv_pairs = 1;
  for (int i = 0; i < num_pairs; i++){
    new_kv_array->kv_array = realloc(new_kv_array->kv_array,
				     num_kv_pairs *
				     sizeof(*new_kv_array->kv_array));
    new_kv_array->kv_array[i] = readAPair(f, new_kv_array);
    // abstract it out
    new_kv_array->array_size = num_kv_pairs;
    num_kv_pairs++;
  }
  if (num_pairs == 0){
    new_kv_array->array_size = 0;
    free(new_kv_array->kv_array);
  }
  
  if (fclose(f) != 0){
    freeKVs(new_kv_array);
    fprintf(stderr,"Error: could not close file\n");
    exit(EXIT_FAILURE);
  }
  
  return new_kv_array;
}

void freeKVs(kvarray_t * pairs) {
  // free all allocated memory
  for (int i = 0; i < pairs->array_size; i++){
    free(pairs->kv_array[i]->key);
    free(pairs->kv_array[i]->value);
    free(pairs->kv_array[i]);
  }
  if(pairs->array_size != 0){
    free(pairs->kv_array);
  }
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  if (pairs == NULL){
    free(pairs);
    fprintf(stderr,"Error: printKVs passed in NULL\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < pairs->array_size; i++){  // check for pairs uninitialized 
    printf("key = '%s' value = '%s'\n", pairs->kv_array[i]->key,
	   pairs->kv_array[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  // Search the kvarray_t for the key, return corresponding value
  if (pairs == NULL){
    free(pairs);
    fprintf(stderr,"Error: lookupValue passed in NULL\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < pairs->array_size; i++){ // check for uninitialized values
    if (!strcmp(pairs->kv_array[i]->key, key)){
      return pairs->kv_array[i]->value;
    }
  }
  return NULL;
}
