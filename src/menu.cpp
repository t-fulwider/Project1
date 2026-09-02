#include <string>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include "menu.h"

void Menu::Start() {
	//Loading();
	while (true)
	{
		ClearScreen();

		std::cout << std::endl;
		std::cout << std::setfill('=') << std::setw(50) << "" <<  std::endl;
		std::cout << std::right << std::setfill(' ') << std::setw(35) << "TFUL\'S STUDENT DATABASE" << std::endl;
		std::cout << std::setfill('=') << std::setw(50) << "" <<  std::endl;
		std::cout << std::endl;
		std::cout << "1. Log in" << std::endl;
		std::cout << "2. Register" << std::endl;
		std::cout << "3. About" << std::endl;
		std::cout << "0. Exit" << std::endl;

		std::string option;
		std::cin >> option;

		if (option == "1")
		{
			Login();
		}
		else if (option == "2")
		{
			Register();
		}
		else if (option == "3")
		{
			About();
		}
		else if (option == "0")
			break;
		else
			std::cout << "\nThat is not a valid option. Only enter the integers provided.";
	}
}

void Menu::Loading() {

	for (int i = 0; i < 5; i++)
	{
		ClearScreen();
		std::cout << "\t\t\t\t Loading";
		for (int j = 0; j < 5; j++)
		{
			std::cout << '.';
			std::cout << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}

void Menu::Login() {

	ClearScreen();

	std::cout << std::endl;
	std::cout << std::setfill('=') << std::setw(50) << "" <<  std::endl;
	std::cout << std::right << std::setfill(' ') << std::setw(28) << "LOGIN" << std::endl;
	std::cout << std::setfill('=') << std::setw(50) << "" <<  std::endl;
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "Enter your username: ";
	std::string uname;
	std::cin >> uname;
	std::cout << std::endl << "Enter your password: ";
	std::string pw;
	std::cin >> pw;

	// logic for searching a user
}

void Menu::ClearScreen() {

	#if defined(_WIN32) || defined(_WIN64)
		std::system("cls");
	#else
		std::system("clear");
	#endif
}

void Menu::Register() {

	ClearScreen();

	std::cout << std::endl;
	std::cout << std::setfill('=') << std::setw(50) << "" <<  std::endl;
	std::cout << std::right << std::setfill(' ') << std::setw(28) << "REGISTER" << std::endl;
	std::cout << std::setfill('=') << std::setw(50) << "" <<  std::endl;
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "Create a username: ";
	std::string uname;
	std::cin >> uname;
	std::cout << std::endl << "Create a password: ";
	std::string pw;
	std::cin >> pw;

	// add logic for creating user (faculty or student)
}

void Menu::About() {

	ClearScreen();

	std::cout << std::endl;
	std::cout << std::setfill('=') << std::setw(50) << "" <<  std::endl;
	std::cout << std::right << std::setfill(' ') << std::setw(32) << "ABOUT THIS PROJECT" << std::endl;
	std::cout << std::setfill('=') << std::setw(50) << "" <<  std::endl;
	std::cout << "\n\n";

	std::cout << "This project is a student \"database\" system to track student information.\n";
	std::cout << "\nOrginally, this was for a school assignment. I have decided to tranform it into a more functional application.\n";
	std::cout << "\nThanks for checking this out, and I hope you enjoy.\n\n";

	std::cout << "Press ENTER to return to main menu.";
	std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}
