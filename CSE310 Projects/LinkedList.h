// ASU CSE310 Assignment #5 (Fall 2022)
// Name of Author:Nina Nitin Kamble
// ASU ID:1221391951
// Description: A simple linked list that implements a list of Car objects. The functions of the linkedlist are defined here. These functions are called in Hash.h
//              perform searching, insertion or deletion on the linked list.
//              //---- is where you should add your own code

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Car
{
  string model, make;
  int vin;
  double price;
  struct Car* next;
};

class LinkedList
{
 private:
  struct Car* head;
  int size;      //a variable represents number of Cars inside the list
 public:
  LinkedList();
  ~LinkedList();
  Car* getHead();
  int getSize();
  bool searchCar(int carVIN);
  bool insertCar(string model, string make, int vin, double price);
  bool deleteCar(int carVIN);
  void displayList();
};

//Constructor
LinkedList::LinkedList()
{
  //----
  head=NULL;
  //---
}

//Destructor
LinkedList::~LinkedList()
{
  //----
  Car* curr;
  curr=head;
  for(curr=head; head; curr=head)
    {
      head= head->next;
      delete curr;
    }
  //---
}

Car* LinkedList::getHead()
{
  //----
  return head;
}

//Return number of Cars inside the Linked list
int LinkedList::getSize()
{
  //----
  return size;
}

//This function does a linear search on the Car list with the given Car VIN
//it returns true if the corresponding Car is found, otherwise it returns false.
bool LinkedList::searchCar(int carVIN)
{
  //----
  Car* curr=head;
  while(curr != NULL)
    {
      if(curr->vin == carVIN)
	return true;
      curr=curr->next;
    }
  return false;
  /*  Car* curr=head;

  while(curr!=NULL)
    {
      if(curr->vin == carVIN)
        {
	  curr=curr->next;
          return true;
        }
      return false;
    }
  //---
  return true;*/
  //---
}

//Insert the parameter Car at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertCar(string model, string make, int vin, double price)
{
  //----
  Car* newCar = new Car;
  newCar->vin=vin;
  newCar->make=make;
  newCar->model=model;
  newCar->price=price;

  if(!(searchCar(newCar->vin)))//check if car already exists
    {
      //      cout<<"check done"<<endl;
      if(head==NULL)
	{
	  head=newCar;
	  head->next=NULL;
	  size++;
	  return true;
	}
      else
	{
	  newCar->next = head->next;
	  head->next=newCar;
	  size++;
	  return true;
	}
    }
  return false;
  //---
}

//Delete the Car with the given Car VIN from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteCar(int carVIN)
{
  //----
  Car* temp=head;
  Car* prev = NULL;
  
  if(temp != NULL && temp->vin ==carVIN)
    {
      head=temp->next;
      size--;  
      delete temp;
      return true;
    }
  else
    {
      while(temp != NULL && temp->vin != carVIN)
	{
	  prev=temp;
	  temp=temp->next;
	}
      if(temp==NULL)
	return false;
      prev->next=temp->next;
      size--;
      delete temp;
      return true;
    }
  return false;
}

//This function displays the content of the linked list.
void LinkedList::displayList()
{
  struct Car *temp = head;
  if(head == NULL)
    {
      //empty linked list, print nothing here
    }
  else
    {
      while(temp != NULL)
	{
	  cout << left    << setw(18) << temp->model
	       << left    << setw(18) << temp->make
	       << right   << setw(8)  << temp->vin
	       << setw(10) << fixed << setprecision(2) << temp->price << "\n";
	  temp = temp->next;
	}
    }
}
