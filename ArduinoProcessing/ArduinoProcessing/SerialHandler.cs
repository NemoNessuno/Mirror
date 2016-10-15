using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoProcessing
{
    internal class SerialHandler
    {
        DataHandler handler = new DataHandler();

        internal SerialHandler()
        {
            SerialPort port = new SerialPort("COM20", 9600);
            port.Parity = Parity.None;
            port.DataBits = 8;
            port.StopBits = StopBits.One;
            port.RtsEnable = true;
            port.Handshake = Handshake.None;
            port.Open();
            port.DataReceived += port_DataReceived;
            while (true)
            {
                string text = Console.ReadLine();
                port.WriteLine(text);
            }
        }

        void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort port = (SerialPort)sender;
            string data = port.ReadExisting();
            Console.Write(data);
            handler.AddData(data);
        }

    }
}
