#include "node.h"

Node *  buildTree(uint64_t * counts) {
  // build priority queue of node *'s
  priority_queue_t pq;  // don't dynamically allocate 
  // counts has 257 symbols
  for (int i = 0; i < 257; i++){ // construct new node and add it to queue
    if (counts[i] != 0){
      pq.push(new Node(i, counts[i]));
    }
  }
  // once the initial priority queue is built, construct the tree
  while (pq.size() >= 2){  // will end when there's just one node (the root)
    Node * currentLeft = pq.top();
    pq.pop(); // remove the current first minimum
    Node * currentRight = pq.top();
    pq.pop(); // remove the current second minimum
    pq.push(new Node(currentLeft, currentRight));
  }
  return pq.top();
}  
