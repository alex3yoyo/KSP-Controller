#!/usr/bin/env python

##############################################################################
# @file __filename__
# @version 1.0
# @author alex3yoyo
# @contact alex3yoyo@gmail.com
#
# http://github.com/alex3yoyo/KSP-Controller/
#
# Copyright (c) 2014 alex3yoyo
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
##############################################################################

import serial
import time
import math

from telemachus_plugin import telemachus_plugin
import config


class KSP_Controller():
    def __init__(self):
        """Setup stuff"""
        # Setup serial
        # Configure the serial connections
        # Be sure to change these to suit your particular device(s)
        self.url = config.url()

        self.ser = serial.Serial(
            port=config.arduinoSerialPort(),
            # port='COM3',
            baudrate=9600
            # parity=serial.PARITY_ODD,
            # stopbits=serial.STOPBITS_TWO,
            # bytesize=serial.SEVENBITS
        )
        self.tele = telemachus_plugin()

    def map(self, value, old_min, old_max, new_min, new_max):
        """Re-maps a number from one range to another"""
        # Figure out how 'wide' each range is
        old_span = old_max - old_min
        new_span = new_max - new_min
        # Convert the old range into a 0-1 range (float)
        value_scaled = float(value - old_min) / float(old_span)
        # Convert the 0-1 range into a value in the new range.
        return new_min + (value_scaled * new_span)

    def get_flight_data(self, resources):
        """Gather all of the flight data"""
        data_values = {}
        for i in resources:
            value = self.tele.get_value(i)
            data_values[i] = value
        return data_values

    # Arduino Utilities
    def arduino_format(self, in_list):
        # Takes list of numbers, rounds as ints, returns them as a string
        # Ideally this should be called only immedietely before transmission
        # midlist = []
        for i in in_list:
            value = in_list[i]
            value = map(value=value,
                        old_min=0, old_max=0,
                        new_min=0, new_max=255
                        )
            # midlist.append(int(round(float(i))))
        #midlist.append("\n")
        # outstr = str(midlist)[1:-1]
        # return outstr

    def push_to_arduino(self, inputline):
        # ser.flushOutput()
        # Send data to the Arduino and end w/ a newline
        self.ser.write(inputline + '\n')
        # ser.write("255, 255, 255 \n")
        # time.sleep(.2)

    # def start(self):
    #     # Time to get started...
    #     print("Now starting program.")
    #     print("Warming up the Arduino...")
    #     time.sleep(2)
    #     print("Starting main loop")

    #     # program_runtime = time.time()
    #     arduino_sleep_marker = 0
    #     # button_sleep_marker = 0
    #     memB = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    #     # memBOLD = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    #     n = 0

    #     while 1:
    #         loop_start_time = time.time()

    #         # climbgauge = tele.read_verticalspeed()
    #         # if climbgauge > 0:
    #         #     climbgauge = self.clamp((int(4 * math.sqrt(climbgauge)) + 127), 0, 2255)
    #         # elif climbgauge < 0:
    #         #     climbgauge = self.clamp((0 - int(4 * math.sqrt(
    #         #         abs(climbgauge))) + 127), 0, 255)
    #         # else:
    #         #     climbgauge = 127  # Neutral

    #         memA = (str(int(round(tele.read_missiontime()))).zfill(8)
    #                 + str(int(round(tele.read_asl()))).zfill(8)
    #                 + str(int(round(tele.read_apoapsis()) / 100)).zfill(8)
    #                 + str(int(round((tele.read_periapsis() / 100)))).zfill(8)
    #                 + str(int(round(tele.read_verticalspeed()))).zfill(8)
    #                 + chr(climbgauge) + 'BCDEFGH'
    #                 )

    #         # arduinostring = [255, 255, 255]

    #         if arduino_sleep_marker > 0.2:
    #             try:
    #                 print '.............'
    #                 self.push_to_arduino(memA)
    #                 print memA
    #             finally:
    #                 arduino_sleep_marker = 0

    #         if self.ser.inWaiting > 9:
    #             serCharIn = str(self.ser.read(1))
    #             if serCharIn == '[':
    #                 while n < 10:
    #                     serCharIn = str(self.ser.read(1))
    #                     if serCharIn == ']':
    #                         n = 0
    #                         self.ser.flushInput()
    #                         break
    #                     else:
    #                         memB[n] = serCharIn
    #                     n += 1
    #                     if n == 11:
    #                         self.ser.flushInput()

    #         # if button_sleep_marker > 0.1:
    #         #     buttonHandler()  # Reads memB for which buttons are pressed, then sends
    #         #                      # calls to telemachus as needed.
    #         #     button_sleep_marker = 0

    #         #     print memB
    #         #     print memBOLD
    #         #     memBOLD = list(memB)

    #         time.sleep(0.05)
    #         # This is used mostly to save CPU cycles and battery life of my laptop

    #         loop_end_time = time.time()
    #         loop_time = loop_end_time - loop_start_time
    #         arduino_sleep_marker += loop_time
    #         # button_sleep_marker += loop_time
