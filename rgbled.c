#include "rgbled.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>

#define RGBLED_DEV  "/dev/rgbled"

int rgbled_fd = -1;

int main(int argc, char *argv[])
{
	if (argc < 4 || argc > 4)
	{
		printf("Usage: ./led <red> <green> <blue>\n");
		return -1;
	}
	
	rgbled_fd = open(RGBLED_DEV, O_RDWR, S_IRUSR | S_IWUSR);
	
	unsigned int color = 0x00;
	unsigned char red = 0x00;
	unsigned char green = 0x00;
	unsigned char blue = 0x00;
	
	red = atoi(argv[1]);
	green = atoi(argv[2]);
	blue = atoi(argv[3]);
	
	printf("Red:%2x\tGreen:%2x\tBlue:%2x\n", red, green, blue);
    struct ledcfg cfg;
	color = RGB2LONG(red, green, blue);
    
    ioctl(rgbled_fd, LED_GET_CFG, &cfg);
    cfg.r = L2RED(color);
    cfg.g = L2GREEN(color);
    cfg.b = L2BLUE(color);
	cfg.LCFG.lcfg.MD = 0;

    ioctl(rgbled_fd, LED_SET_WORK, &cfg);
    
	close(rgbled_fd);
}
