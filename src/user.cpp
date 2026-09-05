#include "user.h"

User::User(std::string &un, std::string &pw, bool admin) {
	_uname = un;
	_pw = pw;
	_admin = admin;
}

bool User::GetAdmin() const {
	return _admin;
}

std::string User::GetName() const {
	return _uname;
}

std::string User::GetPassword() const {
	return _pw;
}