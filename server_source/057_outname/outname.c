#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * suffix = ".counts";
  unsigned len = strlen(inputName) + strlen(suffix) + 1; // +1 for NULL terminator
  char * returnFile = malloc(len * sizeof(*returnFile));
  snprintf(returnFile,len,"%s%s",inputName,suffix);
  return returnFile;
}
