#include "DataBase.h"



DataBase::DataBase()
{
	int rc = sqlite3_open("trivia.db", &_db);
	rcCheck(rc, _db);
}


DataBase::~DataBase()
{
	sqlite3_close(_db);
}

bool DataBase::isUserExists(string username)
{
	return false;
}

bool DataBase::addNewUser(string, string, string)
{
	return false;
}

bool DataBase::isUserAndPassMatch(string user, string pass)
{
	return false;
}

vector<Question*> DataBase::initQuestions(int num)
{
	return vector<Question*>();
}

vector<string> DataBase::getBestScores()
{
	return vector<string>();
}

vector<string> DataBase::getPersonalStatus(string)
{
	return vector<string>();
}

int DataBase::insertNewGame()
{
	return 0;
}

bool DataBase::updateGameStatus(int)
{
	return false;
}

bool DataBase::addAnswerToPlayer(int, string, int, string, bool, int)
{
	return false;
}

int DataBase::callbackCount(void *, int, char **, char **)
{
	return 0;
}

int DataBase::callbackQuestions(void *, int, char **, char **)
{
	return 0;
}

int DataBase::callbackBestScore(void *, int, char **, char **)
{
	return 0;
}

int DataBase::callbackPersonalStatus(void *, int, char **, char **)
{
	return 0;
}

/*
check if rc is valid
input: rc and the database
output: none
*/
void DataBase::rcCheck(int rc, sqlite3* db)
{
	if (rc)
	{
		std::cout << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
	}
}
