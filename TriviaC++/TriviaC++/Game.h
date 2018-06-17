#pragma once

#include "Protocol.h"

class User;
class DataBase;
class Question;

class Game
{
public:
	Game(const vector<User*>& , int, DataBase&);
	~Game();
	void sendFirstQuestion();
	void handleFinishGame();
	bool handleNextTurn();
	bool handleAnswerFromUser(User*, int, int);
	bool leaveGame(User*);
	int getId();

private:
	void sendQuestionToAllUsers();

	int _id;
	vector<Question*> _questions;
	vector<User*> _players;
	int _questions_no;
	int _currQuestionIndex;
	DataBase& _db;
	map<string, int> _results;
	int _currentTurnAnswers;
};

