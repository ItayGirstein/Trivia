#pragma once

#include "Helper.h"

class User;

class RecievedMessage
{
public:
	RecievedMessage(SOCKET,int);
	RecievedMessage(SOCKET, int,vector<string>);
	~RecievedMessage() = default;
	SOCKET getSock();
	User* getUser();
	void setUser(User*);
	int getMessageCode();
	vector<string>& getValues();

private:
	SOCKET _sock;
	User* _user;
	int _messageCode;
	vector<string> _values;
};

