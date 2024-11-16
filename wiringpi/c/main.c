#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <softPwm.h>
#include "oled_087.h"
#include "oled_font.h"

//fan control pin is P1(D18) or P26(D12) or P29(D21)
#define PIN_FAN  1

#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define MAX_SIZE  20
char temp_str[20];
char eth0_ip[20],wlan0_ip[20];

float Get_cpu_temp(char *tmp_str)
{
    int i,temp_fd;
    float temp=0.0;
    char buf[MAX_SIZE];
    temp_fd = open(TEMP_PATH, O_RDONLY);
    if(temp_fd<0)
    {
	printf("Failed to open temp path!\n");
    }
    if(read(temp_fd, buf, MAX_SIZE)<0)
    {
	printf("Failed to read temp\n");
    }
    //printf("%s\n",buf);
    //memcpy(tmp_str,buf,20);
    temp = atoi(buf)/1000.0;
    close(temp_fd);
    sprintf(tmp_str,"%.2lf",temp);
    printf("temp:%.2f\n",temp);
    return temp;
}

void Get_IP(char *eth0,char *wlan0)
{
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;
    getifaddrs(&ifAddrStruct);
    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr)
        {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) // check it is IP4
		{
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            //printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
            if(ifa->ifa_name[0] == 'e' && ifa->ifa_name[1] == 't')
			{
				printf("eth0\n");
                strcpy(eth0,addressBuffer);
			}
			if(ifa->ifa_name[0] == 'w' && ifa->ifa_name[1] == 'l')
			{
				strcpy(wlan0,addressBuffer);
				printf("wlan0\n");
			}
        }
        else if (ifa->ifa_addr->sa_family == AF_INET6) // check it is IP6
        {
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            //printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        }
    }
    if (ifAddrStruct!=NULL)
    {
		freeifaddrs(ifAddrStruct);
    }
}

int main(void)
{
    int i,temp_fd;
    float temp=0.0;
    char show_turn=0;
    unsigned int fan_speed = 0; 

    wiringPiSetup(); //init wiringpi lib
    pinMode(PIN_FAN, OUTPUT);  //buzzer 
    softPwmCreate(PIN_FAN, 0, 100); //fan 

    Oled_Init();
    Oled_clear();
    draw_string(0,16,"Temp:",16,1);    

    while(1)
    {
	    //read cpu temperature
	    if(show_turn==0)
	    {
			draw_string(0,2,"Eth0:               ",12,1);
			draw_string(0,16,"Temp:",16,1);
			temp = Get_cpu_temp(temp_str);
			Get_IP(eth0_ip,wlan0_ip);
			draw_string(40,16,temp_str,16,1);
			draw_string(35,2,eth0_ip,12,1);
			Oled_refresh();
		}
	    if(show_turn==1)
	    {
			draw_string(0,2,"Wlan:               ",12,1);
			draw_string(0,16,"Temp:",16,1);
			temp = Get_cpu_temp(temp_str);
			Get_IP(eth0_ip,wlan0_ip);
			draw_string(40,16,temp_str,16,1);
			draw_string(35,2,wlan0_ip,12,1);
			Oled_refresh();
		}
		if(temp<40.0)
		{
			fan_speed = 40;//set FAN speed to 40%
		}
		else if(temp >= 40.0 && temp < 50.0)
		{
			fan_speed = 50;//set FAN speed to 50%
		}
		else if(temp >= 50.0 && temp < 55.0)
		{
			fan_speed = 75; //set FAN speed to 75%
		}
		else if(temp >= 55.0 && temp < 60.0)
		{
			fan_speed = 90;//set FAN speed to 90%
		}
		else if(temp >= 60.0)
		{
			fan_speed = 100;//set FAN speed to 100%
		}
        printf("speed:%d %\n",fan_speed);                      
        softPwmWrite(PIN_FAN,fan_speed);
		if(show_turn==0)show_turn=1;
		else show_turn=0;
		delay(1000);
    } 
}
