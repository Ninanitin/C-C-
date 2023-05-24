//************************************************************************
// ASU CSE310 Assignment #6 Fall 2022
// Author: Nina Nitin Kamble
// ASU ID: 1221391951 (nkamble)
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition. Red Black Tree methods ar//e defined here.
//************************************************************************

//include the relevant header file
#include "RedBlackTree.h"
#include <iostream>
#include <iomanip>
//----

using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
  //----
  root=NULL;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
  //----
  int nodeSize=0;
  Node* curr=root;//inorder
  if(curr == NULL)
    return;
  
  nodeSize=deleteNode(curr);
  //----
  cout << "The number of nodes deleted: " << nodeSize << endl;
}

//**************************************************************
//Accessor for the root of the red-black tree

//write your own code according to red-black tree definition
Node* RedBlackTree::getRoot()
{
  return root;
}
//----
//*******************************************************************
void transplant(Node* root, Node* u, Node* v)
{
  cout<<"in transplant"<<endl;  
  if(u->parent == NULL)
    root=v;
  else if(u==u->parent->leftChild)
    u->parent->leftChild = v;
  else
    u->parent->rightChild = v;

  v->parent = u->parent;
}
//delete the sub-tree rooted at 'node' and return number of nodes deleted
//This should be defined as a recursive function
//write your own code according to red-black tree definition

int RedBlackTree:: deleteNode(Node *node)
{
  int count=0;
  if(node == NULL)
    return 0;
  count+=deleteNode(node->leftChild);
  count+=deleteNode(node->rightChild);
  delete node;
  node=NULL;
  count++;
  return count;
}

//----
//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.
//write your own code according to red-black tree definition
void RedBlackTree::insertNode(Node *node)
{
  Node* z= node;
  string zkey= to_string(node->vin)+node->model+node->make;
  Node* y= NULL;
  Node* x=root;
  string xkey;
  
  while(x!=NULL)
    {
      y=x;
      xkey= to_string(x->vin)+x->model+x->make;

      if(zkey.compare(xkey) < 0)
	x=x->leftChild;
      else
	x=x->rightChild;
    }
  if(y==NULL)
    root=z;
  else if(zkey.compare(xkey) < 0)
    {
      y->leftChild = z;
      z->parent=y;
    }
  else
    {
      y->rightChild=z;
      z->parent=y;
    }
}



//----


//*******************************************************************
//At beginning, each newly added node will always be RED,
//this may violate the red-black tree property #4. fixUp()
//function will restore the property.

//write your own code according to red-black tree definition

void RedBlackTree::fixUp(Node* node)
{
  Node *nodeparent = NULL;
  Node *nodegp= NULL;
  Node *uncle=NULL;
 
 
  while((node != root) && ((node->color.compare("RED")==0)) && (node->parent->color.compare("RED")==0))
    {
      nodeparent=node->parent;
      nodegp=node->parent->parent;

      if(nodeparent == nodegp->leftChild)//checking if node->parent is a left child
	{
	  uncle=nodegp->rightChild;

	  if(uncle != NULL && (uncle->color.compare("RED")==0))//case1- uncle is red and node is a left child
	    {
	      nodegp->color = "RED";
	      nodeparent->color = "BLACK";
	      uncle->color = "BLACK";
	      node = nodegp;
	    }
	  else // case 2- uncle is black and node is a right child
	    {
	      if(node == nodeparent->rightChild)//checking if node is a right child then left rotate
		{
                  node = nodeparent;
		  leftRotate(node);
		  nodeparent = node->parent;
		} 
	      else//case 3-uncle is black and node is a left child then right rotate
		{
		  rightRotate(nodegp);
		  swap(nodeparent->color, nodegp->color);
		  node = nodeparent;
		}
	    }
	}
      else//if node->parent is a right child
	{
	  uncle = nodegp->leftChild;
       
	  if((uncle != NULL) && (uncle->color.compare("RED")==0))
	    {
	      nodegp->color = "RED";
	      nodeparent->color = "BLACK";
	      uncle->color = "BLACK";
	      node = nodegp;
	    }
	  else
	    {
	      if(node==nodeparent->leftChild)
		{
		  rightRotate(nodeparent);
		  node=nodeparent;
		  nodeparent=node->parent;
		}
	      
	      leftRotate(nodegp);
	      swap(nodeparent->color, nodegp->color);
	      node = nodeparent;

	    }
	}
    }
  root->color="BLACK";
}

