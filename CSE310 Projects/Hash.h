// ASU CSE310 Assignment #5 Fall 2022
// Name of Author:Nina Nitin Kamble
// ASU ID:1221391951 (nkamble@asu.edu)
// Description: The hash functions are defined here. They are called in Assignment5.cpp. Most of them call functions in LinkedList.h
//
// such as hashInsert, hashDelete, hashSearch and hashDisplay
// ---- is where you should add your own code

#include "LinkedList.h"
#include <cmath>
#include <iomanip>
#include <ios>

using namespace std;

class Hash
{
 private:
  LinkedList** hashTable;     //hashTable is a one-dimensional array of LinkedList
  int m;                     //slots number of the hash table
 public:
  Hash(int size);
  ~Hash();
  bool hashSearch(string model, string make, int vin);
  bool hashInsert(string model, string make, int vin, double price);
  bool hashDelete(string model, string make, int vin);
  int hashLoadFactor();
  void hashDisplay();
  int hashFunction(string key);
};

//constructor
Hash::Hash(int size)
{
  //----
  m=size;
  hashTable=new LinkedList*[size];
  for(int i=0;i<size;i++)
    {
      hashTable[i]=new LinkedList();
    }
  //----
}

//Destructor
Hash::~Hash()
{
  //----
  delete[] hashTable;
  //----
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashSearch(string model, string make, int vin)
{
  bool found = false;
  //----
  string key=model+make+to_string(vin);
  found= hashTable[hashFunction(key)]->searchCar(vin);
  //----

  if (found == true)
      cout << "\n" << left
	   << setw(18) << model
	   << setw(18) << make
	   << setw(8)  << vin
	   << " is found inside the hash table." << endl;
  else
      cout << "\n" << left
           << setw(18) << model
           << setw(18) << make
           << setw(8)  << vin
           << " is NOT found inside the hash table." << endl;
  //----
  return found;
  //----
}

//hashInsert inserts a Car with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string model, string make, int vin, double price)
{
  //----
  bool success=false;
  string key=model+make+to_string(vin);
  success=hashTable[hashFunction(key)]->insertCar(model, make, vin, price);
  return success;
  //----
}

//hashDelete deletes a Car with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashDelete(string model, string make, int vin)
{
  //----
  bool found=false;
  string key=model+make+to_string(vin);
  found= hashTable[hashFunction(key)]->deleteCar(vin);
 
  //----
  if(found)
    {
      cout << "\n";
      cout << setw(18) << model
	   << setw(18) << make
	   << setw(8)  << vin
	   << " is deleted from hash table." << endl;
    }
  //----
  //----
  else
    {
      cout << "\n";
      cout << setw(18) << model
	   << setw(18) << make
	   << setw(8)  << vin
	   << " is NOT deleted from hash table." << endl;
    }
  //----
  return found; 
  //----
}

//This function computes your hash table real load factor
//it is the longest linked list size
int Hash::hashLoadFactor()
{
  //----
  int size=0,max=0;
  double idealLF, no=0, pr;
  for(int i=0; i<m; i++)
    {
      if(hashTable[i] != NULL)
	{
	  size=hashTable[i]->getSize();
	  no=no+size;
	  //cout<<"index: "<<i<<" size: "<<size<<endl;
	  if(size>max)
	    {
	      max=size;
	    }
	}
    }
  //  cout<<"The ideal load factor is: "<<max<<endl;
  idealLF=no/m;
  //  idealLF=ceil(idealLF*100.0)/100.0;
  cout<<"The ideal load factor is: "<<std::setprecision(3)<<idealLF<<endl;
  pr=max/idealLF;
  //  pr=ceil(pr*100.0)/100.0;
  cout<<"My hash table real load factor is: "<<std::setprecision(3)<<max<<endl;
  cout<<"My hash table performance ratio is: "<<std::setprecision(3)<<pr<<endl;
  cout<<"\n";
  return max;
  
  //----
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
  //----
  LinkedList* element;
  int c=0;
  for(int i=0; i<m; i++)
    {
      element=hashTable[i];
      c=element->getSize();
      cout<<"HashTable["<<i<<"], size = "<<c<<endl; //TODO: ADD SIZE
      element->displayList();
      cout<<"\n";
    }
  //----
}

//This is the hash function you need to design. Given a
//string key, the function should return the slot number
//where we will hash the key to
int Hash::hashFunction(string key)
{
  //----
  int len=key.length();
  int index=0, tot=0;

  for(int i=0; i<len; i++)
    {
      tot+=(int)key[i];
    }
  index=tot%m;
  //cout<<"index: "<<index<<endl;
  return index;
  //----
}
