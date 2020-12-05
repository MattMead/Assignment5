#include"DoubleListNode.h"
using namespace std;
template <class T>
class DoubleLinkedList{

public:
  // Variables
  unsigned int size;
  DoubleListNode<T> *front;
  DoubleListNode<T> *back;


  // Operator Constructor
  friend ostream& operator <<(ostream& fileStream, DoubleLinkedList<T>& lList){
    DoubleListNode<T>* current = lList.front;
    while(current != NULL){
      fileStream << current->data << endl;
      current = current->next;
    }
    return fileStream;
  }

  // Constructor
  DoubleLinkedList(){
    size = 0;
    front = NULL;
    back = NULL;
  }

  // Destructor
  ~DoubleLinkedList(){
  }

  // Checks to see if the list is Empty
  bool isEmpty(){
    if(size == 0){
      return true;
    }
    else{
      return false;
    }
  }

  // Prints the entire list
  void printAll(){
    DoubleListNode<T> *current = front;
    while (*current != NULL)
    {
      cout << current->data << endl;
      current = current->next;
    }
  }


  // Gets the size of the list
  unsigned int getSize(){
    return size;
  }

  // Gets data at a specified index
  T getIndexData(int index){
    DoubleListNode<T> *current = front;
    for(int i = 0; i < index; ++i){
      current = current -> next;
    }
    return current->data;
  }

  // Inserts data at the front of the list
  void insertAtFront(T d){
    DoubleListNode<T> *node = new DoubleListNode<T>(d);
    if(isEmpty()){
      back = node;
    }
    else{
      front -> previous = node;
      node -> next = front;
    }
    front = node;
    size++;
  }

  // Inserts data at the back of the List
  void insertAtBack(T d){
    DoubleListNode<T> *node = new DoubleListNode<T>(d);
    if(isEmpty()){
      front = node;
      back = node;
    }
    else{
        back-> next = node;
        node-> previous = back;
    }
    back = node;
    size++;
  }

  // Deletes data at a certain index in the list
  T deletePosition(T position){
    DoubleListNode<T> *current = front;
    DoubleListNode<T> *previous = front;
    int index = 0;

    while (index != position){
      previous = current;
      current = current->next;
      index++;
    }
    previous->next = current-> next;
    current->next = NULL;
    T temp = current->data;
    delete current;
    size--;
    return temp;
   }


   // Removes data from the front of the list
   T removeFromFront(){
    DoubleListNode<T> *ft = front;
      if(front->next == NULL){
        back = NULL;
      }
      else{
        front->next->previous = NULL;
      }
      front = front->next;
      T temp = ft->data;
      ft->next = NULL;
      //decrement size
      size--;
      //delete original node and return the temporary node
      delete ft;
      return temp;
    }

    // Removes data in the list
    DoubleListNode<T>* Remove(T d){
      DoubleListNode<T>* current = front;
      while(current->data != d){
        current = current->next;
        if(current = NULL){
          return NULL;
        }
      }
      if(current == front){
        front = current->next;
      }
      else if(current == back){
        current->previous->next = current->next;
        back = current->next;
      }
      else{
        current->previous->next = current->next;
        current->next->previous = current->previous;
      }
      current->next = NULL;
      current->previous = NULL;
      size--;
      return current;
    }

    // Locates the index a specific value
    T Find(T d){
      int index = 0;
      DoubleListNode<T> *current = front;
      while(current != NULL){
        if(current -> data == d){
          break;
        }
        index++;
        current = current -> next;
      }
      //this is for when we reach the end of the list and still have not found the value
      if(current == NULL){
        index = -1;
      }
      return index;
    }
};
