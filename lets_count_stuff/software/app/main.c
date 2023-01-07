#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "alt_types.h"
#include "io.h"
#include "unistd.h"



void segment(int addr,int nbr){
	
	switch(nbr){
		case 0: 
			alt_printf("0\n");
			IOWR_ALTERA_AVALON_PIO_DATA(addr,0b1000000);
			break;
		case 1: 
			alt_printf("1\n");
			IOWR_ALTERA_AVALON_PIO_DATA(addr,0b1111001);
			break;
		case 2: 
			alt_printf("1\n");
			IOWR_ALTERA_AVALON_PIO_DATA(addr,0b0100100);
			break;
		case 3: 
			alt_printf("1\n");
			IOWR_ALTERA_AVALON_PIO_DATA(addr,0b0110000);
			break;
		case 4: 
			alt_printf("1\n");
			IOWR_ALTERA_AVALON_PIO_DATA(addr,0b0011001);
			break;
		case 5: 
			alt_printf("1\n");
			IOWR_ALTERA_AVALON_PIO_DATA(addr,0b0010010);
			break;
		case 6: 
			alt_printf("1\n");
			IOWR_ALTERA_AVALON_PIO_DATA(addr,0b0000010);
			break;
		case 7: 
			alt_printf("1\n");
			IOWR_ALTERA_AVALON_PIO_DATA(addr,0b1111000);
			break;
		case 8: 
			alt_printf("1\n");
			IOWR_ALTERA_AVALON_PIO_DATA(addr,0b0000000);
			break;
		case 9: 
			alt_printf("1\n");
			IOWR_ALTERA_AVALON_PIO_DATA(addr,0b0010000);
			break;
		default:
			IOWR_ALTERA_AVALON_PIO_DATA(addr,0b1111111);
			break;
	}
	usleep(400000);
}



int main(){
	alt_printf("Dans le main\n");
	
	int i =0;
	while(1){
		for(i=0;i<10;i++){
			segment(PIO_0_BASE,i);
		}
		i = 0;
	}
}
