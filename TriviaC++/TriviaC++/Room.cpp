#include "Room.h"
#include "User.h"

Room::Room(int id, User * a, string n, int max, int time, int q) : _id(id), _admin(a), _name(n), _maxUsers(max), _questionTime(time), _questionsNo(q)
{
	_users.push_back(a);
}

bool Room::joinRoom(User* user)
{
	if (_maxUsers == _users.size())
	{
		user->send(Protocol::M110('1', _questionsNo, _questionTime));	//failure in joining room
		return false;
	}
	_users.push_back(user);
	user->send(Protocol::M110('0', _questionsNo, _questionTime));	//success in joining room
	sendMessage(getUsersListMessage());	//online users msg
	return true;
}

void Room::leaveRoom(User* user)
{
	bool found = false;
	for (int i = 0; i < _users.size() && !found; i++)
	{
		if (_users[i] == user)
		{
			_users.erase(_users.begin() + i);
			sendMessage(user, Protocol::M112());	//success in leaving room
			found = true;	//DONT KEEP GOING
		}
	}
	sendMessage(getUsersListMessage());	//online users msg
}

int Room::closeRoom(User* user)
{
	if (user == _admin)
	{
		for (int i = 0; i < _users.size(); i++)
		{
			_users[i]->send(Protocol::M116());	//close room msg
			if (_users[i] != user)
			{
				_users[i]->clearRoom();	//clearing room to everybody but admin
			}
		}
		return _id;
	}
	return NOT_ADMIN;
}

vector<User*> Room::getUsers()
{
	return _users;
}

string Room::getUsersListMessage()
{
	return Protocol::M108(_users);
}

int Room::getQuestionsNo()
{
	return _questionsNo;
}

int Room::getId()
{
	return _id;
}

string Room::getName()
{
	return _name;
}

int Room::getQuestionTime()
{
	return _questionTime;
}

string Room::getUsersAsString(vector<User*> users, User* user)
{
	string toReturn = user->getUsername();
	for (int i = 0; i < users.size(); i++)
	{
		toReturn += "," + users[i]->getUsername();
	}
	return toReturn;
}

void Room::sendMessage(string msg)
{
	sendMessage(nullptr, msg);
}

void Room::sendMessage(User* exUser, string msg)
{
	for (int i = 0; i < _users.size(); i++)
	{
		try
		{
			if (_users[i] != exUser)
			{
				_users[i]->send(msg);
			}
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}