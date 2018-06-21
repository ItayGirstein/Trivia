#pragma once

#include "Helper.h"

class Room;
class Question;
class User;

enum msgCodes
{

	UNKOWN_ERROR = 0,

	SIGNIN_REQ = 200,
	SIGNOUT_REQ = 201,
	SIGNUP_REQ = 203,
	ROOMS_LIST_REQ = 205,
	USERS_IN_ROOM_REQ = 207,
	JOIN_ROOM_REQ = 209,
	LEAVE_ROOM_REQ = 211,
	CREATE_ROOM_REQ = 213,
	CLOSE_ROOM_REQ = 215,
	START_GAME_REQ = 217,
	SEND_ANSWER = 219,
	LEAVE_GAME = 222,
	BEST_SCORE_REQ = 223,
	PERSONAL_STATUS_REQ = 225,
	RAGE_QUIT = 299,
	
	SIGNIN_RES = 102,
	SIGNUP_RES = 104,
	ROOMS_LIST = 106,
	USERS_IN_ROOM_RES = 108,
	JOIN_ROOM_RES = 110,
	LEAVE_ROOM_RES = 112,
	CREATE_ROOM_RES = 114,
	CLOSE_ROOM_RES = 116,
	SEND_QUESTION = 118,
	ANS_RESPONSE = 120,
	END_GAME = 121,
	BEST_SCORE_RES = 124,
	PERSONAL_STATUS_RES = 126

};
// # == 1byte , ## == 2byte
class Protocol
{
public:																																		//Msg code:

	static string M200(string userName, string password);																		//200
	static string M201();																																//201
	static string M203(string userName, string password, string email);													//203
	static string M205();																																//205
	static string M207(int roomID);																												//207
	static string M209(int roomID);																												//209
	static string M211();																																//211
	static string M213(Room roomToCreate);																								//213
	static string M215();																																//215
	static string M217();																																//217
	static string M219(int ansIndex, int ansTimeSeconds);																		//219
	static string M222();																																//222
	static string M223();																																//223
	static string M225();																																//225
	static string M299();																																//299
	
	static string M102(string status);																											//102
	static string M104(string status);																											//104
	static string M106(map<int, Room*> roomsList);																					//106
	static string M108(vector<User*> usersList);																							//108
	static string M110(char status, int questionsNumber, int qusetionTime);											//110
	static string M112();																																//112
	static string M114(string status);																											//114
	static string M116();																																//116
	static string M118(Question* q);																											//118
	static string M120(bool ansStatus);																										//120
	static string M121(map<string, int> results);																						//121
	static string M124(vector<string> bestScoreList);														//124
	static string M126(vector<string> personalStatus);			//126
};