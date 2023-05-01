#include <iostream>
#include "LinkedList.h"
using namespace std;

LinkedList::LinkedList(){ //default constructor
  head = nullptr;
  length = 0;
}

LinkedList::LinkedList(LinkedList &List){ //copy constructor
    if(List.head == nullptr){
      this -> head = nullptr;
      return;
    }
    
    this -> head = List.head;
    this -> length = List.length;

    Node* start = this -> head;
    Node* original = List.head;
    Node* curr;
    while((original -> getNext()) != nullptr){
      original = original -> getNext();
      curr = new Node(original -> getCoef(), original -> getExp());
      start -> setNext(curr);
      start = start -> getNext();   
    }
}

LinkedList::~LinkedList(){
  del(head);
}

Node* LinkedList::del(Node* head){
    if (head == nullptr){
      delete head;
      return nullptr;
    }

    Node* ptr = head;    
    head = head -> getNext();
    delete ptr;
    return head;
}

//accessors
Node* LinkedList::getHead() const{
  return head;
}
    
int LinkedList::getLength() const{
  return length;
}

//mutators
void LinkedList::setHead(Node* headptr){
  if(headptr == nullptr){
    head = nullptr;
    this -> setLength(0);
    return;
  }

  head = headptr;
  this -> setLength(1);

  if(headptr == this->getHead()) {
    int count = 1;
    Node* ptr = head->getNext();
    while(ptr != nullptr){
      count++;
      ptr = ptr -> getNext();
    }
    this -> setLength(count);
  }
}

void LinkedList::setLength(int len){
  length = len;
}


//For head mutator, make sure to update the length of the linkedlist
void LinkedList::sortList(){
 
  int track;
  Node *Ptr, *A;
  Node *X, *Y;

  A = nullptr;
  do{
    track = 0;
    Ptr = this -> getHead();
    

    while(Ptr -> getNext() != A){
      if((Ptr -> getExp()) < (Ptr -> getNext() -> getExp())){
          X = Ptr;
          Y = Ptr -> getNext();
          
          
          int temp = X -> getExp();
	        X -> setExp(Y -> getExp());
          Y -> setExp(temp);
          
          double temp2 = X -> getCoef();
	        X -> setCoef(Y -> getCoef());
          Y -> setCoef(temp2);
          
          
          track = 1;
      }
      Ptr = Ptr -> getNext();
    }
    A = Ptr;

  }while(track);

}

//Combines Like Terms based on the list being sorted in descending order
void LinkedList::combineLikeTerms() {
  Node* current = head;
  
  while (current && current->getNext()) {
    if (current->getExp() == current->getNext()->getExp()) {
      double sum = current->getCoef() + current->getNext()->getCoef();
      current->setCoef(sum);
      Node* temp = current->getNext();
      current->setNext(temp->getNext());
      delete temp;
      length--;
    } else {
      current = current->getNext();
    }
  }
}

void LinkedList::removeZeroCoeffTerms() {
    Node *current = head;
    Node *prev = nullptr;
    while (current) {
        if (current->getCoef() == 0) { // check if the current node's coefficient is zero
            Node* temp = current;
            current = current->getNext(); // move current to the next node before deleting the current node
            if (prev) {
                prev->setNext(temp->getNext());
            } else {
                head = temp->getNext();
            }
            delete temp;
            length--;
        } else {
            prev = current;
            current = current->getNext();
        }
    }
}



//operators
//overloaded [] operator
Node* LinkedList::operator[](int index) const{
    if(this -> head == nullptr){
      return nullptr;
    }
    int pos = 0;
    Node* ptr = this -> head;
    
    if(index == 0){
      return ptr;
    }
    
    while(ptr != nullptr){
      if(pos == index){
        return ptr;
      }
      ptr = ptr -> getNext();
      pos++;
    }
    return nullptr;
}

ostream &operator << (ostream &out, LinkedList &L){
    for(int i = 0; i < L.getLength(); i++){
      if(L[i] -> getCoef() < 0){
        if(i != 0)
          out << " - " << L[i];
        else
          out << "-" << L[i];
      }
      else{
        if(i != 0){
          out << " + " << L[i];
        }
        else 
          out << L[i];
      }
    }
    return out;
}

void LinkedList::operator+=(Node* add){
  add -> setNext(nullptr);
  
  
  Node* ptr = this -> head;
  if(this -> head == nullptr){
    this -> setHead(add);
    this -> setLength(1);
    return;
  }

  else {
    
    while(ptr -> getNext() != nullptr){
      ptr = ptr -> getNext();
    }
    ptr -> setNext(add);
    this -> setLength(this -> getLength() + 1);
  }
}