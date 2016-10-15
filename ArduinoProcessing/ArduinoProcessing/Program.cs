using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Threading;
using System.Linq;

namespace ArduinoProcessing
{
    class Program
    {
        static void Main(string[] args)
        {
            //CSVHandler.Read("../../../../movement1.csv");
            SerialHandler handler = new SerialHandler();
        }
    }
}