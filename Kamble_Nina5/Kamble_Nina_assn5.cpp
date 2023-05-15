/*//////////////////////////////////////////////////
Name: Nina Nitin Kamble
ASU ID: nkamble@asu.edu
description: creating a doubly linked list from scratch and creating functions to edit the DLL as needed.
/////////////////////////////////////////////////////*/


#include "dllsmall.h"
#include "zombie.h"

#include <bits/stdc++.h>
using namespace std;

template <class T>
void MyDLL<T>::AddToFront(T new_data)//creating a node containing T data and add it to the front of the list 
{
  /* allocate node */
  Node<T>* new_node = new Node<T>();
 
  /* put in the data */
  new_node->data = new_data;
 
  /*Make next of new node as head
     and previous as NULL */
  if(head != NULL)//not empty dll
    {
      new_node->next = head;
      new_node->prev = NULL;
      /* Make prev of head_ref as new node */
      head->prev = new_node;
    }
  else//empty dll
    {
      new_node->next = NULL;
      new_node->prev = NULL;
    }

  /* move the head to point to the new node */
  head = new_node;
  size++;
}

template <class T>
void MyDLL<T>::AddToEnd(T new_data)//creating a node containing T data and add it to the end of the list 
{
  Node<T>* node=head;
  Node<T>* last=head;

  /*iterate to reach last node*/
  while (node != NULL)
    {
      last=node;
      node=node->next;
    }

  /* allocate node */
  Node<T>* new_node = new Node<T>();

  /* put in the data */
  new_node->data = new_data;

  /* This new node is going to be the last node, so
     make next of it as NULL*/
  new_node->next = NULL;

  /* If the Linked List is empty, then make the new
     node as head */
  if (head == NULL)
    {
      new_node->prev = NULL;
      head = new_node;
      return;
    }
  /* Change the next of last node */
  last->next = new_node;

  /* Make last node as previous of new node */
  new_node->prev = last;
  size++;

  return;
}

template <class T>
void MyDLL<T>::AddAtIndex(T data,int index)//creating a node containing T data and adding it to the list at index. 
{
  Node<T>* new_node = new Node<T>();
  new_node->data = data;

  if(index == 0)//add to front
    {
      new_node->next = head;
      head = new_node;
    }

  else
    {
      Node<T>* ptr = head;

      while((index>1) && (ptr->next !=NULL))//check if the index is not greater than size of the DLL
{
  ptr = ptr->next;
  --index;
}

      new_node->next = ptr->next;

      new_node->prev = ptr;

      if(new_node->next != NULL)
        ptr->next->prev = new_node;
      ptr->next=new_node;
    }
  size++;
}

template <class T>
void MyDLL<T>::AddBefore(Node<T>* node, T data)//creating a node containing T data and adding it before a particular node 
{
  if(node == NULL)
    {
      cout<<"the given previous node cannot be NULL\n";
      return;
    }

  Node<T>* current= new Node<T>();

  current->data = data;
  current->prev=node->prev;
  current->next=node;
  node->prev->next=current;
  node->prev=current;
  size++;
}

template<class T>
void MyDLL<T>::AddAfter(Node<T>* prev_node, T data)//creating a node containing T data and adding it after a particular node 
{
  if(prev_node == NULL)
    {
      cout<<"the given previous node cannot be NULL\n";
      return;
    }

  Node<T>* current= new Node<T>();

  current->data = data;
  current->next = prev_node->next;
  current->prev = prev_node;

  if(current->next != NULL)
    prev_node->next->prev = current;
  prev_node->next=current;
}



template <class T>
Node<T>* MyDLL<T>::RemoveFromFront()//Deleting first item and returning its contents 
{
  Node<T>* current=head;

  if(head==NULL)//if DLL is empty
    cout<<"DLL is Empty\n";

  else //if DLL is not empty
    {
      cout<<"Item being deleted:"<<head->data<<"\n";
      head = head->next;
      head->prev=NULL;
      delete(current);  //deleting first item
    }
  size--;
  return current;
}

template <class T>
Node<T>* MyDLL<T>::RemoveFromEnd()//Deleting last item and returning its contents
{
  Node<T>* current=head;

  if(head==NULL)//if DLL is empty
    cout<<"DLL is Empty\n";

  else if(head->next==NULL)//if DLL has only one item
    {
      cout<<"Item being deleted:"<<head->data<<"\n";
      delete(head);
      head=NULL;
    }

  else //if DLL has more than one items
    {
      while(current->next != NULL)
        {
          current=current->next;
        }
      cout<<"Item being deleted:"<<current->data<<"\n";
      current->prev->next=NULL;
      delete(current);
    }
  size--;
  return current;
}

