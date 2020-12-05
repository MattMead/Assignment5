#include<iostream>
using namespace std;
template <class T>
class DoubleListNode{

public:
  // Variables
  T data;
  DoubleListNode<T> *next;
  DoubleListNode<T> *previous;

  // Constructor
  DoubleListNode(){
      data = NULL;
      next = NULL;
      previous = NULL;
  }

  // Overloaded Constructor
  DoubleListNode(T d){
      data = d;
      next = NULL;
      previous = NULL;
  }

  // Destructor
  ~DoubleListNode(){
      if(next == NULL){
        delete next;
        previous = NULL;
      }
  }
};
