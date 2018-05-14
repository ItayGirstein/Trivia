#include "User.h"



User::User()
{
}


User::User(string, SOCKET)
{
}

User::~User()
{
}

void User::send(string)
{

}

string User::getUsername()
{
	return _username;
}

SOCKET User::getSocket()
{
	return _sock;
}

Room * User::getRoom()
{
	return _currRoom;
}

Game * User::getGame()
{
	return _currGame;
}

void User::setGame(Game* currGame)
{
	_currGame = currGame;
}

void User::clearRoom()
{
}

bool User::createRoom(int, string, int, int, int)
{
	//_currRoom = new Room();
	return false;
}

bool User::joinRoom(Room *)
{
	return false; // todo
}

void User::leaveRoom()
{
	_currGame = nullptr; // todo
}

int User::closeRoom()
{
	return 0;
}

bool User::leaveGame()
{
	return false;
}
