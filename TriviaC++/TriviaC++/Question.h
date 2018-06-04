#pragma once

#include "Protocol.h"

class Question
{
public:
	Question(int cA, string q, string a, string b, string c, string d);
	~Question() = default;

	string getQuestion();
	string* getAnswers();
	int getCorrectAnswerIndex();
	int getId();

private:
	string _question;
	string _answers[4];
	int _correctAnswerIndex;
	int _id;
};

