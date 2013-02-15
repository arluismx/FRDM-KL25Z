/*******************************************************************************
 * \brief		FRDM-KL25Z GPIO functions.
 *
 * \file		gpio.c
 * \version		1.0
 * \date		2013-02-13
 * \author		rct1
 ******************************************************************************/
/*
 * functions global:
 *				GPIO_init
 *				GPIO_bit_set
 *				GPIO_bit_reset
 *				GPIO_port_set
 * functions local:
 *				.
 *
 ******************************************************************************/

/*----- Header-Files -------------------------------------------------------*/
#include <MKL25Z4.H>
#include "gpio.h"

/*----- Macros -------------------------------------------------------------*/
#define FGPIO_TO_PORT(FGPIO)	(						\
		(FGPIO == FPTA) ? PORTA :	/* Port A? */		\
		(FGPIO == FPTB) ? PORTB :	/* Port B? */		\
		(FGPIO == FPTC) ? PORTC :	/* Port C? */		\
		(FGPIO == FPTD) ? PORTD :	/* Port D? */		\
		(FGPIO == FPTE) ? PORTE :	/* Port E? */		\
		((PORT_Type *)0x00000000u))	/* no port is set */

#define PIN_TO_BIT(PIN)		(							\
		(PIN == PIN_0)  ?  0 :	/* Pin  0? */			\
		(PIN == PIN_1)  ?  1 :	/* Pin  1? */			\
		(PIN == PIN_2)  ?  2 :	/* Pin  2? */			\
		(PIN == PIN_3)  ?  3 :	/* Pin  3? */			\
		(PIN == PIN_4)  ?  4 :	/* Pin  4? */			\
		(PIN == PIN_5)  ?  5 :	/* Pin  5? */			\
		(PIN == PIN_6)  ?  6 :	/* Pin  6? */			\
		(PIN == PIN_7)  ?  7 :	/* Pin  7? */			\
		(PIN == PIN_8)  ?  8 :	/* Pin  8? */			\
		(PIN == PIN_9)  ?  9 :	/* Pin  9? */			\
		(PIN == PIN_10) ? 10 :	/* Pin 10? */			\
		(PIN == PIN_11) ? 11 :	/* Pin 11? */			\
		(PIN == PIN_12) ? 12 :	/* Pin 12? */			\
		(PIN == PIN_13) ? 13 :	/* Pin 13? */			\
		(PIN == PIN_14) ? 14 :	/* Pin 14? */			\
		(PIN == PIN_15) ? 15 :	/* Pin 15? */			\
		(PIN == PIN_16) ? 16 :	/* Pin 16? */			\
		(PIN == PIN_17) ? 17 :	/* Pin 17? */			\
		(PIN == PIN_18) ? 18 :	/* Pin 18? */			\
		(PIN == PIN_19) ? 19 :	/* Pin 19? */			\
		(PIN == PIN_20) ? 20 :	/* Pin 20? */			\
		(PIN == PIN_21) ? 21 :	/* Pin 21? */			\
		(PIN == PIN_22) ? 22 :	/* Pin 22? */			\
		(PIN == PIN_23) ? 23 :	/* Pin 23? */			\
		(PIN == PIN_24) ? 24 :	/* Pin 24? */			\
		(PIN == PIN_25) ? 25 :	/* Pin 25? */			\
		(PIN == PIN_26) ? 26 :	/* Pin 26? */			\
		(PIN == PIN_27) ? 27 :	/* Pin 27? */			\
		(PIN == PIN_28) ? 28 :	/* Pin 28? */			\
		(PIN == PIN_29) ? 29 :	/* Pin 29? */			\
		(PIN == PIN_30) ? 30 :	/* Pin 30? */			\
		(PIN == PIN_31) ? 31 :	/* Pin 31? */			\
		-1)						/* no pin is set */

/*----- Data types ---------------------------------------------------------*/
typedef struct _PORT_PIN_t {
	FGPIO_Type *GPIOx;
	unsigned long Pin;
} PORT_PIN_t;

/*----- Function prototypes ------------------------------------------------*/

