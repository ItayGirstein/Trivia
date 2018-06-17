#include "Game.h"
#include "DataBase.h"
#include "User.h"
#include "Question.h"

Game::Game(const vector<User*>& players, int questionsNo, DataBase &db) : _questions_no(questionsNo), _db(db)
{
	try
	{
		_id = _db.insertNewGame();
		_questions = _db.initQuestions(_questions_no);
		_players = players;
		for (int i = 0; i < _players.size(); i++)
		{
			_players[i]->setGame(this);
			_results.insert(pair<string, int>(_players[i]->getUsername(), 0));
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

Game::~Game()
{
	_questions.clear();
	_players.clear();
}

void Game::sendFirstQuestion()
{
	sendQuestionToAllUsers();
}

void Game::handleFinishGame()
{
	_db.updateGameStatus(getId());
	for (int i = 0; i < _players.size(); i++)
	{
		try
		{
			_players[i]->send(Protocol::M121(_results));
			_players[i]->setGame(nullptr);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

bool Game::handleNextTurn()
{
	bool toReturn = true;
	if (_players.size() == 0)
	{
		handleFinishGame();
		toReturn = false;
	}
	for (int i = 0; i < _players.size(); i++)
	{
		if (_players.size() == _currentTurnAnswers)
		{
			if (_currQuestionIndex == _questions_no)
			{
				handleFinishGame();
				toReturn = false;
			}
			else
			{
				_currQuestionIndex++;
				sendQuestionToAllUsers();
			}
		}
	}
	return toReturn;
}

bool Game::handleAnswerFromUser(User* user, int answerNo, int time)
{
	bool isCorrect = false;
	_currentTurnAnswers++;
	if (_questions[_currQuestionIndex]->getCorrectAnswerIndex() == answerNo)	//user is right
	{
		_results[user->getUsername()]++;
		isCorrect = true;
	}
	if (answerNo == 5)	//user didnt answer (bcz of time)
	{
		_db.addAnswerToPlayer(_id, user->getUsername(), _questions[_currQuestionIndex]->getId(), "", isCorrect, time);
	}
	else
	{
		_db.addAnswerToPlayer(_id, user->getUsername(), _questions[_currQuestionIndex]->getId(), _questions[_currQuestionIndex]->getAnswers()[answerNo], isCorrect, time);
	}
	user->send(Protocol::M120(isCorrect));
	return handleNextTurn();
}

bool Game::leaveGame(User* CurrUser)
{
	for (int i = 0; i < _players.size(); i++)
	{
		if (_players[i] == CurrUser)
		{
			_players.erase(_players.begin() + i);
		}
	}
	return handleNextTurn();
}

int Game::getId()
{
	return _id;
}

void Game::sendQuestionToAllUsers()
{
	_currentTurnAnswers = 0;
	for (int i = 0; i < _players.size(); i++)
	{
		try
		{
			_players[i]->send(Protocol::M118(_questions[_currQuestionIndex]));
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}
