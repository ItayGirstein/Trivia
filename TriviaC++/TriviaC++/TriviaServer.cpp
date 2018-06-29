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
	while (true)
	{
		acceptClient();
	}
}

void TriviaServer::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	if (::bind(_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

void TriviaServer::acceptClient()
{
	SOCKET client_socket = accept(_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::thread tr(&TriviaServer::clientHandler, _socket);
	tr.detach();
}

void TriviaServer::clientHandler(SOCKET client_socket)
{
	RecievedMessage* currRcvMsg = nullptr;
	try
	{
		// get the first message code
		int msgCode = Helper::getMessageTypeCode(client_socket);

		while (msgCode != msgCodes::C299) //C299 == EXIT
		{
			currRcvMsg = buildRecievedMessage(client_socket, msgCode);
			addRecievedMessage(currRcvMsg);

			msgCode = Helper::getMessageTypeCode(client_socket);
		}

		currRcvMsg = buildRecievedMessage(client_socket, msgCodes::C299);
		addRecievedMessage(currRcvMsg);

	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was catch in function clientHandler. socket=" << client_socket << ", what=" << e.what() << std::endl;
		currRcvMsg = buildRecievedMessage(client_socket, msgCodes::C299);
		addRecievedMessage(currRcvMsg);
	}
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

void TriviaServer::handleLeaveGame(RecievedMessage* msg)
{
	if (msg->getUser()->leaveGame())
	{
		delete msg->getUser()->getGame();
		msg->getUser()->leaveGame();
	}
}
//todo
void TriviaServer::handleStartGame(RecievedMessage* msg)
{
}

void TriviaServer::handlePlayerAnswer(RecievedMessage* msg)
{
	if (msg->getUser()->getGame() != nullptr)
	{
		if (!msg->getUser()->getGame()->handleAnswerFromUser(msg->getUser(), std::stoi(msg->getValues()[0]), std::stoi(msg->getValues()[1])))
		{
			delete msg->getUser()->getGame();
			msg->getUser()->leaveGame();
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
	while (true)
	{
		if (_queRcvMessages.size() > 0)
		{
			_mtxRecievedMessages.lock();
			RecievedMessage* rcv = _queRcvMessages.front();
			_queRcvMessages.pop();
			_mtxRecievedMessages.unlock();
			switch (rcv->getMessageCode())
			{
			case msgCodes::C200:
				handleSignin(rcv);
				break;

			case msgCodes::C201:
				handleSignout(rcv);
				break;

			case msgCodes::C203:
				handleSignup(rcv);
				break;

			case msgCodes::C205:
				handleGetRooms(rcv);
				break;

			case msgCodes::C207:
				handleGetUsersInRoom(rcv);
				break;

			case msgCodes::C209:
				handleJoinRoom(rcv);
				break;

			case msgCodes::C211:
				handleLeaveRoom(rcv);
				break;

			case msgCodes::C213:
				handleCreateRoom(rcv);
				break;

			case msgCodes::C215:
				handleCloseRoom(rcv);
				break;
			case msgCodes::C217:
				handleStartGame(rcv);
				break;

			case msgCodes::C219:
				handlePlayerAnswer(rcv);
				break;

			case msgCodes::C222:
				handleLeaveGame(rcv);
				break;

			case msgCodes::C223:
				handleGetBestScores(rcv);
				break;

			case msgCodes::C225:
				handleGetPersonalStatus(rcv);
				break;

			default:
				break;
			}
			delete rcv;
		}
	}
}

void TriviaServer::addRecievedMessage(RecievedMessage* msg)
{
	_mtxRecievedMessages.lock();
	_queRcvMessages.push(msg);
	_mtxRecievedMessages.unlock();
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