/*----- Data ---------------------------------------------------------------*/
PORT_PIN_t Onboard_Port_Pin[] = {
		{ FPTB, PIN_18 },		/* RGB LED Red			*/
		{ FPTB, PIN_19 },		/* RGB LED Green		*/
		{ FPTD, PIN_1  },		/* RGB LED Blue			*/
		{ FPTE, PIN_24 },		/* I2C					*/
		{ FPTE, PIN_25 },		/* I2C					*/
		{ FPTA, PIN_14 },		/* Accelerometer INT1	*/
		{ FPTA, PIN_15 },		/* Accelerometer INT1	*/
		{ FPTB, PIN_16 },		/* Touch Slider			*/
		{ FPTB, PIN_17 },		/* Touch Slider			*/
};

PORT_PIN_t HeaderJ1_Port_Pin[] = {
		{ FPTC, PIN_7  },		/* J1 01	*/
		{ FPTA, PIN_1  },		/* J1 02	*/
		{ FPTC, PIN_0  },		/* J1 03	*/
		{ FPTA, PIN_2  },		/* J1 04	*/
		{ FPTC, PIN_3  },		/* J1 05	*/
		{ FPTD, PIN_4  },		/* J1 06	*/
		{ FPTC, PIN_4  },		/* J1 07	*/
		{ FPTA, PIN_12 },		/* J1 08	*/
		{ FPTC, PIN_5  },		/* J1 09	*/
		{ FPTA, PIN_4  },		/* J1 10	*/
		{ FPTC, PIN_6  },		/* J1 11	*/
		{ FPTA, PIN_5  },		/* J1 12	*/
		{ FPTC, PIN_10 },		/* J1 13	*/
		{ FPTC, PIN_8  },		/* J1 14	*/
		{ FPTC, PIN_11 },		/* J1 15	*/
		{ FPTC, PIN_9  },		/* J1 16	*/
};

PORT_PIN_t HeaderJ2_Port_Pin[] = {
		{ FPTC, PIN_12         },		/* J2 01	*/
		{ FPTA, PIN_13         },		/* J2 02	*/
		{ FPTC, PIN_13         },		/* J2 03	*/
		{ FPTD, PIN_5          },		/* J2 04	*/
		{ FPTC, PIN_16         },		/* J2 05	*/
		{ FPTD, PIN_0          },		/* J2 06	*/
		{ FPTC, PIN_17         },		/* J2 07	*/
		{ FPTD, PIN_2          },		/* J2 08	*/
		{ FPTA, PIN_16         },		/* J2 09	*/
		{ FPTD, PIN_3          },		/* J2 10	*/
		{ FPTA, PIN_17         },		/* J2 11	*/
		{ FPTD, PIN_1          },		/* J2 12	*/
		{ FPTE, PIN_31         },		/* J2 13	*/
		{ 0, 0 /* GND */       },		/* J2 14	*/
		{ 0, 0 /* NC */        },		/* J2 15	*/
		{ 0, 0 /* VREFH */     },		/* J2 16	*/
		{ FPTD, PIN_6          },		/* J2 17	*/
		{ FPTE, PIN_1          },		/* J2 18	*/
		{ FPTD, PIN_7          },		/* J2 19	*/
		{ FPTE, PIN_0          },		/* J2 20	*/
};

PORT_PIN_t HeaderJ9_Port_Pin[] = {
		{ FPTB, PIN_8          },	/* J9 01	*/
		{ 0, 0 /* PTD5 */      },	/* J9 02	*/
		{ FPTB, PIN_9          },	/* J9 03	*/
		{ 0, 0 /* P3V3 */      },	/* J9 04	*/
		{ FPTB, PIN_10         },	/* J9 05	*/
		{ FPTA, PIN_20         },	/* J9 06	*/
		{ FPTB, PIN_11         },	/* J9 07	*/
		{ 0, 0 /* P3V3 */      },	/* J9 08	*/
		{ FPTE, PIN_2          },	/* J9 09	*/
		{ 0, 0 /* P5V_USB */   },	/* J9 10	*/
		{ FPTE, PIN_3          },	/* J9 11	*/
		{ 0, 0 /* GND */       },	/* J9 12	*/
		{ FPTE, PIN_4          },	/* J9 13	*/
		{ 0, 0 /* GND */       },	/* J9 14	*/
		{ FPTE, PIN_5          },	/* J9 15	*/
		{ 0, 0 /* P5-9V_VIN */ },	/* J9 16	*/
};

