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
    public partial class CreateRoom : Form
    {
        public CreateRoom()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string _rName, _numberOfP, _numberOfQ, _timeForQ;
            _rName = roomName.Text;
            _numberOfP = numberOfPlayers.Text;
            _numberOfQ = numberOfQ.Text;
            _timeForQ = timeForQ.Text;

            string msg = ClientCodes.CreateRoom
                + (_rName.Length.ToString()).PadLeft(2, '0')
                + _rName
                + _numberOfP
                + _numberOfQ.PadLeft(2, '0')
                + _timeForQ.PadLeft(2, '0');

            byte[] buffer = new ASCIIEncoding().GetBytes(msg);
            Program.sock.Write(buffer, 0, msg.Length);

            byte[] buffer2 = new byte[4096];
            int bytesRead = Program.sock.Read(buffer2, 0, 4096);

            string input = new ASCIIEncoding().GetString(buffer2); // getting data from server.

            if (input.Equals(ServerCodes.CreateRoomSuccess))
            {
                Program._roomName = _rName;
                Program.max_number_players = _numberOfP;
                Program.number_of_questions = _numberOfQ;
                Program.time_per_questions = _timeForQ;
                Lobby l = new Lobby();
                this.Hide();
                l.ShowDialog();
                l.Show();
                //should open wait tab.
            }
            else
            {
                label6.Text = "Error: couldn't create a room.";
            }
        }
    }
}
