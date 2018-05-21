#include "Game.h"

Game::Game(const vector<User*>& names, int flag, DataBase &db)
{
}

void Game::sendFirstQuestion()
{
}

void Game::handleFinishGame()
{
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
}
