import serial
import time
import threading
from datetime import datetime
import logic.choreos

# The following Strings are subject to change.
# Check for the correct string in your system
# settings and/or the arduino IDE

#MAC
BLUETOOTH_MAC = "/dev/tty.Zynchron02-DevB"
CABLE_MAC = "/dev/cu.usbmodem1411"

#WINDOWS
BLUETOOTH_WINDOWS = "COM28"
CABLE_WINDOWS = "COM28"

class SerialHandler(threading.Thread):
    def __init__(self, port, baudrate=9600):
        threading.Thread.__init__(self)
        self.port = port
        self.baudrate = baudrate
        self.commands = []

    def run(self):
        print("Serial Handler activated")
        ser = serial.Serial(
            self.port,
            self.baudrate,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            timeout=1)

        ser.xonxoff = False
        ser.rtscts = False
        ser.dsrdtr = False

        i = 0
        while i < len(self.commands):
            time_before = datetime.now()
            condition = True

            while condition:
                command_string = "(3"+str(self.commands[i][0])+")"
				// To send a string simply write to the serial
				// Don't forget to encode the command or else it will
				// be interpreted as integer
                ser.write(str(command_string+command_string).encode())
                time.sleep(.02)
                time_now = datetime.now()
                condition = (time_now - time_before).total_seconds() <= self.commands[i][1]

            i += 1

        print("Serial Handler Finished")

if __name__ == '__main__':
    serialHandler = SerialHandler(CABLE_MAC)  # For MacOS

    i = 3
    while i:
        print("Start Running in: " + str(i))
        time.sleep(1)
        i -= 1

    serialHandler.commands = logic.choreos.basic_choreo
    serialHandler.start()
    serialHandler.join()