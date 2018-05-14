#include "Room.h"

Room::Room(int id, User * a, string n, int max, int time, int q) : _id(id), _admin(a), _name(n), _maxUsers(max), _questionTime(time), _questionsNo(q)
{
}

bool Room::joinRoom(User *)
{
	return false;
}

void Room::leaveRoom(User *)
{
}

int Room::closeRoom(User *)
{
	return 0;
}

vector<User*> Room::getUsers()
{
	return _users;
}

string Room::getUsersListMessage()
{
	return string();
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

string Room::getUsersAsString(vector<User*> users, User * user)
{
	string toReturn = user.getUsername();
	for (int i = 0; i < users.size(); i++)
	{
		toReturn += "," + users[i].getUsername();
	}
	return toReturn;
}

void Room::sendMessage(string)
{
}

void Room::sendMessage(User *, string)
{
}
