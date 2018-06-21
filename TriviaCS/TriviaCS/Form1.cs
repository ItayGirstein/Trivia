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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            label4.Text = "user";

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
        }

        private void Quit_Click(object sender, EventArgs e)
        {
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
            label4.Text = "";

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
            sock.sListener = 
        }
    }
}
