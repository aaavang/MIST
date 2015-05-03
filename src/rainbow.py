import serial
import time
from random import randint
from colors import ColorWheel

wheel = ColorWheel()

arduino = serial.Serial('COM3', 57600, timeout=.1)
time.sleep(1)

data = bytes([255,0,0,0,0,1,255,255,255])
arduino.write(data)

adressMode = 0
while True:
    colorHex = str(wheel.next().hex)
    print(colorHex)
    r = int(colorHex[:2],16)
    g = int(colorHex[2:4],16)
    b = int(colorHex[4:],16)
    x = 0
    y = 0
    z = 0
    if(adressMode == 0):
        x = randint(0,4)
        x = 255 if x == 4 else x
        y = randint(0,4)
        y = 255 if y == 4 else y
        z = randint(0,4)
        z = 255 if z == 4 else z
    else:
        x = randint(0,15)
        y = randint(0,15)
        z = randint(0,15)
    data = bytes([255,r,g,b,adressMode,1,x,y,z])
    arduino.write(data)
    time.sleep(.1)
    # arduino.write(data)
    # time.sleep(.25)
    arduino.flushInput()
    arduino.flushOutput()
    