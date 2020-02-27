using BindingsKernel;
using CelesteEditor.Data;
using CelesteEditor.Editors;
using CelesteEditor.ViewModels;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Editors
{
    public class LuaShellViewModel : EditorViewModel
    {
        #region Properties and Fields
        
        public string Input { get; set; }

        private string output = "";
        public string Output
        {
            get { return output; }
            set
            {
                output = value;
                NotifyOnPropertyChanged(nameof(Output));
            }
        }

        private Socket socket = new Socket(SocketType.Stream, ProtocolType.Tcp);

        #endregion

        public LuaShellViewModel(object targetObject) :
            base(targetObject)
        {
            TryConnect();
        }

        #region Communication Functions

        private void TryConnect()
        {
            if (!socket.Connected)
            {
                SocketAsyncEventArgs eventArgs = new SocketAsyncEventArgs();
                eventArgs.RemoteEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 27015);
                eventArgs.Completed += (o, e) => { TryConnect(); };
                socket.ConnectAsync(eventArgs);
            }
        }

        public void Send()
        {
            byte[] bytes = Encoding.ASCII.GetBytes(Input);
            int sent = socket.Send(bytes);

            SocketAsyncEventArgs eventArgs = new SocketAsyncEventArgs();
            eventArgs.SetBuffer(new byte[1024], 0, 1024);
            eventArgs.Completed += DataReceived;
            socket.ReceiveAsync(eventArgs);
        }

        private void DataReceived(object sender, SocketAsyncEventArgs e)
        {
            StringBuilder builder = new StringBuilder(256);

            int total = e.BytesTransferred;

            while (total > 0)
            {
                int thisChunk = Math.Min(total, e.Buffer.Length);

                // Translate data bytes to a ASCII string.
                builder.Append(Encoding.ASCII.GetString(e.Buffer, 0, thisChunk));

                total -= thisChunk;
            }

            Output = builder.ToString();
        }

        #endregion
    }
}
