// Assignment: ASU CSE310 HW#3 Fall 2022
// Your Name:Nina Nitin Kamble
// ASU ID:nkamble (1221391951)
// ASU Email address: nkamble@asu.edu
// Description: Class definition for MaxHeap. Function definitions.
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

//Each Car will have a unique vin
struct Car
{
  string model, make;
  int vin;        //Vehicle Identification Number
  double price;
};

//class MaxHeap represents a max heap that contains Car objects. The underline data structure
//is a one dimensional array of Cars.
class MaxHeap
{
 private:
  struct Car* carArr;//an array of Cars
  int capacity, size;

 public:
  MaxHeap(int capacity);
  ~MaxHeap();

  Car* getCarArr();
  int getSize();
  void setSize(int newSize);
  int getCapacity();
  int isFound(int aVin);
  bool heapIncreaseVIN(int index, Car oneCarWithNewVIN);
  bool heapInsert(int vin, string model, string make, double price);
  void heapify(int index);
  Car getHeapMax();
  void extractHeapMax();
  int leftChild(int parentIndex);
  int rightChild(int parentIndex);
  int parent(int childIndex);
  void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacity)
{
  //Add your own code
  size=0;
  //  cout<<"Enter capacity of the Heap:";
  //cin>> capacity;
  this->capacity=capacity;
  carArr= new Car[capacity];//dynamic allocation of memory for this array
  //----
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
  //Add your own code
  int carCount=0;
  for(int i=0; i<=size; i++)
    {
      //      delete &carArr[i];
      carCount++;
    }
  delete[] carArr;
  //----
  cout << "\nThe number of deleted cars is: " << carCount << endl;
}

Car* MaxHeap:: getCarArr()
{
  return carArr;
}

int MaxHeap:: getSize()
{
  return size;
}

void MaxHeap:: setSize(int newSize)
{
  size=newSize;
}

int MaxHeap:: getCapacity()
{
  return capacity;
}

int MaxHeap:: isFound(int aVin)
{
  for(int i=0;i<=size;i++)
    {
      if((carArr[i].vin)==aVin)
	{
	  return i; 
	}
    }
  return -1;
} 
//****************************************************
//increase the Car's VIN located at the specific index
bool MaxHeap::heapIncreaseVIN(int index, Car oneCarWithNewVIN)
{
  Car temp;
  int parentndx= floor((index-1)/2);
  if (index>size)
    {
      cout << "\nIncrease VIN error: index out of range" << endl;
      return false;
    }

    //Add your own code
    //----
  /*  else if(carArr[index].vin > oneCarWithNewVIN.vin)
    {
      cout<<"error: new vin is smaller than old vin"<<endl;
      return false;
    }
  */
  else
    {
      carArr[index].vin=oneCarWithNewVIN.vin;
      while(parentndx>=0 && carArr[parentndx].vin < carArr[index].vin)
	{
	  // cout<<"swapping check "<<index<<" index vin "<<carArr[index].vin<<" parentindex:"<<parentndx<<" parent vin "<<carArr[parentndx].vin<<endl;
	  //	  heapify(parentndx);
	  temp=carArr[index];
	  carArr[index]=carArr[parentndx];
	  carArr[parentndx]=temp;
	  index=parentndx;
	  parentndx=floor((index-1)/2);
	}

      return true;
    }
}
  //Add your own code to finish other functions
  //----
bool MaxHeap::heapInsert(int vin, string model, string make, double price)
{
  if(size+1 >= capacity)//TODO handling doubling of capacity
    {
      capacity *= 2;      
      struct Car* doubleCarArr;
      doubleCarArr= new Car[capacity];
      for(int i=0;i<size;i++)
	{
	  doubleCarArr[i]=carArr[i];
	}
      delete[] carArr;
      carArr=doubleCarArr;
    }

  //TODO check if VIN already exists before inserting
  struct Car* another = new (struct Car);
  another->vin=vin;
  another->model=model;
  another->make=make;
  another->price=price;
  carArr[size]= *another;
  //int parentndx=floor((size-1)/2);
  size++;
  carArr[size].vin=-10000;
  heapIncreaseVIN(size-1, carArr[size-1]);
  /*
  if(vin > carArr[parentndx].vin)
    {
      cout<<"heapify parentndx "<<parentndx<<" parent vin:"<<carArr[parentndx].vin<<" current index "<<size-1<<" current vin "<<vin<<endl;
      heapify(parentndx);
      }
  */
  return true;
} 

void MaxHeap::heapify(int index)
{
  Car temp;
  int large=index;
  int left=(index*2)+1;
  int right=(index*2)+2;
  //cout<<"in heapify index"<<index<<endl;
  //cout<<"left index: "<<left<<" left.vin: "<<carArr[left].vin<<endl;
  //cout<<"right index: "<<right<<" right.vin: "<<carArr[right].vin<<endl;

  if(index>(size/2) && index <=size)
    return;

  if(left<size && carArr[left].vin>carArr[index].vin)
    large=left;
  else 
    large=index;
  
  if (right<size && carArr[right].vin>carArr[large].vin)
    large=right;
  
  if (large != index)
    {
      //  cout<<"swapping index "<<index<<"  with large "<<large<<endl;
      temp=carArr[index];
      carArr[index]=carArr[large];
      carArr[large]=temp;
      heapify(large);
    }
}     

 
Car MaxHeap::getHeapMax()
{
  return carArr[0];
}

void MaxHeap::extractHeapMax()
{
  carArr[0]=carArr[size-1];
  heapify(0);
  size=size-1;
}

int MaxHeap::leftChild(int parentIndex)
{
  int left = (parentIndex*2)+1;
  return left;
}

int MaxHeap::rightChild(int parentIndex)
{
  int right = (parentIndex*2)+2;
  return right;
}

int MaxHeap::parent(int childIndex)
{
  int child=childIndex/2;
  return child;
}

void MaxHeap::printHeap()
{
  Car oneCar;
  if(size == 0)
    cout<<"Empty heap, no elements"<<endl;
  else
    {
      cout<<"\nHeap Capacity = "<<capacity<<endl;
      cout<<"\nHeap Size = "<<size<<"\n"<<endl;

      for(int i=0;i<size; i++)
	{
	  oneCar=carArr[i];
	  cout<< left;
	  cout << setw(8) << oneCar.vin
	       << setw(12) << oneCar.model
	       << setw(12) << oneCar.make
	       << setw(8) << fixed << setprecision(2) << oneCar.price << endl;
	}
    }
}
