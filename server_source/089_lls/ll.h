#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>
#include <algorithm>
#include <string>
#include <iostream>

//YOUR CODE GOES HERE
class LLException: public std::exception{
 private:
  std::string error; // new exception has an error string specific to linked list
  
 public:
 LLException(std::string msg):error(msg){}
  ~LLException() throw(){}  // destructor will always be implemented this way unless non-trivial 
  virtual const char * what() const throw(){  // always good practice to override 'what' method 
    return error.c_str();
  }

};


template<typename T>
class LinkedList{

 private:
  
  class Node{
  public:  // can be public so linked list will have access to inner class members
    T data;
    Node * next;
    Node * previous;
  Node(const T& d): data(d), next(NULL), previous(NULL){}
  Node(const T& d, Node * n, Node * p):data(d),next(n),previous(p){}
  };
  
  Node * head;
  Node * tail;
  int size;

 public:
  // make constructors 
 LinkedList():head(NULL), tail(NULL), size(0){} // default

  //LinkedList(const LinkedList& rhs):head(rhs.head), tail(rhs.tail), size(rhs.size){} // this is
  // incorrect, pretty sure it's making another list that refers to the same nodes instead of a copy
  
 LinkedList(const LinkedList& rhs):size(rhs.size){  // copy constructor, start by setting size
    if (rhs.head == NULL){ // empty list
      this->head = NULL;
      this->tail = NULL;
      this->size = 0;
    }
    else{
      this->head = new Node(rhs.head->data, rhs.head->next, rhs.head->previous);
      // create new head with other lists head data, next and set previous to NULL
      Node * rhs_curr = rhs.head;
      Node * curr = this->head; 
      while (rhs_curr->next != NULL){  // create the next node if it exists
	curr->next = new Node(rhs_curr->next->data, rhs_curr->next->next, curr);
	rhs_curr = rhs_curr->next;
	curr = curr->next;
      }
      this->tail = curr;
    }
  }	

  LinkedList & operator=(const LinkedList & rhs){
    if (this != &rhs){
      LinkedList temp(rhs); // create new linked list temp from rhs 
      std::swap(temp.head, this->head); // swap newly constructed copy of rhs with this linked list
      std::swap(temp.tail, this->tail);
      std::swap(temp.size, this->size);
      // temp will be deleted when it goes out of scope with this function 
    }
    return *this;
  }
  
  // write a destroy function that is used in destructor and operator=
  ~LinkedList(){
    destroy(this->head); // works, kinda ugly though 
  }
  
  void addFront(const T& item){
    this->head = new Node(item, head, NULL);
    // create new head node with item, next node set to previous head

    if (this->tail == NULL){  // if adding to an empty list
      this->tail = this->head;
    }
    else{
      this->head->next->previous = this->head; // set the old head's previous pointer to the added node
    }
    this->size++;
  }
  
  void addBack(const T& item){
    this->tail = new Node(item, NULL, tail);
    // create new tail node with item, next set to NULL, and previous to the old tail
    if (this->head == NULL){ // if adding to an empty list
      this->head = this->tail;
    }
    else{
      this->tail->previous->next = this->tail;
    }
    this->size++;
  }

  bool remove(const T& item){
    if (this->head == NULL){ // empty list
      return false;
    }
    Node* current = this->head;
    while (current != NULL){
      if (current->data == item){
	// corner cases here
	if (current == this->head){
	  this->head = current->next; // move head to next node
	  delete this->head->previous; // delete the old head
	  this->head->previous = NULL;
	  this->size--;
	  if (this->size == 1){
	    this->tail = this->head;
	  }
	  return true;
	}
	else if (current == this->tail){
	  this->tail = current->previous;
	  delete this->tail->next;
	  this->tail->next = NULL;
	  this->size--;
	  if (this->size == 1){
	    this->tail = this->head;
	  }
	  return true;
	}
	else{
	  current->previous->next = current->next;
	  current->next->previous = current->previous;
	  delete current;
	  this->size--;
	  return true;
	}
      }
      current = current->next;
    }
    return false;
  }

  T& operator[](int index){
    if (index >= this->size){
      throw LLException("Index out of range\n");
    }
    if (index == 0){
      return this->head->data;
    }
    else{
      Node * current = this->head;
      while (index > 0){
	current = current->next;
	index--;
      }
      return current->data;
    }
  }

  const T& operator[](int index) const{
    if (index >= this->size){
      throw LLException("Index out of range\n");
    }
    if (index == 0){
      return this->head->data;
    }
    else{
      Node * current = this->head;
      while (index > 0){
	current = current->next;
	index--;
      }
      return current->data;
    }
  }


  int find(const T& item)const{
    Node * current = this->head;
    for (int i = 0; i < this->size; i++){
      if (current != NULL){
	if(current->data == item){
	  return i;
	}
	current = current->next;
      }
    }
    return -1;
  }
  // returns index or -1 if non-existent

  void destroy(Node * curr){  // for singly linked, but your're destorying so I think its okay 
    while(curr != NULL){
      Node * temp = curr->next;
      delete curr;
      curr = temp;
    }
  }
  
  int getSize() const{ // const because doesn't modify anything
    return this->size;
  }

  void print() const{  // for debugging
    Node * current = this->head;
    while (current != NULL){
      std::cout << current->data << "\n";
      current = current->next;
    }
  }
};

#endif
