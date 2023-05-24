//********************************************************************
// ASU CSE310 Fall 2022 Assignment #7
// Name:Nina Nitin Kamble
// ASU ID:nkamble(1221391951)
// Description: The driver file for assignment 7
//********************************************************************

//include necessary header file here
#include <iostream>
#include <string>
#include "ArrivalCityList.h"
#include "MinPriorityQueue.h"
#include "Graph.h"
//----

using namespace std;

void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList);
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance);     //**optional

int main()
{
  int count;       //a variable for number of nodes
  string oneLine, sourceCityName, sourceCity;
  string answer = "yes";       //a variable to decide whether to run Dijkstra multiple times
  string ans="yes";
  string depCityName;

  //  cout << "Enter number of cities: ";
  cin >> count;
  cin.ignore(20, '\n');

  //For each line of the file, we will create an ArrivalCityList(which is a linked list)
  //for a specific departure city. It represents all its reachable arrival cities with distance info.
  //Here we use an array of DepCity to store them
  DepCity* depCityArr = new DepCity[count];
  ArrivalCityList* arrCityList = NULL;
  MinPriorityQueue* minPQ = new MinPriorityQueue(count); //setting the capacity to count
  Graph* thisGraph=NULL; 

  //Initialize depCityArr. Set each node's d value to be very large 30000
  //initialize each arrival city list
  for(int i = 0; i< count; i++)
    {
      depCityArr[i].d = 10000+i;
      //----
      //----
    }

  //get input line by line and create the depCityArr
  for(int i = 0; i< count; i++)
    {
      getline(cin, oneLine);
      //----
      arrCityList=new ArrivalCityList();
      getCityInfo(oneLine, depCityName, arrCityList);
      depCityArr[i].depCityName= depCityName;
      depCityArr[i].arrCityList=arrCityList;
      //cout<<arrCityList->getArrCityList()<<endl;
      minPQ->insert(depCityArr[i]);

      //----
    }

  //create a Graph object
  thisGraph=new Graph(count, minPQ);
  //----

  //print the graph adjacency list before running Dijkstra algorithm
  cout << "\nPrint the graph adjacency list before running Dijkstra algorithm" << endl;

  minPQ->printHeap();
  
  while(ans.compare(answer)==0)
    {
      cout<<"\nEnter source city name: "<<endl;
      cin>>sourceCityName;
      cin.ignore(20, '\n');
      if(thisGraph->findOneCity(sourceCityName) != -1)
	{
	  //	  cout<<"index: "<<thisGraph->findOneCity(sourceCityName)<<endl;
	  thisGraph->dijkstra(sourceCityName);
	  thisGraph->printDijkstraPath(sourceCityName);
	}
      else
	cout<<sourceCityName<<" does NOT exist"<<endl;
      cout<<"\nFind shortest path for another departure city(yes or no): "<<endl;
      cin>>ans;
      cin.ignore(20, '\n');

    }
  //----

  //Next you need to design a sentinel value controlled while loop base on answer
  //If user answer is 'yes', get source city name, run Dijkstra algorithm, print
  //shortest path, then ask whether user want to continue or not...

}

//************************************************************************
//Give one line in input file, this function extract tokens and get departure city
//name and its arrival cities info.
void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList)
{
  //----
  string delimiter =",";
  string startDelimit="(";
  string endDelimit=")";
  string arrivalCity;
  size_t pos, posBo, posBc;
  int dDepArr;
  string token;
  pos=oneLine.find(delimiter);
  //cout<<"pos: "<<pos<<endl;
  token=oneLine.substr(0,pos);
  depCityName=token;
  //  cout<<"pos+demilength: "<<pos+delimiter.length()<<endl;
  oneLine.erase(0, pos+delimiter.length());
  //cout<<"depCityName: "<<depCityName<<endl;

  pos=oneLine.find(delimiter);

  while(pos != string::npos) //TODO:CLEANUP comments
    {
     
      token=oneLine.substr(0,pos);
      posBo=token.find(startDelimit);
      posBc=token.find(endDelimit);
      arrivalCity=token.substr(0,posBo);
      
      if((posBo != string::npos) && (posBc != string::npos))
	{
	  dDepArr=stoi(token.substr(posBo+startDelimit.length(),posBc-posBo-1));
	  arrCityList->addArrCity(arrivalCity, dDepArr);
	}

      oneLine.erase(0, pos+delimiter.length());      
      pos=oneLine.find(delimiter);
    }

  return;
  //----
}

//****************************************************************************
//Given one arrival city info. format of, such as Z(60), this function
//extract arrival city name 'Z' and distance 60 from it.
//this function is optional. Feel free to extract tokens using your own way
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance)
{
  //----
  return;
  //----
}
