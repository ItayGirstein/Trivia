#include "Validator.h"

bool Validator::isPasswordValid(string pass)
{
	if (pass.length() < 4)
	{
		return false;
	}

	if (pass.find(" ") < 0)
	{
		return false;
	}

	if (!std::any_of(pass.begin(), pass.end(), ::isdigit))
	{
		return false;
	}

	if (!std::any_of(pass.begin(), pass.end(), ::isupper))
	{
		return false;
	}

	if (!std::any_of(pass.begin(), pass.end(), ::islower))
	{
		return false;
	}

	return true;
}

bool Validator::isUsernameVaild(string username)
{
	if (username[0] > 122 || username[0] < 65)
	{
		return false;
	}

	if (username.find(" ") < 0)
	{
		return false;
	}

	if (username.length() == 0)
	{
		return false;
	}

	return true;
}

