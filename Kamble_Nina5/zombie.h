#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_

#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <time.h>
using namespace std;
 

enum class Color { Red, Yellow, Green, Blue, Magenta, Cyan };

// A zombie class 
class Zombie
{
 private:
  Color color;

 public:
  Zombie();
    
  friend ostream &operator<<( ostream &out, const Zombie* zombie)//overloading operator << for zombie
  {
    if(zombie->color == Color::Red)
      out <<"R ";
    if(zombie->color == Color::Yellow)
      out <<"Y ";
    if(zombie->color == Color::Green)
      out <<"G ";
    if(zombie->color == Color::Blue)
      out <<"B ";
    if(zombie->color == Color::Magenta)
      out <<"M ";
    if(zombie->color == Color::Cyan)
      out <<"C ";

    return out;
  }

};

#endif
