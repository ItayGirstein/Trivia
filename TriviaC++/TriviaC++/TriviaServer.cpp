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
	catch (...) {}
}

void TriviaServer::serve()
{
	bindAndListen();
	std::thread clienthandler(&TriviaServer::clientHandler, _socket);
}

void TriviaServer::clientHandler(SOCKET)
{
}
