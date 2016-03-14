/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "extUSART.h"
/* Structure for USART module instance */
struct usart_module console_instance;

/* Configure serial Console.
* GLCK for SERCOM	-> GCLK_GENERATOR_1 (8MHz)
* SERCOM instance	-> 3
* BAUDRATE			-> 9600
*/

void configure_console(void)
{
	
	struct usart_config conf_usart;
	
	usart_get_config_defaults(&conf_usart);
	
	conf_usart.generator_source = GCLK_GENERATOR_1;
	conf_usart.baudrate = 9600;
	conf_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	
	conf_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	conf_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	conf_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	conf_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	
	stdio_serial_init(&console_instance, EDBG_CDC_MODULE, &conf_usart);
	
	usart_enable(&console_instance);
}

int main (void)
{
	uint8_t tiles[6] = {0,0,0,0,0,0}, receivedData,i = 0;
	int quotient;
	system_init();
	ext_usart_clock_init();
	ext_usart_pin_init();
	ext_usart_init();
	configure_console();
	printf("Up and running!\r");
	while (1) {
		receivedData = USART_Receive();
		quotient = receivedData;
		i = 0;
		while(quotient != 0) {
			tiles[i] = quotient%2;
			quotient /= 2;
			i++;
		}
		for(int i = 0; i < 6; i++) {
			printf("%d",tiles[i]);
			tiles[i] = 0;
		}
	printf("\n");
	}
}
