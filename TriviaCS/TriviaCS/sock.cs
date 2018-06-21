using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace TriviaCS
{
    class sock
    {
        public static TcpClient client = new TcpClient();

        IPEndPoint serverEndPoint = new 
        IPEndPoint(IPAddress.Parse("127.0.0.1"), 1226);

    }
}
