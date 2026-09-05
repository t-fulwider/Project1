#pragma once
#include <vector>
#include "user.h"
#include "AVL.h"

class Menu {
private:
	std::vector<User> _users;
	AVL _students;

	void  Loading();
	void  Login();
	void  ClearScreen();
	void Register();
	void  About();
	void  Exit();
	void GetData();
	void StudentDB(bool isAdmin);
	void DisplayHeader(std::string prompt);

public:
	void  Start();
};