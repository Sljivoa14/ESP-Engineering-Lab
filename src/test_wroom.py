import serial
import time

wroom = serial.Serial('COM6', 115200, timeout=1)  # Replace 'COM3' with the appropriate port for your system

time.sleep(2)

print("Connected to WROOM!")

wroom.write(b'BACKEND:ONLINE\n')  # Send the message to the WROOM
wroom.write(b'CAMERA:ONLINE\n')  # Send the message to the WROOM

print("Status messages sent!")