//************************************************************************
// ASU CSE310 Assignment #8 Fall 2022
// ASU ID:nkamble
// Name:Nina Nitin Kamble
// Description: this is the main drivers program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph. It calls methods from Graph.h and Edge.h to create the graph
// //---- is where you need to add your own codes
//**************************************************************************
#include <iostream>
#include <string>
#include "Edge.h"
#include "Graph.h"

using namespace std;

void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance);
int searchCityArr(City* oneCityArray, int size, string oneCityName);

int main()
{
  int V, E;        //number of vertice and edges

  //cout << "Enter number of vertice and edges: " << endl;
  cin >> V >> E;
  cin.ignore(20, '\n');

  //a City array used to store all vertice (Cities) of the graph
  City* cityArray = new City[V];

  //an array used to store all edges of the graph
  Edge* edgeArray = new Edge[E];

  //----
  //----

  int i =0, j=0; //index for cityArray and edgeArray

  //local variables
  City* city1;
  City* city2;
  City* checkCity;
  Edge* aNewEdge;
  int check;

  string oneLine,token;
  string delimiter=",";
  string edgeCity;
  int edgeCityDist=0;
  int citySize=0, edgeSize=0;
  size_t pos;
  //cout << "Enter one departure and its arrival city info." << endl;
  getline(cin, oneLine);

  while(oneLine.compare("End") != 0)
    {
      //get one line of the input, extract the first token
      //create a City if it does not exist in cityArray,
      //insert it inside the cityArray. This will be first point of the 'aNewEdge'
      //----
      //cout<<"oneLine: "<<oneLine<<endl;
      pos=oneLine.find(delimiter);
      token=oneLine.substr(0,pos);
      //cout<<"token name city: "<<token<<endl;
      //      city1=new City(token);
      oneLine.erase(0, pos+delimiter.length());
      //cout<<"after erase: "<<oneLine<<endl;
      //cout<<"pos: "<<pos<<endl;
      check=searchCityArr(cityArray,citySize,token); 
      if(check == -1)//checking if the vertex exists, if not, adding city
	{
	  city1=new City(token);
	  cityArray[citySize]=*city1;
	  ++citySize;
	  //  cout<<"citySize: "<<citySize<<endl;
	  //cout<<"city1: "<<cityArray[citySize-1].cityName<<endl;
	}
      else
	{
	  city1=&(cityArray[check]);
	}
     //----

      //extract the arrival city info. check whether it exists in
      //cityArray or not, if not, create a new City, add it inside.
      //This city will be the second point of the 'aNewEdge'
      //----
      //cout<<"pos before: "<<pos<<endl;
      pos=oneLine.find(delimiter);
      //cout<<"pos after: "<<pos<<endl;
      while((pos != string::npos) && (pos != 0))
        {
          token=oneLine.substr(0,pos);
          getArrCityInfo(token,edgeCity,edgeCityDist);
	  //  cout<<"edgeCity: "<<edgeCity<<" edgeCityDistance: "<<edgeCityDist<<endl;
	 
	  check=searchCityArr(cityArray,citySize,edgeCity);
	  if(check == -1)//checking if the vertex exists, if not, adding city
	    {
	      city2=new City(edgeCity);
              ++citySize;
	      cityArray[citySize-1]=*city2;
	      //cout<<"citySize: "<<citySize<<endl;
	      //  cout<<"city2: "<<cityArray[citySize-1].cityName<<endl;
	    }
	  else
	    {
	      city2=&(cityArray[check]);
	    }
	  //----
	  
	  //by using the two cities we got above, create a new edge, add
	  //it inside edgeArray
	  //----
	  aNewEdge=new Edge(city1,city2,edgeCityDist);
	  edgeArray[edgeSize]=*aNewEdge;
	  edgeSize++;
	  //cout<<"edgeSize: "<<edgeSize<<endl;
	  //cout<<"edgecity1: "<<edgeArray[edgeSize-1].getCity1()->cityName<<endl;
	  //cout<<"EDGE: city1: "<<edgeArray[edgeSize-1].getCity1()->cityName<<", city2: "<<edgeArray[edgeSize-1].getCity2()->cityName<<" distance: "<<edgeArray[edgeSize-1].getDistance()<<endl;
	  
	  oneLine.erase(0, pos+delimiter.length());
          pos=oneLine.find(delimiter);

	  //----
	}
      //get next line
      //cout<<"\n"<<endl;
      getline(cin, oneLine);
    } //repeat until the 'End'
  
  //Create a Graph object by using cityArray and edgeArray
  //----
  Graph* myGraph = new Graph(V, E, cityArray, edgeArray);
  myGraph->MST_Kruskal();
  
  //Run Kruskal MST algorithm on above graph
  //----
}

//****************************************************************
//By giving a string, for example 'Y(1234)', this function
//extract the arrival city name 'Y' and distance '1234'
//Note: the delimiter is left and right parenthesis
//****************************************************************
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance)
{
  //----
 
  string startDelimit="(";
  string endDelimit=")";
  size_t pos, posBo, posBc;
  string token;
  pos=oneArrCityInfo.find(startDelimit);
  token=oneArrCityInfo.substr(0,pos);
  //cout<<"token: "<<token<<endl;
  posBo=oneArrCityInfo.find(startDelimit);
  posBc=oneArrCityInfo.find(endDelimit);
  arrCityName=token;
  //cout<<"arrCityName: "<<arrCityName<<endl;
  
  if((posBo != string::npos) && (posBc != string::npos))
    {
      distance=stoi(oneArrCityInfo.substr(posBo+startDelimit.length(),posBc-posBo-1));
      //  cout<<"distance: "<<distance<<endl;      
    }
}

  //----

//*********************************************************************
//Given a city name, this function searches cityArray and it return the
//index of the City if it exists, otherwise it returns -1
//****************************************************************
int searchCityArr(City* oneCityArray, int size, string oneCityName)
{
  //----
  for(int i=0; i<size; i++)
    {
      if(oneCityArray[i].cityName.compare(oneCityName)==0)
	return i;
    }
  return -1;
  //----
}
