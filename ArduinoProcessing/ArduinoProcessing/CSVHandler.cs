using CsvHelper;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoProcessing
{
    public class CSVHandler
    {
        public static DataHandler Read(string path){
            var dataHandler = new DataHandler();
            var parser = new CsvParser(new StreamReader(path));
            while (true)
            {
                var row = parser.Read();
                if (row == null)
                {
                    break;
                }
                else
                {
                    dataHandler.AddVectors(row);
                }
            }

            return dataHandler;
        }
    }
}
