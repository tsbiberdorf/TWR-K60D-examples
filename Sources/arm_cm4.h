/*
 * v4.01 unverified/k60_freertos_gcc-cw/arm_cm4.h
 * September 4, 2013
 * Distributed per InterNiche ref US3313-1
 */
/*
 * File:		arm_cm4.h
 * Purpose:		Definitions common to all ARM Cortex M4 processors
 *
 * Notes:
 */

#ifndef _CPU_ARM_CM4_H
#define _CPU_ARM_CM4_H

#include "common.h"

/*ARM Cortex M4 implementation for interrupt priority shift*/
#define ARM_INTERRUPT_LEVEL_BITS          4

/***********************************************************************/
// function prototypes for arm_cm4.c
void stop (void);
void wait (void);
void write_vtor (int);
void enable_irq (int);
void disable_irq (int);
void set_irq_priority (int, int);

/***********************************************************************/
  /*!< Macro to enable all interrupts. */
#define EnableInterrupts asm(" CPSIE i");

  /*!< Macro to disable all interrupts. */
#define DisableInterrupts asm(" CPSID i");
/***********************************************************************/


/*
 * Misc. Defines
 */
#ifdef	FALSE
#undef	FALSE
#endif
#define FALSE	(0)

#ifdef	TRUE
#undef	TRUE
#endif
#define	TRUE	(1)

#ifdef	NULL
#undef	NULL
#endif
#define NULL	(0)

#ifdef  ON
#undef  ON
#endif
#define ON      (1)

#ifdef  OFF
#undef  OFF
#endif
#define OFF     (0)

/***********************************************************************/
/*
 * The basic data types
 */
typedef unsigned char		uint8;  /*  8 bits */
typedef unsigned short int	uint16; /* 16 bits */
typedef unsigned long int	uint32; /* 32 bits */

//typedef char			    int8;   /*  8 bits */
typedef short int	        int16;  /* 16 bits */
//typedef int		            int32;  /* 32 bits */

//typedef volatile int8		vint8;  /*  8 bits */
typedef volatile int16		vint16; /* 16 bits */
//typedef volatile int32		vint32; /* 32 bits */

typedef volatile uint8		vuint8;  /*  8 bits */
typedef volatile uint16		vuint16; /* 16 bits */
typedef volatile uint32		vuint32; /* 32 bits */

// function prototype for main function
int main(void);

/***********************************************************************/
#endif	/* _CPU_ARM_CM4_H */
