#include "Protocol.h"
#include "Room.h"
#include "Question.h"
#include "User.h"

//200
string Protocol::M200(string userName, string password)
{
	return to_string(msgCodes::C200) +
		"##" + userName +
		"##" + password;
}

//201
string Protocol::M201()
{
	return to_string(msgCodes::C201);
}

//203
string Protocol::M203(string userName, string password, string email)
{
	return to_string(msgCodes::C203) +
		"##" + userName +
		"##" + password +
		"##" + email;
}

//205
string Protocol::M205()
{
	return to_string(msgCodes::C205);
}

//207
string Protocol::M207(int roomID)
{
	return to_string(msgCodes::C207) +
		"####" + to_string(roomID);
}

//209
string Protocol::M209(int roomID)
{
	return to_string(msgCodes::C209) +
		"####" + to_string(roomID);
}

//211
string Protocol::M211()
{
	return to_string(msgCodes::C211);
}

//213
string Protocol::M213(Room roomToCreate)
{
	return to_string(msgCodes::C213) +
		"##" + roomToCreate.getName() +
		"#" + to_string(roomToCreate.getUsers().size()) +
		"##" + to_string(roomToCreate.getQuestionsNo()) +
		"##" + to_string(roomToCreate.getQuestionTime());
}

//215
string Protocol::M215()
{
	return to_string(msgCodes::C215);
}

//217
string Protocol::M217()
{
	return to_string(msgCodes::C217);
}

//219
string Protocol::M219(int ansIndex, int ansTimeSeconds)
{
	return to_string(msgCodes::C219) +
		"#" + to_string(ansIndex) +
		"##" + to_string(ansTimeSeconds);
}

//222
string Protocol::M222()
{
	return to_string(msgCodes::C222);
}

//223
string Protocol::M223()
{
	return to_string(msgCodes::C223);
}

//225
string Protocol::M225()
{
	return to_string(msgCodes::C225);
}

//299
string Protocol::M299()
{
	return to_string(msgCodes::C299);
}

//102
string Protocol::M102(string status)
{
	if (status == "success")
		return to_string(msgCodes::C102) +
		"0";

	else if (status == "Wrong Details")
		return to_string(msgCodes::C102) +
		"1";

	else if (status == "User is already connected")
		return to_string(msgCodes::C102) +
		"2";

	return to_string(msgCodes::UNKOWN_ERROR);
}

//104
string Protocol::M104(string status)
{
	if (status == "success")
		return to_string(msgCodes::C104) +
		"0";

	else if (status == "Pass illegal")
		return to_string(msgCodes::C104) +
		"1";

	else if (status == "Username is already exists")
		return to_string(msgCodes::C104) +
		"2";

	else if (status == "Username is illegal")
		return to_string(msgCodes::C104) +
		"3";

	else if (status == "Other")
		return to_string(msgCodes::C104) +
		"4";

	return to_string(msgCodes::UNKOWN_ERROR);
}

//106
string Protocol::M106(map<int, Room*> roomsList)
{
	string toReturn(to_string(msgCodes::C106) + to_stringProtocol(roomsList.size(),4));
	map<int, Room*>::iterator it = roomsList.begin();
	while (it != roomsList.end())
	{
		toReturn += to_stringProtocol(it->first,4) + to_stringProtocol(it->second->getName().length(),2) + it->second->getName();
		it++;
	}
	return toReturn;
}

//108
string Protocol::M108(vector<User*> usersList)
{
	string toReturn(to_string(msgCodes::C108) + to_string(usersList.size()));
	if (usersList[0]->getRoom())
		for (int i = 0; i < usersList.size(); i++)
		{
			toReturn += to_stringProtocol(usersList[i]->getUsername().length(),2) + usersList[i]->getUsername();
		}

	else
		toReturn += to_string(msgCodes::UNKOWN_ERROR);

	return toReturn;
}

//110
string Protocol::M110(char status, int questionsNumber, int qusetionTime)
{
	if (status == '0')
		return to_string(msgCodes::C110) +
		"0" +
		to_stringProtocol(questionsNumber,2) +
		to_stringProtocol(qusetionTime,2);

	else if (status == '1')
		return to_string(msgCodes::C110) +
		"1";

	else if (status == '2')
		return to_string(msgCodes::C110) +
		"2";

	return to_string(msgCodes::UNKOWN_ERROR);
}

//112
string Protocol::M112()
{
	return to_string(msgCodes::C112) + "0";
}

//114
string Protocol::M114(string status)
{
	if (status == "success")
		return to_string(msgCodes::C114) +
		"0";

	else if (status == "fail")
		return to_string(msgCodes::C114) +
		"1";

	return to_string(msgCodes::UNKOWN_ERROR);
}

//116
string Protocol::M116()
{
	return to_string(msgCodes::C116);
}

//118
string Protocol::M118(Question * q)
{
	string msg("118"+ to_stringProtocol(q->getQuestion().length(),3) + q->getQuestion());
	string* ans = q->getAnswers();
	for (int i = 0; i < 4; i++)
	{
		msg += to_stringProtocol(ans[i].length(),3) + ans[i];
	}
	return msg;
}

//120
string Protocol::M120(bool ansStatus)
{
	string msg("120");
	if (ansStatus)
	{
		return msg += "1";
	}
	return msg += "0";
}

//121
string Protocol::M121(map<string, int> results)
{
	string msg("121" + to_string(results.size()));
	map<string, int>::iterator it = results.begin();
	while (it != results.end())
	{
		msg += to_stringProtocol(it->first.length(),2) + it->first + to_stringProtocol(it->second,2);
		it++;
	}
	return msg;
}

//124
string Protocol::M124(vector<string> bestScoreList)
{
	string toReturn(to_string(msgCodes::C124));
	//1st = 0,1
	//2nd = 2,3
	//3rd = 4,5
	toReturn += to_stringProtocol(bestScoreList[0].length(),2) + bestScoreList[0] +
		to_stringProtocol(std::stoi(bestScoreList[1]),6) +
		to_stringProtocol(bestScoreList[2].length(),2) + bestScoreList[2] +
		to_stringProtocol(std::stoi(bestScoreList[3]), 6) +
		to_stringProtocol(bestScoreList[4].length(),2) + bestScoreList[4] +
		to_stringProtocol(std::stoi(bestScoreList[5]), 6);
	return toReturn;
}

//126
string Protocol::M126(vector<string> personalStatus)
{
	string toReturn(to_string(msgCodes::C126));
	toReturn += to_stringProtocol(std::stoi(personalStatus[0]),4) +
		to_stringProtocol(std::stoi(personalStatus[1]),6) +
		to_stringProtocol(std::stoi(personalStatus[2]),6) +
		to_stringProtocol(std::stoi(personalStatus[3]),4);
	return toReturn;
}

string Protocol::to_stringProtocol(int num, int bytesNum)
{
	string toReturn(to_string(num));
	int size = bytesNum - toReturn.length();
	for (int i = 0; i < size; i++)
	{
		toReturn = "0" + toReturn;
	}
	return toReturn;
}
