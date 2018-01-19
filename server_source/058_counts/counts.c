#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * newCounts = malloc(sizeof(*newCounts));
  newCounts->counts = malloc(sizeof(*newCounts->counts));
  //newCounts->num_counts = 0;
  // num_counts field is initialized
  // counts (array of one_count_t structs) uninitalized
  one_count_t * firstCount = malloc(sizeof(*firstCount));
  //firstCount->string = malloc(sizeof(*firstCount->string));
  firstCount->string = "!";
  firstCount->count = 0;

  *(newCounts->counts) = firstCount;
  newCounts->num_counts = 1;
  newCounts->num_unknowns = 0;
  return newCounts;
}


void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL){
    // check if you already have an <unknown>
    /*
    if (isIn(c,"<unknown> ")){
      // if the count entry is present, increase the count
      for (int i = 0; i < c->num_counts; i++){
	if (!strcmp(c->counts[i]->string, "<unknown> ")){
	  // if you're at the count to update
	  c->counts[i]->count++;
	  return;
	}
      }
    }
    // create unknown entry
    c->num_counts++;
    c->counts = realloc(c->counts, c->num_counts * sizeof(*c->counts));
    c->counts[c->num_counts - 1] = malloc(sizeof(*c->counts[c->num_counts]));
    c->counts[c->num_counts - 1]->string = malloc(sizeof("<unknown> "));
    strcpy(c->counts[c->num_counts - 1]->string,"<unknown> ");
    c->counts[c->num_counts - 1]->count = 1;
    return;
    */
    //c->num_counts++;
    c->num_unknowns++;
  }
  // need to crate a count in counts if there isnt one
  else if (isIn(c,name)){
    // if the count entry is present, increase the count
    for (int i = 0; i < c->num_counts; i++){
      if (!strcmp(c->counts[i]->string, name)){
	// if you're at the count to update
	c->counts[i]->count++;
      }
    }
  }
  else{
    // create the entry
    // will have to re-allocate
    for (int i = 0; i < c->num_counts; i++){
      // check for an 'empty' one_count_entry
      if(!strcmp(c->counts[i]->string,"!")){
	// if you're at an empty entry, make it the one you add too
	c->counts[i]->string = malloc(sizeof(*c->counts[i]->string) * (strlen(name) + 1));
	// reallocate space for the name
	//memset(c->counts[i]->string,'\0',sizeof(strlen(c->counts[i]->string)));
	strcpy(c->counts[i]->string,name);
	c->counts[i]->count++;
	return;
      }
    }
    // create whole new entry
    c->num_counts++;
    c->counts = realloc(c->counts, c->num_counts * sizeof(*c->counts));
    c->counts[c->num_counts - 1] = malloc(sizeof(*c->counts[c->num_counts]));
    c->counts[c->num_counts - 1]->string =
      malloc(sizeof(*c->counts[c->num_counts -1]->string) * (strlen(name)+ 1));
    strcpy(c->counts[c->num_counts - 1]->string,name);
    c->counts[c->num_counts - 1]->count = 1;
  }
  return;
}


  
int isIn(counts_t * c, const char * name){
  for (int i = 0; i < c->num_counts; i++){
    if (!strcmp(c->counts[i]->string,name)){
      return 1;
    }
  }
  return 0;
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->num_counts; i++){
    fprintf(outFile,"%s: %d\n",c->counts[i]->string, c->counts[i]->count);
  }
  if (c->num_unknowns > 0){
    fprintf(outFile,"<unknown> : %d\n",c->num_unknowns);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->num_counts; i++){
    free(c->counts[i]->string);
    free(c->counts[i]);
  }
  free(c->counts);
  free(c);
}
