#include <iostream>
#include <fstream>
#include "TreeNode.h"
using namespace std;

template <class T>
class BST{

public:
  // Declaring bothy the root and end node constant
  TreeNode<T> *root;
  const string endNode = "||";

  // Constructor
  BST(){
    root = NULL;
  }

  // Destructor
  ~BST(){

  }

  // Checks to see if the tree is empty
  bool isEmpty(){
    if(root == NULL){
      return true;
    }
    else{
      return false;
    }
  }

  // Retrieves the minimum value of the tree
  //this would be the value all the way to the left
  TreeNode<T>* getMinimum(){
    TreeNode<T> *current = root;
    if(root == NULL){
      return NULL;
    }
    while(current->left != NULL){
      current = current->left;
    }
    return current;
  }

  // Retrieves the maximum value of the trees
  // This would be the value all the way to the left
  TreeNode<T>* getMaximum(){
    TreeNode<T> *current = root;
    if(root == NULL){
      return NULL;
    }
    while(current->right != NULL){
      current = current->right;
    }
    return current;
  }

  // Prints out the entire tree
  void printOutTree(){
    printSubtree(root);
  }

  //Prints out the subtree
  void printSubtree(TreeNode<T> *node){
    if(node == NULL){
      return;
    }
    printSubtree(node->left);
    node->value->toString();
    cout << endl;
    printSubtree(node->right);
  }

  // Allows for adjusting a nodes values by accessing the node and returning it
  T printNode(int nodeKey){
    if(root == NULL){
      return NULL;
    }
    else{
      TreeNode<T> *current = root;
      while(current->key != nodeKey){
        if(nodeKey < current->key){
          current = current->left;
        }
        else{
          current = current->right;
        }
        if(current == NULL){
          return NULL;
        }
      }
      return current-> value;
    }
  }

  // Searches the tree ofr an integers value
  bool Search(int value){
    if(root == NULL){
      return false;
    }
    else{
      // it will keep moving left or right as long as the key does not equal current
      // if it reaches the end and it does not find the value, it is not in the tree
      TreeNode<T> *current = root;
      while(current->key != value){
        if(value < current->key){
          current = current->left;
        }
        else{
          current = current->right;
        }
        if(current == NULL){
          return false;
        }
      }
    }
    return true;
  }

  // Inserts a node into the tree
  void insert(int key, T value){
    TreeNode<T> *node = new TreeNode<T>(key, value);
    if(root == NULL){
      root = node;
    }
    //If the tree is not empy we then need to find the right place to insert the node
    else{
      bool istrue = true;
      TreeNode<T> *current = root;
      TreeNode<T> *parent = NULL;
      while(istrue){
        parent = current;
        // Going to the left
        if(key < current->key){
          current = current->left;
          if(current == NULL){
            parent->left = node;
            break;
          }
        }
        //Going to the right
        else{
          current = current->right;
          if(current == NULL){
            parent->right = node;
            break;
          }
        }
      }
    }
  }


  // Delete a specified node in the tree
  bool deleteNode(int key){
    if(root == NULL){
      return false;
    }
    bool isLeft = true;
    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;

    // Here is the loop to find the right node to delete
    while(current->key != key){
      parent = current;
      // go left
      if(key < current->key){
        isLeft = true;
        current = current->left;
      }
      // go right
      else{
        isLeft = false;
        current = current->right;
      }
      // Specified value does not exist
      if(current == NULL){
        return false;
      }
    }

    //At this point we found the node that needs to be deleted
    // need to make proper tree adjustments based on the type of node it is
    if(current->left == NULL && current->right == NULL){
      if(current == root){
        root = NULL;
      }

      else if(isLeft){
        parent->left = NULL;
      }
      else{
        parent->right = NULL;
      }
    }
    else if(current->right == NULL){
      if(current == root){
        root = current->left;
      }
      else if(isLeft){
        parent->left = current->left;
      }
      else{
        parent->right = current->left;
      }
    }

    else if(current->left == NULL){
      if(current == root){
        root = current->right;
      }
      else if(isLeft){
        parent->left = current->right;
      }
      else{
        parent->right = current->right;
      }
    }

    // Node that needs to be removed has two children
    else{
      TreeNode<T> *successor = getNodeSuccessor(current);
      if(current == root){
        root = successor;
      }
      else if(isLeft){
        parent->left = successor;
      }
      else{
        parent->right = successor;
      }
      successor->left = current->left;
    }
  }

  // Used to help delete nodes with two children
  TreeNode<T>* getNodeSuccessor(TreeNode<T> *d){
    TreeNode<T> *current = d->right;
    TreeNode<T> *sp = d;
    TreeNode<T> *successor = d;
    while(current != NULL){
      sp = successor;
      successor = current;
      current = current->left;
    }
    if(successor != d->right){
      sp->left = successor->right;
      successor->right = d->right;
    }
    return successor;
  }


  // Pushes our tree to a file
  void TreeToFile(string fileName){
    ofstream fileStream;
    fileStream.open(fileName, ios::out);
    if(!fileStream){
      throw runtime_error ("Could not open the file.");
    }
    NodeFile(root, fileStream);
    fileStream.close();
  }


  // Put all nodes in the tree to a file
  // Will be assisted by TreeToFile method
  void NodeFile(TreeNode<T> *node, ofstream& fileStream){
    if(node == NULL){
      fileStream << endNode << endl;
      return;
    }
    NodeFile(node->left, fileStream);
    fileStream<< node->key << endl;
    fileStream << *(node->value) << endl;
    NodeFile(node->right, fileStream);
  }
};
