#pragma once

#include "Protocol.h"
#include "Room.h"
#include "Question.h"
#include "User.h"
#include "DataBase.h"
#include "RecievedMessage.h"
#include "Game.h"
#include "Validator.h"
#include "WSAInitializer.h"

#define PORT 1226
#define IFACE 0

class TriviaServer
{
public:
	TriviaServer();
	~TriviaServer();

	void serve();

private:
	void bindAndListen();
	void acceptClient();
	void clientHandler(SOCKET);
	void safeDeleteUser(RecievedMessage*);

	User* handleSignin(RecievedMessage*);
	bool handleSignup(RecievedMessage*);
	void handleSignout(RecievedMessage*);

	void handleLeaveGame(RecievedMessage*);
	void handleStartGame(RecievedMessage*);
	void handlePlayerAnswer(RecievedMessage*);

	bool handleCreateRoom(RecievedMessage*);
	bool handleCloseRoom(RecievedMessage*);
	bool handleJoinRoom(RecievedMessage*);
	bool handleLeaveRoom(RecievedMessage*);
	void handleGetUsersInRoom(RecievedMessage*);
	void handleGetRooms(RecievedMessage*);

	void handleGetBestScores(RecievedMessage*);
	void handleGetPersonalStatus(RecievedMessage*);

	void handleRecievedMessages();
	void addRecievedMessage(RecievedMessage*);
	RecievedMessage* buildRecievedMessage(SOCKET, int);

	User* getUserByName(string);
	User* getUserBySocket(SOCKET);
	Room* getRoomById(int);

	static int _roomIdSequence;

	SOCKET _socket;
	map<SOCKET, User*> _connectedUsers;
	DataBase _db;
	map<int, Room*> _roomsLIst;
	std::mutex _mtxRecievedMessages;
	queue<RecievedMessage*> _queRcvMessages;
};