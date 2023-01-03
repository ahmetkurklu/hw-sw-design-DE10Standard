#include "system.h"
#include "altera_avalon_pio_regs.h"

int main(){
	
	int i = 0;
	int addr = 0x01;
	
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,0x01);
	usleep(400000);
	while(1){
		while(addr != 0x80){
			addr = addr<<1;
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,addr);
			usleep(400000);
		}
		while(addr != 0x01){
			addr = addr>>1;
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,addr);
			usleep(400000);
		}
	}
}