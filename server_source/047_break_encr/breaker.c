#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// 'z' is 25 away from 'a'

int findMostCommonIndex(int letter_frequency[]){
  int currMostCommon;
  int mostCommon = 0;
  int indexOfMostCommon;
  for (int i = 0; i < 26; i++){

    currMostCommon = letter_frequency[i];

    if(currMostCommon > mostCommon){
      mostCommon = currMostCommon;
      indexOfMostCommon = i;
    }
  }

  // check to ensure that there are not two most common letters

  int blankInputCheck = 0;
  for (int k = 0; k < 26; k++){
    blankInputCheck += letter_frequency[k];
  }
  if(blankInputCheck == 0){
    // the key 0 i guess?
    return 4;  // this will make the key 0
  }
  
  for(int j =0; j < 26; j++){
    if ((mostCommon == letter_frequency[j]) && (j != indexOfMostCommon) ){
     
      fprintf(stderr,"Failed to break\n");
      exit(EXIT_FAILURE);
    }
  }
  
  return indexOfMostCommon;  // index of the most common letter
}

int main(int argc, char ** argv){
  if (argc != 2){
    fprintf(stderr,"Usage: breaker inputFileName\n");
    exit(EXIT_FAILURE);
  }
  
  FILE * input_file = fopen(argv[1], "r");
  if (input_file == NULL){
    fprintf(stderr,"Could not open file.\n");
    exit(EXIT_FAILURE);
  }

  int numChars = 0;
  int current_char;
  int char_frequency[26] = {0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0,0,0,0,0,
			    0,0,0,0,0,0};
  // stores the frequency for 26 lowercase letters in order
  
  while((current_char = fgetc(input_file)) != EOF){
    if (isalpha(current_char)){
      current_char = tolower(current_char);
      // you now have the valid current character from the file being read
      for (int i = 97; i < 123; i++){  // from 'a' to 'z'
	if (current_char == i){
	  char_frequency[i - 97]++;
	}
      }
      numChars++;
    }
  }
  if (fclose(input_file) != 0){
    fprintf(stderr,"Failed to close the input file.\n");
    exit(EXIT_FAILURE);
  }
  
  int most_occurring_index = findMostCommonIndex(char_frequency);
    
  int guess_key = -('e' - (most_occurring_index + 97));
  
  if (guess_key < 0){
    // gotta loop around
    guess_key = 26 + guess_key;
  }

  fprintf(stdout,"%d\n",guess_key);
  
  return EXIT_SUCCESS;
}
