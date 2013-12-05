/* ###################################################################
 **     Filename    : ProcessorExpert.c
 **     Project     : ProcessorExpert
 **     Processor   : MK60DN512VLQ10
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2013-11-18, 09:55, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file ProcessorExpert.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */         
/*!
 **  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
 **  @{
 */         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "FRTOS1.h"
#include "UTIL1.h"
#include "CsIO1.h"
#include "IO1.h"
#include "PDB0.h"
#include "ADC0.h"
#include "SPI2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "arm_cm4.h"
#include "Initialize.h"
#include "spiDriver.h"
#include "ATSTask.h"



/* User includes (#include below this line is not maintained by Processor Expert) */
static portTASK_FUNCTION(Task1, pvParameters) 
{
	(void)pvParameters; /* ignore unused parameter */
	int spiFlag = 0;
	uint8_t txBuffer[5];
	uint8_t rxBuffer[5];
	
	YellowLEDInit();
//	PerformanceGPIOInit();
//	ADC0Init();
	ADC0_Init();
	PDB0Init();
//	SPI2_Init();
//	Spi1MasterInit(SPI2_BASE_PTR,BAUDRATE_500KHZ);
	
//	PDB0_Init();
	hal_spi_init();
	
	hal_spi_transfe_start();
	txBuffer[0] =  hal_spi_transfer_one_byte(0x9F,0);
	txBuffer[1] =  hal_spi_transfer_one_byte(0x0,0);
	txBuffer[2] =  hal_spi_transfer_one_byte(0x0,0);
	txBuffer[3] =  hal_spi_transfer_one_byte(0x0,0);
	txBuffer[4] =  hal_spi_transfer_one_byte(0x0,1);
	hal_spi_transfe_stop();
	printf("%x %x %x %x %x\n",txBuffer[1],txBuffer[2],txBuffer[3],txBuffer[4]);
	
	
	// Enable the ADC and PDB interrupts in NVIC
	set_irq_priority (INT_ADC0-16, 2);
	enable_irq(INT_ADC0-16) ;   // ready for this interrupt.
	set_irq_priority (INT_PDB0-16, 2);
	enable_irq(INT_PDB0-16) ;    // ready for this interrupt.

//	set_irq_priority (INT_SPI2-16, 2);
//	enable_irq(INT_SPI2-16) ;    // ready for this interrupt.

	
//	set_irq_priority (INT_SWI-16, 3);
//	enable_irq(INT_SWI-16);

	EnableInterrupts;
//	NVICSTIR = (INT_SWI-16);

	// Start triggering from PDB peripheral  
	PDB0_SC |= PDB_SC_SWTRIG_MASK;  
	
	for(;;) 
	{
		//		GreenLED_Neg();
		NegYellowLED();
		if(spiFlag)
		{
			spiFlag = 0;
			txBuffer[0] = 0x9f;
			Spi2MasterTx(txBuffer,rxBuffer,4);
		}
		FRTOS1_vTaskDelay(100/portTICK_RATE_MS); /* wait for 100 ms */
	} /* for */
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	size_t heapSize=1;

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	(void)FRTOS1_xTaskCreate(Task1, (signed portCHAR *)"Task1", configMINIMAL_STACK_SIZE*3, NULL, tskIDLE_PRIORITY, NULL);
	heapSize = xPortGetFreeHeapSize();
	printf("starting my ADC application %d\n",heapSize);
	FRTOS1_vTaskStartScheduler();

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.2 [05.07]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
