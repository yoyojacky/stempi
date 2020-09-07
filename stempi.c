#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


int n=0;
/* 该程序主要功能：从树莓派系统获取当前温度信息并通过串口传给单片机 */
int main(void)
{
	while(1){
 int serial_port = open("/dev/ttyAMA0", O_RDWR);

if (serial_port < 0){
	printf("Error $i from open: %s\n", errno, strerror(errno));
 }

struct termios tty;

if(tcgetattr(serial_port, &tty) !=0)
 {
	printf("Error $i from open: %s\n", errno, strerror(errno));
 }
/* Stop bit*/

tty.c_cflag &= ~PARENB; 
tty.c_cflag &= ~CSTOPB; 
tty.c_cflag |= CS8;
tty.c_cflag &= ~CRTSCTS;
tty.c_cflag |= CREAD | CLOCAL;

tty.c_lflag &= ~ICANON;
tty.c_lflag &= ~ECHO;
tty.c_lflag &= ~ECHOE;
tty.c_lflag &= ~ECHONL;
tty.c_lflag &= ~ISIG;

tty.c_iflag &= ~(IXON | IXOFF | IXANY);
tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

tty.c_oflag &= ~OPOST;
tty.c_oflag &= ~ONLCR;

tty.c_cc[VTIME] = 10;
tty.c_cc[VMIN] = 0;

cfsetispeed(&tty, B115200);
cfsetospeed(&tty, B115200);

if (tcsetattr(serial_port, TCSANOW, &tty) !=0){
	printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
}
FILE *fp;
char buff[8];
fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
fgets(buff, 8, (FILE*)fp);
fclose(fp);
// write(serial_port, buff, sizeof(buff));
write(serial_port, buff, 8);
close(serial_port);
printf("temp: %s\t", buff);
printf("Send Temperature %d times\n", n+=1);
sleep(1);
}
return 0;
}
