#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "alt_types.h"
#include "io.h"
#include "unistd.h"

static void irqhandler(void * context, alt_u32 id){
	alt_printf("Dans main\n");
}

int main(){
	
	alt_printf("Dans main\n");
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_IRQ, 0x0F);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_IRQ, 0x00);
	alt_irq_register(PIO_1_IRQ,NULL, (void*)irqhandler);
	while(1){
		
	}
	
	return 0;
}






/*
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

*/