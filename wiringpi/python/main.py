import os
import sys
import smbus
import time
import socket
from char_data import *
from oled import *
import wiringpi 

#fan control pin is P1(D18),P26(D12),P29(D21)
PIN_FAN = 1 # 

def get_ip():
    s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    s.connect(('8.8.8.8',80))
    ip = s.getsockname()[0]
    s.close()
    return ip
def get_temp():
    with open('/sys/class/thermal/thermal_zone0/temp','rt') as f:
        temp = (int)(f.read())/1000.0
    return temp

if __name__ == '__main__':
    oled = OLED_087()
    oled.init()
    oled.clear()
    
    wiringpi.wiringPiSetup()
    wiringpi.pinMode(PIN_FAN, 1)  # fan pin
    wiringpi.softPwmCreate(PIN_FAN, 0, 100)
    oled.draw_string(0,2,'IP:                ',12,1)
    oled.draw_string(0,16,'Temp:',16,1)
    while True:
        ip_str = get_ip()
        oled.draw_string(24,2,ip_str,12,1)
        temp = get_temp()# read cpu temperature
        print("temp:",temp)
        temp_str = str(((int)(temp*10))/10.0)
        oled.draw_string(40,16,temp_str,16,1)        
        oled.refresh()
        if temp<40.0:
            fan_speed = 40 # set FAN speed to 40%
        elif temp>=40.0 and temp<50.0:
            fan_speed = 50 # set FAN speed to 50%
        elif temp>=50.0 and temp<55.0:
            fan_speed = 75 # set FAN speed to 75%
        elif temp>=55.0 and temp<60.0:
            fan_speed = 90 # set FAN speed to 90%
        elif temp>=60.0:
            fan_speed = 100 # set FAN speed to 100%
        print("speed:",fan_speed,"%")            
        wiringpi.softPwmWrite(PIN_FAN,fan_speed)
        time.sleep(1)















