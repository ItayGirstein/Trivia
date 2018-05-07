#pragma once
#include "Helper.h"
#include "Room.h"
#include "Game.h"

class User
{
public:
	User();
	~User();



private:
	string _username;
	SOCKET _sock;
	Game* _currGame;
	Room* _currRoom;
};

