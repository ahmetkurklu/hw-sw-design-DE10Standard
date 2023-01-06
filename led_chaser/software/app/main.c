#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "alt_types.h"
#include "io.h"
#include "unistd.h"

//Initialisation fonction handler interrupt
static void key_interrupt(void *Context);
//Variable pour le temps d'att afin de gere la vitesse de led_chaser
int time = 400000;
//Variable pour recupere le bouton presser
int key;


int main(){
	// Variable pour debug
	int mask;
	int addr = 0x01;
	
	alt_printf("In main start\n");
	
	
	mask = IORD_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE);
	alt_printf("MASK = %x\n",mask);
	
	// applique un mask 0b1111 afin d'activer les boutons
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE,0xf);
	mask = IORD_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE);
	alt_printf("MASK = %x\n",mask);
	
	// active la detection des boutons
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE,0xf);
	
	//Création de l'interruption
	if(alt_ic_isr_register(PIO_1_IRQ_INTERRUPT_CONTROLLER_ID,PIO_1_IRQ,key_interrupt,NULL,NULL) != 0){
		alt_printf("Erreur creation interruption\n");
	}
	
	//Led chaser
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
	// On vérifier le bouton et on modifier la valeur du temps
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
	//Reset la detection des boutons
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE,0xf);
}
