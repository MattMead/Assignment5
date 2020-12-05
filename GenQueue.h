#ifndef GENQUEUE_H
#define GENQUEUE_H
#include "DoubleLinkedList.h"
#include <iostream>
template <class T>


class GenQueue{
public:

  // Contructor
  GenQueue(){
    queue = new DoubleLinkedList<T>();
  }

  // Destructor
  ~GenQueue(){
  }

  // Checks if the queue is empty
  bool isEmpty(){
    return (queue->getSize() == 0);
  }

  // Gets the size of the queue
  int getSize(){
    return queue->getSize();
  }

  // Peeks at the value at the front of the queue
  T Peek(){
    return queue-> front->data;
  }

  // Inserts data at the end of the queue
  void insert(T data){
    queue->insertAtBack(data);
  }

  // Removes the data at the very front of the queue
  T Remove(){
    T c = queue->removeFromFront();
    return c;
  }

// will declare the queue here
private:
  DoubleLinkedList<T> *queue;
};
#endif
