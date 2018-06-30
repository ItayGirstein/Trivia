#include "Question.h"
#include <algorithm>

template<typename T, int N>
T* end_of(T(&arr)[N])
{
	return arr + N;
}


Question::Question(int id, int cA, string q, string a, string b, string c, string d) : _correctAnswerIndex(cA), _question(q), _id(id)
{
	_answers[0] = a;
	_answers[1] = b;
	_answers[2] = c;
	_answers[3] = d;
}

string Question::getQuestion()
{
	return _question;
}

string* Question::getAnswers()
{
	return _answers;
}

int Question::getCorrectAnswerIndex()
{
	return _correctAnswerIndex;
}

int Question::getId()
{
	return _id;
}
