import time
import os
import sys
import socket
from char_data import *
from oled import *
from gpiozero import *

FAN_PIN   = 18 # D12 or D18 or D21 in BCM number

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
def get_hostname():
    hostname = socket.gethostname()
    return hostname

if __name__=='__main__':
    oled = OLED_087()
    oled.init()
    fan = PWMOutputDevice(FAN_PIN,frequency = 100)# buzzer pin
    fan.value = 0.0 
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
            fan_speed = 0.4 # set FAN speed to 40%
        elif temp>=40.0 and temp<50.0:
            fan_speed = 0.5 # set FAN speed to 50%
        elif temp>=50.0 and temp<55.0:
            fan_speed = 0.75 # set FAN speed to 75%
        elif temp>=55.0 and temp<60.0:
            fan_speed = 0.9 # set FAN speed to 90%
        elif temp>=60.0:
            fan_speed = 1 # set FAN speed to 100%
        print("speed:",fan_speed*100,"%")            
        fan.value=fan_speed
        time.sleep(1)
               
        
        
        
        
        