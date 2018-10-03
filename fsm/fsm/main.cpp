#include <iostream>
#include <random>
#include <time.h>


int main()
{
	int currentState;

	//sets rand to be something other than 1 almost like initalising it
	srand(time(NULL));

	currentState = (rand() % 5);

	int aiStates = currentState;

	//will output the case based on random number need to find a way to repeat
	//this multiple times after a set amount of time and change the random number
	//or base it on user input easily done by just changing the case.
	switch(aiStates)
	{

	case 0:
		std::cout << "Idle\n";
		break;
	case 1:
		std::cout << "Walking\n";
		break;
	case 2:
		std::cout << "Running\n";
		break;
	case 3:
		std::cout << "Jumping\n";
		break;
	case 4:
		std::cout << "Killing\n";
		break;

	};
	
	return 0;
};