/* 
Name: Nina Nitin Kamble  
Date: 04/10
Description: wavefront Path Finder using breadth-first search 
Usage: Use the usual ./Kamble_Nina_hw4.c to run the code. Enter the height, width and impassible terrain as asked. If you need to input a file, use -f followed by your input file name. Then enter start and goal positions. Your output path will be printed on the screen and in the output file wave.txt.
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h> 
//protocols for functions needed
void PrintEnvironment(int**, FILE* , int, int);
int myrand(int);
void setImpassTerrain(int**, int, int, int);
void setGoal(int**, int, int);
void printGoal(char**, int, int);
void printStart(char**, int, int);

void hcImpassTerrain(int**);

//defining structs
struct Position {
  int x,y;
};

struct Queue {
  int front, rear, size;
  unsigned capacity;
  struct Position* array;
};

//protocols for functions needed
struct Position dequeue(struct Queue*);
struct Position front(struct Queue*);
struct Position rear(struct Queue*);

struct Queue* createQueue(unsigned);
int isFull(struct Queue*);
int isEmpty(struct Queue*);
void enqueue(struct Queue* ,struct Position);
void runwave(int**, int**,struct Queue*, int, int);
void printPath(int**, char**, FILE*, int, int, int, int, int, int);
struct Position findPath(int**, char**, int, int, int, int, int, int);

int main(int argc, char** argv)
{ 
  FILE *ifile;  //input file to be read
  FILE *ofile = fopen("wave.txt","w"); //output file

  if(argc <= 3) //checking if user has inputted proper command lines
    {
      if(argc==1)
	;
      else if((argc==3) && ((strcmp("-f",argv[1]))==0))//checking for input file
	{
	  ifile = fopen(argv[2],"r");
	}
      else
	{
	  printf("Error -- usage: <%s> -f <input file: %s>\n",argv[0],argv[1]);  //printing error if invalid command is passed
	  exit(0);
	}
    }
  
 
  int w,h,it,i,j,gx,gy,sx,sy;
  char ans;
  printf("Welcome to CSE240 WaveFront Pather\n");
  if(argc==1)//reading width, height and impassible terrain percentage from the user/stdin
    {
      printf("Please tell me about the grid you want to generate.\n");
      printf("Enter the width (at least 10):\n");
      scanf ("%d",&w);
      printf("Enter the height (at least 10):\n");
      scanf ("%d",&h);
      printf("Enter the percent of impassible terrain (0 – 100):\n");
      scanf ("%d",&it);
  
      if(it>35)  //checking for impassible terrain
	{
	  printf("Having a value greater than 35 might create poor results, do you wish to continue? (y/n):\n");
	  scanf("%s",&ans);
	  if(ans == 'y')
	    {
	      printf("Enter the percent of impassible terrain (0 – 100):\n");
	      scanf ("%d",&it);
	      printf("it:%d",it);
	    }
	  else
	    {
	      printf("exiting Wavefront Pathfinder\n");
	      exit(0);
	    }
	}
    }
  else
    {
      fscanf(ifile,"%d",&h);
      fscanf(ifile,"%d",&w);
    }
  printf("h=%d,w=%d\n",h,w);
 
  
  time_t t;
  int val;
  //  val = ((it*h*w)/100);
  
  /* Intializes random number generator */
  srand((unsigned) time(&t));

  char** chararr = (char**)malloc(h * sizeof(char*));//creating character array
  for (i = 0; i < h; i++)
    chararr[i] = (char*)malloc(w * sizeof(char));


  int** arr = (int**)malloc(h * sizeof(int*));//creating integer array
  for (i = 0; i < h; i++)
    arr[i] = (int*)malloc(w * sizeof(int));
 
  if(argc==1)//for user input, initialize the array and set impassible terrain
    {
      for (i = 0; i < h; i++)
	for (j = 0; j < w; j++)
	  arr[i][j] = 0; // initializing all positions to zero
      val = ((it*h*w)/100);//setting number of impassible terrain
      printf("number of impassible positions:%d\n",val); 
      setImpassTerrain(arr,w,h,val);
    }
  else //read from the input file-array and impassible terrain
    {
      for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
	  {
	    arr[i][j] = 0;
	    fscanf(ifile,"%d",&arr[i][j]);
	    if(arr[i][j]==1)
	      arr[i][j]=-1;
	  }
    }
  PrintEnvironment(arr,ofile,w,h);
  printf("\n\n");
  fprintf(ofile,"\n\n");

  //inputting goal position from the user
  printf("Please enter the Goal Position X:\n");
  scanf("%d",&gx);
  printf("Please enter the Goal Position Y:\n");
  scanf("%d",&gy);
  printf("gx:%d and gy:%d\n",gx,gy);
  
  //checking if goal position entered is an obstacle
  while(arr[gy][gx]==-1)
    {
      printf("Sorry, that position is inside an obstacle\n");
      printf("Please enter the Goal Position X:\n");
      scanf("%d",&gx);
      printf("Please enter the Goal Position Y:\n");
      scanf("%d",&gy);
      printf("gx:%d and gy:%d\n",gx,gy);
    }
  
  setGoal(arr,gx,gy);
  

  //inputting start position from the user
  printf("Please enter the Start Position X:\n");
  scanf("%d",&sx);
  printf("Please enter the Start Position Y:\n");
  scanf("%d",&sy);
  printf("sx:%d and sy:%d\n",sx,sy);

  //checking if the start position is an obstacle or the same as the goal position
  while((arr[sy][sx]==-1) || ((sy==gy) && (sx==gx)))
    {
      printf("Sorry, that position is inside an obstacle or the same as goal position\n");
      printf("Please enter the Start Position X:\n");
      scanf("%d",&sx);
      printf("Please enter the Start Position Y:\n");
      scanf("%d",&sy);
      printf("sx:%d and sy:%d\n",gx,gy);
    }
  //PrintEnvironment(arr,ofile,w,h);

  //hcImpassTerrain(arr); //hard coded impassible terrain to the example for testing purposes

  //wave status is a 2D array to track if runwave has been called before for that [x][y] position visited
  int** wavestatus = (int**)malloc(h * sizeof(int*));
  for (i = 0; i < h; i++)
    wavestatus[i] = (int*)malloc(w * sizeof(int));


  for (i = 0; i < h; i++)
    for (j = 0; j < w; j++)
      wavestatus[i][j] = 0; //0 is waverun not run and 1 is waverun completed
  //queue is used to store the unvisited neighbours in a breadth-first search manner
  struct Queue* queue = createQueue(w*h);
  struct  Position goal ={gx,gy};

  enqueue(queue, goal);
  wavestatus[gy][gx] =1;
  

  while (queue->size != 0)
    runwave(arr,wavestatus,queue,w,h);

  //PrintEnvironment(arr,ofile,w,h);

  struct Position pathpos;
  pathpos.x=sx;
  pathpos.y=sy;
  chararr[sy][sx]='@';//pathpos is at the start
  //printPath(arr,chararr,ofile,gx,gy,sx,sy,w,h);

  while(1)
    { 
      pathpos=findPath(arr,chararr,gx,gy,sx,sy,w,h);
      if((pathpos.x==sx) && (pathpos.y==sy)) //path not found case
	{
	  printf("No Path Found\n");
	  break;
	}
      if((pathpos.x==gx) && (pathpos.y==gy)) //reached the goal
	break;
      sx=pathpos.x; //start the next iteration with the new pathpos
      sy=pathpos.y;
      //printPath(arr,chararr,ofile,gx,gy,sx,sy,w,h);
    }

  printf("\n\n");
  fprintf(ofile,"\n\n");
  fprintf(ofile,"Result array:\n");
 
  printPath(arr,chararr,ofile,gx,gy,sx,sy,w,h);//printing final path

  for (int i = 0; i < h; i++)
    free(arr[i]);
  
  free(arr);
  free(wavestatus);
 
  return 0;

}

