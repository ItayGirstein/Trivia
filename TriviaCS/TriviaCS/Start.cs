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
    public partial class Start : Form
    {
        public Start()
        {
            InitializeComponent();
            try
            {
                TcpClient client = new TcpClient();
                IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8820);
                client.Connect(serverEndPoint);

                Program.sock = client.GetStream();

                this.Hide();
                Form1 f = new Form1();
                f.ShowDialog();
                this.Close();
            }
            catch (Exception)
            {

            }

        }

        private void close_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void ok_Click(object sender, EventArgs e)
        {
            Hide();
            Start reopen = new Start();
            reopen.Show();
            Dispose();
        }
    }
}
