#include"systemInit.h"



int main(void)
{
	jtagWait();												//	������
	clockInit();											//	ϵͳʱ������
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);          //	ʹ��GPIOBģ��
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_2); //D0/SCLK/PB2
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_3);//D1/MOSI/PB3
	SetSclk(1);
	SetMosi(0);
	TestMain();
	while(1){};
}
//