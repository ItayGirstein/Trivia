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
}

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
	if (_db.isUserAndPassMatch(msg->getValues[1], msg->getValues[2]))
	{
		if (getUserByName(msg->getValues[1]))
		{
			User newUser = User(msg->getValues[1], msg->getSock());
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
	string username = msg->getValues[1];
	string pass = msg->getValues[2];
	string mail = msg->getValues[3];

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

void TriviaServer::handleRecievedMessages()
{

}

void TriviaServer::addRecievedMessage(RecievedMessage* msg)
{
}

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
