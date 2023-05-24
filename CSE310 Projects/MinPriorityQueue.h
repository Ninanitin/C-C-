//********************************************************************
// ASU CSE310 Fall 2022 Assignment #7
// Name of Author: Nina Nitin Kamble
// ASU ID: nkamble(1221391951)
// Description: The methods of the min priority queue(min heap) are defined here.
//********************************************************************

//include necessary header file here
#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

#include<iostream>
#include<string>
#include<cmath>
#include "ArrivalCityList.h"

//----

using namespace std;

//represent each node of the graph which is a departure City
struct DepCity
{
  string depCityName;
  int d;
  struct DepCity* pi;
  ArrivalCityList* arrCityList;
};

//class MinPriorityQueue represents a Min-heap that contains DepCity objects.
//The key of each DepCity is its d value.

class MinPriorityQueue
{
 private:
  struct DepCity* depCityArr;        //a DepCity array
  int capacity, size;

 public:
  MinPriorityQueue(int capacity);
  ~MinPriorityQueue();

  DepCity* getDepCityArr();
  int getSize();
  void setSize(int sz);
  int getCapacity();
  int isFound(string oneDepCityName);
  bool decreaseKey(int index, DepCity oneDepCityWithNewDValue);
  bool insert(DepCity oneDepCity);
  void heapify(int index);
  DepCity getHeapMin();
  void extractHeapMin();
  int leftChild(int parentIndex);
  int rightChild(int parentIndex);
  int parent(int childIndex);
  void printHeap();
  void build_min_heap();
};


//*********************************************************
MinPriorityQueue::MinPriorityQueue(int capacity)
{
  size=0;
  this->capacity=capacity;
  depCityArr= new DepCity[capacity];
}

MinPriorityQueue::~MinPriorityQueue()
{
  delete[] depCityArr;
} 

void MinPriorityQueue::printHeap()
{

  cout << "\nHeap size = " << getSize() << "\n" << endl;

  cout << left;
  cout << setw(15) << "Dep. City"
       << setw(12) << "d Value"
       << setw(15) << "PI"
       << "Arrival City List" << endl;
  //----
  for(int i=0; i<size; i++)
    {
      if(depCityArr[i].pi)
	{
	  cout<< left;
	  cout << setw(15) << depCityArr[i].depCityName
	       << setw(12) << depCityArr[i].d
	       << setw(15) <<  depCityArr[i].pi
	       << depCityArr[i].arrCityList->getArrCityList()<<endl;
	}
      else
	{
	  cout<< left;
          cout << setw(15) << depCityArr[i].depCityName
               << setw(12) << depCityArr[i].d
               << setw(15) << "No Parent"
               << depCityArr[i].arrCityList->getArrCityList()<<endl;
	}
    }


  //----
}

//According to above class definition, define all other functions accordingly
//----
DepCity* MinPriorityQueue:: getDepCityArr()
{
  return depCityArr;
}

int MinPriorityQueue::getSize()
{
  return size;
}

void MinPriorityQueue::setSize(int sz)
{
  size=sz;
}

int MinPriorityQueue::getCapacity()
{
  return capacity;
}

int MinPriorityQueue::isFound(string oneDepCityName)
{
  string name;
  for(int i=0; i<=size; i++)
    {
      name=depCityArr[i].depCityName;
      if((name.compare(oneDepCityName) == 0))
	{
	  return i;
	}
    }
  return -1;
}
  
bool MinPriorityQueue::decreaseKey(int index, DepCity oneDepCityWithNewDValue)
{
  DepCity temp;
  int key_d;
  int parentndx = parent(index);
  key_d=oneDepCityWithNewDValue.d;

  if(index>size)
    {
      cout<<"index out of range"<<endl;
    }

  else if(key_d > depCityArr[index].d)
    {
      cout<<"error: new key is greater than current key"<<endl;
    }
  else
    { 
      depCityArr[index].d=key_d;
      while(index>0 && depCityArr[parent(index)].d > depCityArr[index].d)
	{
	  temp=depCityArr[index];
	  depCityArr[index]=depCityArr[parentndx];
	  depCityArr[parentndx]=temp;
	  index=parentndx;
	}
      return true;
    }
  return false;
}

bool MinPriorityQueue::insert(DepCity oneDepCity)
{
  ++size;
  if(size<=capacity)
    {
      depCityArr[size-1]= oneDepCity;
      return true;
    }
  else
    return false;
}

void MinPriorityQueue::heapify(int index)
{
  DepCity temp;
  int smallest=index;
  int left=leftChild(index);
  int right=rightChild(index);

  if(left < size && depCityArr[left].d<depCityArr[index].d)
    smallest=left;
  else
    smallest=index;

  if(right < size && depCityArr[right].d<depCityArr[index].d)
    smallest=right;
  if(smallest != index)
    {
      temp=depCityArr[index];
      depCityArr[index]=depCityArr[smallest];
      depCityArr[smallest]=temp;
      heapify(smallest);
    }
}

DepCity MinPriorityQueue::getHeapMin()
{
  return depCityArr[0];
}

void MinPriorityQueue::extractHeapMin()
{
  struct DepCity temp;

  //  cout<<"in extract, size: "<<size<<endl;
  if(size<1)
    {
      cout<<"not available"<<endl;
      return;
    }
  temp = depCityArr[0];
  depCityArr[0] = depCityArr[size-1];
  depCityArr[size-1]=temp;
  size--;
  heapify(0);
}

int MinPriorityQueue::leftChild(int parentIndex)
{
  return ((parentIndex*2)+1);
}

int MinPriorityQueue::rightChild(int parentIndex)
{
  return ((parentIndex*2)+2);
}

int MinPriorityQueue::parent(int childIndex)
{
  return ((childIndex-1)/2);
}

void MinPriorityQueue::build_min_heap()
{
  int i;
  for(i=floor(size/2); i>=0; i--)
    {
      heapify(i);
    }
}
//----
#endif
