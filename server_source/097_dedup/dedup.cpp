#include "hashmap.h"  // custom templated hash map class like from AOP
                      // hashmap.h has all other necessary includes
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>


// --- Main functions for directory scanning ---
struct dataHolder{
public:
  //HashMap<off_t, std::string, std::hash<off_t>> * sizeToFile;
  //std::list<std::pair</*file size*/ off_t, /*file name*/ std::string>> * dupCan;
  HashMap<std::string, std::string, std::hash<std::string>> * contentsToFile;
  std::list<std::pair<std::string,std::string>> * duplicates;
};
typedef struct dataHolder dataHolder_t;


typedef struct dirent dirent_t;

void scan_directory(std::string dir_name, dataHolder_t * d);  
void scan_file(std::string file_name, dataHolder_t * d);
void dirent_handler(dirent_t * entity, dataHolder_t * d);

//std::string path = "/home/cmg88/ece551/"; // this is a dummy for the path for now
std::string path = "";

// maybe pass be reference instead of pointer 
void scan_directory(std::string dir_name, dataHolder_t * d){
  std::string target_dir_name = path + dir_name; // may have to concatenate file path, idk
  DIR* current_dir_stream = opendir(target_dir_name.c_str()); // open the directory stream 

  path = target_dir_name + "/"; // new path for the content of the directory
  
  //std::cout << "Scanning directory: " << target_dir_name.c_str() << "\n";
  if (current_dir_stream == NULL){  // if you failed to open the directory
    //std::cout << "Could not open directory: " << target_dir_name.c_str() << "\n";
    return;
  }
  // from readder man page
  dirent_t * current_file;
  while (current_dir_stream){  // while the stream is valid
    errno = 0;
    if ((current_file = readdir(current_dir_stream)) != NULL){
      dirent_handler(current_file, d);  // process current file
    }
    else{
      // might have to do error checking here 
      if (errno == 0){
	closedir(current_dir_stream);
	path.resize(path.length() - 1 - dir_name.length());
	return;
      }
      closedir(current_dir_stream);
      std::cerr << "Error reading from directory stream: " << target_dir_name << " \n";
      exit(EXIT_FAILURE);
    }
  }
  /*
  dirent_t * entity = readdir(current_dir_stream);

  while (entity != NULL){
    dirent_handler(entity);  // process each entity (file) in the directory 
    entity = readdir(current_directory);
  }
  */
  //closedir(current_directory);  
  // after this the directory is finished remove it from the path
  //path.resize(path.length() - 1 - dir_name.length());
}


void scan_file(std::string file, dataHolder_t * d){  // perform file operations
 
  //std::cout << "Scanning file: " << file.c_str() << "\n";
  std::ifstream fileStream;

  //std::cout << path << "\n";
  
  fileStream.open((path + file), std::ifstream::in); // get the current files stream

  //std::cout << "Is file open? " << fileStream.is_open() << ". File good? "<< fileStream.good() << "\n";
  
  std::string line;
  std::string result; // file contents as string to be hashed

  
  if (fileStream.is_open()){
    //std::cout << "File opened.\n";
    while (getline(fileStream, line)){  // read while there are lines to be read
      result += line;
      //std::cout << "Reading line: " << line << "\n";
    }
    fileStream.close();
  }
  //std::cout << "Result for file: " << file << " = " << result << "\n";
  if (d->contentsToFile->isEmptyBucket(result)){  // if the is not a duplicate
    d->contentsToFile->add(result, (path + file));
  }
  else{ // we've seen the file before
    d->duplicates->push_front(std::pair<std::string,std::string>(path + file,
				   d->contentsToFile->getKeysValue(result)/*"dummy"*/));
  }			      
}

void dirent_handler(dirent_t * entity, dataHolder_t * d){
  if (entity->d_type == DT_DIR){ // if the entity is a directory, process recursively 
    
    if (entity->d_name[0] == '.'){
      return; // omit . and ..
    }
    else{
      
      scan_directory(std::string(entity->d_name), d);
      return;
    }
  }
  if (entity->d_type == DT_REG){ // if the entity is a regular file
    scan_file(std::string(entity->d_name), d);
    return;
  }
  //std::cout << "Not regular file or directory \n"; // some other file type
}  
// ---------------------------------------------


int main(int argc, char ** argv){

  /*
  // map in which keys are file size and values are file path + name
  HashMap<off_t, std::string, std::hash<off_t>> * sizeToFileMap =
    new HashMap<off_t, std::string, std::hash<off_t> >(); 
  // this will be used as a filter for any duplication candidates

  std::list<std::pair< off_t, std::string>> * duplicateCandidates =
    new std::list<std::pair<off_t,std::string> >();
  // list containing pairs of files that are the same size as another file (potential duplicates
  */
  
  HashMap<std::string, std::string, std::hash<std::string>> * contentsToFileMap =
    new HashMap<std::string, std::string, std::hash<std::string> >();
  // map in which keys are hash of file contents and values are the files name including the path

  std::list<std::pair<std::string,std::string>> * duplicatesList =
    new std::list<std::pair<std::string, std::string> >();
  // list of true duplicates and the file they duplicate 
  
  dataHolder_t * data = new dataHolder();
  //data->sizeToFile = sizeToFileMap;
  //data->dupCan = duplicateCandidates;
  data->contentsToFile = contentsToFileMap;
  data->duplicates = duplicatesList;

  for (int i = 1; i < argc; i++){
    
    scan_directory(argv[i], data);
    /*
    for (std::list<std::pair<std::string,std::string> >::iterator
	   it = data->duplicates->begin(); it != data->duplicates->end(); ++it){

      std::cout << "#Removing " << std::get<0>(*it)
		<< " (duplicate of " << std::get<1>(*it) << ")\n";
      std::cout << "rm " << std::get<0>(*it) << "\n";
    }
    */
  }

  std::cout << "#!/bin/bash" << std::endl;

  for (std::list<std::pair<std::string,std::string> >::iterator
	 it = data->duplicates->begin(); it != data->duplicates->end(); ++it){
    
    std::cout << "#Removing " << std::get<0>(*it)
	      << " (duplicate of " << std::get<1>(*it) << ").\n";
    std::cout << "rm " << std::get<0>(*it) << "\n";
  }

  //delete sizeToFileMap;
  //delete duplicateCandidates;
  delete contentsToFileMap;
  delete duplicatesList;
  delete data;
  
  return EXIT_SUCCESS;
}

