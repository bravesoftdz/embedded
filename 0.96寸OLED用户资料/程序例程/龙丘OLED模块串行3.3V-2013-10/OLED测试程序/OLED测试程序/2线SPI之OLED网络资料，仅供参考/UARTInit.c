#include"all.h"


void UartInit(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);						  		 		//ʹ��UARTģ��
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);						   				//ʹ��RX0/TX0����GPIOģ��
	GPIOPinTypeUART(GPIO_PORTA_BASE, (GPIO_PIN_0|GPIO_PIN_1));			   				//ʹ��RX0/TX0
	UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(),9600,UART_CONFIG_WLEN_8|		    //����UART��������Ϊ9600,����λ8λ
						UART_CONFIG_PAR_NONE|										    //ֹͣλ1λ
						UART_CONFIG_STOP_ONE);											//��У��						   						
	UARTEnable(UART0_BASE);																//ʹ��UART
}
//
