import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

import pyautogui
import sys
import time
from AlphaBotController import AlphaBotController

# Set up the serial connection (The port and baud rate should match your Arduino configuration)
ser = serial.Serial('/dev/cu.usbserial-14420', 9600)  # Replace 'COM3' with your Arduino's serial port

screen_resolution = pyautogui.size()
screen_width = screen_resolution[0]
screen_height = screen_resolution[1]

x_delta = 0.01
y_delta = 0.01

control_type = "alphabot"


controller = AlphaBotController('ise-pi-986291.luddy.indiana.edu', 'pi', 'Betamax321')

controller.connect()

x_command, y_command, click_command = 0, 0, 0
forward_speed = 20
turn_speed = 20

while(True):
    line = ""
    try:
        line = ser.readline().decode('utf-8').strip()  # Read a line from the serial port
    except ValueError:
        pass

    if line:  # If the line is not empty
        try:
            print(line)
            x_command, y_command, click_command = map(float, line.split())  # Split the line into x and y values and convert them to floats
            x_command = int(x_command)
            y_command = int(y_command)
            click_command = int(click_command)

        except ValueError:
            pass  # If the conversion fails, ignore the data point

    print("command: ", x_command, y_command, click_command)

    if control_type == "mouse":
        pyautogui.moveRel(x_command*x_delta*screen_width, -1*y_command*y_delta*screen_height)
        if click_command == 1:
            pyautogui.click()
    elif control_type == "alphabot":
        if x_command > 0:
            controller.command(y_command*forward_speed, y_command*forward_speed + x_command*turn_speed)
        elif x_command < 0:
            controller.command(y_command*forward_speed + -1*x_command*turn_speed, y_command*forward_speed)
        else:
            controller.command(y_command*forward_speed, y_command*forward_speed)
            
        # wait here
        time.sleep(.3)
        
        