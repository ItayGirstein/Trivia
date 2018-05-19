#pragma once

#include "Helper.h"
#include "Question.h"

class User;
class DataBase;

class Game
{
public:
	Game(const vector<User*>&, int, DataBase&);
	~Game() = default;
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


	vector<Question*> _questions;
	vector<User*> _players;
	int _questions_no;
	int _cuurQuestionIndex;
	DataBase& _db;
	map<string, int> _results;

};

