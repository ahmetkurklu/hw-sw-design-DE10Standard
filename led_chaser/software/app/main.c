#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "alt_types.h"
#include "io.h"
#include "unistd.h"




volatile int edge_capture;

static void handle_button_interrupts(void* context){
	volatile int* edge_capture_ptr = (volatile int*) context;
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE);
	alt_printf("Dans interrupt\n");
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE);
}



int main(){
	
	
	
	
	
	
	
	alt_printf("Dans le main\n");
	
	void* edge_capture_ptr = (void*) &edge_capture;
	
	
	//IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE, 1);
	//Reset the edge capture register. 
	//IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0);
	
	if(alt_ic_isr_register(PIO_1_IRQ_INTERRUPT_CONTROLLER_ID, PIO_1_IRQ, handle_button_interrupts, edge_capture_ptr, 0) != 0){
		alt_printf("ERROR \n");
	}
	if(alt_ic_irq_enable(PIO_1_IRQ_INTERRUPT_CONTROLLER_ID,PIO_1_IRQ) != 0){
		alt_printf("interrupt enable error\n");
	}
	if(alt_ic_irq_enabled(PIO_1_IRQ_INTERRUPT_CONTROLLER_ID,PIO_1_IRQ) != 0){
		alt_printf("interrupt enabled\n");
	}
	
	
	alt_printf("fin init\n");	
	while(1){
		
	}
	return 0;
}


/*
int main(){
	
	int addr = 0x01;
	int time = 400000;
	int key;
	alt_printf("Dans le main\n");
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