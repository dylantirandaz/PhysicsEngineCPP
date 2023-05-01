#include <iostream>
using namespace std;
#ifndef NODE_H
#define NODE_H


class Node{
  private: //private member variables of coefficient, exponent, and node pointer
    double coef;
    int exp;
    Node* next;

  public: // public functions
    Node(); //default constructor
    
    Node(double c, int e); //overloaded constructor
    
    double getCoef() const; //accessors
    int getExp() const;
    Node* getNext() const;
    
    void setCoef(double coefficient);//mutators
    void setExp(int exponent);
    void setNext(Node* nextptr);

    //overloaded << operator
    friend ostream &operator << (ostream &out, Node* n);
};


#endif