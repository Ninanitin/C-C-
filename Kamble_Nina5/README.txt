Zombie congaline is a linked list in which each node is going to store a zombie in it.
Zombies can be Red, Yellow, Green,Blue, Magenta and Cyan.
Every turn will randomly generate a Zombie object and an action. It will
then perform that action using the Zombie object as the parameter for that
action.


Actions:
• Engine!
	o This zombie becomes the first Zombie in the conga line
• Caboose!
	o This zombie becomes the last zombie in the conga line
• Jump in the Line!
	o This zombie joins the conga line at position X where X <= length of
	the linked list
• Everyone Out!
	o Remove all matching zombies from the linked list
• You’re done!
	o Remove the first matching zombie from the linked list
• Brains!
	o Generate two more matching Zombies and add one to the front, one to
	the end and one to the middle (round down).
• Rainbow Brains!
	o Add this zombie to the front, then add one of each zombie color to 	the end of the conga line.
• Making new Friends!
	o Find the first Zombie of this color in line. “Flip a coin” 50% chance of adding before or after that zombie.
	o If no Zombie of that color exists, add this one before the Tail zombie
• Unstable Zombie
	o Walk the list to locate the first Zombie of this color in line and
	remove it.
	o As you walk the list: the first zombie of each color before that
	splits and adds a new zombie before them.
 G -> R -> B -> R -> Y -> C -> G
Generate C
 G -> G -> R -> R -> B -> B -> R -> Y -> Y -> G
Every 5 rounds remove the Head zombie and Tail zombie.

User Interface:
• Ask the user how many rounds they want to run.
• Then generate that many random actions and fulfill them.
• If the conga line ever empties completely due to an action tell the user
that the Party is Over.
• Once the number of rounds has finished. Ask the user if they want to
continue the party or end.
• If they choose to continue ask them for a new number of rounds to run.



Kindly use the following command to compile:
g++ -g -Wall Kamble_Nina_assn5.cpp zombie.cpp -o Kamble_Nina_assn5
