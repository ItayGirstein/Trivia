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
	if (_currRoom == nullptr)
	{
		_currRoom = new Room(roomId, this, roomName, maxUsers, questionTime, questionsNo);
		send(Protocol::M114("success"));	//success creating room
		return true;
	}
	send(Protocol::M114("fail"));	//failure creating room
	return false;
}

bool User::joinRoom(Room* newRoom)
{
	if (_currRoom == nullptr)
	{
		newRoom->joinRoom(this);
	}
	return false;
}

void User::leaveRoom()
{
	if (_currRoom)
	{
		_currRoom->leaveRoom(this);
		_currRoom = nullptr;
	}
}

int User::closeRoom()
{
	if (_currRoom)
	{
		int id = _currRoom->closeRoom(this);
		if (id != NOT_ADMIN)
		{
			delete(_currRoom);
			_currRoom = nullptr;
		}
		return id;
	}
	return USER_NOT_IN_ROOM;
}

bool User::leaveGame()
{
	if (_currGame)
	{
		_currGame->leaveGame(this);
		_currGame = nullptr;
	}
	return false;
}