//----


//*****************************************************
//This function print the pre-order traversal of the
//subtree rooted at 'node'.It's a recursive function

//write your own code according to red-black tree definition

void RedBlackTree::preOrderTraversal(Node *node)
{
  Node* curr=node;
  if(curr==NULL)
    return;

  print(curr);
  preOrderTraversal(curr->leftChild);
  preOrderTraversal(curr->rightChild);
}

//----

//**************************************************
//This function print the in-order traversal of the
//subtree rooted at 'node'.It's a recursive function

//write your own code according to red-black tree definition
void RedBlackTree::inorderTraversal(Node *node)
{
  Node* curr=node;
  if(curr == NULL)
    return;

  inorderTraversal(curr->leftChild);
  print(curr);
  inorderTraversal(curr->rightChild);

}
//----

//**************************************************
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function

//write your own code according to red-black tree definition
void RedBlackTree::postOrderTraversal(Node* node)
{
  Node* curr= node;
  if(curr==NULL)
    return;
  postOrderTraversal(curr->leftChild);
  postOrderTraversal(curr->rightChild);
  print(curr);
}
//----


//**************************************************************
//This function returns a pointer points to the minimum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function

//write your own code according to red-black tree definition
Node* RedBlackTree::findMinimumNode(Node *node)
{
  Node* curr=node;
  while(curr->leftChild != NULL)
    {
      curr=curr->leftChild;
    }
  return curr;
}

//----

//**************************************************************
//This function returns a pointer points to the maximum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function

//write your own code according to red-black tree definition
Node* RedBlackTree::findMaximumNode(Node* node)
{
  Node* curr=node;
  while(curr->rightChild != NULL)
    {
      curr=curr->rightChild;
    }
  return curr;
}
//----


//**************************************************************
//This function search the tree for a given key of a Car
//Note: key is the combination of vin, model and make of the Car
//It returns a pointer points to the node if founded; otherwise it returns NULL

//write your own code according to red-black tree definition

Node* RedBlackTree::treeSearch(int vin, string model, string make)
{  
  string searchKey= to_string(vin)+model+make;
  Node* x=root;
  string xkey;
  
  while(x!=NULL)
    {
      xkey= to_string(x->vin)+x->model+x->make;
      if(xkey.compare(searchKey)==0)
	{
	  cout << left;
	  cout << setw(8)  << vin
	       << setw(12) << model
	       << setw(13) << make
	       << "is FOUND."<<endl;
	  return x;
	}
      else if(searchKey.compare(xkey) < 0)
	x=x->leftChild;
      else
	x=x->rightChild;
    }
  cout << left;
  cout << setw(8)  << vin
       << setw(12) << model
       << setw(13) << make
       << "is NOT FOUND."<<endl;

  return NULL;
}

//----

//****************************************************
//This function left-rotate the BST rooted at 'node'

//write your own code according to red-black tree definition
void RedBlackTree::leftRotate(Node *node)
{
  Node* y=NULL;
  Node* x=node;
  y= x->rightChild; //set y to the right child of x
  x->rightChild=y->leftChild; // turn y's left subtree into x's right subtree
  if(y->leftChild != NULL)
    y->leftChild->parent=x;
  y->parent=x->parent; //link x's parent to y
  if(x->parent == NULL)
    root=y;
  else if(x==x->parent->leftChild)
    x->parent->leftChild=y;
  else 
    x->parent->rightChild=y;
  y->leftChild=x;//put x on y's left
  x->parent=y;
}
//----


//***************************************************
//This function right-rotate the BST rooted at 'node'

//write your own code according to red-black tree definition
void RedBlackTree::rightRotate(Node* node)
{
  Node* y=NULL;
  Node* x=node;
  y=x->leftChild;
  x->leftChild=y->rightChild;//turn y's right subtree into x's left subtree
  if(y->rightChild != NULL)
    y->rightChild->parent=x; 
  y->parent=x->parent; //link x's parent to y
  if(x->parent==NULL)
    root=y;
  else if(x==x->parent->rightChild)
    x->parent->rightChild=y;
  else
    x->parent->leftChild=y;
  y->rightChild=x;//put x on y's right
  x->parent=y;
}

