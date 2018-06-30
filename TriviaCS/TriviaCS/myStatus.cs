using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TriviaCS
{
    public partial class myStatus : Form
    {
        public myStatus()
        {
            InitializeComponent();

            byte[] buffer = new ASCIIEncoding().GetBytes(ClientCodes.PersonalStatus);
            Program.sock.Write(buffer, 0, ClientCodes.PersonalStatus.Length);

            byte[] buffer2 = new byte[4096];
            int bytesRead = Program.sock.Read(buffer2, 0, 4096);

            string input = new ASCIIEncoding().GetString(buffer2);

            string temp = input;
            temp = temp.Substring(3); // Skipping the Message Code.

            string[] _Values = new string[4];
            _Values[0] = temp.Substring(0, 4); // Number of Games Played
            temp = temp.Substring(4);

            _Values[1] = temp.Substring(0, 6); // Number of Correct Answers
            temp = temp.Substring(6);

            _Values[2] = temp.Substring(0, 6); // Number of Wrong Answers
            temp = temp.Substring(6);

            _Values[3] = temp; // Average Time for answer

            NumberofGames.Text = "Number of Games Played: " + Convert.ToInt16(_Values[0]).ToString();
            NumberofCorrectAnswers.Text = "Number of Correct Answers: " + Convert.ToInt16(_Values[1]).ToString();
            NumberofWrongAnswers.Text = "Number of Wrong Answers: " + Convert.ToInt16(_Values[2]).ToString();
            AverageAnswerTime.Text = "Average Answer Time: " + Convert.ToDouble(_Values[3]).ToString();
        }

        private void back_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }
    }
}
