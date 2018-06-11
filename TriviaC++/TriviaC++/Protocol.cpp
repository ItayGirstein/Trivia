#include "Protocol.h"
#include "Room.h"
#include "Question.h"
#include "User.h"

//200
string Protocol::M200(string userName, string password)
{
	return to_string(msgCodes::SIGNIN_REQ) +
		"##" + userName +
		"##" + password;
}

//201
string Protocol::M201()
{
	return to_string(msgCodes::SIGNOUT_REQ);
}

//203
string Protocol::M203(string userName, string password, string email)
{
	return to_string(msgCodes::SIGNUP_REQ) +
		"##" + userName +
		"##" + password +
		"##" + email;
}

//205
string Protocol::M205()
{
	return to_string(msgCodes::ROOMS_LIST_REQ);
}

//207
string Protocol::M207(int roomID)
{
	return to_string(msgCodes::USERS_IN_ROOM_REQ) +
		"####" + to_string(roomID);
}

//209
string Protocol::M209(int roomID)
{
	return to_string(msgCodes::JOIN_ROOM_REQ) +
		"####" + to_string(roomID);
}

//211
string Protocol::M211()
{
	return to_string(msgCodes::LEAVE_ROOM_REQ);
}

//213
string Protocol::M213(Room roomToCreate)
{
	return to_string(msgCodes::CREATE_ROOM_REQ) +
		"##" + roomToCreate.getName() +
		"#" + to_string(roomToCreate.getUsers().size()) +
		"##" + to_string(roomToCreate.getQuestionsNo()) +
		"##" + to_string(roomToCreate.getQuestionTime());
}

//215
string Protocol::M215()
{
	return to_string(msgCodes::CLOSE_ROOM_REQ);
}

//217
string Protocol::M217()
{
	return to_string(msgCodes::START_GAME_REQ);
}

//219
string Protocol::M219(int ansIndex, int ansTimeSeconds)
{
	return to_string(msgCodes::SEND_ANSWER) +
		"#" + to_string(ansIndex) +
		"##" + to_string(ansTimeSeconds);
}

//222
string Protocol::M222()
{
	return to_string(msgCodes::LEAVE_GAME);
}

//223
string Protocol::M223()
{
	return to_string(msgCodes::BEST_SCORE_REQ);
}

//225
string Protocol::M225()
{
	return to_string(msgCodes::PERSONAL_STATUS_REQ);
}

//299
string Protocol::M299()
{
	return to_string(msgCodes::RAGE_QUIT);
}

//102
string Protocol::M102(string status)
{
	if (status == "success")
		return to_string(msgCodes::SIGNIN_RES) +
		"#" + "0";

	else if (status == "Wrong Details")
		return to_string(msgCodes::SIGNIN_RES) +
		"#" + "1";

	else if (status == "User is already connected")
		return to_string(msgCodes::SIGNIN_RES) +
		"#" + "2";

	return to_string(msgCodes::UNKOWN_ERROR);
}

//104
string Protocol::M104(string status)
{
	if (status == "success")
		return to_string(msgCodes::SIGNUP_RES) +
		"#" + "0";

	else if (status == "Pass illegal")
		return to_string(msgCodes::SIGNUP_RES) +
		"#" + "1";

	else if (status == "Username is already exists")
		return to_string(msgCodes::SIGNUP_RES) +
		"#" + "2";

	else if (status == "Username is illegal")
		return to_string(msgCodes::SIGNUP_RES) +
		"#" + "3";

	else if (status == "Other")
		return to_string(msgCodes::SIGNUP_RES) +
		"#" + "4";

	return to_string(msgCodes::UNKOWN_ERROR);
}

//106
string Protocol::M106(map<int, Room> roomsList)
{
	string toReturn(to_string(msgCodes::ROOMS_LIST) + "####" + to_string(roomsList.size()));
	map<int, Room>::iterator it = roomsList.begin();
	while (it != roomsList.end())
	{
		toReturn += "####" + to_string(it->first) + "##" + it->second.getName();
		it++;
	}
	return toReturn;
}

//108
string Protocol::M108(vector<User*> usersList)
{
	string toReturn(to_string(msgCodes::USERS_IN_ROOM_RES) + to_string(usersList.size()));
	if (usersList[0]->getRoom())
		for (int i = 0; i < usersList.size(); i++)
		{
			toReturn += "##" + usersList[i]->getUsername();
		}

	else
		toReturn += to_string(msgCodes::UNKOWN_ERROR);

	return toReturn;
}

//110
string Protocol::M110(char status, int questionsNumber, int qusetionTime)
{
	if (status == '0')
		return to_string(msgCodes::JOIN_ROOM_RES) +
		"#" + "0" +
		"##" + to_string(questionsNumber) +
		"##" + to_string(qusetionTime);

	else if (status == '1')
		return to_string(msgCodes::JOIN_ROOM_RES) +
		"#" + "1";

	else if (status == '2')
		return to_string(msgCodes::JOIN_ROOM_RES) +
		"#" + "2";

	return to_string(msgCodes::UNKOWN_ERROR);
}

//112
string Protocol::M112()
{
	return to_string(msgCodes::LEAVE_ROOM_RES) + "0";
}

//114
string Protocol::M114(string status)
{
	if (status == "success")
		return to_string(msgCodes::CREATE_ROOM_RES) +
		"#" + "0";

	else if (status == "fail")
		return to_string(msgCodes::CREATE_ROOM_RES) +
		"#" + "1";

	return to_string(msgCodes::UNKOWN_ERROR);
}

//116
string Protocol::M116()
{
	return to_string(msgCodes::CLOSE_ROOM_RES);
}

//118
string Protocol::M118(Question * q)
{
	string msg("118###" + q->getQuestion());
	string* ans = q->getAnswers();
	for (int i = 0; i < 4; i++)
	{
		msg += "###" + ans[i];
	}
	return msg;
}

//120
string Protocol::M120(bool ansStatus)
{
	string msg("120#");
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
		msg += "##" + it->first + "##" + to_string(it->second);
		it++;
	}
	return msg;
}

//124
string Protocol::M124(vector<pair<string, int>> bestScoreList)
{
	return string();
}

//126
string Protocol::M126(int numberOfGames, int rightAnsC, int wrongAnsC, double avgAnsTime)
{
	return string();
}
