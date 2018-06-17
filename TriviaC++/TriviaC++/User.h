#pragma once
#include "Protocol.h"

#define USER_NOT_IN_ROOM -1

class Room;
class Game;

class User
{
public:
	User(string, SOCKET);
	~User() = default;
	void send(string);
	string getUsername();
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

