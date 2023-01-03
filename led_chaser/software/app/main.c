#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"

int main(){
	
	int addr = 0x01;
	int time = 400000;
	int key;
	
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,0x01);
	usleep(time);
	while(1){
		key = IORD_ALTERA_AVALON_PIO_DATA(PIO_1_BASE);
		alt_printf("%x\n",key);
		if(key == 0x0E){
			time = 200000;
		}
		else if(key == 0x0D){
			time = 100000;
		}
		else if(key == 0x0B){
			time = 50000;
		}
		else if(key == 0x07){
			time = 25000;
		}
		else{
			time = 400000;
		}
		
		while(addr != 0x80){
			addr = addr<<1;
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,addr);
			usleep(time);
		}
		while(addr != 0x01){
			addr = addr>>1;
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,addr);
			usleep(time);
		}
	}
}

