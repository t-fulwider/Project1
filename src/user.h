#include <string>

class User {
	bool _admin;
	std::string _uname;
	std::string _pw;
public:
	User(std::string& un, std::string& pw, bool admin);
	bool GetAdmin() const;
	std::string GetName() const;
	std::string GetPassword() const;
};

