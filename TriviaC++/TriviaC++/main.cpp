#pragma comment (lib, "ws2_32.lib")

#include "TriviaServer.h"
#include <iostream>
#include <fstream>
#include "WSAInitializer.h"

int main()
{
	try
	{
		WSAInitializer wsa_init;
		TriviaServer trServer;
		trServer.serve();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
		return 1;
	}
	catch (...)
	{
		std::cout << "Unknown exception in main !" << std::endl;
		return 1;
	}
	return 0;
}