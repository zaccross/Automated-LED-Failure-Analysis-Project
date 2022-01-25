# This is the first draft of our device automation code
# The goal is to send commands over the serial pins of the raspberry pi, and recieve data back.

# Imports:
import serial # pyserial package that will do the heavy lifting of machine/serial commands
import time # A way to time the updates of the different components
import numpy
import csv
#import pandas as pd # package for DataFrame object to help with CSV writing

# Setting up our serial object: Port for Pi is ttyS0. Baudrate agreed with arduino code, the rest is default parameters
# Not necessary to worry about unless we want to do higher complexity serial communication later.
# timeout of 1 seconds
ser = serial.Serial(
        port = '/dev/ttyS0',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
        )

# Command flags for Arduinos. Stop is the same across all devices so it has a -1
FLAGS = {0: bytes(b'driver\n'), 1: bytes(b'current\n'), 2:bytes(b'photoOne\n'), 3: bytes(b'photoTwo\n'), -1: bytes(b'stop/n')}
N = 4 # number of arduinos
WAITTIME = 30 # Wait time between checks in seconds
readColumns = ['C0', 'C1', 'C2', 'C3', 'C4','C5', 'PR0', 'PR1', 'PR2', 'PR3', 'PR4', 'PR5', 'TIME', 'MEASURE_NUM']
#READOUT = pd.df(columns=readColumns)

# Tracking values to connect serial out from the arduino to columns:
VALDICT = {"00": 'C0', "10": 'C1', "11": 'C2', "12": 'C3', "13": 'C4', "14": 'C5', "20": 'PR0', "30": 'PR1', "31": 'PR2', "32": 'PR3', "33": 'PR4', "34": 'PR5'}
# Maintaining a mutable version of the data to update as we go
DATADICT = {'C0':[], 'C1':[], 'C2':[], 'C3':[], 'C4':[],'C5':[], 'PR0':[], 'PR1':[], 'PR2':[], 'PR3':[], 'PR4':[], 'PR5':[], 'TIME':[], 'MEASURE_NUM':[]}

# Stick everything inside the main function
def main(filename="/home/pi/test/test.csv"):



    ###########
    # set time to initialize the code to 0 so it starts right away
    old_time = 0
    row_time = 0

    # Keep the script running until something breaks
    while True:

        # Only initialize if it's been 30 seconds or more
        if time.time() >= (old_time+WAITTIME):

            for i in range(30):
                    DATADICT['TIME'].append(row_time)
                    DATADICT['MEASURE_NUM'].append(i)

            # cycle through each arduino
            for i in range(N):

                # command write and flush
                ser.write(FLAGS[i])
                ser.flush()

                # read lines: 1 pin, 30 measurements
                cnt = 0
                while ser.in_waiting > 0:

                    # read in the line as a string
                    line = ser.readline().decode('utf-8').rstrip()

                    # if this is the first of 31, thats the column
                    if cnt == 0:
                        column = line
                        index = str(i)+column
                    else:
                        DATADICT[index].append(line)

                    # increment the counter and reset if all values for a pin have been read
                    cnt +=1
                    if cnt == 31:
                        cnt = 0

                # stop
                ser.write(FLAGS[-1])
                ser.flush()

        # Wrting to a csv file
        with open(filename, 'w',newline='') as csvfile:
            dataWriter = csv.writer(csvfile, delimiter = ',')
            dataWriter.writerow(readColumns)
            for i in range(len(DATADICT["C0"])):
                newRow = []
                for key in DATADICT:
                    newRow.append(DATADICT[key][i])
                dataWriter.writerow(newRow)

        # reset old_time to the new time so the loop waits 30 seconds+
        old_time = time.time()


    print("Error: The while loop was broken")
    return False

filename = input('PLZ ENTR FILLNAME')
if __name__ == '__main__':
    main(filename)
