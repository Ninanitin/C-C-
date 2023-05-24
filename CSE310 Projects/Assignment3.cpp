// Assignment: ASU CSE310 HW#3 Fall 2022
// Name:Nina Nitin Kamble
// ASU ID:nkamble (1221391951)
// ASU Email Address: nkamble@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             //---- is where you should add your own code
//********************************************************************************

#include "MaxHeap.h"

using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);

int main()
{
  char input1 = 'Z';
  int vin, newVIN;
  string model, make;
  double price;
  int capacity;   //array capacity 
  bool success = false;

  //declare any other variables in case you need them
  //----

  Car oneCar;
  Car maxCar;
  struct Car* carArr1;

  // instantiate an empty Heap
  MaxHeap* heap1 = nullptr;
  printMenu();

  do {
    cout << "\nWhat action would you like to perform?" << endl;
    cin.get(input1);
    input1 = toupper(input1);
    cin.ignore(20, '\n');//flush the buffer

    // matches one of the cases
    switch (input1)
      {
      case 'C'://create empty Heap with the relevant capacity
	cout << "\nPlease enter the heap capacity: ";
	cin >> capacity;
	cin.ignore(20, '\n');//flush the buffer

	//Add your own code
	heap1= new MaxHeap(capacity);
	//----

	break;

      case 'D'://delete the heap, call the destructor explicitly
	cout << "\nDelete the heap" << endl;
	//Add your own code
	delete[] heap1;
	//----
	
	//re-initialize it with capacity 5
	//Add your own code
	capacity=5;
	heap1= new MaxHeap(capacity);
	//----
	break;

      case 'E'://Extract the maximum node
	if (heap1 == nullptr)
	  cout << "\nEmpty heap, can NOT extract max" << endl;
	else
	  {
	    //Add your own code
	    cout<<"Before extract heap max operation:\n";
	    heap1->printHeap();
	    heap1->extractHeapMax();
	    cout<<"After extract heap max operation:\n";
	    heap1->printHeap();
	    //----
	  }
	break;

      case 'F'://Find a Car
	cout << "\nEnter the car VIN you want to search: ";
	cin >> vin;
	cin.ignore(20, '\n');//flush the buffer
	int x;
	//Add your own code
	x=heap1->isFound(vin);
	if(x==(-1))
	  cout<<"\nCar with VIN:"<<vin<<" is NOT found"<<endl;
	else 
	  cout<<"\nCar with VIN:"<<vin<<" is found"<<endl;
	//----

	break;

      case 'I'://Insert a Car
	cout << "\nEnter the car model: ";
	cin >> model;

	cout << "\nEnter the car make: ";
	cin >> make;

	cout << "\nEnter the car VIN: ";
	cin >> vin;
	cout << "\nEnter the car price: ";
	cin >> price;
	cin.ignore(20, '\n');//flush the buffer

	//Add your own code
	success=heap1->heapInsert(vin, model, make, price);
	if(success==true)
	  {
	    cout<<"\nCar \""<<model<<" "<<make<<"\" is added"<<endl;
	  }
	else 
	  {
	    cout<<"\nCar"<<make<<" "<<model<<" is NOT added"<<endl;
	  }
	//----

	break;
	
      case 'K'://increase the vin
	cout << "\nEnter the old car VIN you want to increase: ";
	cin >> vin;
	cout << "\nEnter the new car VIN: ";
	cin >> newVIN;
	cin.ignore(20, '\n');//flush the buffer
	if(newVIN<vin)
	  {
	    cout<<"Increase VIN error: new vin is smaller than current vin"<<endl;
	  }

	//Add your own code
	
	int indexVINold;
	indexVINold=heap1->isFound(vin);
	if(indexVINold != -1)
	  {
	    carArr1=heap1->getCarArr();
	    carArr1[indexVINold].vin = newVIN;
	    success = heap1->heapIncreaseVIN(indexVINold,carArr1[indexVINold]);
	  }
	else
	  cout<<"The old VIN you try to increase does not exist"<<endl;


	if(success==true)
	  {
	    cout<<"Before increase VIN operation: "<<endl;
	    heap1->printHeap();
	    cout<<"Car with old vin: "<<vin<<" is increased to new VIN: "<<newVIN<<endl;
	    cout<<"After increase VIN operation: "<<endl;
	    heap1->printHeap();
	  }	
	else
	  cout<<"The new VIN you entered already exist, increase VIN operation failed"<<endl;
      
	//----

	break;
	
      case 'M'://get maximum node

	//Add your own code
	maxCar= heap1->getHeapMax();
	if(heap1->getSize() != 0)
	  {
	    cout<<"The maximum heap node is: "<<endl;
	    cout << left;
	    cout << setw(8) << maxCar.vin
		 << setw(12) << maxCar.model
		 << setw(12) << maxCar.make
		 << setw(8) << fixed << setprecision(2) << maxCar.price << endl;
	  }
	else 
	  cout<<"Empty heap, can NOT get max node"<<endl;
	//----

	break;
	
      case 'P'://Print heap contents

	//Add your own code
	if(heap1 != NULL)
	  {
	    heap1->printHeap();
	  }
	else
	  cout<<"Empty heap, no elements"<<endl;
	//----

	break;
		
      case 'S'://HeapSort
	cout << "\nHeap sort. Cars will be sorted in increasing order of their VINs" << endl;
	//Add your own code
	heapSort(heap1);	
	
	//----
	break;
	
      case 'Q'://Quit
	delete heap1;
	break;
	
      case '?'://Display Menu
	printMenu();
	break;

      default:
	cout << "Unknown action\n";
	break;
      }
  } while (input1 != 'Q');
  return 0;
}

//*****************************************************
//Given a max heap, we want to sort it in increasing order according to Car VIN, put the
//sorting result inside another array and print it out
void heapSort(MaxHeap* oneMaxHeap)
{
  Car temp;
  Car oneCar;
  struct Car* carArrSort;
  int size=oneMaxHeap->getSize();
  //Add your own code
  for(int i=(size-1); i>=1; i--)
    {
      //temp=oneMaxHeap[0];
      carArrSort=oneMaxHeap->getCarArr();
      temp=carArrSort[0];
      carArrSort[0] = carArrSort[i];
      carArrSort[i] = temp;
      oneMaxHeap->setSize(i);
      oneMaxHeap->heapify(0);
    }      
  for(int j=0; j<size; j++)
    {
      oneCar=carArrSort[j];
      cout<< left;
      cout << setw(8) << oneCar.vin
	   << setw(12) << oneCar.model
	   << setw(12) << oneCar.make
	   << setw(8) << fixed << setprecision(2) << oneCar.price << endl;
    }
}

//**The function displays the menu to a user**
void printMenu()
{
  cout << "Choice\t\tAction\n";
  cout << "------\t\t------\n";
  cout << "C\t\tCreate a heap\n";
  cout << "D\t\tDelete the heap\n";
  cout << "E\t\tExtract max node\n";
  cout << "F\t\tFind a Car by VIN\n";
  cout << "I\t\tInsert a Car\n";
  cout << "K\t\tIncrease the VIN\n";
  cout << "M\t\tGet the max node\n";
  cout << "P\t\tPrint the heap\n";
  cout << "S\t\tHeap Sort\n";
  cout << "Q\t\tQuit\n";
  cout << "?\t\tDisplay Help\n\n";
}
