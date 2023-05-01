#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "Node.h"
#include "LinkedList.h"
using namespace std;

//creates a node when given a string equation + the sign of the equation
//Function will parse the equation for operators & exponents signs
//and split each term of the equation into nodes 
//and each equation will be its own linkedlist
Node* createNode(string str, string sign){
  double c = 5;
  int e = 6;
  
  if(sign == "+"){
    if(str.find("^") < size_t(str.length())){
      if(str[0] == 'x'){
        c = 1;
        e = stoi(str.substr(str.find("^") + 1, str.length() - str.find("^")));
      }
      
      else{
        c = stod(str.substr(0, str.find("x")));
        e = stoi(str.substr(str.find("^") + 1, str.length() - str.find("^")));
      } 
    }
    
    else{
      if(str[0] == 'x'){
        c = 1;
        e = 0;
      }
      
      else{
        c = stod(str.substr(0, str.find("x")));
        e = 0;
      }
    }
  }
  
  else{
    if(str.find("^") < size_t(str.length())){
      if(str[0] == 'x'){
        c = -1 * 1;
        e = stoi(str.substr(str.find("^") + 1, str.length() - str.find("^")));
      }

      else{
        c = -1 * stod(str.substr(0, str.find("x")));
        e = stoi(str.substr(str.find("^") + 1, str.length() - str.find("^")));
      }
    }    
    
    else{
      if(str[0] == 'x'){
        c = -1 * 1;
        e = 0;
      }
      
      else{
        c = -1 * stod(str.substr(0, str.find("x")));
        e = 0;
      }
    }
  }
  
  Node* N = new Node(c, e);
  return N;
}

double evaluate(LinkedList *L, double eval){
  //evaluates equation, by applying the value to every node in the linkedlist
  double sum = 0.0;

  for(int i = 0; i < L -> getLength(); i++){
    sum += ((*L)[i] -> getCoef()) * pow(eval, (*L)[i] -> getExp());
  }
  
  return sum;
}

int main() {
 string fName;
 //cout << "Enter a file name: " << endl;
 cin >> fName;
 fstream dataFile(fName, ios::in);
 
 
 string expression = " ";
 int Opos = 0;
 int Cpos = 0;
 int startExp = 0;
 string polynomial = " ";
 bool firstTerm;
 string sign = " ";
 LinkedList *L = new LinkedList();
 double evaluator = 0.0;

 if(dataFile){
   while(dataFile.good()){
     
     
     getline(dataFile, expression);


     Opos = static_cast<int>(expression.find("("));
     Cpos = static_cast<int>(expression.find(")"));
     evaluator = stod(expression.substr(2, (Cpos - Opos) - 1));
     
     
     firstTerm = true;
     while(expression.length() > 0){
       if(firstTerm){
         startExp = static_cast<int>(expression.find("="));
         if(expression[startExp + 2] == '-'){
           sign = "-";
           expression.erase(0, startExp + 3);
           polynomial = expression.substr(0, expression.find(" "));
           *L += createNode(polynomial, sign);
           expression.erase(0, expression.find(" "));
         }
         else{
           sign = "+";
           expression.erase(0, startExp + 2);
           polynomial = expression.substr(0, expression.find(" "));
           *L += createNode(polynomial, sign);
           expression.erase(0, expression.find(" "));
           
         }
       }

       else{
         sign = expression[1];
         expression.erase(0, 3);
         polynomial = expression.substr(0, expression.find(" "));
         *L += createNode(polynomial, sign);
         expression.erase(0, expression.find(" "));
       }


       firstTerm = false;
     }
     L -> sortList(); //sort list first
     L->combineLikeTerms(); //now combine because it only works once it is already sorted
     L->removeZeroCoeffTerms();
     
     cout << fixed << showpoint;
     cout << setprecision(3);
     
     cout << *L << " = ";
     cout << evaluate(L, evaluator) << endl;

     L -> setHead(nullptr);
     L -> setLength(0);
     
   }//loops through entire file
 }//end of file check
    dataFile.close();
}//end of main 