//Function to calculate and print integer array
void PrintEnvironment(int** array, FILE* ofile, int width, int height)
{
  printf("Grid %d x %d\n",width,height);
  int i,j;
  
  for (i = 0; i < height; i++)
    {
      for (j = 0; j < width; j++)
	{
	  printf("%4d", array[i][j]);
	  fprintf(ofile, "%4d", array[i][j]);
	}
      printf("\n");
      fprintf(ofile,"\n");
    }
}


int myrand(int i) //returns a integer between 0 and i
{
  return (int)((((float)rand()/RAND_MAX))*i);
  
}

//Function to set and print impassible terrain
void setImpassTerrain(int** arr, int w, int h, int itval)
{
  int wit,hit;
  for(int k=0;k<itval;k++)
    {
      wit= myrand(w);
      hit= myrand(h);
      //printf("wit:%d , hit:%d\n",wit,hit);
      //if i get same wit and hit, call myrand for wit and hit again
      if((arr[hit][wit])!=-1)
        arr[hit][wit]=-1;
      else
        k--;

    }
}

//Function to set goal
void setGoal(int** arr, int gx, int gy)
{
  arr[gy][gx]=1;
}

//Function to print start position in the character array
void printStart(char** chararr, int sx, int sy)
{
  chararr[sy][sx]='@';
}

