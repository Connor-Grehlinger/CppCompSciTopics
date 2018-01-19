#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray():data(NULL),numElements(0){}

IntArray::IntArray(int n): data(new int[n]), numElements(n) {}

IntArray::IntArray(const IntArray & rhs): data(new int[rhs.numElements]),
					  numElements(rhs.numElements){
  for (int i = 0; i < numElements; i++){
    data[i] = rhs.data[i];
  }
}

IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs){  // check to make sure you're not assigning to the same object 
    
    //int * temp = new int[rhs.numElements];
    
    //if(rhs.data != NULL){
    
    int * temp = new int[rhs.numElements];
    
    for (int i = 0; i < rhs.numElements; i++){
      temp[i] = rhs.data[i]; // copy right hand operand's array
    }
    
    delete[] this->data; // free the old array memeory
    numElements = rhs.numElements;
    data = temp;
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index < this->numElements);
  assert(index >= 0);
  return this->data[index];
}

int & IntArray::operator[](int index) {
  assert(index < this->numElements);
  assert(index >= 0);
  return this->data[index];
}

int IntArray::size() const {
  return this->numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (rhs.numElements == this->numElements){
    for (int i = 0; i < this->numElements; i++){
      if (rhs.data[i] != this->data[i]){
	return false;
      }
    }
    return true;
  }
  else{
    return false;
  }
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (rhs.numElements == this->numElements){
    for (int i = 0; i < this->numElements; i++){
      if (rhs.data[i] != this->data[i]){
	return true;
      }
    }
    return false;
  }
  else{
    return true;
  }
}

/*
std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.numElements - 1; i++){
    s << rhs.data[i] << ", ";
  }
  s << rhs.data[rhs.numElements - 1] << "}";
  return s;
}
*/


int IntArray::getNumElements() const{
  return this->numElements;
}

int * IntArray::getData() const{
  return this->data;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.getNumElements() == 0 || rhs.getData() == NULL){
    s << "{}";
    return s;
  }
  
  s << "{";
  for (int i = 0; i < rhs.getNumElements() - 1; i++){
    s << rhs.getData()[i] << ", ";
  }
  s << rhs.getData()[rhs.getNumElements() - 1] << "}";

  return s;
}
