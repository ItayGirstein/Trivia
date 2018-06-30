using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;


namespace TriviaCS
{
    public static class ClientCodes
    {
        public const string SignIn = "200";
        public const string SignOut = "201";
        public const string ForgotPassword = "202";
        public const string SignUp = "203";
        public const string AllRoomsList = "205";
        public const string AllRoomUsers = "207";
        public const string JoinRoom = "209";
        public const string LeaveRoom = "211";
        public const string CreateRoom = "213";
        public const string CloseRoom = "215";
        public const string StartGame = "217";
        public const string Answer = "219";
        public const string LeaveGame = "222";
        public const string BestScores = "223";
        public const string PersonalStatus = "225";
        public const string LeaveApp = "299";
    }

    public static class ServerCodes
    {
        #region SignIn
        public const int SignInSuccess = 1020;
        public const int SignInWrong = 1021;
        public const int SignInAlreadyConnected = 1022;
        public const int SignInFail = 1023;
        #endregion // using Regions to make code more easier to read.
        #region SignUp
        public const int SignUpSuccess = 1040;
        public const int SignUpPassIllegal = 1041;
        public const int SignUpUsernameExists = 1042;
        public const int SignUpUsernameIllegal = 1043;
        public const int SignUpOther = 1044;
        #endregion
        #region JoinRoom
        public const string JoinRoom = "110";
        public const string JoinRoomSuccess = "1100";
        public const string JoinRoomFull = "1101";
        public const string JoinRoomFail = "1102";
        #endregion
        #region CreateRoom
        public const string CreateRoom = "114";
        public const string CreateRoomSuccess = "1140";
        public const string CreateRoomFail = "1141";
        #endregion
        #region else
        public const string AllRooms = "106";
        public const string AllRoomUsers = "108";
        public const string LeaveRoom = "112";
        public const string CloseRoom = "116";
        public const string SendQuestions = "118";
        public const string TrueFalse = "120";
        public const string EndGame = "121";
        public const string BestScores = "124";
        public const string PersonalState = "126";
        #endregion
    }
}
