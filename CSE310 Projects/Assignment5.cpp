// ASU CSE310 Assignment #5 Fall 2022
// Name of Author:Nina Nitin Kamble
// ASU ID:1221391951 (nkamble@asu.edu)
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.
// USE: ./ to compile. If there is an input file that us to be red, use 
// EXAMPLE: ./Assignment < inputfile.txt
// to output in a file, USE: ./Assignmnet < inputfile.txt > outputfile.txt
// ---- is where you need to add your own code

/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Car
//   object's hash value.
//(2)Did your hash function work well? For each of the four test cases, list here
//   your hash function's performance ratio and the longest LinkedList size.
//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
********************************************************************************/

#include "Hash.h"
#include <iostream> 
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

//This function used to get a Car key which is the combination of model, make and vin
void getCarInfo(string oneLine, string& model, string& make, int& vin, double& price);
void getSearchInfo(string oneLine, string& model, string& make, int& vin);

int main()
{
  int size = 0 ;
  int numOfCommand = 0;
  string model, make;
  int vin;
  double price;
  Hash* hashTable = NULL;//extra
  //declare any other necessary variables here
  string command, token, firstToken, thisLine, delimiter;
  int pos;
 
  if(std::cin)
    {
      cout<<"Enter the size of the hash table: "<<endl;
      getline(std::cin, thisLine, '\n');
      size = stoi(thisLine);//first line is the size
      //cout<<"size: "<<size<<"\n";
      hashTable= new Hash(size);
      getline(std::cin, thisLine, '\n');

      //use this do..while loop to repeatly get one line Car info. and extract tokens
      //create one Car object and insert it inside the hashTable until seeing the message

      do
	{
	  getCarInfo(thisLine, model, make, vin, price);
	  hashTable->hashInsert(model,make,vin,price);
          getline(std::cin, thisLine, '\n');

	}
      while(thisLine.compare("InsertionEnd") != 0);

    }

  //cout << "\nEnter number of commands: ";   //***need to comment out in submitting
  //cin >> numOfCommand;
  //cin.ignore(20, '\n');
  getline(std::cin, thisLine, '\n');
  numOfCommand=stoi(thisLine);
  //  cout<<"numOfCommand: "<<numOfCommand<<endl;
 
  for(int i= 0; i < numOfCommand; i++)
    {
      //get one line command, extract the first token, if only one token
      getline(std::cin, thisLine, '\n');
      delimiter = ",";
      pos=thisLine.find(delimiter);
      //      cout<<"pos: "<<pos<<endl;
      if(pos==-1)
	{
	  token=thisLine;
	}
      else
	{
	  token = thisLine.substr(0,pos);
	  command = token;
	  thisLine.erase(0, pos+delimiter.length());
	}
      
      if(token.compare("hashDisplay") == 0)
	{
	  //----
	  hashTable->hashDisplay();
	  //----
	}
      else if(token.compare("hashLoadFactor") == 0)
	{
	  hashTable->hashLoadFactor();
	}
      else  //more than one tokens, check the command name, extract the remaining tokens
	{
	  //----
	  //----
	  if(command.compare("hashSearch")==0)
            //----
	    {
	      getSearchInfo(thisLine, model, make, vin);
	      hashTable->hashSearch(model, make, vin);
	    }	      
	    //----
	  else if(command.compare("hashDelete")==0)
            //----
	    {
	      getSearchInfo(thisLine, model, make, vin);
	      hashTable->hashDelete(model,make,vin);
	    }
            //----
	  else if(command.compare("hashLoadFactor")==0)
            //----
	    {
	    }
	    //----
	  else
	    {
	      cout<<"Invalid command"<<endl;
	    }
	}
    } //end for loop  
  return 0;
}

//****************************************************************************************
//Given one line, this function extracts the model, make, vin info. of a Car
//This function is completed and given here as a study guide for extracting tokens
void getCarInfo(string oneLine, string& model, string& make, int& vin, double& price)
{
  string delimiter = ",";
  string token;
  int pos;
  pos=oneLine.find(delimiter);
  token = oneLine.substr(0,pos);
  model = token;
  oneLine.erase(0, pos+delimiter.length());

  pos=oneLine.find(delimiter);
  token = oneLine.substr(0,pos);
  make = token;
  oneLine.erase(0, pos+delimiter.length());

  pos=oneLine.find(delimiter);
  token = oneLine.substr(0,pos);
  vin = stoi(token);
  oneLine.erase(0, pos+delimiter.length());

  pos=oneLine.find(delimiter);
  token = oneLine.substr(0,pos);
  price = stod(token);
  oneLine.erase(0, pos+delimiter.length());

}

void getSearchInfo(string oneLine, string& model, string& make, int& vin)
{
  string delimiter = ",";
  int pos;
  string command;
  pos=oneLine.find(delimiter);
  string token = oneLine.substr(0,pos);
  model = token;
  oneLine.erase(0, pos+delimiter.length());

  pos=oneLine.find(delimiter);
  token = oneLine.substr(0,pos);
  make = token;
  oneLine.erase(0, pos+delimiter.length());

  pos=oneLine.find(delimiter);
  token = oneLine.substr(0,pos);
  vin = stoi(token);
  oneLine.erase(0, pos+delimiter.length());
}

