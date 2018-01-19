#include"set.h"
#include<algorithm>

// BST class remains the same from BstMap but with one template parameter, just using differently
template<typename T>
class BST{
private:

  class Node{
  public:
    T key;
    Node * left;
    Node * right;

    Node():left(NULL),right(NULL){}
    Node(const T& k):key(k),left(NULL),right(NULL){}
  };
  
  Node * root;
  
public:
  BST():root(NULL){}
  
  BST(const T& k): root(new Node(k)){}

  ~BST(){
    destroy(this->root);
  }

  void copyHelper(const Node * current){
    if (current == NULL){
      return;
    }
    if (current != NULL){
      add(current->key);
    }
    if (current->left != NULL){
      copyHelper(current->left);
    }
    if (current->right != NULL){
      copyHelper(current->right);
    }
  }
  
  BST(const BST& otherTree):root(NULL){
    copyHelper(otherTree.root);
  }
  
  BST& operator=(const BST & rhs){
    if (this != &rhs){
      BST temp(rhs);
      std::swap(temp.root,this->root);
    }
    return *this;
  }
    
  void destroy(Node * current){
    if (current != NULL){
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }

  // add functionality using pointer to a node method
  void add(const T& k){    
    Node ** current = &root;
    while (*current != NULL){
      if (k < (*current)->key){
	current = &(*current)->left;
      }
      else{
	current = &(*current)->right;
      }
    }
    *current = new Node(k);
  }
  /*
  const V& getValueFromKey(const K& k, const V& v) const throw(std::invalid_argument){
    Node * current = root;
    while (current != NULL){
      if (current->key == k){
	return current->value;
      }
      else if(k < current->key){
	current = current->left;
      }
      else{
	current = current->right;
      }
    }
    throw std::invalid_argument("Error: Key not found\n");
  }
  */

  bool contains(const T& k) const{  // does not modify the tree
    Node * current = root;
    while (current != NULL){
      if (current->key == k){
	return true;
      }
      else if(k < current->key){
	current = current->left;
      }
      else{
	current = current->right;
      }
    }
    return false;
  }

  Node * findMin(Node * subTreeRoot){ // will be used for the leftmost right node 
    Node * current = subTreeRoot;
    while (current->left != NULL){
      current = current->left;
    }
    return current;
  }

  Node * removeHelper(Node * root,const T& k){

    if (root == NULL){ // base case
      return root;
    }

    else if (k < root->key){ // key to be removed it less than current sub tree root
      root->left = removeHelper(root->left, k); // key is in left subtree
    }
    else if (k > root->key){  // key is greater than current subtree root
      root->right = removeHelper(root->right, k);
    }
    else{ // key matches the current nodes key, delete this node
      if(root->left == NULL){  // case of no left child or no child
	
	Node * replacement = root->right;
	delete root;
	return replacement;
      }
      else if (root->right == NULL){
	
	Node * replacement = root->left;
	delete root;
	return replacement;
      }
      Node * leftMostRight = findMin(root->right); // Node to be removed has two children
      root->key = leftMostRight->key; // perform swap      
      root->right = removeHelper(root->right, leftMostRight->key);      
    }
    return root;
  }	
      
  void remove(const T& k){
    this->root = removeHelper(this->root, k);
  }

  void print(){
    printInorder(this->root);
  }

  void printInorder(Node * current){
    if (current != NULL){
      printInorder(current->left);
      //std::cout << "(" << current->key << "," << current->value << ")" << "\n";
      printInorder(current->right);
    }
  }

};


template<typename T>
class BstSet : public Set<T>{
private:
  BST<T> * bst;
  
public:
 
  BstSet():bst(new BST<T>()){}
  
  BstSet(const T& k):bst(new BST<T>(k)){}

  BstSet(const BstSet& rhs):bst(new BST<T>((*rhs.bst))){}

  BstSet & operator=(const BstSet& rhs){
    if (this != &rhs){
      BstSet temp(rhs);
      std::swap(temp.bst, this->bst);
    }
    return *this;
  }

  virtual ~BstSet(){
    delete (this->bst);
  }
    
  virtual void add(const T& key){
    bst->add(key);
  }

  /*
  virtual const V & lookup(const K& key) const throw(std::invalid_argument){
    return bst->getValueFromKey(key);
  }
  */
  bool contains(const T& key) const{
    return bst->contains(key);
  }

  virtual void remove(const T& key){
    bst->remove(key);
  }

  void print(){
    bst->print();
  }

};
