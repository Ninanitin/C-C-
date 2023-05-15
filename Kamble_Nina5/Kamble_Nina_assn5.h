#ifndef _DLLSMALL_H_
#define _DLLSMALL_H_

#include <iostream>
#include <bits/stdc++.h>
#include <string>
using namespace std;
 
template <class T>
class MyDLL;

// A linked list node
template <class T>
class Node 
{
  friend class MyDLL <T>;

public:
  T data;
  Node* next;
  Node* prev;

  Node<T>()
  {
    next = NULL;
    prev = NULL;
  }

  friend ostream &operator<<( ostream &out, const Node<T>* node)//overloading operator << for node
  {
    out << node->data;
    return out;
  }

};

template <class T> 
class MyDLL
{
  private:
   Node<T>* head;
   int size;
public:
  MyDLL()
  {
    head = NULL;
    size = 0;
  } 
  //  ~MyDLL();


  void AddToFront(T);
  void AddToEnd(T);
  void AddAtIndex(T,int);
  void AddBefore(Node<T>*, T);
  void AddAfter(Node<T>*, T);
  Node<T>* RemoveFromFront();
  Node<T>* RemoveFromEnd();
  T RemoveBefore(Node<T>*);
  T RemoveAfter(Node<T>*);
  void RemoveTheFirst(T);
  T RemoveAllOf(T);
  bool ElementExists(T);
  Node<T>* Find(T);
  T RetrieveFront();
  T RetrieveEnd();
  T Retrieve(int);
  int Length();
  void PrintList();
  void Empty();  
  Node<T>* ItemAtIndex(int);
  
  //  template <class TT>
  friend ostream &operator<<( ostream &out, const MyDLL<T>* myDLL)//overloading operator << for MyDLL
    {
      Node<T> *temp = myDLL->head;
      while(temp != NULL)
	{
	  out<< temp->data<<"->";
	  temp=temp->next;
	}
      cout<<endl;
      return out;
    }
};
/*
MyDLL::~MyDLL()
{
  this->Empty();
}
*/

#endif