PORT_PIN_t HeaderJ10_Port_Pin[] = {
		{ FPTE, PIN_20 },		/* J10 01	*/
		{ FPTB, PIN_0  },		/* J10 02	*/
		{ FPTE, PIN_21 },		/* J10 03	*/
		{ FPTB, PIN_1  },		/* J10 04	*/
		{ FPTE, PIN_22 },		/* J10 05	*/
		{ FPTB, PIN_2  },		/* J10 06	*/
		{ FPTE, PIN_23 },		/* J10 07	*/
		{ FPTB, PIN_3  },		/* J10 08	*/
		{ FPTE, PIN_29 },		/* J10 09	*/
		{ FPTC, PIN_2  },		/* J10 10	*/
		{ FPTE, PIN_30 },		/* J10 11	*/
		{ FPTC, PIN_1  },		/* J10 12	*/
};

PORT_PIN_t ArduinoA_Port_Pin[] = {
		{ FPTB, PIN_0 },		/* A0	*/
		{ FPTB, PIN_1 },		/* A1	*/
		{ FPTB, PIN_2 },		/* A2	*/
		{ FPTB, PIN_3 },		/* A3	*/
		{ FPTC, PIN_2 },		/* A4	*/
		{ FPTC, PIN_1 },		/* A5	*/
};

PORT_PIN_t ArduinoD_Port_Pin[] = {
		{ FPTA, PIN_1  },		/* D0	*/
		{ FPTA, PIN_2  },		/* D1	*/
		{ FPTD, PIN_4  },		/* D2	*/
		{ FPTA, PIN_12 },		/* D3	*/
		{ FPTA, PIN_4  },		/* D4	*/
		{ FPTA, PIN_5  },		/* D5	*/
		{ FPTC, PIN_8  },		/* D6	*/
		{ FPTC, PIN_9  },		/* D7	*/
		{ FPTA, PIN_13 },		/* D8	*/
		{ FPTD, PIN_5  },		/* D9	*/
		{ FPTD, PIN_0  },		/* D10	*/
		{ FPTD, PIN_2  },		/* D11	*/
		{ FPTD, PIN_3  },		/* D12	*/
		{ FPTD, PIN_1  },		/* D13	*/
		{ FPTE, PIN_0  },		/* D14	*/
		{ FPTE, PIN_1  },		/* D15	*/
};

/*----- Implementation -----------------------------------------------------*/
/**
 *****************************************************************************
 * \fn			GPIO_init
 * \brief		Configure  GPIOs for the RGB LED
 *****************************************************************************
 */
