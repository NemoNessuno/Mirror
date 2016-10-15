using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;

namespace ArduinoProcessing
{
    public class Vector3
    {
        public float X { get; private set; }
        public float Y { get; private set; }
        public float Z { get; private set; }

        public Vector3(string x, string y, string z) : this(Parse(x), Parse(y), Parse(z)) { }

        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        private static float Parse(string number)
        {
            return float.Parse(number, CultureInfo.InvariantCulture);
        }

        public static Vector3 operator *(float scalar, Vector3 vector)
        {
            return vector * scalar;
        }

        public static Vector3 operator * (Vector3 vector, float scalar){
            return new Vector3(vector.X * scalar, vector.Y * scalar, vector.Z * scalar);
        }

        public static Vector3 operator +(Vector3 vector, float scalar)
        {
            return new Vector3(vector.X + scalar, vector.Y + scalar, vector.Z + scalar);
        }

        public static Vector3 operator +(Vector3 vector1, Vector3 vector2)
        {
            return new Vector3(vector1.X + vector2.X, vector1.Y + vector2.Y, vector1.Z + vector2.Z);
        }

        /// <summary>
        /// Creates a new vector3 by multiplying the elements of vector1 with vector2.
        /// </summary>
        /// <param name="vector1"></param>
        /// <param name="vector2"></param>
        /// <returns></returns>
        internal static Vector3 Combine(Vector3 vector1, Vector3 vector2)
        {
            return new Vector3(
                vector1.X * vector2.X,
                vector1.Y * vector2.Y,
                vector1.Z * vector2.Z
                );
        }

        internal static Vector3 Zero()
        {
            return new Vector3(0, 0, 0);
        }
    }
}
