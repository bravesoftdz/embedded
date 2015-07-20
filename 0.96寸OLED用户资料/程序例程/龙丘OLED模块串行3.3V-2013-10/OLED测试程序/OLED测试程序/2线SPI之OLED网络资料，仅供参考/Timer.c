#include"systemInit.h"


void TimerInit(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);						//	ʹ�ܶ�ʱ��T0
	TimerConfigure(TIMER0_BASE, TIMER_CFG_16_BIT_PAIR|				//	��T0���ó�16λ��ʱ��
								TIMER_CFG_A_PERIODIC);				//	��T0��A��ʱ������Ϊ16λ���ڶ�ʱ��
	TimerPrescaleSet(TIMER0_BASE, TIMER_A,99);						//	T0��A��ʱ��Ԥ��Ƶ100��
	TimerLoadSet(TIMER0_BASE, TIMER_A,1000);						//	����T0 A��ʱ����װ��ֵ������ʱʱ��Ϊ5ms
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);           		//	ʹ��T0 A��ʱ������ж�
	IntMasterEnable();												//	ʹ�ܴ������ж�
	IntEnable(INT_TIMER0A);											//	ʹ��TO A��ʱ�����ж�
	TimerEnable(TIMER0_BASE, TIMER_A);								//	ʹ��T0 A��ʱ������
	Flag=0;
}


void Timer0A_ISR(void)
{
	TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);                 //	����жϱ�־λ
	if(++a==200)
	{	
		a=0;
		Flag=~Flag;
		}
	}
//