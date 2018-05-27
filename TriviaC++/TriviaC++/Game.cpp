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
	string msg("121" + std::to_string(_players.size()));
	for (int i = 0; i <_players.size(); i++)
	{
		msg += "##" + _players[i]->getUsername() + std::to_string(_results[_players[i]->getUsername()]);
	}
	for (int i = 0; i < _players.size(); i++)
	{
		try
		{
			_players[i]->send(msg);
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
	return false;
}

bool Game::handleAnswerFromUser(User *, int, int)
{
	return false;
}

bool Game::leaveGame(User *)
{
	return false;
}

int Game::getId()
{
	return 0;
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
	string msg("118###"+_questions[0]->getQuestion());
	_currentTurnAnswers = 0;
	string* ans = _questions[0]->getAnswers();
	for (int i = 0; i < 4; i++)
	{
		msg += "###"+ans[i];
	}
	for (int i = 0; i < _players.size(); i++)
	{
		try
		{
			_players[i]->send(msg);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}
