#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

//YOUR CODE GOES HERE!
template <class T>
class Matrix{
 private:

  int numRows; // indexes which vector (row)
  int numColumns;  // indexes the vector (column)
  vector<T> ** rows;

 public:

 Matrix(): numRows(0), numColumns(0), rows(NULL){};
  
 Matrix(int r, int c):numRows(r), numColumns(c), rows(new vector<T>*[r]){
    for (int i = 0; i < r; i++){
      this->rows[i] = new vector<T>(c);
    }
  }
  
 Matrix(const Matrix & rhs): numRows(rhs.numRows), numColumns(rhs.numColumns),
                             rows(new vector<T> * [rhs.numRows]){

    for (int i = 0; i < rhs.numRows; i++){
      rows[i] = new vector<T>(rhs.numColumns);
      for (int j = 0; j < rhs.numColumns; j++){
	*(this->rows[i]) = *(rhs.rows[i]);
      }
    }
    
  }

  ~Matrix(){
    for (int i = 0; i < this->numRows; i++){
      delete rows[i];
    }
    delete[] rows;
  }

  Matrix & operator=(const Matrix & rhs){
    if (this != &rhs){
      vector<T> ** tempRows = new vector<T> *[rhs.numRows];
      for (int i = 0; i < rhs.numRows; i++){
	tempRows[i] = new vector<T>(rhs.numColumns);
	*tempRows[i] = *rhs.rows[i];
      }
      for (int i = 0; i < this->numRows; i++){
	delete this->rows[i];
      }
      delete[] this->rows;

      this->rows = tempRows;
      this->numColumns = rhs.numColumns;
      this->numRows = rhs.numRows;
    }
    return *this;
  }

  int getRows() const{
    return this->numRows;
  }
  int getColumns() const{
    return this->numColumns;
  }
  
  const vector<T> & operator[](int index) const{
    assert(index < this->numRows);
    assert(index >= 0);
    return *(this->rows[index]);
  }

  vector<T> & operator[](int index){
    assert(index < this->numRows);
    assert(index >= 0);
    return *(this->rows[index]);
  }
  
  bool operator==(const Matrix & rhs) const{
    if (this->numRows == rhs.numRows){
      if (this->numColumns == rhs.numColumns){
	for (int i = 0; i < this->numRows; i++){
	  for (int j = 0; j < this->numColumns; j++){
	    if ( (*(this->rows[i]))[j] != (*(rhs.rows[i]))[j] ){
	      return false;
	    }
	  }
	}
	// true if you make it through loop
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
  
  
  Matrix operator+(const Matrix<T> & rhs) const{
    assert(this->numRows == rhs.numRows);
    assert(this->numColumns == rhs.numColumns);
    for (int i = 0; i < this->numRows; i++){
      for (int j = 0; j < this->numColumns; j++){
	(*(this->rows[i]))[j] += (*(rhs.rows[i]))[j];
      }
    }
    return *this;
  }
  
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs){
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++){
    s << "{";
    for (int j = 0; j < rhs.getColumns(); j++){
      s << rhs[i][j];
      if (j < rhs.getColumns() - 1){
	s << ", ";
      }
      else {
	s << "}";
      }
    }
    if (i < rhs.getRows() - 1){
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}


#endif
