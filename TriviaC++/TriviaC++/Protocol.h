#pragma once

#include "Helper.h"

class Room;
class Question;
class User;

//C == code
enum msgCodes
{

	UNKOWN_ERROR = 0,

	C200 = 200,
	C201 = 201,
	C203 = 203,
	C205 = 205,
	C207 = 207,
	C209 = 209,
	C211 = 211,
	C213 = 213,
	C215 = 215,
	C217 = 217,
	C219 = 219,
	C222 = 222,
	C223 = 223,
	C225 = 225,
	C299 = 299,
	
	C102 = 102,
	C104 = 104,
	C106 = 106,
	C108 = 108,
	C110 = 110,
	C112 = 112,
	C114 = 114,
	C116 = 116,
	C118 = 118,
	C120 = 120,
	C121 = 121,
	C124 = 124,
	C126 = 126

};
// # == 1byte , ## == 2byte
class Protocol
{
public:																																		//Msg code:
	//M == msg
	static string M200(string userName, string password);																	//200
	static string M201();																																//201
	static string M203(string userName, string password, string email);											//203
	static string M205();																																//205
	static string M207(int roomID);																												//207
	static string M209(int roomID);																												//209
	static string M211();																																//211
	static string M213(Room roomToCreate);																							//213
	static string M215();																																//215
	static string M217();																																//217
	static string M219(int ansIndex, int ansTimeSeconds);																	//219
	static string M222();																																//222
	static string M223();																																//223
	static string M225();																																//225
	static string M299();																																//299
	
	static string M102(string status);																											//102
	static string M104(string status);																											//104
	static string M106(map<int, Room*> roomsList);																				//106
	static string M108(vector<User*> usersList);																					//108
	static string M110(char status, int questionsNumber, int qusetionTime);									//110
	static string M112();																																//112
	static string M114(string status);																											//114
	static string M116();																																//116
	static string M118(Question* q);																											//118
	static string M120(bool ansStatus);																										//120
	static string M121(map<string, int> results);																						//121
	static string M124(vector<string> bestScoreList);																			//124
	static string M126(vector<string> personalStatus);																			//126

private:
	static string to_stringProtocol(int,int);
};