//----


//**************************************************************
//This function finds the predecessor of the given 'node'
//it prints the relevant predecessor info. on screen and also
//return a pointer that points to the predecessor

//write your own code according to red-black tree definition

Node* RedBlackTree:: findPredecessorNode(Node *node)
{
  Node* y=NULL;
  if(node == NULL)
    return NULL;
  if(node->leftChild != NULL)
    return findMaximumNode(node->leftChild);
  y=node->parent;
  while((y != NULL) && (node == y->leftChild))
    {
      node=y;
      y=y->parent;
    }
  return y;
}

//----

//**************************************************************
//This function finds the successor of the given 'node'
//it prints the relevant successor info. on screen and also return
//a pointer that points to the successor node

//write your own code according to red-black tree definition
Node* RedBlackTree::findSuccessorNode(Node *node)
{
  Node* y=NULL;
  if(node == NULL)
    return NULL;
  if(node->rightChild != NULL)
    return findMinimumNode(node->rightChild);
  y=node->parent;
  while((y != NULL) && (node == y->rightChild))
    {
      node=y;
      y=y->parent;
    }
  return y;
}
//----

//****************************************************************
//This function find the minimum node of the entire red-black tree
//It print out the minimum node info. on screen if tree is not empty
//or print Tree is empty. No Minimum. message on screen.

//write your own code according to red-black tree definition

void RedBlackTree::treeMinimum()
{
  Node* node=NULL;
  node=findMinimumNode(root);
  if(node==NULL)
    cout<<"tree is empty"<<endl;
  else
    {
      cout<<"The MINIMUM is:"<<endl;
      print(node);
    }
}

//----

//**************************************************************
//This function find the maximum node of the entire red-black tree
//It print out the maximum node info. on screen if tree is not empty
//or print Tree is empty. No Maximum. message on screen.

//write your own code according to red-black tree definition
void RedBlackTree::treeMaximum()
{
  Node* node=NULL;
  node=findMaximumNode(root);
  if(node==NULL)
    cout<<"tree is empty"<<endl;
  else
    {
      cout<<"The MAXIMUM is:"<<endl;
      print(node);
    }
}
//----

//****************************************************************************
//This function print out the pre-order traversal of the entire red-black tree

//write your own code according to red-black tree definition
void RedBlackTree::treePreorder()
{
  Node* node= root;
  preOrderTraversal(node);
}
//----

//***************************************************************************
//This function print out the in-order traversal of the entire red-black tree

//write your own code according to red-black tree definition
void RedBlackTree::treeInorder()
{
  Node* node= root;
  inorderTraversal(node);
}
//----

//*****************************************************************************
//This function print out the post-order traversal of the entire red-black tree

//write your own code according to red-black tree definition
void RedBlackTree::treePostorder()
{
  Node* node= root;
  postOrderTraversal(node);
}
//----

//******************************************************************
//Given a Car key, this function first check whether the
//Car is inside the tree or not, if it is inside, it will print
//its predecessor info. on screen, if not, it print an error message

//write your own code according to red-black tree definition
void RedBlackTree::treePredecessor(int vin, string model, string make)
{
  Node* predecessor=NULL;
  Node* node= treeSearch(vin, model, make);
  if(node)
    {
      predecessor=findPredecessorNode(node);
      if(predecessor)
	{
	  cout<<"Its Predecessor is: "<<endl;
	  print(predecessor);
	}
      else
	cout<<"Its Predecessor does NOT EXIST"<<endl;
    }
}
//----

//******************************************************************
//Given a Car key, this function first check whether the
//Car is inside the tree or not, if it is inside, it will print
//its successor info. on screen, if not, it print an error message

