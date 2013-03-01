	/**
 *****************************************************************************
 **
 **  File        : startup_MKL25Z4.c
 **
 **  Abstract    : This file contains interrupt vector and startup code.
 **
 **  Functions   : Reset_Handler() and Default_Handler()
 **
 **  Target     : Freescale Kinetis microcontrollers
 **
 **  Environment : Atollic TrueSTUDIO(R)
 **
 **  Distribution: The file is distributed “as is,” without any warranty
 **                of any kind.
 **
 **  (c)Copyright Atollic AB.
 **  You may use this file as-is or modify it according to the needs of your
 **  project. Distribution of this file (unmodified or modified) is not
 **  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
 **  rights to distribute the assembled, compiled & linked contents of this
 **  file as part of an application binary file, provided that it is built
 **  using the Atollic TrueSTUDIO(R) toolchain.
 **
 *****************************************************************************
 */

/**
 **===========================================================================
 **  Revisions
 **===========================================================================
 **       Date        Modification
 **       2012-03-20  First issue.
 **===========================================================================
 */

/**
 **===========================================================================
 **  External declarations
 **===========================================================================
 */
extern unsigned long _sdata, _edata, _sidata, _sbss, _ebss;
extern unsigned long _estack;
//extern void __libc_init_array();
extern void SystemInit();
extern void SystemCoreClockUpdate();
extern void main();

/**
 **===========================================================================
 **  Default interrupt handler
 **===========================================================================
 */
void Default_Handler() {
  /* Hang here */
  while (1) {
  }
}

/**
 **===========================================================================
 **  Reset handler
 **===========================================================================
 */
__attribute__((naked)) void Reset_Handler() {
  /* Data and BSS variables */
  unsigned long *srcdata, *dstdata, *sbss;

  /* Set up the stack pointer */
  asm("ldr r0,=_estack\n\t");
  asm("mov sp, r0");

  srcdata = &_sidata;
  dstdata = &_sdata;
  sbss = &_sbss;

  /* Copy data */
  while (dstdata != &_edata) {
    *(dstdata++) = *(srcdata++);
  }

  /* Clear BSS */
  while (sbss != &_ebss) {
    *(sbss++) = '\0';
  }

  /* Run static constructors */
//  __libc_init_array();

  /* Initialize System */
  SystemInit();
  SystemCoreClockUpdate();

  /* Jump to main */
  main();

  /* In case main returns, use default handler */
  Default_Handler();
}

/* Weak definitions of handlers point to Default_Handler if not implemented */
void NMI_Handler() __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler() __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler() __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler() __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler() __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler() __attribute__ ((weak, alias("Default_Handler")));
void DebugMonitor_Handler() __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler() __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler() __attribute__ ((weak, alias("Default_Handler")));

void DMA0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DMA3_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void Reserved20_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void FTFA_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void LVD_LVW_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void LLW_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void I2C0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void SPI0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void UART2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void ADC0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void CMP0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void TPM0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void TPM1_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void TPM2_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void RTC_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void RTC_Seconds_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PIT_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void Reserved39_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void USB0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void DAC0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void TSI0_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void MCG_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void LPTimer_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void Reserved45_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PORTA_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void PORTD_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));



void (* const InterruptVector[])() __attribute__ ((section(".isr_vector"))) = {
		/* Processor exceptions */
		(void(*)(void)) &_estack,
		Reset_Handler,
		NMI_Handler,                 /* NMI Handler                  */
		HardFault_Handler,           /* Hard Fault Handler           */
		MemManage_Handler,           /* MPU Fault Handler            */
		BusFault_Handler,            /* Bus Fault Handler            */
		UsageFault_Handler,          /* Usage Fault Handler          */
		0,                           /* Reserved                     */
		0,                           /* Reserved                     */
		0,                           /* Reserved                     */
		0,                           /* Reserved                     */
		SVC_Handler,                 /* SVCall Handler               */
		DebugMonitor_Handler,        /* Debug Monitor Handler        */
		0,                           /* Reserved                     */
		PendSV_Handler,              /* PendSV Handler               */
		SysTick_Handler,             /* SysTick Handler              */

		/* External Interrupts */
		DMA0_IRQHandler,          /* DMA channel 0 transfer complete interrupt */
		DMA1_IRQHandler,          /* DMA channel 1 transfer complete interrupt */
		DMA2_IRQHandler,          /* DMA channel 2 transfer complete interrupt */
		DMA3_IRQHandler,          /* DMA channel 3 transfer complete interrupt */
		Reserved20_IRQHandler,    /* Reserved interrupt 20 */
		FTFA_IRQHandler,          /* FTFA interrupt */
		LVD_LVW_IRQHandler,       /* Low Voltage Detect, Low Voltage Warning */
		LLW_IRQHandler,           /* Low Leakage Wakeup */
		I2C0_IRQHandler,          /* I2C0 interrupt */
		I2C1_IRQHandler,          /* I2C0 interrupt 25 */
		SPI0_IRQHandler,          /* SPI0 interrupt */
		SPI1_IRQHandler,          /* SPI1 interrupt */
		UART0_IRQHandler,         /* UART0 status/error interrupt */
		UART1_IRQHandler,         /* UART1 status/error interrupt */
		UART2_IRQHandler,         /* UART2 status/error interrupt */
		ADC0_IRQHandler,          /* ADC0 interrupt */
		CMP0_IRQHandler,          /* CMP0 interrupt */
		TPM0_IRQHandler,          /* TPM0 fault, overflow and channels interrupt */
		TPM1_IRQHandler,          /* TPM1 fault, overflow and channels interrupt */
		TPM2_IRQHandler,          /* TPM2 fault, overflow and channels interrupt */
		RTC_IRQHandler,           /* RTC interrupt */
		RTC_Seconds_IRQHandler,   /* RTC seconds interrupt */
		PIT_IRQHandler,           /* PIT timer interrupt */
		Reserved39_IRQHandler,    /* Reserved interrupt 39 */
		USB0_IRQHandler,          /* USB0 interrupt */
		DAC0_IRQHandler,          /* DAC interrupt */
		TSI0_IRQHandler,          /* TSI0 interrupt */
		MCG_IRQHandler,           /* MCG interrupt */
		LPTimer_IRQHandler,       /* LPTimer interrupt */
		Reserved45_IRQHandler,    /* Reserved interrupt 45 */
		PORTA_IRQHandler,         /* Port A interrupt */
		PORTD_IRQHandler,         /* Port D interrupt */
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		Default_Handler,
		(void(*)(void)) 0xFFFFFFFF, /* 0x400 Backdoor Comparison Key */
		(void(*)(void)) 0xFFFFFFFF, /* 0x404 Backdoor Comparison Key */
		(void(*)(void)) 0xFFFFFFFF, /* 0x408 FPROT */
		(void(*)(void)) 0xFFFFFFFE  /* 0x40c FSEC, FOPT, FEPROT, FDPROT */
};
