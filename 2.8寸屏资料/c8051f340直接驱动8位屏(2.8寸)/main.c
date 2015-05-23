/*******************************************************************************
*  Copyright (C) 2010 - All Rights Reserved
*		
* ��������:	��ɼ���
* ��Ȩ����: ��ɵ���	
* ��������:	2010��6��10�� 
* ������ʷ:	2010��11��2���޸�
* Version:  1.0 
* Demo �Ա���ַ��http://store.taobao.com/shop/view_shop.htm?asker=wangwang&shop_nick=qifeidianzi
**********************************************************************************************************************************************
����������������������������������������������������������������������������������������������������������������������������������������������
����������������������һ������������������������������������������������������������һ����������������������������һһһһһһһ��������������
������һһһһ��һһһһһһ������������һһһһһһһһ�������������������ą�����һһ������һ������������������һһһһ����һһһ������������
������������һ������һ��һ������������һһһһ�ą���һ����һһ������������һһһһһһһһһһһ������������������������һһһһ��������������
�������ą���һ��������������������������������������һ��һһ��������������һһ����һһ������һһ������������������������һһ������������������
������һ����һһһһһһһһһһһ������������������һһ������������������һһһһһһһһһһ������������һһһһһһһһһһһһһһһ������
������һһһһһ����һһ��һ����������������������һһһһһ��������������һһ����һһ������һ������������һһ����������һһ������һһ��������
��������������һ��һ��һ��һ������������������������һ����һһ������������һһһһһһһһһһ��������������������������һһ������������������
����һһһ��������һһһ��һ������������������������һһ����������������������������һ��������������һ������������������һһ������������������
������������һ����������һһ��������������������������һһһһһһ������������������һһһһһһһһһ������������������һһ������������������
��������һһһ������һһһһ����������������������������һһһһһ��������������������һһһһһһһ��������������һһһһ��������������������
����������������������������������������������������������������������������������������������������������������������������������������������
**********************************************************************************************************************************************/
//
#include<TFT.h>
#include<delay.h>
#include<C8051F340.h>


void OSCILLATOR_Init (void);
void Port_Init(void);
void Ext_Interrupt_Init (void);

unsigned char Vsync_Flag=0;

void main(void)
{		
   int i,j;
	PCA0MD &= ~0x40;      //���Ź���ֹ                
  	OSCILLATOR_Init();    //ʱ�ӳ�ʼ��
	Port_Init();          //�˿ڳ�ʼ�� 	             
	P0MDOUT&=~0xC0;       //����VCYNC��HREF�˿�Ϊ����ģʽ
	P0MDIN|=0xC0;
	P0|=0xC0;


	delay(10);

	Tft_Init();          //TFT��ʼ��
	TftClear(RED);       //����

	TftWR_Str(20,100,"C8051F340 TFT Test ",RED,BLACK);
	delay_ms(5000);
	delay_ms(5000);
	delay_ms(5000);
	while(1)
	{
		
		delay_ms(5000);
		TftClear(BLACK);
		delay_ms(5000);
		TftClear(BLUE);
		delay_ms(5000);
		TftClear(RED);
		delay_ms(5000);
		TftClear(GREEN);
		delay_ms(5000);
		TftClear(CYAN);
		delay_ms(5000);
		TftClear(MAGENTA);
		delay_ms(5000);
		TftClear(YELLOW);
		delay_ms(5000);
		TftClear(WHITE);
	
	}/**/

}

void OSCILLATOR_Init (void)
{
    int i = 0;
    FLSCL     = 0x90;
    CLKMUL    = 0x80;
    for (i = 0; i < 20; i++);    // Wait 5us for initialization
    CLKMUL    |= 0xC0;
    while ((CLKMUL & 0x20) == 0);
    CLKSEL    = 0x03;
    OSCICN    = 0x83;            
}

//-------------------------
// Port_Init
//-------------------------
// Port Initialization
// - Configure the Crossbar and GPIO ports.

void Port_Init(void)
{  
	P4MDOUT=0xFF;
	P3MDOUT=0xFF;
	P2MDOUT=0xFF;
	P0MDOUT=0xFF;
	P1MDOUT   = 0xFF;

	XBR0      = 0x01;
	XBR1      = 0x40;

} 


