#include"all.h"


//  ����KEY
#define  KEY_PERIPH             SYSCTL_PERIPH_GPIOB
#define  KEY_PORT               GPIO_PORTB_BASE
#define  KEY_PIN                GPIO_PIN_5


//  ��ֹJTAGʧЧ
void jtagWait(void)
{
    SysCtlPeripheralEnable(KEY_PERIPH);                           //  ʹ��KEY���ڵ�GPIO�˿�
    GPIOPinTypeGPIOInput(KEY_PORT, KEY_PIN);                      //  ����KEY���ڹܽ�Ϊ����

    if (GPIOPinRead(KEY_PORT, KEY_PIN) == 0x00)            		  //  ����λʱ����KEY�������
    {
        for (;;);                                          		  //  ��ѭ�����Եȴ�JTAG����
    }

    SysCtlPeripheralDisable(KEY_PERIPH);                          //  ��ֹKEY���ڵ�GPIO�˿�
}



//  ϵͳʱ�ӳ�ʼ��
void clockInit(void)
{
    SysCtlLDOSet(SYSCTL_LDO_2_75V);                         	//  ����PLLǰ�뽫LDO��Ϊ2.75V

    SysCtlClockSet(SYSCTL_USE_PLL |                          	//  ϵͳʱ�����ã�����PLL
                   SYSCTL_OSC_MAIN |                       	    //  ������
                   SYSCTL_XTAL_6MHZ |                       	//  ���6MHz����
                   SYSCTL_SYSDIV_10);                       	//  ��Ƶ���Ϊ20MHz
}


//	UART��ʼ��
extern void UartInit(void);


//	UART���ͺ���
extern void UartSend(unsigned long c);
//