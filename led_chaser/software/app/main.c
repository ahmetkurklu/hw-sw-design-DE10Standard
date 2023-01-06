#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "alt_types.h"
#include "io.h"
#include "unistd.h"


static void key_interrupt(void *Context);
int time = 400000;
int key;


int main(){
	int mask;
	int addr = 0x01;
	
	alt_printf("In main start\n");
	
	mask = IORD_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE);
	alt_printf("MASK = %x\n",mask);
	
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE,0xf);
	mask = IORD_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE);
	alt_printf("MASK = %x\n",mask);
	
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE,0xf);
	
	if(alt_ic_isr_register(PIO_1_IRQ_INTERRUPT_CONTROLLER_ID,PIO_1_IRQ,key_interrupt,NULL,NULL) != 0){
		alt_printf("Erreur creation interruption\n");
	}
	
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,0x01);
	usleep(time);
	while(1){
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

static void key_interrupt(void *Context){
	
	alt_printf("INTERRUPT\n");
	time = time/2;
	
	key = IORD_ALTERA_AVALON_PIO_DATA(PIO_1_BASE);
		alt_printf("%x\n",key);
		switch(key){
			case 0x07:
				time = 500000;
				break;
			case 0x0b:
				time = 200000;
				break;
			case 0x0d:
				time = 100000;
				break;
			case 0x0e:
				time = 20000;
				break;
			default:
				time = 400000;
				break;
		}

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE,0xf);
}
