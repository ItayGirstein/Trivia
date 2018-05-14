#pragma once
#include "Helper.h"
#include "Room.h"
#include "Game.h"

class User
{
public:
	User(string, SOCKET);
	~User();


	void send(string);
	string gestUsername();
	SOCKET getSocket();
	Room* getRoom();
	Game* getGame();
	void setGame(Game* currGame);
	void clearRoom();
	bool createRoom(int, string, int, int, int);
	bool joinRoom(Room*);
	void leaveRoom();
	int closeRoom();
	bool leaveGame();


private:
	string _username;
	SOCKET _sock;
	Game* _currGame;
	Room* _currRoom;
};

