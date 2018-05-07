#pragma once
#include "Helper.h"

using std::string;

class User
{
public:
	User();
	~User();



private:
	string _username;
	SOCKET _sock;
	//Game _currGame;
	//Room _currRoom;
};

