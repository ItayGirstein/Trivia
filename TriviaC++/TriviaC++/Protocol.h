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
public:																																										//Msg code:

	static string signInRequestMsg(string userName, string password);																					//200
	static string signOutRequestMsg();																																		//201
	static string signUpRequestMsg(string userName, string password, string email);															//203
	static string emptyRoomsListRequestMsg();																															//205
	static string userInRoomRequestMsg(int roomID);																												//207
	static string joinRoomRequestMsg(int roomID);																													//209
	static string leaveRoomRequestMsg();																																	//211
	static string creatRoomRequestMsg(Room roomToCreate);																									//213
	static string closeRoomRequestMsg();																																	//215
	static string startGameRequestMsg();																																	//217
	static string sendAnswerMsg(int ansIndex, int ansTimeSeconds);																						//219
	static string sendLeaveGame();																																				//222
	static string bestScoreRequestMsg();																																	//223
	static string personalStatusRequestMsg();																															//225
	static string sendExit();																																							//299

	static string signInResponseMsg(string status);																													//102
	static string signUpResponseMsg(string status);																													//104
	static string roomsListResponseMsg(map<int, Room> roomsList);																						//106
	static string usersInRoomResponsetMsg(vector<User> usersList);																						//108
	static string joinRoomResponseMsg(char status, int questionsNumber, int qusetionTime);												//110
	static string leaveRoomResponseMsg();																																//112
	static string creatRoomResponseMsg(string status);																											//114
	static string closeRoomResponseMsg();																																//116
	static string sendQuestionMsg(Question* q);																														//118
	static string answerResponseMsg(bool ansStatus);																												//120
	static string endGameMsg(std::map<string, int>);																												//121
	static string bestScoreResponseMsg(vector<std::pair<string, int>> bestScoreList);															//124
	static string personalStatusResponseMsg(int numberOfGames, int rightAnsC, int wrongAnsC, double avgAnsTime);    //126
};