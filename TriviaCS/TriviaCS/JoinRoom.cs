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

        private void rooms_SelectedIndexChanged(object sender, EventArgs e)
        {
            joinButton.Enabled = true;
            string msg = ClientCodes.AllRoomUsers + ((rooms.SelectedIndex * 2) - 1);

            byte[] buffer = new ASCIIEncoding().GetBytes(msg);
            Program.sock.Write(buffer, 0, msg.Length);

        }

        private void Back_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Refresh_Click(object sender, EventArgs e)
        {

        }



        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {

        }
    }
}
