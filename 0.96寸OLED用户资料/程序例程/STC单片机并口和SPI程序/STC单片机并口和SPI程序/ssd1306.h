#ifndef  _SH1101A_H_
#define  _SH1101A_H_
#include<intrins.h>

#define PAR	   //����Ϊ����ģʽ���粻�ǣ�ע�͵�����
#ifdef PAR
	#define demo   //��Ϊdemo������Ҫ���򣬶���������������ݷ���Ĵ�������ȥ����Ӳ��һһ��Ӧ��ע�͵����ɣ�
#endif
//����Ϊ�ӿڶ��壬�û������Լ��İ������ж���

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Delay Time
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void uDelay(unsigned char l)
{
	while(l--);
}


void Delay(unsigned char n)
{
unsigned char i,j,k;

	for(k=0;k<n;k++)
	{
		for(i=0;i<131;i++)
		{
			for(j=0;j<15;j++)
			{
				uDelay(203);	
			}
		}
	}
}


extern unsigned char code num[10][16];

#ifdef PAR
	#define xData P0
	sbit RD_oled=P1^1;
	sbit WR_oled=P1^0;
	sbit DC=P1^3;
	sbit RES=P1^2;
	sbit CS=P1^4;
#else
	sbit CLK=P1^7;
	sbit DATA=P1^6;
	sbit DC=P1^5;
	sbit RES=P1^4;
	sbit CS=P1^2;
#endif
//****************************��Ҫ��������************************************
void WriteCommand(unsigned com);		//д�������
void WriteData(unsigned dat);			//д���ݳ���
void esbusini(void);					//��ʼ�����߳���
void ini_oled(void);            		//OLED��ʼ��
void ini_dis(void);						//��ʾ��ʼ��(���������)

#ifdef demo
sbit A_0=ACC^0;//����λ����
sbit A_1=ACC^1;
sbit A_2=ACC^2;
sbit A_3=ACC^3;
sbit A_4=ACC^4;
sbit A_5=ACC^5;
sbit A_6=ACC^6;
sbit A_7=ACC^7;

sbit B_0=B^0;//����λ����
sbit B_1=B^1;
sbit B_2=B^2;
sbit B_3=B^3;
sbit B_4=B^4;
sbit B_5=B^5;
sbit B_6=B^6;
sbit B_7=B^7;

unsigned char SetData(unsigned char DataByte)//ת��������P0�ڵ�����,��ӿڿɲ���˺���
{
	ACC=DataByte;
	B_1=A_0;
	B_0=A_1;

	B_3=A_2;
	B_2=A_3;

	B_5=A_4;
	B_4=A_5;

    B_7=A_6;
	B_6=A_7;
	
	return B;
}
#endif
void Write_Command(unsigned char Data)
{
	DC=0;
	CS=0;
	WR_oled=0;
	#ifdef demo
		xData=SetData(Data);
		//send_UART(Data);
		uDelay(1);
	#else
		xData=Data;
	#endif
	WR_oled=1;
	CS=1;
	DC=1;
}


void Write_Data(unsigned char Data)
{
	DC=1;
	CS=0;
	WR_oled=0;
	#ifdef demo
		xData=SetData(Data);
		//send_UART(Data);
		uDelay(1);
	#else
		xData=Data;
		#endif
	WR_oled=1;
	CS=1;
	DC=1;
}
/*******************************function************************************************************/
//*******************��ʾX��Y���괦��һ���ַ���һ�п�����ʾ16���ַ���XΪ0��15��YΪ0��3**************
void disc(unsigned char X,unsigned char Y,unsigned char * c)
{
	unsigned char n;
	Write_Command (0xb7-(Y<<1));
	if(X%2)
		Write_Command (0x08);
	else
		Write_Command (0x00);
	Write_Command (0x10+(X>>1));
	for(n=0;n<=15;n+=2)
		Write_Data(*(c+n));

	Write_Command (0xb7-(Y<<1)-1);
	if(X%2)
		Write_Command (0x08);
	else
		Write_Command (0x00);
	Write_Command (0x10+(X>>1));
	for(n=1;n<=15;n+=2)
		Write_Data(*(c+n));
}
// X  is 0 to 7
void dish(unsigned char X,unsigned char Y,unsigned char * h)
{
	unsigned char n;
	Write_Command (0xb7-(Y<<1));
	if(X%2)
		Write_Command (0x08);
	else
		Write_Command (0x00);
	Write_Command (0x10+(X>>1));
	for(n=0;n<=31;n+=2)
		Write_Data(*(h+n));

	Write_Command (0xb7-(Y<<1)-1);
	if(X%2)
		Write_Command (0x08);
	else
		Write_Command (0x00);
	Write_Command (0x10+(X>>1));
	for(n=1;n<=31;n+=2)
		Write_Data(*(h+n));
}
void disn(unsigned char X,unsigned char Y,unsigned char n)
{
	unsigned char m;
	Write_Command (0xb7-(Y<<1));
	if(X%2)
		Write_Command (0x08);
	else
		Write_Command (0x00);
	WriteCommand (0x10+(X>>1));
	for(m=0;m<=15;m+=2)
		Write_Data(*(num[n]+m));                     

	Write_Command (0xb7-(Y<<1)-1);
	if(X%2)
		Write_Command (0x08);
	else
		Write_Command (0x00);
	Write_Command (0x10+(X>>1));
	for(m=1;m<=15;m+=2)
		Write_Data(*(num[n]+m));
}
#endif