template <class T>
void MyDLL<T>::RemoveTheFirst(T data)//finding first instance of T data and removing it 
{
  Node<T>* current=head;

  if(head==NULL)//if DLL is empty
    cout<<"DLL is Empty\n";

  else if((head->next==NULL) && (current->data==data))//if DLL has only oneitem
  {
    delete(head);
    head=NULL;
  }

  else //if DLL has more than one items
    {
      while((current->next != NULL) && (current->data!=data))
        {
          current=current->next;
        }

      if(current->data==data)
        {
          cout<<"Item being deleted:"<<current->data<<"\n";

          if(current->next == NULL) //if current is the last item in the DLL
            {
              current->prev->next=NULL;
              delete(current);
            }
	  else if(current->prev != NULL)//if current is not the first element
	    {
	      current->next->prev=current->prev;
	      current->prev->next=current->next;
	      delete(current);
	    }
          else if(current->prev == NULL)//current is the first element
            {
              head=head->next;
              head->prev=NULL;
              delete(current);
            }
        }
      else
        cout<<"Item not found\n";
    }
  size--;
}


template<class T>
T MyDLL<T>::RemoveBefore(Node<T>* node)//delete the node before a particular node, return its contents 
{
  Node<T>* temp;
  int val=NULL;
  if(node == NULL)
    {
      cout<<"the given node cannot be NULL\n";
      return val;
    }

  if(node->prev != NULL)//check if node is not the first node
    {
      if(node->prev->prev == NULL)//check if node is the second node
        {
          head=node;
          val=node->prev->data;
          delete(node->prev);
          node->prev=NULL;
        }
      else//node is 3rd or higher
        {
          node->prev->prev->next=node;
          temp=node->prev->prev;
          val=node->prev->data;
          delete(node->prev);
          node->prev=temp;
        }
    }
  return NULL;
}


template <class T>//delete the node after a particular node, return its contents 
T MyDLL<T>::RemoveAfter(Node<T>* node)
{
  Node<T>* temp;
  int val=-1;
  if(node == NULL)
    {
      cout<<"the given node cannot be NULL\n";
      return val;
    }

  if(node->next != NULL)//check if node is not the last node
    {
      if(node->next->next == NULL)//check if node is the second last node
        {
          val=node->next->data;
          delete(node->next);
          node->next=NULL;
        }
      else // node is third last or higher(from the end)
        {
          node->next->next->prev=node;
          temp=node->next->next;
          val=node->next->data;
          delete(node->next);
          node->next=temp;
        }
    }
  return NULL;
}


template <class T>
T MyDLL<T>::RemoveAllOf(T data)// finding each instance of T data and removing it 
{
  Node<T>* current=head;
  bool found=false;

  if(head==NULL)//if DLL is empty
    cout<<"DLL is Empty\n";

  else if((head->next==NULL) && (current->data==data))//if DLL has only one item
  {
    delete(head);
    head=NULL;
  }

  else //if DLL has more than one items
    {
      while(current != NULL)
        {

          if(current->data==data)
            {
              found=true;
              cout<<"Item being deleted:"<<current->data<<"\n";

	      if(current->next == NULL) //if current is the last item in th DLL
		{
		  current->prev->next=NULL;
		  delete(current);
		}
	      else if(current->prev != NULL)//if current is not the first element
		{
		  current->next->prev=current->prev;
		  current->prev->next=current->next;
		  delete(current);
		}

              else if(current->prev == NULL)//current is the first element
                {
                  head=head->next;
                  head->prev=NULL;
                  delete(current);
                }
            }
	  current=current->next;
        }
      if(!found)
        cout<<"Item not found:"<<data<<"\n";
    }
  size--;
}


template <class T>
bool MyDLL<T>::ElementExists(T data)//Returns a T/F if element exists in list 
{

  Node<T>* current=head;
  bool found=false;

  if(head==NULL)//if DLL is empty
    return found;

  else if((head->next==NULL) && (current->data==data))//if DLL has only one item
  {
    found=true;
    return found;
  }

  else //if DLL has more than one items
    {
      while((current->next != NULL) && (current->data!=data))
        {
          current=current->next;
        }

      if(current->data==data)
        {
          found=true;
          return found;
        }
    }
  return found;
}

template <class T>
Node<T>* MyDLL<T>::Find(T data)//Look for data in the list, return a pointer to its node 
{
  Node<T>* node = head;

  while (node !=NULL)//check if the index is not greater than size of the DLL
  {
    if(node->data==data)
      return node;
    node = node->next;
  }
  return node;
}

template <class T>
void MyDLL<T>::Empty()//Empty out the list, delete everything 
{
  Node<T>* node=head;
  Node<T>* temp;

  while (node !=NULL)
    {
      temp=node;
      node = node->next;
      head = node;
      delete(temp);
    }
}

template <class T>
T MyDLL<T>::RetrieveFront()//returns the data contained in the first node, does not delete it 
{
  if (head == NULL)//if DLL is empty
    cout<<"DLL is empty";

  else//if DLL is not empty
    {
      cout<<"Item being retrieved:"<<head->data<<"\n";
      return head->data;
    }
  return 0;
}

