using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoProcessing
{   
    public class DataHandler
    {
        public List<Vector3> Positions;
        public List<Vector3> Rotations;
        StringBuilder sb;        

        static List<string> blocked = new List<string>(){
            "CALIBRATION", "Gyro", "Accel", "Mag"
        };
        private float SamplePeriod = 0.05f;
        private float[] weights = new float[] { .5f,.5f };
        //new float[] { 41f/840f, 216f/840f, 27f/840f, 272f/840f, 27f/840f, 216f/840f, 41f/840f };

        public DataHandler()
        {
            Positions = new List<Vector3>();
            Rotations = new List<Vector3>();
            sb = new StringBuilder();
        }

        public static List<Vector3> Alphafilter(List<Vector3> input, float alpha)
        {
            var output = new List<Vector3>() { new Vector3(0,0,0) };

            for (int i = 1; i < input.Count; i++)
            {
                output.Add(ApplyAlpha(input[i], input[i-1], alpha));
            }
            output.RemoveAt(0);
            return output;
        }

        private static Vector3 ApplyAlpha(Vector3 input, Vector3 previous, float alpha)
        {
            return (previous * (1 - alpha) + input * alpha);
        }

        public List<Vector3> FilterAcc(float alpha)
        {
            return Alphafilter(Positions, alpha);
        }

        public List<Vector3> Integrate(List<Vector3> input)
        {
            var output = new List<Vector3>() {new Vector3(0,0,0)};

            for(int i = weights.Length - 1; i < input.Count; i++){
            /*    var value = Vector3.Zero();
                for (int j = 0; j < weights.Length; j++)
                {
                    value += input[i + j - weights.Length] * weights[j];
                }               
                output.Add(value * weights.Length * SamplePeriod);
             */
                output.Add((weights[0] * input[i - 1] + weights[1] * input[i]) * SamplePeriod + output[i-1]);
            }         
            
            return output;
        }

        internal void AddData(string data){
            sb.Append(data);
            if (data.EndsWith("\n"))
            {
                if (blocked.Any(sb.ToString().Contains)) { sb.Clear(); return; }

                var coordinates = sb.ToString().Replace(Environment.NewLine, "").Trim().Split(',');
                sb.Clear();

                AddVectors(coordinates);
            }
        }

        internal void AddVectors(string[] coordinates)
        {
           Rotations.Add(new Vector3(coordinates[0], coordinates[1], coordinates[2]));
           Positions.Add(new Vector3(coordinates[3], coordinates[4], coordinates[5]));
        }       
    }
}
