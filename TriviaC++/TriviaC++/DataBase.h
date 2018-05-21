#pragma once
#include "Helper.h"
#include "User.h"
#include "sqlite3.h"


class DataBase
{
public:
	DataBase();
	~DataBase();

	bool isUserExists(string username);
	bool addNewUser(string, string, string);
	bool isUserAndPassMatch(string user, string pass);
	vector<Question*> initQuestions(int num);
	vector<string> getBestScores();
	vector<string> getPersonalStatus(string);
	int insertNewGame();
	bool updateGameStatus(int);
	bool addAnswerToPlayer(int, string, int, string, bool, int);


private:
	static int callbackCount(void*, int, char**, char**);
	static int callbackQuestions(void*, int, char**, char**);
	static int callbackBestScore(void*, int, char**, char**);
	static int callbackPersonalStatus(void*, int, char**, char**);
};