void GPIO_init(void) {
	uint8_t i;

	SIM->SCGC5 |= 0x3E00;					/* Enable all GPIO clocks		*/

	for (i = 0; i < sizeof(Onboard_Port_Pin) / sizeof(PORT_PIN_t); i++) {
		if (Onboard_Port_Pin[i].GPIOx != 0) {
			/* Port is GPIO, Output is 0, Direction is Output */
			FGPIO_TO_PORT(Onboard_Port_Pin[i].GPIOx)->
					PCR[PIN_TO_BIT(Onboard_Port_Pin[i].Pin)] = (1UL << 8);
			Onboard_Port_Pin[i].GPIOx->PDOR |= Onboard_Port_Pin[i].Pin;
			Onboard_Port_Pin[i].GPIOx->PDDR |= Onboard_Port_Pin[i].Pin;
		}
	}

	for (i = 0; i < sizeof(HeaderJ1_Port_Pin) / sizeof(PORT_PIN_t); i++) {
		if (HeaderJ1_Port_Pin[i].GPIOx != 0) {
			/* Port is GPIO, Output is 0, Direction is Output */
			FGPIO_TO_PORT(HeaderJ1_Port_Pin[i].GPIOx)->
					PCR[PIN_TO_BIT(HeaderJ1_Port_Pin[i].Pin)] = (1UL << 8);
			HeaderJ1_Port_Pin[i].GPIOx->PDOR |= HeaderJ1_Port_Pin[i].Pin;
			HeaderJ1_Port_Pin[i].GPIOx->PDDR |= HeaderJ1_Port_Pin[i].Pin;
		}
	}

	for (i = 0; i < sizeof(HeaderJ2_Port_Pin) / sizeof(PORT_PIN_t); i++) {
		if (HeaderJ2_Port_Pin[i].GPIOx != 0) {
			/* Port is GPIO, Output is 0, Direction is Output */
			FGPIO_TO_PORT(HeaderJ2_Port_Pin[i].GPIOx)->
					PCR[PIN_TO_BIT(HeaderJ2_Port_Pin[i].Pin)] = (1UL << 8);
			HeaderJ2_Port_Pin[i].GPIOx->PDOR |= HeaderJ2_Port_Pin[i].Pin;
			HeaderJ2_Port_Pin[i].GPIOx->PDDR |= HeaderJ2_Port_Pin[i].Pin;
		}
	}

	for (i = 0; i < sizeof(HeaderJ9_Port_Pin) / sizeof(PORT_PIN_t); i++) {
		if (HeaderJ9_Port_Pin[i].GPIOx != 0) {
			/* Port is GPIO, Output is 0, Direction is Output */
			FGPIO_TO_PORT(HeaderJ9_Port_Pin[i].GPIOx)->
					PCR[PIN_TO_BIT(HeaderJ9_Port_Pin[i].Pin)] = (1UL << 8);
			HeaderJ9_Port_Pin[i].GPIOx->PDOR |= HeaderJ9_Port_Pin[i].Pin;
			HeaderJ9_Port_Pin[i].GPIOx->PDDR |= HeaderJ9_Port_Pin[i].Pin;
		}
	}

	for (i = 0; i < sizeof(HeaderJ10_Port_Pin) / sizeof(PORT_PIN_t); i++) {
		if (HeaderJ10_Port_Pin[i].GPIOx != 0) {
			/* Port is GPIO, Output is 0, Direction is Output */
			FGPIO_TO_PORT(HeaderJ10_Port_Pin[i].GPIOx)->
					PCR[PIN_TO_BIT(HeaderJ10_Port_Pin[i].Pin)] = (1UL << 8);
			HeaderJ10_Port_Pin[i].GPIOx->PDOR |= HeaderJ10_Port_Pin[i].Pin;
			HeaderJ10_Port_Pin[i].GPIOx->PDDR |= HeaderJ10_Port_Pin[i].Pin;
		}
	}
}

/**
 *****************************************************************************
 * \fn			GPIO_bit_set
 * \brief		Set a GPIO bit on the specific port.
 *
 * \param[in]	port: Can be one of the following values: Onboard, HeaderJ1,
 *				HeaderJ2, HeaderJ9, HeaderJ10, ArduinoA, ArduinoD.
 * \param[in]	bit: Specify the bit number on the port.
 *****************************************************************************
 */
void GPIO_bit_set(PORT_NAME port, uint8_t bit) {
	switch (port) {
	case Onboard:
		if (bit < sizeof(Onboard_Port_Pin) / sizeof(PORT_PIN_t)
		        && Onboard_Port_Pin[bit].GPIOx != 0) {
			Onboard_Port_Pin[bit].GPIOx->PSOR = Onboard_Port_Pin[bit].Pin;
		}
		break;
	case HeaderJ1:
		if (bit < sizeof(HeaderJ1_Port_Pin) / sizeof(PORT_PIN_t)
		        && HeaderJ1_Port_Pin[bit].GPIOx != 0) {
			HeaderJ1_Port_Pin[bit].GPIOx->PSOR = HeaderJ1_Port_Pin[bit].Pin;
		}
		break;
	case HeaderJ2:
		if (bit < sizeof(HeaderJ2_Port_Pin) / sizeof(PORT_PIN_t)
		        && HeaderJ2_Port_Pin[bit].GPIOx != 0) {
			HeaderJ2_Port_Pin[bit].GPIOx->PSOR = HeaderJ2_Port_Pin[bit].Pin;
		}
		break;
	case HeaderJ9:
		if (bit < sizeof(HeaderJ9_Port_Pin) / sizeof(PORT_PIN_t)
		        && HeaderJ9_Port_Pin[bit].GPIOx != 0) {
			HeaderJ9_Port_Pin[bit].GPIOx->PSOR = HeaderJ9_Port_Pin[bit].Pin;
		}
		break;
	case HeaderJ10:
		if (bit < sizeof(HeaderJ10_Port_Pin) / sizeof(PORT_PIN_t)
		        && HeaderJ10_Port_Pin[bit].GPIOx != 0) {
			HeaderJ10_Port_Pin[bit].GPIOx->PSOR = HeaderJ10_Port_Pin[bit].Pin;
		}
		break;
	case ArduinoA:
		if (bit < sizeof(ArduinoA_Port_Pin) / sizeof(PORT_PIN_t)
		        && ArduinoA_Port_Pin[bit].GPIOx != 0) {
			ArduinoA_Port_Pin[bit].GPIOx->PSOR = ArduinoA_Port_Pin[bit].Pin;
		}
		break;
	case ArduinoD:
		if (bit < sizeof(ArduinoD_Port_Pin) / sizeof(PORT_PIN_t)
		        && ArduinoD_Port_Pin[bit].GPIOx != 0) {
			ArduinoD_Port_Pin[bit].GPIOx->PSOR = ArduinoD_Port_Pin[bit].Pin;
		}
		break;
	default:
		break;
	}
}

