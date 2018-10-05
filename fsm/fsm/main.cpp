#include <iostream>
#include <string>
#include <chrono>
#include <thread>

int main()
{
	using namespace std::this_thread; //allows for use of sleep for without std::
	using namespace std::chrono; // allows use of seconds without std::

	char answer = '0';

	//infinitly loops the switch (only way to break out is by pulling your gun on the AI)
loop:
	while (true) {
	
		switch (answer)
		{

		case '0':
			std::cout << "\nThe AI is currently idle\n";
			break;

		case '1':
			std::cout << "\nThe AI is took your order\n";
			sleep_for(seconds(1));
			std::cout << "\nThe AI is currently cooking\n";
			sleep_for(seconds(1));
			std::cout << "\n The AI served your food\n";
			break;

		case '2':
			std::cout << "\nThe AI is currently cleaning\n";
			break;

		case '3':
			std::cout << "\nThe AI has Hid for cover\n";
			sleep_for(milliseconds(500));
			std::cout << "\nThis AI ain't no rookie bot, he teleports behind you and kills you. GAME OVER\n";
			sleep_for(seconds(2));
			return 0;

		case '4':
			std::cout << "\nThe AI is staring at you confused\n";
			break;
			
		default:
			std::cout << "\nYou did not enter a valid option\n";
			break;
		};

		std::cout << "\nPlease choose one of the following options:\n";
		std::cout << "0 = Do nothing.\n";
		std::cout << "1 = Sit down at a table\n";
		std::cout << "2 = Make a mess\n";
		std::cout << "3 = Pull out your gun.\n";
		std::cout << "4 = Run into a wall and hurt yourself.\n";
		std::cin >> answer;
	}
	
	return 0;
};