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
    public partial class JoinRoom : Form
    {
        string[] values = new string[1024];
        int maxRooms;

        public JoinRoom()
        {
            InitializeComponent();

            refresh_function();

        }

        private void rooms_SelectedIndexChanged(object sender, EventArgs e)
        {
            joinButton.Enabled = true;
            roomUsers_Text.Visible = true;
            users.Visible = true;

            users.Items.Clear();

            int i = 0;
            for (i = 0; values[i] != rooms.SelectedItem.ToString(); i++) ;

            string msg = ClientCodes.AllRoomUsers + values[i-1];

            byte[] buffer = new ASCIIEncoding().GetBytes(msg);
            Program.sock.Write(buffer, 0, msg.Length);

            byte[] buffer2 = new byte[4096];
            int bytesRead = Program.sock.Read(buffer2, 0, 4096);

            string input = new ASCIIEncoding().GetString(buffer2); // getting data from server.

            string temp = input;
            temp = temp.Substring(3);

            int numberOfUsers = Convert.ToInt32(temp.Substring(0, 1));
            int nameSize;
            temp = temp.Substring(1);

            for (i = 0; i != numberOfUsers && numberOfUsers != 0; i++)
            {
                nameSize = Convert.ToInt16(temp.Substring(0, 2));
                temp = temp.Substring(2);

                users.Items.Add(temp.Substring(0, nameSize)); // user name
                temp = temp.Substring(nameSize);
            }
        }

        private void Back_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Refresh_Click(object sender, EventArgs e)
        {
            joinButton.Enabled = false;
            roomUsers_Text.Visible = false;
            users.Visible = false;
            refresh_function();
        }



        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {

        }

        private void refresh_function()
        {
            byte[] buffer = new ASCIIEncoding().GetBytes(ClientCodes.AllRoomsList);
            Program.sock.Write(buffer, 0, ClientCodes.AllRoomsList.Length);

            byte[] buffer2 = new byte[4096];
            int bytesRead = Program.sock.Read(buffer2, 0, 4096);

            string input = new ASCIIEncoding().GetString(buffer2); // getting data from server.

            string temp = input;
            int RoomNameSize;
            temp = temp.Substring(3);

            values[0] = temp.Substring(0, 4); // Number of Rooms
            temp = temp.Substring(4);

            maxRooms = Convert.ToInt16(values[0]);

            for (int i = 1; i <= maxRooms * 2 && maxRooms != 0; i += 2)
            {
                values[i] = temp.Substring(0, 4); // Id
                temp = temp.Substring(4);

                RoomNameSize = Convert.ToInt16(temp.Substring(0, 2));
                temp = temp.Substring(2);

                values[i + 1] = temp.Substring(0, RoomNameSize); // Room name
                temp = temp.Substring(RoomNameSize);
            }

            rooms.Items.Clear();

            for (int i = 1; i <= maxRooms + 1 && maxRooms != 0; i += 2)
            {
                rooms.Items.Add(values[i + 1]);
            }
        }
    }
}
