#include "zombie.h"
#include <iostream>
#include <time.h>


Zombie::Zombie()
{
  //  srand ((unsigned) time(0));
  color=(Color)(rand() % (1+ static_cast<int> (Color::Cyan)));
}
/*
int main()
{
  srand((unsigned)time(0));//use current time as seed for random generator

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

  cout<<zombie1<<zombie2<<zombie3<<zombie4<<zombie5<<zombie6<<zombie7<<zombie8<<zombie9<<zombie10<<zombie11<<zombie12<<zombie13<<endl;

  return(0);
}
*/


