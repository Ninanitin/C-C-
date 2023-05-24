//********************************************************************
// ASU CSE310 Fall 2022 Assignment #7
// Name of Author: Nina Nitin Kamble
// ASU ID: nkamble (1221391951)
// Description: The methods of the adjacency list(linked list) are defined in this file.
//********************************************************************

#ifndef ARRIVALCITYLIST_H
#define ARRIVALCITYLIST_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//#ifndef ARRIVALCITYLIST_H
//#define ARRIVALCITYLIST_H

//struct ArrCity represents an arrival city information with
//distance info. from a specific departure city
struct ArrCity
{
  string arrCityName;
  int distance;
  struct ArrCity* next;
};

//class ArrivalCityList is a linked list of ArrCity
//class ArrivalCityList will contains a linked list of ArrCity
class ArrivalCityList
{
 private:
  struct ArrCity* head;
  
 public:
  ArrivalCityList();
  ~ArrivalCityList();
  ArrCity* getHead();
  ArrCity* findArrCity(string oneCity);
  bool addArrCity(string oneCity, int distance);
  void printArrCityList();
  string getArrCityList();
};


ArrivalCityList::ArrivalCityList()
{
  head=NULL;
}

ArrivalCityList::~ArrivalCityList()
{
  ArrCity* curr=head;
  for(curr=head; head; curr=head)
    {
      head=head->next;
      delete curr;
    }
}

ArrCity* ArrivalCityList::getHead()
{
  return head;
}

ArrCity* ArrivalCityList::findArrCity(string oneCity)
{
  ArrCity* curr=head;
  while(curr != NULL)
    {
      if(curr->arrCityName.compare(oneCity)==0)
	return curr;
      curr=curr->next;
    }
  return NULL;
}

bool ArrivalCityList::addArrCity(string oneCity, int distance)
{
  ArrCity* newCity = new ArrCity();
  ArrCity* prevCity=head;
  ArrCity* currCity=head;
  newCity->arrCityName=oneCity;
  newCity->distance=distance;
  if(findArrCity(newCity->arrCityName) == NULL)
    {
      if(head==NULL)
	{
	  head=newCity;
	  head->next=NULL;
	  return true;
	}
      else
	{
	  //TODO: ADD IN ALPHABETICAL ORDER
	  while(currCity != NULL)
	    {
	      if(currCity->arrCityName.compare(newCity->arrCityName) < 0)
		{
		  if(currCity->next == NULL)//if currCity is last node
		    {
		      currCity->next = newCity;
		      return true;
		    }
		  else
		    {
		      prevCity=currCity;
		      currCity=currCity->next;
		    }
		}
	      else//currCity>newCity
		{
		  if(prevCity->next == NULL) //Add new city at the head
		    {
		      newCity->next=prevCity;
		      head=newCity;
		      return true;
		    }
		  else // add new city before prev city
		    {
		      prevCity->next=newCity;
		      newCity->next=currCity;
		      return true;
		    }
		}
	    }
	}
    }
  return false;
}

void ArrivalCityList::printArrCityList()
{
  struct ArrCity *temp= head;
  if(head == NULL)
    {
      cout<<"Arrival city list is empty"<<endl;
    }
  else
    {
      while(temp != NULL)
        {
	  cout << temp->arrCityName
	       << "("<< temp->distance<< "),"<< endl;
	  temp = temp->next;
	}   
    } 
}

string ArrivalCityList::getArrCityList()
{
  struct ArrCity *temp= head;
  string arrCL;
  if(head == NULL)
    {
      arrCL="Arrival city list is empty";
    }
  else
    {
      while(temp != NULL)
        {
	  arrCL+=temp->arrCityName+"("+ to_string(temp->distance)+"),";
          temp = temp->next;
        }
    }
  return arrCL;
}

//*******************************************************************
//ArrCity* findArrCity(string oneCity);
//A function to find whether the parameterized city is inside the LinkedList or not.
//returns a pointer that points to the city if it exist, otherwise return NULL

//*******************************************************************
//bool addArrCity(string oneCity, int distance);
//Creates a new ArrCity and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of the ArrCities while inserting
//it into the list. Note: you cannot insert duplicated ArrCity
//Return value: true if it is successfully inserted and false in case of failures.

//According to above class definition, define all functions accordingly
//----


//----
#endif
