#include <string>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "menu.h"

void Menu::Start() {
	Loading();
	GetData();
	// core loop (pre-login)
	while (true)
	{
		ClearScreen();
		DisplayHeader("TFUL\'S STUDENT DATABASE");
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
		{
			Exit();
			break;
		}
		else
			std::cout << "\nThat is not a valid option. Only enter the integers provided.";
	}
}

void Menu::Loading() {

	for (int i = 0; i < 2; i++)
	{
		ClearScreen();
		std::cout << "\t\t\t\t Loading";
		// repeating dots
		for (int j = 0; j < 5; j++)
		{
			std::cout << '.';
			std::cout << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
}

void Menu::Login() {
	while (true)
	{
		ClearScreen();

		DisplayHeader("LOGIN");

		std::cout << std::endl;
		std::cout << "Enter your username: ";
		std::string uname;
		std::cin >> uname;
		std::cout << std::endl << "Enter your password: ";
		std::string pw;
		std::cin >> pw;

		// searching a user, finding username/password match
		for (auto& user : _users)
		{
			if (user.GetName() == uname)
			{
				if (user.GetPassword() == pw)
				{
					StudentDB(user.GetAdmin());
					return;
				}
			}
		}
		ClearScreen();
		std::cout << "Invalid username or password!\n\n";
		std::cout << "Enter r to retry login, or enter anything else to return to menu.\n";
		std::string option;
		std::cin >> option;
		if (option != "r" && option != "R")
			return;
	}
}

void Menu::ClearScreen() {
	// windows
	#if defined(_WIN32) || defined(_WIN64)
		std::system("cls");
	// macos
	#else
		std::system("clear");
	#endif
}

void Menu::Register() {

	ClearScreen();

	DisplayHeader("REGISTER");

	std::cout << std::endl;
	std::cout << "Create a username: ";
	std::string uname;
	std::cin >> uname;
	std::cout << std::endl << "Create a password: ";
	std::string pw;
	std::cin >> pw;
	bool isAdmin = false;
	while (true)
	{
		std::cout << std::endl << "Are you admin? (type y or n): ";
		std::string admin;
		std::cin >> admin;
		if (admin == "y" || admin == "Y")
		{
			isAdmin = true;
			break;
		}
		if (admin == "n" || admin == "N")
			break;
		std::cout << "\nPlease only type y or n!";
	}
	// check if username already exists in data
	for (auto& usrs : _users)
	{
		if (usrs.GetName() == uname)
		{
			ClearScreen();
			std::cout << "User already exits!";
			std::cout << std::flush;
			std::this_thread::sleep_for(std::chrono::seconds(3));
			return;
		}
	}
	_users.push_back(User(uname, pw, isAdmin));
	StudentDB(isAdmin);
	// add logic for creating user (faculty or student)
}

void Menu::About() {

	ClearScreen();

	DisplayHeader("ABOUT THIS PROJECT");

	std::cout << "This project is a student \"database\" system to track student information.\n";
	std::cout << "\nOrginally, this was for a school assignment. I have decided to tranform it into a more functional application.\n";
	std::cout << "\nThanks for checking this out, and I hope you enjoy.\n\n";

	std::cout << "Press ENTER to return to main menu.";
	std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

void Menu::GetData() {
	// first, get user data
	std::ifstream csvFile("data/users.csv");
	if (!csvFile.is_open()) {
		std::cerr << "Error: Could not create or open the file!" << std::endl;
		return;
	}

	std::string line;
	std::getline(csvFile, line);
	while (std::getline(csvFile,line))
	{
		std::stringstream ss(line);
		std::string usrnm;
		std::getline(ss, usrnm, ',');
		std::string pw;
		std::getline(ss, pw, ',');
		std::string admin;
		std::getline(ss, admin, ',');
		bool isAdmin = false;
		if (admin == "yes")
			isAdmin = true;
		_users.push_back(User(usrnm, pw, isAdmin));
	}
	csvFile.close();

	// retrieve student data
	std::ifstream csv("data/students.csv");
	if (!csv.is_open()) {
		std::cerr << "Error: Could not create or open the file!" << std::endl;
		return;
	}

	getline(csv, line);
	while (getline(csv, line))
	{
		std::stringstream ss(line);
		std::string name;
		std::string ufid;

		std::getline(ss, name, ',');
		std::getline(ss, ufid, ',');
		_students.Insert(name, ufid);
	}
}

void Menu::Exit() {
	// write user data
	std::ofstream csvFile("data/users.csv");

	if (!csvFile.is_open()) {
		std::cerr << "Error: Could not create or open the file!" << std::endl;
		return;
	}

	csvFile << "username,password,admin\n";

	for (auto& user : _users)
	{
		std::string output = user.GetName() + "," + user.GetPassword() + ",";
		if (user.GetAdmin())
			output += "yes\n";
		else
			output += "no\n";
		csvFile << output;
	}
	csvFile.close();

	// write student data as well
	std::ofstream csv("data/students.csv");

	if (!csv.is_open()) {
		std::cerr << "Error: Could not create or open the file!" << std::endl;
		return;
	}

	csv << "name,ufid\n";
	std::vector<string> names = _students.TraverseInorder("name");
	std::vector<string> ids = _students.TraverseInorder("ufid");
	for (int i = 0; i < names.size(); i++)
	{
		std::string output = names[i] + "," + ids[i] + "\n";
		csv << output;
	}
	csv.close();
}

void Menu::StudentDB(bool isAdmin) {
	// second core loop
	while (true)
	{
		ClearScreen();

		DisplayHeader("TFUL\'S STUDENT DATABASE");

		std::cout << "1. Search Student" << std::endl;
		// admin get extra functions vs non-admin
		if (isAdmin)
		{
			std::cout << "2. Add Student" << std::endl;
			std::cout << "3. Remove Student" << std::endl;
		}
		std::cout << "0. Logout" << std::endl;
		std::string option;
		std::cin >> option;
		// functionality for admin's extra choices
		if (isAdmin)
		{
			if (option == "2")
			{
				std::cout << "\nEnter the student's name: ";
				std::string name;
				std::cin >> name;
				std::cout << "\n\nEnter the student's UFID: ";
				std::string ufid;
				std::cin >> ufid;

				bool success = _students.Insert(name, ufid);
				if (!success)
				{
					ClearScreen();

					std::cout << "Invalid name or UFID.";
					std::cout << std::flush;
					std::this_thread::sleep_for(std::chrono::seconds(3));
				}
				else
				{
					ClearScreen();

					std::cout << name << " has been added!";
					std::cout << std::flush;
					std::this_thread::sleep_for(std::chrono::seconds(3));
				}
			}
			else if (option == "3")
			{
				std::cout << "\nEnter the student's UFID: ";
				std::string ufid;
				std::cin >> ufid;

				bool success = _students.RemoveID(ufid);
				if (!success)
				{
					ClearScreen();

					std::cout << "Invalid UFID.";
					std::cout << std::flush;
					std::this_thread::sleep_for(std::chrono::seconds(3));
				}
				else
				{
					ClearScreen();

					std::cout << "The student has been removed!";
					std::cout << std::flush;
					std::this_thread::sleep_for(std::chrono::seconds(3));
				}
			}
		}
		if (option == "1")
		{
			// admin has access to student IDs
			if (isAdmin)
			{
				std::cout << "\n\nWould you like to search by UFID? (Type y for yes and anything else for no)";
				std::string op2;
				std::cin >> op2;
				if (op2 == "y")
				{
					std::cout << "\nPlease enter the UFID: ";
					std::string ufid;
					std::cin >> ufid;

					std::string name = _students.SearchID(ufid);

					if (name.empty())
						std::cout << "\nStudent not found.";
					else
						std::cout << ufid << " belongs to " << name << ".";

					std::cout << "\n\nPress ENTER to return to the menu.";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();
					continue;
				}
			}

			std::cout << "\nPlease enter the student's name: ";
			std::string name;
			std::cin >> name;
			std::vector<string> ufid = _students.SearchName(name);
			if (ufid.empty())
				std::cout << "\n\nStudent not found.";
			else
			{
				std::cout << "\n\nStudent has been found. ";
				if (isAdmin)
				{
					std::cout << "These are the UFIDs who share the name.\n\n";
					for (auto& id : ufid)
					{
						std::cout << id << " ";
					}
				}
			}
			std::cout << "\n\nPress ENTER to return to the menu.";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
		}
		else if (option == "0")
			return;
	}
}

void Menu::DisplayHeader(std::string prompt) {
	int width = prompt.length() / 2;
	std::cout << std::endl;
	std::cout << std::setfill('=') << std::setw(50) << "" <<  std::endl;
	std::cout << std::right << std::setfill(' ') << std::setw(23 + width) << prompt << std::endl;
	std::cout << std::setfill('=') << std::setw(50) << "" <<  "\n\n";
}

