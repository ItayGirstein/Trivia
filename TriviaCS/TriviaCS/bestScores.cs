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
    public partial class bestScores : Form
    {
        public bestScores()
        {
            InitializeComponent();
            InitializeScores();
        }
        public void InitializeScores()
        {
            byte[] buffer = new ASCIIEncoding().GetBytes(ClientCodes.BestScores);
            Program.sock.Write(buffer, 0, ClientCodes.BestScores.Length);

            byte[] buffer2 = new byte[4096];
            int bytesRead = Program.sock.Read(buffer2, 0, 4096);

            string input = new ASCIIEncoding().GetString(buffer2);

            Console.WriteLine(input);

            string temp = input.Replace("\0", String.Empty);
            int Length, i;
            temp = temp.Substring(3); // Skipping the Message code.

            string[] TempValues = new string[6];

            for (i = 0; i < 6 && temp != String.Empty; i += 2)
            {
                Length = Convert.ToInt16(temp.Substring(0, 2));
                temp = temp.Substring(2);

                TempValues[i] = temp.Substring(0, Length); // Username
                temp = temp.Substring(Length);

                TempValues[i + 1] = temp.Substring(0, 6); // Scores
                temp = temp.Substring(6);
            }

            string[] _Values = new string[i];

            for (int j = 0; j < i; j++)
            {
                _Values[j] = TempValues[j];
            }

            switch (_Values.Length)
            {
                case 2:
                    FirstScore.Text = _Values[0] + " - " + Convert.ToInt16(_Values[1]).ToString();
                    SecondScore.Text = null;
                    ThirdScore.Text = null;
                    break;

                case 4:
                    FirstScore.Text = _Values[0] + " - " + Convert.ToInt16(_Values[1]).ToString();
                    SecondScore.Text = _Values[2] + " - " + Convert.ToInt16(_Values[3]).ToString();
                    ThirdScore.Text = null;
                    break;

                case 6:
                    FirstScore.Text = _Values[0] + " - " + Convert.ToInt16(_Values[1]).ToString();
                    SecondScore.Text = _Values[2] + " - " + Convert.ToInt16(_Values[3]).ToString();
                    ThirdScore.Text = _Values[4] + " - " + Convert.ToInt16(_Values[5]).ToString();
                    break;

                default:
                    break;
            }

            //Console.WriteLine(input);
        }
        

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void back_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void bestScores_Load(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
