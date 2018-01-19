#include "node.h"

// Nodes have:
// a symbol (NO_SYM if its not a leaf)
// a frequency
// a left and right node (both NULL if its a leaf)

// the call in the test is tree->buildMap (tree the root node) aka *this is the root node object

void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {

  // implement using recursion to traverse the tree
  // thinking that postorder traversal is the way 
  // NOTE: function takes a bitString, theres a recursion clue
  // Each Node has a map
  
  if (this->sym != NO_SYM){ // BASE CASE: node is a leaf
    //theMap.insert(this->sym, b);  // add the bitstring for this node to the map
    theMap[this->sym] = b;
  }
  else{  // Node is internal, must traverse recursively
    // recurse left
    this->left->buildMap(b.plusZero(),theMap); // pass the bitstring + 0 and map to the left
    this->right->buildMap(b.plusOne(),theMap);
  } 
}
