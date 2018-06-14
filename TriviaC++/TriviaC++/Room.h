#pragma once
#include "Protocol.h"

#define NOT_ADMIN -1

class User;

class Room
{
public:
	Room(int id, User* a, string n, int max, int time, int q);
	~Room() = default;
	bool joinRoom(User*);
	void leaveRoom(User*);
	int closeRoom(User*);
	vector<User*> getUsers();
	string getUsersListMessage();
	int getQuestionsNo();
	int getId();
	string getName();
	int getQuestionTime();

private:
	string getUsersAsString(vector<User*>, User*);
	void sendMessage(string);
	void sendMessage(User*, string);

	vector<User*> _users;
	User* _admin;
	int _maxUsers;
	int _questionTime;
	int _questionsNo;
	string _name;
	int _id;
};

