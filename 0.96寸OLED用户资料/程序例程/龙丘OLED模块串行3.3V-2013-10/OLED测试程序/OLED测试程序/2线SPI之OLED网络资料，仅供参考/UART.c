#include"all.h"

void UartSend(unsigned long c)
{
	UARTCharPut(UART0_BASE,c);				//���ַ����͵����������
}
