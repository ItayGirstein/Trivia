#include "TriviaServer.h"

int TriviaServer::_roomIdSequence = 1;

TriviaServer::TriviaServer() :_db()
{
	WSAData wsa_data = {};
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
		throw	std::exception("WSAStartup failed");

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

	std::thread tr(&TriviaServer::handleRecievedMessages, this);
	tr.detach();

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
	sa.sin_addr.s_addr = INADDR_ANY;
	if (::bind(_socket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	if (::listen(_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

void TriviaServer::acceptClient()
{
	SOCKET client_socket = ::accept(_socket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::thread tr(&TriviaServer::clientHandler, this, client_socket);
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
			currRcvMsg->setUser(getUserBySocket(client_socket));
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
		if (getUserBySocket(client_socket))
			_connectedUsers.erase(client_socket);
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
	if (_db.isUserAndPassMatch(msg->getValues()[0], msg->getValues()[1]))
	{
		if (!getUserByName(msg->getValues()[0]))
		{
			User* newUser = new User(msg->getValues()[0], msg->getSock());
			_connectedUsers.insert(pair<SOCKET, User*>(msg->getSock(), newUser));
			newUser->send(Protocol::M102("success"));
			return newUser;
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
	string username = msg->getValues()[0];
	string pass = msg->getValues()[1];
	string mail = msg->getValues()[2];

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

void TriviaServer::handleStartGame(RecievedMessage* msg)
{
	try
	{
		msg->getUser()->setGame(new Game(msg->getUser()->getRoom()->getUsers(), msg->getUser()->getRoom()->getQuestionsNo(), _db));
		_roomsLIst.erase(msg->getUser()->getRoom()->getId());
		msg->getUser()->getGame()->sendFirstQuestion();
	}
	catch (std::exception& e)
	{
		msg->getUser()->send(Protocol::M114("fail"));
	}
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
		if (msg->getUser()->createRoom(_roomIdSequence++, msg->getValues()[0], std::stoi(msg->getValues()[1]), std::stoi(msg->getValues()[2]), std::stoi(msg->getValues()[3])))
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
		int id = msg->getUser()->getRoom()->getId();
		if (msg->getUser()->closeRoom() != -1)
		{
			_roomsLIst.erase(id);
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
		else
		{
			msg->getUser()->send(Protocol::M110('2', 0, 0));
		}
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

void TriviaServer::handleRecievedMessages()
{
	while (true)
	{
		if (_queRcvMessages.size() > 0)
		{
			bool unknown = false;
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
				unknown = true;
				break;
			}
			if (unknown)
				std::cout << "************" << std::endl << "recived unknown message from " << rcv->getSock() << ": " << to_string(rcv->getMessageCode()) << std::endl << "************" << std::endl;
			else
			{
				std::cout << "recived from " << rcv->getSock() << ": " << to_string(rcv->getMessageCode()) << " ";
				for (int i = 0; i < rcv->getValues().size(); i++)
				{
					std::cout << rcv->getValues()[i] << " ";
				}
				std::cout << std::endl;
				TRACE("------------");
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

RecievedMessage* TriviaServer::buildRecievedMessage(SOCKET client_socket, int msgCode)
{
	//lambda
	auto getUserPass = [client_socket]()
	{
		vector<string> userPass;
		userPass.push_back(Helper::getStringPartFromSocket(client_socket, Helper::getIntPartFromSocket(client_socket, 2)));
		userPass.push_back(Helper::getStringPartFromSocket(client_socket, Helper::getIntPartFromSocket(client_socket, 2)));
		return userPass;
	};

	vector<string> values;

	switch (msgCode)
	{
	case msgCodes::C200:
		values = getUserPass();
		break;

	case msgCodes::C203:
		values = getUserPass();
		values.push_back(Helper::getStringPartFromSocket(client_socket, Helper::getIntPartFromSocket(client_socket, 2)));
		break;

	case msgCodes::C207: case msgCodes::C209:
		values.push_back(Helper::getStringPartFromSocket(client_socket, 4));
		break;

	case msgCodes::C213:
		values.push_back(Helper::getStringPartFromSocket(client_socket, Helper::getIntPartFromSocket(client_socket, 2)));
		values.push_back(Helper::getStringPartFromSocket(client_socket, 1));
		values.push_back(Helper::getStringPartFromSocket(client_socket, 2));
		values.push_back(Helper::getStringPartFromSocket(client_socket, 2));
		break;

	case msgCodes::C219:
		values.push_back(Helper::getStringPartFromSocket(client_socket, 1));
		values.push_back(Helper::getStringPartFromSocket(client_socket, 2));
		break;

	default:
		return new RecievedMessage(client_socket, msgCode);
		break;
	}
	return new RecievedMessage(client_socket, msgCode, values);
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
	if (_connectedUsers.find(client_socket) != _connectedUsers.end())
		return _connectedUsers[client_socket];
	return nullptr;
}

Room * TriviaServer::getRoomById(int roomId)
{
	if (_roomsLIst.find(roomId) != _roomsLIst.end())
		return _roomsLIst[roomId];
	return nullptr;
}
