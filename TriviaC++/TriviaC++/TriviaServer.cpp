#include "TriviaServer.h"

TriviaServer::TriviaServer()
{
	_db = DataBase();
	_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

TriviaServer::~TriviaServer()
{
	_connectedUsers.clear();
	try
	{
		::closesocket(_socket);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TriviaServer::serve()
{
	bindAndListen();
	std::thread clienthandler(&TriviaServer::clientHandler, _socket);
	while (true)
	{
		accept();
	}
}
//todo
void TriviaServer::bindAndListen()
{
}
//todo
void TriviaServer::accept()
{
}
//todo
void TriviaServer::clientHandler(SOCKET)
{
}

void TriviaServer::safeDeleteUser(RecievedMessage* msg)
{
	try
	{
		SOCKET client_socket = msg->getSock();
		handleSignout(msg);
		closesocket(client_socket);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

User* TriviaServer::handleSignin(RecievedMessage* msg)
{
	if (_db.isUserAndPassMatch(msg->getValues()[1], msg->getValues()[2]))
	{
		if (getUserByName(msg->getValues()[1]))
		{
			User newUser = User(msg->getValues()[1], msg->getSock());
			_connectedUsers.insert(pair<SOCKET, User*>(msg->getSock(), &newUser));
			newUser.send(Protocol::M102("success"));
			return &newUser;
		}
		else
		{
			Helper::sendData(msg->getSock(), Protocol::M102("User is already connected"));
		}
	}
	else
	{
		Helper::sendData(msg->getSock(), Protocol::M102("Wrong Details"));
	}
	return nullptr;
}

bool TriviaServer::handleSignup(RecievedMessage* msg)
{
	string username = msg->getValues()[1];
	string pass = msg->getValues()[2];
	string mail = msg->getValues()[3];

	if (Validator::isPasswordValid(pass))
	{
		if (Validator::isUsernameVaild(username))
		{
			if (!_db.isUserExists(username))
			{
				_db.addNewUser(username, pass, mail);
				Helper::sendData(msg->getSock(), Protocol::M104("success"));
				return true;
			}
			else
			{
				Helper::sendData(msg->getSock(), Protocol::M104("Other"));
			}
		}
		else
		{
			Helper::sendData(msg->getSock(), Protocol::M104("Username is illegal"));
		}
	}
	else
	{
		Helper::sendData(msg->getSock(), Protocol::M104("Pass illegal"));
	}
	return false;
}

void TriviaServer::handleSignout(RecievedMessage* msg)
{
	if (msg->getUser())
	{
		_connectedUsers.erase(msg->getUser()->getSocket());
		if (handleCloseRoom(msg))
		{
			if (handleLeaveRoom(msg))
			{
				handleLeaveGame(msg);
			}
		}
	}
}
//check if needed
void TriviaServer::handleLeaveGame(RecievedMessage* msg)
{
	if (msg->getUser()->leaveGame())
	{
		msg->getUser()->getGame()->handleFinishGame();	//me
		delete msg->getUser()->getGame();
	}
}
//todo
void TriviaServer::handleStartGame(RecievedMessage* msg)
{
}
//check if needed
void TriviaServer::handlePlayerAnswer(RecievedMessage* msg)
{
	if (msg->getUser()->getGame() != nullptr)
	{
		if (!msg->getUser()->getGame()->handleAnswerFromUser(msg->getUser(), std::stoi(msg->getValues()[0]), std::stoi(msg->getValues()[1])))
		{
			msg->getUser()->getGame()->handleFinishGame();	//me
			delete msg->getUser()->getGame();
		}
	}
}

bool TriviaServer::handleCreateRoom(RecievedMessage* msg)
{
	if (msg->getUser())
	{
		_roomIdSequence += 1;
		if (msg->getUser()->createRoom(std::stoi(msg->getValues()[0]), msg->getValues()[1], std::stoi(msg->getValues()[2]), std::stoi(msg->getValues()[3]), std::stoi(msg->getValues()[4])))
		{
			_roomsLIst.insert(pair<int, Room*>(msg->getUser()->getRoom()->getId(), msg->getUser()->getRoom()));
			return true;
		}
	}
	return false;
}

bool TriviaServer::handleCloseRoom(RecievedMessage* msg)
{
	if (msg->getUser()->getRoom())
	{
		if (msg->getUser()->closeRoom() != -1)
		{
			_roomsLIst.erase(msg->getUser()->getRoom()->getId());
			return true;
		}
	}
	return false;
}

bool TriviaServer::handleJoinRoom(RecievedMessage* msg)
{
	if (msg->getUser())
	{
		if (getRoomById(std::stoi(msg->getValues()[0])))
		{
			return msg->getUser()->joinRoom(getRoomById(std::stoi(msg->getValues()[0])));
		}
		msg->getUser()->send(Protocol::M110('2', 0, 0));
	}
	return false;
}

bool TriviaServer::handleLeaveRoom(RecievedMessage* msg)
{
	if (msg->getUser())
	{
		if (msg->getUser()->getRoom())
		{
			msg->getUser()->leaveRoom();
			return true;
		}
	}
	return false;
}

void TriviaServer::handleGetUsersInRoom(RecievedMessage* msg)
{
	if (msg->getUser())
	{
		if (getRoomById(std::stoi(msg->getValues()[0])))
		{
			msg->getUser()->send(getRoomById(std::stoi(msg->getValues()[0]))->getUsersListMessage());
		}
		msg->getUser()->send(Protocol::M110('2', 0, 0));
	}
}

void TriviaServer::handleGetRooms(RecievedMessage* msg)
{
	msg->getUser()->send(Protocol::M106(_roomsLIst));
}

void TriviaServer::handleGetBestScores(RecievedMessage* msg)
{
	msg->getUser()->send(Protocol::M124(_db.getBestScores()));
}

void TriviaServer::handleGetPersonalStatus(RecievedMessage* msg)
{
	msg->getUser()->send(Protocol::M126(_db.getPersonalStatus(msg->getUser()->getUsername())));
}
//todo
void TriviaServer::handleRecievedMessages()
{

}
//todo
void TriviaServer::addRecievedMessage(RecievedMessage* msg)
{
}
//todo
RecievedMessage* TriviaServer::buildRecievedMessage(SOCKET client_socket, int msgCode)
{
	return nullptr;
}

User * TriviaServer::getUserByName(string username)
{
	map<SOCKET, User*>::iterator it = _connectedUsers.begin();
	while (it != _connectedUsers.end())
	{
		if (it->second->getUsername() == username)
		{
			return it->second;
		}
		it++;
	}
	return nullptr;
}

User * TriviaServer::getUserBySocket(SOCKET client_socket)
{
	return _connectedUsers[client_socket];
}

Room * TriviaServer::getRoomById(int roomId)
{
	return _roomsLIst[roomId];
}
