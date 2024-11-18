POE-FAN-HAT-D from seengreat:www.seengreat.com
 =======================================
# Instructions
## 1.1、Overview
The POE FAN HAT D is a PoE power supply and cooling solution designed for the Raspberry Pi 3B+/4B. This board supports the IEEE 802.3af/at network standard. It can be used with PoE routers or switches that support the IEEE 802.3af/at network standard, allowing the Raspberry Pi to connect to the network and receive power through a single Ethernet cable. The product also features a 0.87inch OLED display, which can show useful information for users. Additionally, the board is equipped with a high-speed adjustable active cooling fan, providing better heat dissipation. The board is designed based on the Raspberry Pi 40P expansion interface, making it simple and easy to use by plugging directly into the Raspberry Pi's 40PIN expansion interface.<br>
## 1.2Product Parameters
|Dimensions	|65mm (Length) * 56mm (Width)|
|----------------------|------------------------------------|
|Input Voltage	|PoE power input (37V ~ 57V)|
|Output Voltage	|5V and 12v|
|Maximum Output Power	|22.5W (5V/4.5A), can reach up to 5V/4.85A in extreme conditions|
|Network Standard	 |IEEE 802.3af/at PoE|
|Fan Speed (Max)	|9000 RPM|
|Weight	|40g(excluding accessories)|

