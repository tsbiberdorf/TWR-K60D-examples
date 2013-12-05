/*
 * Initialize.h
 *
 *  Created on: Nov 12, 2013
 *      Author: tsbiberdorf
 */

#ifndef INITIALIZE_H_
#define INITIALIZE_H_

////#include "adcTask.h"
//#define EnableInterrupts asm(" CPSIE i");
//  /*!< Macro to disable all interrupts. */
//#define DisableInterrupts asm(" CPSID i");

void PDB0Init(void);
void ADC0Init(void);
void YellowLEDInit();
void SetYellowLED();
void ClrYellowLED();
void NegYellowLED();

void PerformanceGPIOInit();
void SetPTD12();
void ClrPTD12();
void NegPTD12();

void SetPTD13();
void ClrPTD13();
void NegPTD13();

void SetPTD14();
void ClrPTD14();
void NegPTD14();

void SetPTD15();
void ClrPTD15();
void NegPTD15();

void Spi2MasterTx(uint8_t *tx_buff_ptr,uint8_t *rx_buff_ptr,uint8_t tx_count);

#endif /* INITIALIZE_H_ */
