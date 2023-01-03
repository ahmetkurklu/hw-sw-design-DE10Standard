#include "system.h"
#include "altera_avalon_pio_regs.h"

int main(){
	
	
	while(1){
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,0x01);
	usleep(400000);
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,0x10);
	usleep(400000);
	}
}