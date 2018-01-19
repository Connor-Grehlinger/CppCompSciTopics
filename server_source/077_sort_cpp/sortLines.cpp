#include "sortLines.h"




// open std::ifstreams to read file, std::cin for stdin



int main(int argc, char ** argv){

  if (argc == 1){ // read from standard input
    //ifstream stdin(cin);
    // now you have the stream, use getline to extract strings
    string line;
    vector<string> strs;
    while (getline(cin,line)){
      strs.push_back(line);
    }
    sort(strs.begin(),strs.end());
    for (unsigned int i = 0; i < strs.size(); i++){
      cout << strs[i] << endl;
    }
  }
  else{
    for (int i = 1; i < argc; i++){
      // open file at argv[i], sort and print one by one
      ifstream file(argv[i]); // get input file stream
      string fileLine;
      vector<string> strs;
      if (file.is_open()){ // if the file stream opened correctly
	while (getline(file,fileLine)){
	  strs.push_back(fileLine);
	}
      }
      else{
	cerr << "Error, could not open file\n";
	exit(EXIT_FAILURE);
      }
      file.close();
      if (file.is_open()){
	cerr << "Error, could not close file\n";
	exit(EXIT_FAILURE);
      }
      sort(strs.begin(),strs.end());
      for (unsigned int i = 0; i < strs.size(); i++){
	cout << strs[i] << endl;
      }
    }

  }

  return EXIT_SUCCESS;
}
