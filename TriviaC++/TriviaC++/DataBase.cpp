#include "DataBase.h"



DataBase::DataBase()
{
	_rc = sqlite3_open("trivia.db", &_db);
	rcCheck(_rc, _db);
}


DataBase::~DataBase()
{
	sqlite3_close(_db);
}

bool DataBase::isUserExists(string username)
{
	char *zErrMsg = 0;

	string command = "select email from t_users where username = " + username + ";"; // the email used for testing.
	_rc = sqlite3_exec(_db, command.c_str(), this->callbackGeneral, nullptr, &zErrMsg);
	rcCheck(_rc, _db);

	auto it = _results.begin();

	if (_results.size() != 0)
	{
		if (it->second[0] == "")
		{
			return false;
		}
	}

	return true;
}

bool DataBase::addNewUser(string username, string password, string email)
{
	char *zErrMsg = 0;

	string command = "insert into t_users(username, password, email) values(" + username + ", " + password + ", " + email + ");";
	_rc = sqlite3_exec(_db, command.c_str(), this->callbackGeneral, nullptr, &zErrMsg);
	return rcCheck(_rc, _db);
}

bool DataBase::isUserAndPassMatch(string user, string pass)
{
	string command = "select password from t_users where username = " + user + ";";
	char *zErrMsg = 0;

	auto it = _results.begin();

	if (_results.size() != 0)
	{
		if (it->second[0] == pass)
		{
			return true;
		}
	}
	return false;

}

vector<Question*> DataBase::initQuestions(int questionsNo)
{
	vector<Question*> toReturn;
	while (questionsNo != 0)
	{
		

		questionsNo--;
	}
	return toReturn;
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

int DataBase::callbackGeneral(void* notUsed, int argc, char** argv, char** azCol)
{
	for (int i = 0; i < argc; i++)
	{
		auto it = _results.find(azCol[i]);
		if (it != _results.end())
		{
			it->second.push_back(argv[i]);
		}
		else
		{
			std::pair<string, vector<string>> p;
			p.first = azCol[i];
			p.second.push_back(argv[i]);
			_results.insert(p);
		}
	}
	return 0;
}

int DataBase::callbackQuestions(void * notUsed, int argc, char ** argv, char ** azCol)
{
	return 0;
}

/*
check if rc is valid
input: rc and the database
output: none
*/
bool DataBase::rcCheck(int rc, sqlite3* db)
{
	if (rc)
	{
		std::cout << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return true;
	}
	return false;
}