//Funnction to print goal postion in the character array
void printGoal(char** chararr, int gx, int gy)
{
  chararr[gy][gx]='$';
}

//Function to calculate and print wave
void runwave(int** arr, int** wavestatus,struct Queue* queue, int w, int h)
{
  int nwx,nwy,nx,ny,nex,ney,wx,wy,ex,ey,swx,swy,sx,sy,sex,sey;
  
  struct Position item = dequeue(queue);

  //printf("runwave for [%d][%d]\n",item.y,item.x);
  //  wavestatus[item.y][item.x]=1;//runwave for [gy][gx]
  //visiting the dequeued item
  int gx, gy;
  gx=item.x;
  gy=item.y;

  nwx=gx-1;
  nwy=gy-1;
  nx=gx;
  ny=gy-1;
  nex=gx+1;
  ney=gy-1;
  wx=gx-1;
  wy=gy;
  swx=gx-1;
  swy=gy+1;
  sx=gx;
  sy=gy+1;
  sex=gx+1;
  sey=gy+1;
  ex=gx+1;
  ey=gy;

  struct Position pos; 

  if((nwx < w) && (nwx != -1)) //nwx within width bounds
    if((nwy < h) && (nwy != -1))//nwy within height bounds
      if((arr[nwy][nwx]!=-1)&&(wavestatus[nwy][nwx]==0))//if not impassible and not been visited
	{
	  if(arr[nwy][nwx]==0)
	    arr[nwy][nwx]= arr[gy][gx]+1;
	  pos.x=nwx;
	  pos.y=nwy;
	  enqueue(queue, pos);
	  wavestatus[nwy][nwx]=1;
	}


  if((nx < w) && (nx != -1))
    if((ny < h) && (ny != -1))
	if((arr[ny][nx]!=-1)&&(wavestatus[ny][nx]==0))
	{
          if(arr[ny][nx]==0)
	    arr[ny][nx]= arr[gy][gx]+1;
          pos.x=nx;
          pos.y=ny;
          enqueue(queue, pos);
	  wavestatus[ny][nx]=1;
        }

  if((nex < w) && (nex != -1))
    if((ney < h) && (ney != -1))
	if((arr[ney][nex]!=-1)&&(wavestatus[ney][nex]==0))
	{
          if(arr[ney][nex]==0)
	    arr[ney][nex]= arr[gy][gx]+1;
          pos.x=nex;
          pos.y=ney;
          enqueue(queue, pos);
	  wavestatus[ney][nex]=1;
	}

  if((wx < w) && (wx != -1))
    if((wy < h) && (wy != -1))
	if((arr[wy][wx]!=-1)&&(wavestatus[wy][wx]==0))
	{
          if(arr[wy][wx]==0)
	    arr[wy][wx]= arr[gy][gx]+1;
          pos.x=wx;
          pos.y=wy;
          enqueue(queue, pos);
	  wavestatus[wy][wx]=1;
        }
  
  if((swx < w) && (swx != -1))
    if((swy < h) && (swy != -1))
	if((arr[swy][swx]!=-1)&&(wavestatus[swy][swx]==0))
	{
	  if(arr[swy][swx]==0)
	    arr[swy][swx]= arr[gy][gx]+1;
          pos.x=swx;
          pos.y=swy;
          enqueue(queue, pos);
        }

  if((sx < w) && (sx != -1))
    if((sy < h) && (sy != -1))
	if((arr[sy][sx]!=-1)&&(wavestatus[sy][sx]==0))
	{
          if(arr[sy][sx]==0)
	    arr[sy][sx]= arr[gy][gx]+1;
          pos.x=sx;
          pos.y=sy;
          enqueue(queue, pos);
	  wavestatus[sy][sx]=1;
        }

  if((sex < w) && (sex != -1))
    if((sey < h) && (sey != -1))
	if((arr[sey][sex]!=-1)&&(wavestatus[sey][sex]==0))
	{
          if(arr[sey][sex]==0)	    
	    arr[sey][sex]= arr[gy][gx]+1;
          pos.x=sex;
          pos.y=sey;
          enqueue(queue, pos);
	  wavestatus[sey][sex]=1;
        }


  if((ex < w) && (ex != -1))
    if((ey < h) && (ey != -1))
	if((arr[ey][ex]!=-1)&&(wavestatus[ey][ex]==0))
	{
          if(arr[ey][ex]==0)
	    arr[ey][ex]= arr[gy][gx]+1;
	  pos.x=ex;
          pos.y=ey;
          enqueue(queue, pos);
	  wavestatus[ey][ex]=1;
        }

  //  PrintEnvironment(arr,w,h);

}


