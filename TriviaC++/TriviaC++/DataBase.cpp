#include "DataBase.h"

string results;
vector<string> resultsVecor;

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
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);
	rcCheck(_rc, _db);

	if (results.size() != 0)
	{
		if (resultsVecor[0] == "")
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
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);
	return rcCheck(_rc, _db);
}

bool DataBase::isUserAndPassMatch(string user, string pass)
{
	string command = "select password from t_users where username = " + user + ";";
	char *zErrMsg = 0;
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);


	if (results.size() != 0)
	{
		if (resultsVecor[0] == pass)
		{
			return true;
		}
	}
	return false;

}

vector<Question*> DataBase::initQuestions(int questionsNo)
{
	srand(time(NULL));
	vector<Question*> toReturn = vector<Question*>();
	vector<int> generatedValues = vector<int>();
	string command = "select count() from questions;";
	char *zErrMsg = 0;
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);
	rcCheck(_rc, _db);

	int range = std::stoi(resultsVecor[1]);
	int num = 0;

	if (questionsNo > range) {
		std::cout << "Invalid Number of Questions." << std::endl;
		return vector<Question*>();
	}
	for (int i = 0; i < questionsNo; i++) {

		num = 1 + (rand() % (range));
		while (std::find(generatedValues.begin(), generatedValues.end(), num) != generatedValues.end())
		{
			num = 1 + (rand() % (range));
		}
		generatedValues.push_back(num);

		command = "select * from questions where question_id=" + std::to_string(num) + ";";
		results = "";
		_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);

		toReturn.push_back(new Question(num, resultsVecor[2], resultsVecor[3], resultsVecor[4], resultsVecor[5], resultsVecor[6]));
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
	char *zErrMsg = 0;

	string command = "insert into t_games(status, start_game) values(0, timedate('now'));";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);

	command = "select game_id from t_games order by game_id desc limit 1;";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);

	return results[0];
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
	int i = 0;
	results = "";

	for (i = 0; i < argc; i++) {
		if (argv[i]) {
			results += "#";
			results += argv[i];
		}
	}
	resultsVecor.clear();
	std::stringstream test;
	std::string segment;

	test.str(results);
	while (std::getline(test, segment, '#'))
	{
		resultsVecor.push_back(segment);
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