/**
 *****************************************************************************
 * \fn			GPIO_bit_reset
 * \brief		Set a GPIO bit on the specific port.
 *
 * \param[in]	port: Can be one of the following values: Onboard, HeaderJ1,
 *				HeaderJ2, HeaderJ9, HeaderJ10, ArduinoA, ArduinoD.
 * \param[in]	bit: Specify the bit number on the port.
 *****************************************************************************
 */
void GPIO_bit_reset(PORT_NAME port, uint8_t bit) {
	switch (port) {
	case Onboard:
		if (bit < sizeof(Onboard_Port_Pin) / sizeof(PORT_PIN_t)
		        && Onboard_Port_Pin[bit].GPIOx != 0) {
			Onboard_Port_Pin[bit].GPIOx->PCOR = Onboard_Port_Pin[bit].Pin;
		}
		break;
	case HeaderJ1:
		if (bit < sizeof(HeaderJ1_Port_Pin) / sizeof(PORT_PIN_t)
		        && HeaderJ1_Port_Pin[bit].GPIOx != 0) {
			HeaderJ1_Port_Pin[bit].GPIOx->PCOR = HeaderJ1_Port_Pin[bit].Pin;
		}
		break;
	case HeaderJ2:
		if (bit < sizeof(HeaderJ2_Port_Pin) / sizeof(PORT_PIN_t)
		        && HeaderJ2_Port_Pin[bit].GPIOx != 0) {
			HeaderJ2_Port_Pin[bit].GPIOx->PCOR = HeaderJ2_Port_Pin[bit].Pin;
		}
		break;
	case HeaderJ9:
		if (bit < sizeof(HeaderJ9_Port_Pin) / sizeof(PORT_PIN_t)
		        && HeaderJ9_Port_Pin[bit].GPIOx != 0) {
			HeaderJ9_Port_Pin[bit].GPIOx->PCOR = HeaderJ9_Port_Pin[bit].Pin;
		}
		break;
	case HeaderJ10:
		if (bit < sizeof(HeaderJ10_Port_Pin) / sizeof(PORT_PIN_t)
		        && HeaderJ10_Port_Pin[bit].GPIOx != 0) {
			HeaderJ10_Port_Pin[bit].GPIOx->PCOR = HeaderJ10_Port_Pin[bit].Pin;
		}
		break;
	case ArduinoA:
		if (bit < sizeof(ArduinoA_Port_Pin) / sizeof(PORT_PIN_t)
		        && ArduinoA_Port_Pin[bit].GPIOx != 0) {
			ArduinoA_Port_Pin[bit].GPIOx->PCOR = ArduinoA_Port_Pin[bit].Pin;
		}
		break;
	case ArduinoD:
		if (bit < sizeof(ArduinoD_Port_Pin) / sizeof(PORT_PIN_t)
		        && ArduinoD_Port_Pin[bit].GPIOx != 0) {
			ArduinoD_Port_Pin[bit].GPIOx->PCOR = ArduinoD_Port_Pin[bit].Pin;
		}
		break;
	default:
		break;
	}
}

