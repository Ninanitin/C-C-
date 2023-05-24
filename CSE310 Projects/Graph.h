//********************************************************************
// ASU CSE310 Assignment #8 Fall 2022
// Name of Author: Nina Nitin Kamble
// ASU ID: nkamble
// Description: This is the header file that defines an undirected graph
//              with an array of vertice and edges. The graph methods are
//              here.
//********************************************************************

//include necessary header file here
#include <iostream>
#include <iomanip>
#include <string>
#include "Edge.h"

//----

using namespace std;

class Graph
{
 private:
  int V, E;             //number of vertice and edges in the graph
  City* setOfCities;    //an array of cities
  Edge* setOfEdges;     //an array of edges
  void QuickSort(int p, int r);
  int Partition(int p, int r);

 public:
  Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray);
  ~Graph();
  void make_set(City* aCity);
  City* find_set(City* aCity);
  void link(City* aCity, City* bCity);
  void Union(City* aCity, City* bCity);
  void SortEdges();
  void MST_Kruskal();

  //add any auxillary functions in case you need them
  //----
};

//finish each function according to above definition
//----
Graph::Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray)
{
  V=numOfCities;
  E=numOfEdges;
  setOfCities=cityArray;
  setOfEdges=edgeArray;
}

Graph:: ~Graph()
{
  delete[] setOfCities;
  delete[] setOfEdges;
  V=0;
  E=0;
}

void Graph::make_set(City* aCity)
{
  aCity->parent=aCity;
  aCity->rank=0;
}

City* Graph:: find_set(City* aCity)
{
  if(aCity != aCity->parent)
    aCity->parent=find_set(aCity->parent);
  return aCity->parent;
}

void Graph::link(City* aCity, City* bCity)
{
  if(aCity->rank > bCity->rank)
    bCity->parent=aCity;
  else
    {
      aCity->parent = bCity;
      if(aCity->rank == bCity->rank)
	bCity->rank=bCity->rank+1;
    }
      
}

void Graph::Union(City* aCity, City* bCity)
{
  link(find_set(aCity),find_set(bCity));
}

void Graph:: SortEdges()
{
  QuickSort(0,E-1);

  for(int j=0; j<E; j++)
    {
      cout<< left;
      cout << setw(15) << setOfEdges[j].getCity1()->cityName
           << setw(8) << "<--->"
           << setw(16) << setOfEdges[j].getCity2()->cityName
           << setw(8) << "=" << setOfEdges[j].getDistance() << endl;
    }
}

void Graph::QuickSort(int p,int r)
{
  int q;
  cout<<"p: "<<p<<" , r: "<<r<<endl;
  if(p<r)
    { 
      q=Partition(p,r);
      cout<<"q: "<<q<<endl;
      QuickSort(p,q-1);
      QuickSort(q+1,r);
    }
}

int Graph::Partition(int p,int r)
{
  Edge* arr = setOfEdges;
  int i;
  Edge temp;
  Edge x;
    
  x=arr[r];
  i=p-1;
  cout<<"p: "<<p<<" , r: "<<r<<endl;
  for(int j=p; j<r; j++)
    {
      cout<<"j: "<<j<<" , j.d: "<<arr[j].getDistance()<<endl;
      cout<<"r: "<<r<<" , x.d:"<<x.getDistance()<<endl;
      if(arr[j].getDistance() <= x.getDistance())
	{
	  i=i+1;
	  cout<<"check i+1"<<i+1<<endl;
	  temp=arr[i];
	  arr[i]=arr[j];
	  arr[j]=temp;
	}
    }
  cout<<"i+1="<<i+1<<" , r: "<<r<<endl;
  temp=arr[i+1];
  arr[i+1]=arr[r];
  arr[r]=temp;
  cout<<"return i+1= "<<i+1<<endl;
  return i+1;
}

//----
//*******************************************************************
//This function performs the Kruskal algorithm on the graph
void Graph::MST_Kruskal()
{
  cout << "MST Kruskal Algorithm Result\n" << endl;
  int totalDistance = 0;
  //----
  for(int i=0; i<V; i++)
    {
      make_set(&setOfCities[i]);
      cout<<"setOfCities["<<i<<"]"<<setOfCities[i].cityName<<endl;
    }
  //----
  //cout<<"in kruskal"<<endl;
  SortEdges();
  //cout<<"after sortedges()"<<endl;
  //----
  
  for(int j=0; j<E; j++)
    {
      cout<<"j: "<<j<<endl;
      //  cout<<"in for"<<endl;
      //cout<<"find_set "<<setOfEdges[j].getCity1()->cityName<<endl;
      //cout<<"find_set "<<setOfEdges[j].getCity1()->cityName<<" "<<find_set(setOfEdges[j].getCity1())->cityName<<endl;
      
      //cout<<"find_set "<<setOfEdges[j].getCity2()->cityName<<" "<<find_set(setOfEdges[j].getCity2())->cityName<<endl;
      cout<<"city1: "<<setOfEdges[j].getCity1()->cityName<<endl;
      cout<<"city2: "<<setOfEdges[j].getCity2()->cityName<<endl;

      cout<<"city1 set: "<<find_set(setOfEdges[j].getCity1())<<endl;
      cout<<"city2 set: "<<find_set(setOfEdges[j].getCity2())<<endl;;


      /*
      if(find_set(setOfEdges[j].getCity1()) != find_set(setOfEdges[j].getCity2()))
	{
	  cout<< left;
	  cout << setw(15) << setOfEdges[j].getCity1()->cityName
               << setw(8) << "<--->"
               << setw(16) << setOfEdges[j].getCity2()->cityName
               << setw(8) << "=" << setOfEdges[j].getDistance() << endl;
	  Union(setOfEdges[j].getCity1(), setOfEdges[j].getCity2());
	  totalDistance += setOfEdges[j].getDistance();
	}
      */

    }
 
  //----
  //----
  //----
  cout << "=================================================" << endl;
  cout << "Total Price: " << totalDistance << endl;
}
