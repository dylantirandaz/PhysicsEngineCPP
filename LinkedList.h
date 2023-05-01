#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

class LinkedList{
  private:
    Node* head;
    int length;
    Node* del(Node* head); //destructor helper
    
  public:
    LinkedList(); //default constructor
    LinkedList(LinkedList &List); //overloaded constructor
    ~LinkedList(); //destructor
    

    Node* getHead() const; //accessors
    int getLength() const;

    void setHead(Node* headptr); //mutators
    void setLength(int len);
    void sortList(); //uses bubblesort
    void combineLikeTerms();
    void removeZeroCoeffTerms();
    //operators
    Node* operator[](int index) const; 
    friend ostream &operator << (ostream &out, LinkedList &L);
    void operator+=(Node* add);
};


#endif