#include <stdlib.h>
#include <stdio.h>   // Will be reading files
#include <string.h>  // Will be using string library


int emptyFileCheck(char testMatrixRow[]){
  int initializationCheckSum = 0;
  
  for (int i = 0; i < 10; i++){
    initializationCheckSum += testMatrixRow[i];
  }
  if(initializationCheckSum == 0){
    return 1;
  }
  else{
    return 0;
  }
}

void buildMatrix(FILE * inputFile){ // takes in a stream
  
  // must check to see if the lines being read are valid
  // read the line first, then check to make sure

  int row = 0;
  //short errorIndicator = 0;

  char numRowsCheck[15] = {0};

  char matrix[10][15] = {{0}};
  //char temp[15] = {0};

  while (row < 10){
    // fgets returns NULL if EOF is reached and no characters are read or an error occurs
    if (fgets(matrix[row],15,inputFile) != NULL){
      // now matrix[row] (the current row iterating through) is full
      if (matrix[row][10] != '\n'){ // it should be equal if correctly formatted input
	fprintf(stderr,"Error: Incorrectly formatted input file. Too many columns in row %d\n", row);
	exit(EXIT_FAILURE);
      }
    }
    row++;
  }
  //printf("Matrix at 00 = %d\n", matrix[0][0]);
  // For printing
  /*
  printf("Input matrix:\n");
  
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      fprintf(stdout,"%c",matrix[i][j]);
    }
    fprintf(stdout,"\n");
  }
  */
  
  // check to ensure there are only 10 rows
  // fgets after the first 10 rows should now be == NULL
  if (fgets(numRowsCheck,15,inputFile) != NULL){
    fprintf(stderr,"Error: Incorrectly formatted input file. Too many rows\n");
    exit(EXIT_FAILURE);
  }

  if (emptyFileCheck(matrix[0])){
    fprintf(stderr,"Error: Empty input file\n");
    exit(EXIT_FAILURE);
  }

  // now that some checks are done, you can rotate the matrix and print the output
  // start with transpose
  
  for (int row = 0; row < 10; row++){
    for(int column = row + 1; column < 10; column++){
      char temp = matrix[row][column];
      matrix[row][column] = matrix[column][row];
      matrix[column][row] = temp;
    }
  }
  // Now take care of columns
  
  for (int row = 0; row < 10; row++){
    for(int column = 0; column < 10/2; column++){
      char temp = matrix[row][column];
      matrix[row][column] = matrix[row][10-1-column];
      matrix[row][10-1-column] = temp;
    }
  }
  
  // print the rotated matrix that got through checks
  // For printing
  //printf("Rotated matrix:\n");
  
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      fprintf(stdout,"%c",matrix[i][j]);
    }
    fprintf(stdout,"\n");
  }
  
  return;
}
  
  
int main(int argc, char ** argv){  // main will be reading an input file

  // rotate a 10x10 matrix clockwise and print the result to stdout

  // if any errors, print message to stderr and exit
  if (argc != 2){
    fprintf(stderr, "Error: Usage is: ./rotateMatrix fileName\n");
    exit(EXIT_FAILURE);
  }
  FILE * inputFile = fopen(argv[1],"r");  //  open the input file to get stream
  if (inputFile == NULL){
    fprintf(stderr, "Error: Could not open file\n");
    exit(EXIT_FAILURE);
  }
  // below this the input file is valid
  
  buildMatrix(inputFile);

  /*
  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      fprintf(stdout,"%c",matrix[i][j]);
    }
    fprintf(stdout,"\n");
  }
  */

  if (fclose(inputFile) != 0){
    fprintf(stderr,"Error: Could not close file\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
