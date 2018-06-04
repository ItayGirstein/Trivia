#pragma once
#include "Protocol.h"

class Validator
{
public:
	Validator();
	~Validator();

	bool isPasswordValid(string pass);
	bool isUsernameVaild(string username);

};

