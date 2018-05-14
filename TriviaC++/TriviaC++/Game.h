#pragma once

#include "Helper.h"
#include "User.h"
#include "Question.h"

class Game
{
public:
	Game();
	~Game();
private:
	vector<Question*> _questions;
	vector<User*> _players;
	int _questions_no;
	int _cuurQuestionIndex;
	DataBase& _db;
	map<string, int> _results;

};

