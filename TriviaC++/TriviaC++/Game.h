#pragma once

#include "Protocol.h"
#include "Question.h"

class User;
class DataBase;

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
	bool insertGameToDB();
	void initQuestionsFromDB();
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

