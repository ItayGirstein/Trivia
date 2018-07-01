using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace TriviaCS
{
    static class Program
    {
        public static NetworkStream sock = null;
        public static string _username = null;
        public static string _roomName = null;
        public static string max_number_players = null;
        public static string number_of_questions = null;
        public static string time_per_questions = null;

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Start());
        }
    }
}