//write your own code according to red-black tree definition
void RedBlackTree::treeSucessor(int vin, string model, string make)
{
  Node* successor=NULL;
  Node* node= treeSearch(vin, model, make);
  if(node)
    {
      successor=findSuccessorNode(node);
      if(successor)
	{
	  cout<<"Its Successor is: "<<endl;
	  print(successor);
	}
      else
	cout<<"Its Successor does NOT EXIST"<<endl;
    }
}

//----

//**************************************************************
//This function create a node from the given info., then insert
//the node inside the red-black tree. Note: at beginning, the newly
//added node should always be 'RED'

//write your own code according to red-black tree definition

void RedBlackTree::treeInsert(int vin, string model, string make, double price)
{
  //string key=model+make+to_string(vin);
  Node *addNode=new Node();
  addNode->model=model;
  addNode->make=make;
  addNode->vin=vin;
  addNode->price=price;
  addNode->color="RED";
  addNode->leftChild=NULL;
  addNode->rightChild=NULL;
  insertNode(addNode);
  fixUp(addNode);  
}

//*******************************************************************
//**************************************************
//This function print the in-order traversal of the
//subtree rooted at 'node'.It's a recursive function

//write your own code according to red-black tree definition
//----

//**************************************************
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function

//write your own code according to red-black tree definition
//----


//**************************************************************
//This function returns a pointer points to the minimum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function

//write your own code according to red-black tree definition
//----

//**************************************************************
//This function returns a pointer points to the maximum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function

//write your own code according to red-black tree definition
//----


//**************************************************************
//This function search the tree for a given key of a Car
//Note: key is the combination of vin, model and make of the Car
//It returns a pointer points to the node if founded; otherwise it returns NULL

//write your own code according to red-black tree definition
//----

//****************************************************
//This function left-rotate the BST rooted at 'node'

//write your own code according to red-black tree definition
//----


//***************************************************
//This function right-rotate the BST rooted at 'node'

//write your own code according to red-black tree definition
//----


//**************************************************************
//This function finds the predecessor of the given 'node'
//it prints the relevant predecessor info. on screen and also
//return a pointer that points to the predecessor

//write your own code according to red-black tree definition
//----

//**************************************************************
//This function finds the successor of the given 'node'
//it prints the relevant successor info. on screen and also return
//a pointer that points to the successor node

//write your own code according to red-black tree definition
//----

//****************************************************************
//This function find the minimum node of the entire red-black tree
//It print out the minimum node info. on screen if tree is not empty
//or print Tree is empty. No Minimum. message on screen.

//write your own code according to red-black tree definition
//----

//**************************************************************
//This function find the maximum node of the entire red-black tree
//It print out the maximum node info. on screen if tree is not empty
//or print Tree is empty. No Maximum. message on screen.

//write your own code according to red-black tree definition
//----

//****************************************************************************
//This function print out the pre-order traversal of the entire red-black tree

//write your own code according to red-black tree definition
//----

//***************************************************************************
//This function print out the in-order traversal of the entire red-black tree

//write your own code according to red-black tree definition
//----
//******************************************************************
//Given a 'node', this function prints all the node information on screen

void RedBlackTree::print(Node *node)
{
  cout << left;
  cout << setw(8)  << node->vin
       << setw(12) << node->model
       << setw(12) << node->make
       << setw(10) << fixed << setprecision(2) << node->price;
  cout << right << setw(7) << node->color << endl;
}

//**************************************************************
//Given a Node 'node1', this function compares it with another
//node's key.
//key is a string combination of vin + model + make
//It returns a negative number if in alphabetical order, key2 is
//in front of 'node1'; otherwise it returns a positive number

//write your own code according to red-black tree definition
//----//----

//******************************************************************
//Given a 'node', this function prints all the node information on screen
/*void RedBlackTree::print(Node *node)
{
  cout << left;
  cout << setw(8)  << node->vin
       << setw(12) << node->model
       << setw(12) << node->make
       << setw(10) << fixed << setprecision(2) << node->price;
  cout << right << setw(7) << node->color << endl;
}
*/
//**************************************************************
//Given a Node 'node1', this function compares it with another
//node's key.
//key is a string combination of vin + model + make
//It returns a negative number if in alphabetical order, key2 is
//in front of 'node1'; otherwise it returns a positive number

//write your own code according to red-black tree definition
//----