//hardcoded impass terrain as shown in example
void hcImpassTerrain(int** arr)
{
    arr[3][4]=-1;
    arr[4][4]=-1;
    arr[3][5]=-1;
    arr[4][5]=-1;
    arr[3][6]=-1;
    arr[4][6]=-1;
    arr[3][7]=-1;
    arr[4][7]=-1;
    arr[3][8]=-1;
    arr[4][8]=-1;
    arr[3][9]=-1;
    arr[4][9]=-1;
    arr[3][10]=-1;
    arr[4][10]=-1;
    arr[3][11]=-1;
    arr[4][11]=-1;
}


struct Queue* createQueue(unsigned capacity)
{
  struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
  queue->capacity = capacity;
  queue->front = queue->size = 0;
 
  // This is important, see the enqueue
  queue->rear = capacity - 1;
  queue->array = (struct Position*)malloc(queue->capacity * sizeof(struct Position));
  return queue;
}
 
// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
  return (queue->size == queue->capacity);
}
 
// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
  return (queue->size == 0);
}
 
// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue,struct Position item)
{
  if (isFull(queue))
    return;
  queue->rear = (queue->rear + 1)   % queue->capacity;
  queue->array[queue->rear] = item;
  queue->size = queue->size + 1;
  //  printf("%d %d enqueued to queue\n",item.y,item.x);
}
 
// Function to remove an item from queue.
// It changes front and size
struct Position dequeue(struct Queue* queue)
{
  struct Position item={-1,-1};
  if (isEmpty(queue))
    return item;
  item = queue->array[queue->front];
  queue->front = (queue->front + 1)
    % queue->capacity;
  queue->size = queue->size - 1;
  return item;
}
 
// Function to get front of queue
struct Position front(struct Queue* queue)
{
  struct Position item ={-1,-1};


  if (isEmpty(queue))
    return item;
  item = queue->array[queue->front];
  return item;
}
 
// Function to get rear of queue
struct Position rear(struct Queue* queue)
{
  struct Position item = {-1,-1};


  if (isEmpty(queue))
    return item;
  item = queue->array[queue->rear];
  return item;
}

