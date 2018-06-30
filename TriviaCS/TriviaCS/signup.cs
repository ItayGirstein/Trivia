using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace TriviaCS
{
    public partial class SignUp : Form
    {
        public SignUp()
        {
            InitializeComponent();
        }

        private void SignUp_Load(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void back_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void ok_Click(object sender, EventArgs e)
        {
            string _username, _password, _email;

            _username = username.Text;
            _password = pass.Text;
            _email = mail.Text;

            string msg = ClientCodes.SignUp + _username.Length.ToString().PadLeft(2, '0') + _username +
                _password.Length.ToString().PadLeft(2, '0') + _password +
                _email.Length.ToString().PadLeft(2, '0') + _email;

            byte[] buffer = new ASCIIEncoding().GetBytes(msg);
            Program.sock.Write(buffer, 0, msg.Length);
            byte[] buffer2 = new byte[4096]; 
            int bytesRead = Program.sock.Read(buffer2, 0, 4096);

            string input = new ASCIIEncoding().GetString(buffer2);
            int codeNum = Int32.Parse(input);
            switch (codeNum)
            {
                case ServerCodes.SignUpSuccess: //did it
                    this.Close();
                    break;

                case ServerCodes.SignUpPassIllegal: // pass illigal
                    ErrorBox.Text = "The password is illigal! numbers and caps please.";
                    break;

                case ServerCodes.SignUpUsernameExists: // username takens
                    ErrorBox.Text = "Username is already exists.";
                    break;

                case ServerCodes.SignUpUsernameIllegal: // username illigal
                    ErrorBox.Text = "The username is illigal!";
                    break;

                case ServerCodes.SignUpOther: // other
                    ErrorBox.Text = "idk figure it out";
                    break;

                default:
                    break;

            }

        }

        private void mail_TextChanged(object sender, EventArgs e)
        {

        }

        private void pass_TextChanged(object sender, EventArgs e)
        {

        }

        private void username_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
