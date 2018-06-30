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


namespace TriviaCS
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            TcpClient client = new TcpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8820);
            client.Connect(serverEndPoint);

            Program.sock = client.GetStream();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string _username, _password;

            _username = username.Text;
            _password = password.Text;

            string msg = ClientCodes.SignIn + _username.Length.ToString().PadLeft(2, '0') + _username +
                _password.Length.ToString().PadLeft(2, '0') + _password;

            byte[] buffer = new ASCIIEncoding().GetBytes(msg);
            Program.sock.Write(buffer, 0, msg.Length);
            byte[] buffer2 = new byte[4096];
            int bytesRead = Program.sock.Read(buffer2, 0, 4096);

            string input = new ASCIIEncoding().GetString(buffer2);
            int codeNum = Int32.Parse(input);

            switch (codeNum)
            {
                case ServerCodes.SignInSuccess: // did it
                    Program._username = _username;

                    ErrorBox.Text = _username;
                    ErrorBox.ForeColor = Color.Black;

                    label2.Visible = false;
                    label2.Enabled = false;
                    label3.Visible = false;
                    label3.Enabled = false;
                    username.Visible = false;
                    username.Enabled = false;
                    password.Visible = false;
                    password.Enabled = false;
                    SignUp.Visible = false;
                    SignUp.Enabled = false;

                    signOut.Visible = true;
                    signOut.Enabled = true;

                    SignIn.Visible = false;
                    SignIn.Enabled = false;

                    JoinRoom.Enabled = true;
                    CreateRoom.Enabled = true;
                    MyStatus.Enabled = true;
                    BestScores.Enabled = true;
                    break;

                case ServerCodes.SignInWrong: // WD
                    ErrorBox.Text = "Wrong detail.";
                    break;

                case ServerCodes.SignInAlreadyConnected:
                    ErrorBox.Text = "user is already connected.";
                    break;

                case ServerCodes.SignInFail:
                    ErrorBox.Text = "sign in failed";
                    break;

                default:
                    break;

            }
            
        }

        private void Quit_Click(object sender, EventArgs e)
        {
            byte[] buffer = new ASCIIEncoding().GetBytes(ClientCodes.LeaveApp);
            Program.sock.Write(buffer, 0, ClientCodes.LeaveApp.Length);
            this.Close();
        }

        private void SignUp_Click(object sender, EventArgs e)
        {
            SignUp d = new SignUp();

            this.Hide();

            d.ShowDialog();

            this.Show();
        }

        private void signOut_Click(object sender, EventArgs e)
        {
            byte[] buffer = new ASCIIEncoding().GetBytes(ClientCodes.SignOut);
            Program.sock.Write(buffer, 0, ClientCodes.SignOut.Length);

            ErrorBox.Text = "";
            ErrorBox.ForeColor = Color.Red;
            Program._username = null;

            label2.Visible = true;
            label2.Enabled = true;
            label3.Visible = true;
            label3.Enabled = true;
            username.Visible = true;
            username.Enabled = true;
            password.Visible = true;
            password.Enabled = true;
            SignUp.Visible = true;
            SignUp.Enabled = true;

            SignIn.Visible = true;
            SignIn.Enabled = true;

            signOut.Visible = true;
            signOut.Enabled = false;

            JoinRoom.Enabled = false;
            CreateRoom.Enabled = false;
            MyStatus.Enabled = false;
            BestScores.Enabled = false;

            signOut.Visible = false;
        }

        private void MyStatus_Click(object sender, EventArgs e)
        {
            myStatus b = new myStatus();

            this.Hide();

            b.ShowDialog();

            this.Show();

        }

        private void BestScores_Click(object sender, EventArgs e)
        {
            bestScores b = new bestScores();

            this.Hide();

            b.ShowDialog();

            this.Show();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void JoinRoom_Click(object sender, EventArgs e)
        {
            JoinRoom d = new JoinRoom();

            this.Hide();

            d.ShowDialog();

            this.Show();
        }
    }
}
