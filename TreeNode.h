#include<iostream>
#include "GenQueue.h"
using namespace std;
template <class T>

class TreeNode{
public:
  
  // Node variables
  TreeNode *left;
  TreeNode *right;
  int key;
  T value;

  // Constructor
  TreeNode(){
    right = NULL;
    left = NULL;
  }

  // Overloaded Constructor
  TreeNode(int k, T val){
    key = k;
    value = val;
    left = NULL;
    right = NULL;
  }

  // Destructor
  ~TreeNode(){
  }
};
