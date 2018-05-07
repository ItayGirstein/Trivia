#pragma once
#include "Helper.h"
#include "User.h"

class Room
{
public:
	Room();
	~Room();

private:
	vector<User*> _users;
	User* _admin;
	int _maxUsers;
	int _questionTime;
	int _questionNo;
	string _name;
	int _id;
};

