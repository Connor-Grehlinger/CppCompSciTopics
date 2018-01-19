#include "IntMatrix.h"

IntMatrix::IntMatrix(): numRows(0), numColumns(0), rows(NULL){}

// NOTE: you should be using your old object 

IntMatrix::IntMatrix(int r, int c): numRows(r), numColumns(c), rows(new IntArray*[r]){
  for (int i = 0; i < r; i++){
    this->rows[i] = new IntArray(c); // for each row, create an int array with num entries = columns
  }
}

// rows is an array of pointers to IntArray objects

IntMatrix::IntMatrix(const IntMatrix & rhs): numRows(rhs.numRows),numColumns(rhs.numColumns),
					     rows(new IntArray*[rhs.numRows]){
  for (int i = 0; i < rhs.numRows; i++){
    rows[i] = new IntArray(rhs.numColumns);
    for (int j = 0; j < rhs.numColumns; j++){
      // this->rows[i] = is a IntArray * (pointer to IntArray)
      *(this->rows[i]) = *(rhs.rows[i]);
    }
  }
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < this->numRows; i++){
    delete rows[i];
  }
  delete[] rows;
}


IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs){
    IntArray ** tempRows = new IntArray*[rhs.numRows];

    for (int i = 0; i < rhs.numRows; i++){
      *(tempRows[i]) = *(rhs.rows[i]); // IntArray object ought to handle this
      
    }
    /*
    for (int i = 0; i < this->numRows; i++){
      delete rows[i];
    }
    */
    delete[] rows; // other objects function handles the other delete

    this->rows = tempRows;
  }
  return *this;
}


int IntMatrix::getRows() const {
  return this->numRows;
}

int IntMatrix::getColumns() const {
  return this->numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
  assert(index < this->numRows);
  assert(index >= 0);
  return *(this->rows[index]);
}

IntArray & IntMatrix::operator[](int index){
  assert(index < this->numRows);
  assert(index >= 0);
  return *(this->rows[index]);
}


bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (this->numRows == rhs.numRows){
    if (this->numColumns == rhs.numColumns){
      for (int i = 0; i < this->numRows; i++){
	if (*(this->rows[i]) != *(rhs.rows[i])){
	  return false; // compare int array objects for equality
	}
      }
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}


IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(this->numRows == rhs.numRows);
  assert(this->numColumns == rhs.numColumns);
  // this will return an IntMatrix object
  

  IntMatrix newMatrix = IntMatrix(rhs); // make a new matrix starting with the copy of rhs
  for (int i = 0; i < rhs.numRows; i++){ // for all IntArray objects in the matrix
    // rows[i] is pointer to intArray
    for (int j = 0; j < rhs.numColumns; j++){
      (*(newMatrix.rows[i]))[j] += (*(this->rows[i]))[j];
    }
  }
  
  return newMatrix;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if (rhs.getRows() == 0 || rhs.getColumns() == 0){
    s << "[ ]";
    return s;
  }
  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++){
    // for each IntArray object ref
    s << rhs[i];
    s << ",\n";
  }
  s << rhs[rhs.getRows() -1] << " ]";
  return s;
}