/**
 *****************************************************************************
 * \fn			GPIO_port_set
 * \brief		Set a GPIO port to a value.
 *
 * \param[in]	port: Can be one of the following values: Onboard, HeaderJ1,
 *				HeaderJ2, HeaderJ9, HeaderJ10, ArduinoA, ArduinoD.
 * \param[in]	value: Value to set to the port.
 *****************************************************************************
 */
void GPIO_port_set(PORT_NAME port, uint16_t value) {
	uint8_t i;
	uint16_t bit = 1U;

	switch (port) {
	case Onboard:
		for (i = 0; i < sizeof(Onboard_Port_Pin) / sizeof(PORT_PIN_t); i++) {
			if (Onboard_Port_Pin[i].GPIOx != 0) {
				if (value & bit) {
					Onboard_Port_Pin[bit].GPIOx->PSOR = bit;
				}
				else {
					Onboard_Port_Pin[bit].GPIOx->PCOR = bit;
				}
			}
			bit <<= 1;
		}
		break;
	case HeaderJ1:
		for (i = 0; i < sizeof(HeaderJ1_Port_Pin) / sizeof(PORT_PIN_t); i++) {
			if (HeaderJ1_Port_Pin[i].GPIOx != 0) {
				if (value & bit) {
					HeaderJ1_Port_Pin[bit].GPIOx->PSOR = bit;
				}
				else {
					HeaderJ1_Port_Pin[bit].GPIOx->PCOR = bit;
				}
			}
			bit <<= 1;
		}
		break;
	case HeaderJ2:
		for (i = 0; i < sizeof(HeaderJ2_Port_Pin) / sizeof(PORT_PIN_t); i++) {
			if (HeaderJ2_Port_Pin[i].GPIOx != 0) {
				if (value & bit) {
					HeaderJ2_Port_Pin[bit].GPIOx->PSOR = bit;
				}
				else {
					HeaderJ2_Port_Pin[bit].GPIOx->PCOR = bit;
				}
			}
			bit <<= 1;
		}
		break;
	case HeaderJ9:
		for (i = 0; i < sizeof(HeaderJ9_Port_Pin) / sizeof(PORT_PIN_t); i++) {
			if (HeaderJ9_Port_Pin[i].GPIOx != 0) {
				if (value & bit) {
					HeaderJ9_Port_Pin[bit].GPIOx->PSOR = bit;
				}
				else {
					HeaderJ9_Port_Pin[bit].GPIOx->PCOR = bit;
				}
			}
			bit <<= 1;
		}
		break;
	case HeaderJ10:
		for (i = 0; i < sizeof(HeaderJ10_Port_Pin) / sizeof(PORT_PIN_t); i++) {
			if (HeaderJ10_Port_Pin[i].GPIOx != 0) {
				if (value & bit) {
					HeaderJ10_Port_Pin[bit].GPIOx->PSOR = bit;
				}
				else {
					HeaderJ10_Port_Pin[bit].GPIOx->PCOR = bit;
				}
			}
			bit <<= 1;
		}
		break;
	case ArduinoA:
		for (i = 0; i < sizeof(ArduinoA_Port_Pin) / sizeof(PORT_PIN_t); i++) {
			if (ArduinoA_Port_Pin[i].GPIOx != 0) {
				if (value & bit) {
					ArduinoA_Port_Pin[bit].GPIOx->PSOR = bit;
				}
				else {
					ArduinoA_Port_Pin[bit].GPIOx->PCOR = bit;
				}
			}
			bit <<= 1;
		}
		break;
	case ArduinoD:
		for (i = 0; i < sizeof(ArduinoD_Port_Pin) / sizeof(PORT_PIN_t); i++) {
			if (ArduinoD_Port_Pin[i].GPIOx != 0) {
				if (value & bit) {
					ArduinoD_Port_Pin[bit].GPIOx->PSOR = bit;
				}
				else {
					ArduinoD_Port_Pin[bit].GPIOx->PCOR = bit;
				}
			}
			bit <<= 1;
		}
		break;
	default:
		break;
	}
}
