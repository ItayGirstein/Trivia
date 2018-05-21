#include "User.h"
#include "Room.h"

User::User(string username, SOCKET sock) : _currGame(nullptr), _currRoom(nullptr), _username(username), _sock(sock)
{
}

void User::send(string msg)
{
	Helper::sendData(_sock, msg);
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
	_currRoom = nullptr;
	_currGame = currGame;
}

void User::clearRoom()
{
	_currGame = nullptr;
}

bool User::createRoom(int roomId, string roomName, int maxUsers, int questionsNo, int questionTime)
{
	return false;
}

bool User::joinRoom(Room* newRoom)
{
	return false;
}

void User::leaveRoom()
{
}

int User::closeRoom()
{
	return 0;
}

bool User::leaveGame()
{
	return false;
}
