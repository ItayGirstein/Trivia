#pragma once
#include "Helper.h"
#include "User.h"
#include "sqlite3.h"
#include <unordered_map>

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
<<<<<<< HEAD
	int callbackGeneral(void* notUsed, int argc, char** argv, char** azCol);
=======
	void rcCheck(int rc, sqlite3* db);
	static int callbackCount(void* notUsed, int argc, char** argv, char** azCol);
>>>>>>> 7f7a295c7f887a669488086263f8ada64aed6742
	static int callbackQuestions(void* notUsed, int argc, char** argv, char** azCol);
	//static int callbackBestScore(void* notUsed, int argc, char** argv, char** azCol);
	//static int callbackPersonalStatus(void* notUsed, int argc, char** argv, char** azCol);
	sqlite3* _db;
	int _rc;
	std::unordered_map<string, vector<string>> _results;
};

