#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "alt_types.h"
#include "io.h"
#include "unistd.h"


static void key_interrupt(void *Context);




int main(){
	int addr;
	alt_printf("In main start\n");
	
	addr = IORD_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE);
	alt_printf("ADDR = %x\n",addr);
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE,0x1);
	addr = IORD_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE);
	alt_printf("ADDR = %x\n",addr);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE,0x1);
	
	if(alt_ic_isr_register(PIO_1_IRQ_INTERRUPT_CONTROLLER_ID,PIO_1_IRQ,key_interrupt,NULL,NULL) != 0){
		alt_printf("Erreur creation interruption\n");
	}
	
	while(1){
		
	}
}

static void key_interrupt(void *Context){
	alt_printf("INTERRUPT\n");


	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE,0x1);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE);
}