template <class T>
T MyDLL<T>::RetrieveEnd()//returns the data contained in the last node
{
  Node<T>* current = head;

  if(head==NULL)//if DLL is empty
    cout<<"DLL is Empty\n";

  else if(head->next==NULL)//if DLL has only one item
    {
      cout<<"Item being retrieved:"<<head->data<<"\n";
    }

  else //if DLL has more than one items
    {
      while(current->next != NULL)
        {
          current=current->next;
        }
      cout<<"Item being retrieved:"<<current->data<<"\n";
    }
  return 0;
}

template <class T>
T MyDLL<T>::Retrieve(int index)//returns the data contained in node # index
{
  Node<T>* temp;
  temp = head;
  int i = 0;

  if(index < 0 || index >= size)
    {
      throw "index out of bounds ";
    }

  while(temp != NULL)
    {
      if(i == index)
	{
	  return temp->value;
	}
      temp = temp->next;
      i++;
    }
  return -1;
}

template <class T>
int MyDLL<T>::Length()//length of DLL
{
  Node<T>* temp;

  temp = head;
  int count = 0;

  while(temp != NULL)
    {
      temp = temp->next;
      count++;
    }
  return count;
}

// This function prints contents of
// linked list starting from the given node
template <class T>
void MyDLL<T>::PrintList()//Printing contents of node
{
  Node<T>* node=head;
  Node<T>* last=head;

  while (node != NULL)
    {
      cout<<node->data<<"->"; 
      last=node;
      node=node->next;
    }
  cout<<"\n";
  node=last;
  /*
  cout<<"\nTraversal in reverse direction \n";//printing in reverse
  
  while (node != NULL)
    {
      cout<<node->data<<"->";
      node = node->prev;
    }
    cout<<"\n";
  */
}

template <class T>
Node<T>* MyDLL<T>::ItemAtIndex(int index)//returns the item at the given index number
{
  Node<T>* node = NULL;

  if(index == 0)//return the front node
    {
      node=head;
      return node;
    }

  else
    {
      Node<T>* ptr = head;

      while((index>=1) && (ptr->next !=NULL))//check if the index is not greater than size of the DLL
	{
	  ptr = ptr->next;
	  --index;
	}
      return ptr;
    }
}



int main()
{
  /*
  MyDLL<int>* myDLL = new MyDLL<int>(); 
  cout<<"MyDLL<int> created\n";
  Node<int>* node = NULL;
  */

  MyDLL<Zombie*>* congaline = new MyDLL<Zombie*>();
  cout<<"congaline:\n";
  srand ((unsigned) time(0));


  Zombie* zombie1=new Zombie();
  Zombie* zombie2=new Zombie();
  Zombie* zombie3=new Zombie();
  Zombie* zombie4=new Zombie();
  Zombie* zombie5=new Zombie();
  Zombie* zombie6=new Zombie();
  Zombie* zombie7=new Zombie();
  Zombie* zombie8=new Zombie();
  Zombie* zombie9=new Zombie();
  Zombie* zombie10=new Zombie();
  Zombie* zombie11=new Zombie();
  Zombie* zombie12=new Zombie();
  Zombie* zombie13=new Zombie();

  congaline->AddToFront(zombie3);
  cout<<"AddToFront(zombie3)\n";

  congaline->AddToFront(zombie6);
  cout<<"AddToFront(zombie6)\n";

  congaline->AddToEnd(zombie2);
  cout<<"AddToEnd(zombie2)\n";

  congaline->RemoveFromEnd();
  cout<<"RemoveFromEnd()\n";

  congaline->AddAtIndex(zombie12,3);
  cout<<"AddAtIndex(zombie12,3)\n";

  congaline->AddToFront(zombie4);
  cout<<"AddToFront(zombie4)\n";

  congaline->AddToFront(zombie5);
  cout<<"AddToFront(zombie5)\n";

  congaline->AddToFront(zombie6);
  cout<<"AddToFront(zombie6)\n";

  congaline->AddToFront(zombie7);
  cout<<"AddToFront(zombie7)\n";

  congaline->AddToFront(zombie8);
  cout<<"AddToFront(zombie8)\n";

  congaline->AddToFront(zombie1);
  cout<<"AddToFront(zombie1)\n";

  congaline->AddToFront(zombie9);
  cout<<"AddToFront(zombie9)\n";

  congaline->AddToFront(zombie10);
  cout<<"AddToFront(zombie10)\n";

  congaline->AddToFront(zombie11);
  cout<<"AddToFront(zombie11)\n";

  congaline->AddToFront(zombie13);
  cout<<"AddToFront(zombie13)\n";


  cout<<congaline;
 
  //return 0;
}