# Raspberry Pi Example Usage
The example code is divided into two versions: one using the WiringPi library and the other using the LGPIO library. The Bullseye system uses the WiringPi library, while the Bookworm system uses the LGPIO library.<br>
## 2.1、Resource Overview Diagram
Resource overview is as shown in the following diagram:<br>
![image](https://github.com/seengreat/POE-FAN-HAT-D/blob/main/08.jpg)<br>
Figure 2-1: Resource Overview Diagram of POE FAN HAT D<br>
① 0.87inch OLED display<br>
② 3007 active cooling fan<br>
③ 5V power indicator LED<br>
④ 12V output pin header<br>
⑤ Raspberry Pi 40-Pin expansion pin header<br>
⑥ Raspberry Pi 4B/3B+ PoE power input header<br>
⑦ Speed-adjustable fan driver pin selection header<br>
## 2.2、Instructions
The product installation wiring diagram is shown in Figure 2-2. The PoE switch/router needs to support the IEEE 802.3af/at network standard. Then, correctly insert the product into the Raspberry Pi 3B+/4B and connect it with an 8-pin Ethernet cable. <br>                    
![image](https://github.com/seengreat/POE-FAN-HAT-D/blob/main/08.jpg)<br>
Figure 2-2: Product Wiring Diagram<br>
## 2.3、Python Libraries Installation
The example program uses the Python 3 environment. To run the Python example program, you need to install smbus:<br>
```sudo apt-get install -y python-smbus```
## 2.4、WiringPi Library Installation
```sudo apt-get install wiringpi```

```wget https://project-downloads.drogon.net/wiringpi-latest.deb #```<br>
Download the WiringPi package:<br>
```sudo dpkg -i wiringpi-latest.deb```<br>
```gpio -v #```<br>
If version 2.52 appears, it indicates that the installation was successful. <br>
#For the Bullseye branch system, use the following commands:<br>
```git clone https://github.com/WiringPi/WiringPi```<br>
```cd WiringPi```<br>
```. /build``` <br>
```gpio -v ```#<br>
# Running gpio -v will display version 2.70. If not, it means the installation failed.<br>
If the error "ImportError: No module named 'wiringpi'" appears when running the Python version of the sample program, execute the following command:<br>
For Python2.x <br>
```pip install wiringpi```<br>
For Python3.x <br>
```pip3 install wiringpi```<br>
Note: If the installation fails, you can try the following compilation installation:<br>
```git clone --recursive https://github.com/WiringPi/WiringPi-Python.git```<br>
Note: The `--recursive` option can automatically fetch submodules; otherwise, you will need to download them manually.  <br>
Enter the newly downloaded WiringPi-Python folder and input the following commands to compile and install:<br>
For Python2.x <br>
```sudo python setup.py install```<br>
For Python3.x <br>
```sudo python3 setup.py install```<br>
If the following error occurs:<br>
Error: Building this module requires either that swig is installed<br>
(e.g.,'sudo apt install swig')or that wiringpi wrap.c from the<br>
source distribution(on pypi) is available.<br>
At this point, enter the command `sudo apt install swig` to install SWIG. After completion, then execute `sudo python3 setup.py install` to compile and install. If similar information appears as shown below, it indicates a successful installation.<br>
ges<br>
Adding wiringpi 2.60.0 to easy-install.pth file<br>
Installed /usr/local/lib/python3.7/dist-packages/wiringpi-2.60.0-py3.7-linux-armv7<br>
Processing dependencies for wiringpi==2.60.0<br>
Finished processing dependencies for wiringpi==2.60.0<br>

## 2.5、lgpio library installation
The C language version of the example program uses the lgpio library.<br>
Raspberry Pi lgpio library installation:<br>
```wget https://github.com/joan2937/lg/archive/master.zip```<br>
```unzip master.zip```<br>
```cd lg-master```<br>
```make```<br>
```sudo make install```<br>
## 2.6、Configure the I2C interface<br>
```sudo raspi-config```<br>
Enable the I2C interface:<br>
Interfacing Options -> I2C -> Yes <br>
Install the i2c-tools to confirm.<br>
```sudo apt-get install i2c-tools```<br>
Check the connected I2C devices:<br>
```i2cdetect -y 1```<br>
If you see the address, it indicates that the board's OLED screen is successfully connected to the Raspberry Pi, with the default address being 0x3c.<br>
## 2.7、Run the example<br>
1）Properly install the POE FAN HAT D onto the Raspberry Pi 3B+/4B and power on the Raspberry Pi.<br>
2）Download the example program from the Resources section at the bottom of the product's WIKI page to the Raspberry Pi.<br>
3）Run the Python program:<br>
Navigate to the poe-fan-hat-d/wiringpi/python/ or poe-fan-hat-d/lgpio/python/ folder and run the program:<br>

```sudo python3 main.py```<br>
After running the program, the OLED screen on the board will display the Raspberry Pi's IP address (for example, 192.168.1.22 as shown in the image) and the real-time CPU temperature (for example, 37.9℃ as shown in the image)<br>
4）Run the C program:<br>
Navigate to the poe-fan-hat-d/wiringpi/c/ or poe-fan-hat-d/lgpio/c/ folder and execute the following command:<br>
```sudo make clean```
```sudo make```
```sudo ./main```
5）Temperature Control Test<br>
Open a new terminal window and then install stress using the following command:<br>
```sudo apt install stress```<br>
 Run the test command:<br>
```stress -c 4```<br>
At this point, the CPU temperature will gradually rise; the higher the CPU temperature, the faster the onboard fan will spin.<br>
## 2.8、Auto-Startup Test<br>
Using systemd (taking the lgpio library as an example):<br>
Create a .service file on the Raspberry Pi, such as poe-fan-hat-d.service, with the following content (the path for the main.py file is /home/pi/poe-fan-hat-d):<br>
```[Unit]```<br>
```Description=poe-fan-hat-d service```<br>
```After=network.target```<br>

```[Service]```<br>
```Restart=always```<br>
```RestartSec=5```<br>
```Type=simple```<br>
```ExecStart=/usr/bin/python3 -u /home/pi/poe-fan-hat-d/lgpio/python/main.py```<br>
```User=pi```

```[Install]```
```WantedBy=multi-user.target```<br>
Save and exit, then copy the file to the /etc/systemd/system directory:<br>
```sudo cp poe-fan-hat-d.service /etc/systemd/system/  ```<br>                         
Reload all services:<br>
```sudo systemctl daemon-reload ```        <br>                                   
Enable the task to run automatically on startup:<br>
```sudo systemctl enable poe-fan-hat-d.service```     <br>                            
Start the task immediately:<br>
```sudo systemctl start poe-fan-hat-d.service``` <br>                                   
Check the task's running status; under normal circumstances, the OLED display will show the IP address and CPU temperature in real time.<br>
Restart the Raspberry Pi and observe whether the OLED screen displays the IP address and CPU temperature correctly.
If you are using the C language example program, change the line:<br>
“ExecStart=/usr/bin/python3 -u /home/pi/poe-fan-hat-d/lgpio/python/main.py”
to
“ExecStart=/home/pi/poe-fan-hat-d/lgpio/c/main”<br>

__Thank you for choosing the products of Shengui Technology Co.,Ltd. For more details about this product, please visit:
www.seengreat.com__

