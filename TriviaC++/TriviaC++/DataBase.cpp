#include "DataBase.h"
#include "User.h"
#include "Question.h"

string results;
vector<string> resultsVector;

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

	string command = "select email from t_users where username = \'" + username + "\';"; // the email used for testing.
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);
	rcCheck(_rc, _db);

	if (results.size() != 0)
	{
		if (resultsVector[1] == "")
		{
			return true;
		}
	}

	return false;
}

bool DataBase::addNewUser(string username, string password, string email)
{
	char *zErrMsg = 0;

	string command = "insert into t_users(username, password, email) values(\'" + username + "\', \'" + password + "\',\' " + email + "\');";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);
	return rcCheck(_rc, _db);
}

bool DataBase::isUserAndPassMatch(string user, string pass)
{
	string command = "select password from t_users where username = \'" + user + "\';";
	char *zErrMsg = 0;
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);


	if (results.size() != 0)
	{
		if (resultsVector[1] == pass)
		{
			return true;
		}
	}
	return false;

}

vector<Question*> DataBase::initQuestions(int questionsNo)
{
	//srand(time(NULL)); // need to be written on Main().
	vector<Question*> toReturn = vector<Question*>();
	vector<int> generatedValues = vector<int>();
	string command = "select count() from t_questions;";
	char *zErrMsg = 0;
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);
	rcCheck(_rc, _db);

	int range = std::stoi(resultsVector[1]);
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

		command = "select * from t_questions where question_id=\'" + std::to_string(num) + "\';";
		results = "";
		_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);

		toReturn.push_back(new Question(num, resultsVector[2], resultsVector[3], resultsVector[4], resultsVector[5], resultsVector[6]));
	}

	return toReturn;
}

vector<string> DataBase::getBestScores()
{
	char *zErrMsg = 0;
	vector<string> toReturn;

	//retive the best one
	string command = "select username from t_players_answers where is_correct = 1 group by username order by count(is_correct) desc limit 1;";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);

	string username = resultsVector[1];
	toReturn.push_back(username);

	//retrive that user's score
	command = "select count(is_correct) from t_players_answers where username=\"" + username + "\";";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);

	toReturn.push_back(resultsVector[1]);

	//second best one
	command = "select username from t_players_answers where is_correct = 1 group by username order by count(is_correct) desc limit 1 offset 1;";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);

	username = resultsVector[1];
	toReturn.push_back(username);

	//retrive that user's score
	command = "select count(is_correct) from t_players_answers where username=\"" + username + "\";";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);

	toReturn.push_back(resultsVector[1]);

	//third best
	command = "select username from t_players_answers where is_correct = 1 group by username order by count(is_correct) desc limit 1 offset 2;";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);

	username = resultsVector[1];
	toReturn.push_back(username);

	//retrive that user's score
	command = "select count(is_correct) from t_players_answers where username=\"" + username + "\";";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);

	toReturn.push_back(resultsVector[1]);

	return toReturn;
}

vector<string> DataBase::getPersonalStatus(string name)
{
	char *zErrMsg = 0;
	vector<string> toReturn;

	string command = "select count(game_id) from t_players_answers where username=\"" + name + "\";";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);
	toReturn.push_back(resultsVector[1]);

	command = "select count(is_correct) from t_players_answers where username=\"" + name + "\";";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);
	toReturn.push_back(resultsVector[1]);

	command = "select count(is_correct) from t_players_answers where username=\"" + name + "\" and is_correct=0;";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);
	toReturn.push_back(resultsVector[1]);

	command = "select avg(answer_time) from t_players_answers where username = \"" + name + "\" ;";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);
	if (resultsVector.size())
		toReturn.push_back(resultsVector[1]);
	else
		toReturn.push_back("0");

	return toReturn;
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

	return stoi(resultsVector[1]);
}

bool DataBase::updateGameStatus(int gameId)
{
	char *zErrMsg = 0;

	string command = "update status = 1, end_game = timedate('now') where game_id = \'" + std::to_string(gameId) + "\';";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);

	return rcCheck(_rc, _db);
}

bool DataBase::addAnswerToPlayer(int gameId, string username, int questionId, string answer, bool isCorrect, int answerTime)
{
	char *zErrMsg = 0;

	string command = "insert into t_players_answers(game_id, username, question_id, player_answer, is_correct, answer_time) values(\'" +
		std::to_string(gameId) +
		"\',\'" + username +
		"\',\'" + std::to_string(questionId) +
		"\',\'" + answer +
		"\',\'" + std::to_string(isCorrect) +
		"\',\'" + std::to_string(answerTime) +
		"\');";
	results = "";
	_rc = sqlite3_exec(_db, command.c_str(), callbackGeneral, nullptr, &zErrMsg);

	return rcCheck(_rc, _db);
}

int DataBase::callbackGeneral(void* notUsed, int argc, char** argv, char** azCol)
{
	int i = 0;
	results = "";

	for (i = 0; i != argc; i++) {
		if (argv[i]) {
			results += "#";
			results += argv[i];
		}
	}
	resultsVector.clear();
	std::stringstream test;
	std::string segment;

	test.str(results);
	//std::getline(test, segment, '#'); // remove the first empty line
	while (std::getline(test, segment, '#'))
	{
		std::cout << segment << std::endl;
		resultsVector.push_back(segment);
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
