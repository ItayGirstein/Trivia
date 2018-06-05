#include "Game.h"
#include "DataBase.h"
#include "User.h"

Game::Game(const vector<User*>& players, int flag, DataBase &db) : _players(players), _db(db)
{
	try
	{
		_db.insertNewGame();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	_db.initQuestions(0);
	_results.clear();
	for (int i = 0; i < _players.size(); i++)
	{
		_players[i]->setGame(this);
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
			_players[i]->send(Protocol::endGameMsg(_results));
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
	if (!_players.size())
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

bool Game::insertGameToDB()
{
	return false;
}

void Game::initQuestionsFromDB()
{
}

void Game::sendQuestionToAllUsers()
{
	_currentTurnAnswers = 0;
	for (int i = 0; i < _players.size(); i++)
	{
		try
		{
			_players[i]->send(Protocol::sendQuestionMsg(_questions[_currQuestionIndex]));
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}
