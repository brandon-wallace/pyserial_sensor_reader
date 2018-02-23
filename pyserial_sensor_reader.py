#!/usr/bin/env python3
"""

This program will request data from an Arduino device's DS18S20 temperature 
sensors at a specified interval. The data is written to a sqlite database.


"""


import serial
import sqlite3
import datetime
import time


# Initiate the serial connection to the Arduino.
try:
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
    # Brief pause to establish connection to port.
    time.sleep(3)
except Exception as e:
    print(e)
    exit(1)


# Connect to database.
conn = sqlite3.connect('temperatures.db')
 
# Create cursor object.
cur = conn.cursor()
 
# Create table for database.
cur.execute('''CREATE TABLE IF NOT EXISTS sensors ( 
        date_time TEXT NOT NULL, 
        sensor1 REAL NOT NULL, 
        sensor2 REAL NOT NULL, 
        sensor3 REAL NOT NULL
        )''')
 
 
def insert_data(date_time, sensor1, sensor2, sensor3):
    '''Insert data into the database.'''
    with conn:
        cur.execute("INSERT INTO sensors VALUES (:date_time, :sensor1, :sensor2, :sensor3)", {'date_time': date_time, 'sensor1': sensor1, 'sensor2': sensor2, 'sensor3': sensor3})
 

def read_sensors():
    '''Send the command to the Arduino to read the sensors.'''
    global sensor1, sensor2, sensor3
    # When the Arduino receives the character 'z' it will read the sensor data.
    ser.write(b'z')
    data = ser.readline().decode('utf-8')
    data = data.split()
    sensor1 = data[0]
    sensor2 = data[1]
    sensor3 = data[2]
    return (sensor1, sensor2, sensor3)


while True:
    # Get the current date and time from the datetime module.
    time_now = datetime.datetime.today()
    date_time = datetime.datetime.strftime(time_now, "%Y-%m-%d %H:%M:%S")
    read_sensors()
    # Save data in a sqlite3 database.
    insert_data(date_time, sensor1, sensor2, sensor3)
    time.sleep(300)