//Function to print in the character array
void printPath(int** arr, char** chararr ,FILE* ofile, int gx, int gy, int sx, int sy, int w, int h)
{
  int i,j;

  for (i = 0; i < h; i++)
    {
      for (j = 0; j < w; j++)
	{
	  if(arr[i][j] == -1) //check for impassible terrain
	    chararr[i][j] = '#';
	  else if((i==gy)&&(j==gx))//check for goal position
	    chararr[i][j]='$';
	  else if(chararr[i][j]=='@')//check for start position which was set before calling findPath
	    ;
	  else if(chararr[i][j]=='*')//path position
	    ; //no operation
	  else//check for all other positions
	    chararr[i][j]=' ';

	  printf("%4c", chararr[i][j]);
	  fprintf(ofile, "%4c", chararr[i][j]);
	}
      printf("\n");
      fprintf(ofile,"\n");
    }
}
//Function to find the path
struct Position findPath(int** arr, char** chararr, int gx, int gy, int startx, int starty, int w, int h)
{  
  int nwx,nwy,nx,ny,nex,ney,wx,wy,ex,ey,swx,swy,sx,sy,sex,sey;

  nwx=startx-1;
  nwy=starty-1;
  nx=startx;
  ny=starty-1;
  nex=startx+1;
  ney=starty-1;
  wx=startx-1;
  wy=starty;
  swx=startx-1;
  swy=starty+1;
  sx=startx;
  sy=starty+1;
  sex=startx+1;
  sey=starty+1;
  ex=startx+1;
  ey=starty;

  struct Position neighbour;
  neighbour.x=startx;
  neighbour.y=starty;

  int min=arr[starty][startx];
  //printf("startx:%d starty:%d min:%d\n", startx, starty,min);

  if((nwx < w) && (nwx != -1) && (nwy < h) && (nwy != -1))//checking for bounds
    if((arr[nwy][nwx]!=-1)&&(arr[nwy][nwx] != 0))//checking for not equal to 0 or -1
      if(arr[nwy][nwx] < min)
	{
	  neighbour.x=nwx;
	  neighbour.y=nwy;
	  min=arr[nwy][nwx];//resetting min position
	}

  if((nx < w) && (nx != -1) && (ny < h) && (ny != -1))
    if((arr[ny][nx]!=-1) && (arr[ny][nx] != 0))
      if(arr[ny][nx] < min)
        {
          neighbour.x=nx;
          neighbour.y=ny;
          min=arr[ny][nx];
        }

  if((nex < w) && (nex != -1) && (ney < h) && (ney != -1))
    if((arr[ney][nex]!=-1) && (arr[ney][nex] != 0))
      if(arr[ney][nex] < min)
        {
	  neighbour.x=nex;
          neighbour.y=ney;
          min=arr[ney][nex];
        }
       
       
  if((ex < w) && (ex != -1) && (ey < h) && (ey != -1))
    if((arr[ey][ex]!=-1) && (arr[ey][ex] != 0))
      if(arr[ey][ex] < min)
	{
	  neighbour.x=ex;
	  neighbour.y=ey;
	  min=arr[ey][ex];
	}

  if((sex < w) && (sex != -1) && (sey < h) && (sey != -1))
    if((arr[sey][sex]!=-1) && (arr[sey][sex] !=0))
      if(arr[sey][sex] < min)
        {
          neighbour.x=sex;
          neighbour.y=sey;
          min=arr[sey][sex];
        }

  if((sx < w) && (sx != -1) && (sy < h) && (sy != -1))
    if((arr[sy][sx]!=-1) && (arr[sy][sx] !=0))
      if(arr[sy][sx] < min)
        {
          neighbour.x=sx;
          neighbour.y=sy;
          min=arr[sy][sx];
        }

  if((swx < w) && (swx != -1) && (swy < h) && (swy != -1))
    if((arr[swy][swx]!=-1) && (arr[swy][swx] != 0))
      if(arr[swy][swx] < min)
        {
          neighbour.x=swx;
          neighbour.y=swy;
          min=arr[swy][swx];
        }


  if((wx < w) && (wx != -1) && (wy < h) && (wy != -1))//checking for bounds
    if((arr[wy][wx]!=-1) && (arr[wy][wx] != 0))//checking for not equal to 0 or -1
      if(arr[wy][wx] < min)
        {
          neighbour.x=wx;
          neighbour.y=wy;
          min=arr[wy][wx];//resetting min position
        }
       
  if(arr[neighbour.y][neighbour.x]< arr[starty][startx])
    chararr[neighbour.y][neighbour.x]='*';//printing path
  
  //printf("neighbourx:%d neighboury:%d min:%d\n", neighbour.x,neighbour.y,min);
  return neighbour;
}
