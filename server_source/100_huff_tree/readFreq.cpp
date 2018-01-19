#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include "readFreq.h"

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}

uint64_t * readFrequencies(const char * fname) {
  std::ifstream fileStream;
  fileStream.open(fname, std::fstream::in);

  uint64_t * symbolFreqs = new uint64_t[257];  // initialize all 257 entries to 0

  for (int i = 0; i < 257; i++){  // initialize array to 0's
    symbolFreqs[i] = 0;
  }
  
  int currentSymbol;
  
  if (fileStream.is_open()){  // if the file opened successfully 
    while (fileStream.good()){ // while the stream is valid 
      currentSymbol = fileStream.get();
      //std::cout << currentSymbol << "\n";
      if (currentSymbol == -1){ // check for EOF
	symbolFreqs[256] = 1;
	break;
      }
      else{
	symbolFreqs[currentSymbol]++;  // increase the count of the read symbol	
      }
    }
  }
  else{
    std::cerr << "Error: Could not open file: " << fname << "\n";
    exit(EXIT_FAILURE);
  }
  fileStream.close(); // close file when done reading 
  
  return symbolFreqs;
}
