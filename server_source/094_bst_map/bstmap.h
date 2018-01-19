#include"map.h"
#include<algorithm>

template<typename K, typename V>
class BST{
private:

  class Node{
  public:
    K key;
    V value;
    Node * left;
    Node * right;

    Node():left(NULL),right(NULL){}
    Node(const K& k, const V& v):key(k),value(v),left(NULL),right(NULL){}
  };
  
  Node * root;
  
public:
  BST():root(NULL){}
  
  BST(const K& k, const V& v): root(new Node(k,v)){}

  ~BST(){
    destroy(this->root);
  }

  void copyHelper(const Node * current){
    if (current == NULL){
      return;
    }
    if (current != NULL){
      add(current->key, current->value);
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
  void add(const K& k, const V& v){    
    Node ** current = &root;
    while (*current != NULL){
      if (k < (*current)->key){
	current = &(*current)->left;
      }
      else{
	current = &(*current)->right;
      }
    }
    *current = new Node(k,v);
  }
  
  const V& getValueFromKey(const K& k) const throw(std::invalid_argument){
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

  Node * findMin(Node * subTreeRoot){ // will be used for the leftmost right node 
    Node * current = subTreeRoot;
    while (current->left != NULL){
      current = current->left;
    }
    return current;
  }

  Node * removeHelper(Node * root,const K& k){

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
      root->key = leftMostRight->key;
      root->value = leftMostRight->value; // perform swap      
      root->right = removeHelper(root->right, leftMostRight->key);      
    }
    return root;
  }	
      
  void remove(const K& k){
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


template<typename K, typename V>
class BstMap : public Map<K,V>{
private:
  BST<K,V> * bst;
  
public:
 
  BstMap():bst(new BST<K,V>()){}
  
  BstMap(const K& k, const V& v):bst(new BST<K,V>(k,v)){}

  BstMap(const BstMap& rhs):bst(new BST<K,V>((*rhs.bst))){}

  BstMap & operator=(const BstMap& rhs){
    if (this != &rhs){
      BstMap temp(rhs);
      std::swap(temp.bst, this->bst);
    }
    return *this;
  }

  virtual ~BstMap(){
    delete (this->bst);
  }
    
  virtual void add(const K & key, const V & value){
    bst->add(key, value);
  }
  
  virtual const V & lookup(const K& key) const throw(std::invalid_argument){
    return bst->getValueFromKey(key);
  }

  virtual void remove(const K& key){
    bst->remove(key);
  }

  void print(){
    bst->print();
  }

};
