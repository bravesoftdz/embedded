/*******************************************************************************
*  Copyright (C) 2010 - All Rights Reserved
*		
* �������:	��ɼ���
* ��Ȩ����: ��ɵ���	
* ��������:	2010��6��10�� 
* �����ʷ:	2010��11��2���޸�
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
/***************************************************************************
��    �ƣ� TFT.C
��    �ܣ� �Ӻ�������
��    �ߣ� H&G
��    ���� V1.0
����ʱ�䣺 2011-6-10
***************************************************************************/

/***************************************************************************
ͷ�ļ�
***************************************************************************/
#include <TFT.h>
#include <delay.h>
#include <english_16x8.h>

/***************************************************************************
��    �ƣ�void Tft_WR_DATA16(unsigned int inputdata)
��    �ܣ���TFT RAM��д������
��ڲ�����inputdata  ��д������ֵ��RGB 565  ��ʽ
���ڲ�������
˵    ����
���÷�����Tft_WR_DATA16(0xffff);
***************************************************************************/
void Tft_WR_DATA16(unsigned int inputdata)
{
	 unsigned char inputdatal,inputdatah;
	 unsigned int x;
	 x=inputdata;
	 inputdatal=inputdata&0x00ff;
	 inputdatah=(inputdata>>8)&0x00ff;
	 Port4MDOUT= 0XFF;

//	 Tft_CS_PIN=0; 
	 Tft_RS_PIN=1;//��Ϊ���ݣ���Ϊָ��
	 Tft_RD_PIN=1;

	 Port4=inputdatah; 
     Tft_WR_PIN=0;
     Tft_WR_PIN=1;

	 Port4=inputdatal;
     Tft_WR_PIN=0;
     Tft_WR_PIN=1;	 
//	 Tft_CS_PIN=1;
	 Port4MDOUT= 0X00;
  
}

/***************************************************************************
��    �ƣ�void TftWrite16(unsigned int index)
��    �ܣ�д�Ĵ���ָ��
��ڲ�����index ��д��ָ��
���ڲ�������
˵    ����
���÷�����TftWrite16(0x0022);
***************************************************************************/
void TftWrite16(unsigned int index)//д����������
{   
     unsigned int indexh;
	 unsigned int indexl;
	 indexh=(index&0xff00)>>8;
	 indexl=index&0x00ff;
	 Port4MDOUT= 0XFF;
	
//     Tft_CS_PIN=0;
	 Tft_RD_PIN=1;
	 Tft_RS_PIN=0;

     Port4=indexh; 
	 Tft_WR_PIN=0;
     Tft_WR_PIN=1;

	 Port4=indexl;
	 Tft_WR_PIN=0;
     Tft_WR_PIN=1;

//     Tft_CS_PIN=1;
	 Port4MDOUT= 0X00;
 
}

/***************************************************************************
��    �ƣ�void TftWrite(unsigned int index,unsigned int inputdata)
��    �ܣ���ָ���Ĵ���д����
��ڲ�����index       �Ĵ�����ַ
          inputdata   ��ָ���Ĵ�����д���ֵ
���ڲ�������
˵    ����
���÷�����TftWrite(0x0000,0x0001);
***************************************************************************/
void TftWrite(unsigned int index,unsigned int inputdata)
{
    unsigned int x;
	unsigned int y;
    unsigned int indexh;
	unsigned int indexl;
	unsigned int inputdatah;
	unsigned int inputdatal;
	x=index;
	y=inputdata;
    indexh=(index&0xff00)>>8;
	indexl=index&0x00ff;
	inputdatah=(inputdata&0xff00)>>8;
	inputdatal=inputdata&0x00ff;
	Port4MDOUT= 0XFF;

//	Tft_CS_PIN=0;
	Tft_RS_PIN= 0;
	Tft_RD_PIN=1;
	
	Port4=indexh;
	Tft_WR_PIN=0;   
	Tft_WR_PIN=1;

	Port4=indexl; 
	Tft_WR_PIN=0;   
	Tft_WR_PIN=1;

	Tft_RS_PIN=1;

	Port4=inputdatah;
    Tft_WR_PIN=0;	
    Tft_WR_PIN=1;

	Port4=inputdatal; 
    Tft_WR_PIN=0;	
    Tft_WR_PIN=1;

//	Tft_CS_PIN=1;
	Port4MDOUT= 0X00;


}

/***************************************************************************
��    �ƣ�unsigned int Tft_ReadID(void)
��    �ܣ�������TFT��ID��
��ڲ�������
���ڲ���������TFT ID
˵    ����
���÷�����m=Tft_ReadID();
***************************************************************************/
unsigned int Tft_ReadID(void)
{
	unsigned int m;
	unsigned int n;
	m=0;
	n=0;


//	Tft_CS_PIN=0;
	Tft_RS_PIN=0;
	Tft_RD_PIN=1;

	Port4MDOUT= 0XFF;

	Port4=0x00;	
	Tft_WR_PIN=0;  
	Tft_WR_PIN=1;
	Port4=0x00;
	Tft_WR_PIN=0;  
	Tft_WR_PIN=1;

	Tft_RS_PIN=1;

	Port4=0x00;
	Tft_WR_PIN=0;  
	Tft_WR_PIN=1;
	Port4=0x01;
	Tft_WR_PIN=0;  
	Tft_WR_PIN=1;

	Port4MDOUT =0X00;
	Port4=0xff;

	Tft_RD_PIN=0;
	Tft_RD_PIN=1;
	m=Port4;
	Tft_RD_PIN=0;
	Tft_RD_PIN=1;
	n=Port4;

	return (m<<8)|n;

}

/***************************************************************************
��    �ƣ�unsigned int Tft_ReadPoint(unsigned int Xpos,unsigned int Ypos)
��    �ܣ���ȡTFT ָ������ɫֵ 
��ڲ�����Xpos       X����λ��   0<Xpos<239
          Ypos       Y����λ��   0<Ypos<319
���ڲ�����ָ������ɫֵ��RGB565��ʽ
˵    ����
���÷�����m=Tft_ReadPoint(100,100);
***************************************************************************/
unsigned int Tft_ReadPoint(unsigned int Xpos,unsigned int Ypos)
{
	unsigned int readdatah,readdatal,t;
	readdatah=0;
	readdatal=0;
	t=0;
	if(Xpos>=240||Ypos>=320)return 0;//�����˷�Χ,ֱ�ӷ���	
	Tft_SetCursor(Xpos,Ypos);
	TftWrite16(0x0022);       //ѡ��GRAM��ַ
	 

	Port4MDOUT=0x00;
	Port4=0xff;

	Tft_RS_PIN=1;
//	Tft_CS_PIN=0;
	//��ȡ����(��GRAMʱ,��Ҫ��2��)
	//dummy READ
	Tft_RD_PIN=0;				   
	Tft_RD_PIN=1;	   
	Tft_RD_PIN=0;		
	Tft_RD_PIN=1;
	//��ȡ����	
	Tft_RD_PIN=0;		   
	Tft_RD_PIN=1;
	readdatah=Port4;
	Tft_RD_PIN=0;				   
	Tft_RD_PIN=1; 
	readdatal=Port4; 	
//	Tft_CS_PIN=1; 
	t=  (readdatah<<8)+readdatal;
	if (BGR==0) 
		return t;
    else
	    return BGR2RGB(t);
}

/***************************************************************************
��    �ƣ�unsigned int BGR2RGB(unsigned int color)
��    �ܣ���RGBת��ΪBGR
��ڲ�����RGB��ɫֵ
���ڲ�����BGR��ɫֵ
˵    �����ڲ���������
���÷�����m=BGR2RGB(color);
***************************************************************************/
unsigned int BGR2RGB(unsigned int color)
{

	unsigned int r,g,b,rgb;   
	b=(color>>0)&0x1f;
	g=(color>>5)&0x3f;
	r=(color>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);

}

/***************************************************************************
��    �ƣ�void Tft_Init(void)
��    �ܣ�TFT ��ʼ��
��ڲ�������
���ڲ������� 
˵    ����
���÷�����Tft_Init();
***************************************************************************/
void Tft_Init(void)
{
unsigned int id;
	 	Tft_RST_PIN=1;
		delay(200); 
		Tft_RST_PIN=0;//Ӳ����λ
		delay(200);
		Tft_RST_PIN=1;
		delay(200); 
		P2=0xff; //���ƴ�
		delay(200);
		id=Tft_ReadID();
		delay(200);
	if(id==0x9325||id==0x0000)
	{
		TftWrite(0x00e7, 0x0010);	
		TftWrite(0x0000, 0x0001);	
		TftWrite(0x0001, 0x0100);
		TftWrite(0x0002, 0x0700);
	#if AM==000       
		TftWrite(0x0003,0x1000);//��Ļ��ת���� TFM=0,TRI=0,SWAP=1,16 bits system interface  swap RGB to BRG���˴�ORG��HWM Ϊ0
	#elif AM==001        
		TftWrite(0x0003,0x1008);      
	#elif AM==010  
	    TftWrite(0x0003,0x1010);        
	#elif AM==011
		TftWrite(0x0003,0x1018);
	#elif AM==100  
		TftWrite(0x0003,0x1020);      
	#elif AM==101  
		TftWrite(0x0003,0x1028);      
	#elif AM==110  
		TftWrite(0x0003,0x1030);      
	#elif AM==111  
		TftWrite(0x0003,0x1038);
	#endif
		TftWrite(0x0004, 0x0000);
		TftWrite(0x0008, 0x0207);	
		TftWrite(0x0009, 0x0000);	
		TftWrite(0x000A, 0x0000);
		TftWrite(0x000C, 0x0001);	
		TftWrite(0x000D, 0x0000);	
		TftWrite(0x000F, 0x0000);	
	//-----Power On sequence-----------------------	
		TftWrite(0x0010, 0x0000);	
		TftWrite(0x0011, 0x0007);	
		TftWrite(0x0012, 0x0000);	
		TftWrite(0x0013, 0x0000);	
		delay_ms(1000);
		TftWrite(0x0010, 0x1590);	
		TftWrite(0x0011, 0x0227);	
		delay_ms(1000);
		TftWrite(0x0012, 0x009c);	
	delay_ms(1000);
		TftWrite(0x0013, 0x1900);	
		TftWrite(0x0029, 0x0023);
		TftWrite(0x002b, 0x000e);		
	delay_ms(1000);
	//-----Gamma control-----------------------	
		TftWrite(0x0030, 0x0000);	
		TftWrite(0x0031, 0x0505);	
		TftWrite(0x0032, 0x0004);	
		TftWrite(0x0035, 0x0006);	
		TftWrite(0x0036, 0x0707);	
		TftWrite(0x0037, 0x0105);	
		TftWrite(0x0038, 0x0002);	
		TftWrite(0x0039, 0x0707);	
		TftWrite(0x003C, 0x0704);	
		TftWrite(0x003D, 0x0807);	
	//-----Set RAM area-----------------------	
		TftWrite(0x0050, 0x0000);
		TftWrite(0x0051, 0x00EF);
		TftWrite(0x0052, 0x0000);
		TftWrite(0x0053, 0x013F);
		TftWrite(0x0060, 0x2700);
		TftWrite(0x0061, 0x0001);
		TftWrite(0x006A, 0x0000);
	#if AM==000         
		TftWrite(0x0020,0x00ef);//GRAMˮƽ��ʼλ��
		TftWrite(0x0021,0x013f);      
	#elif AM==001
		TftWrite(0x0020,0x00ef);
		TftWrite(0x0021,0x013f);      
	#elif AM==010
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x013f);      
	#elif AM==011
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x013f);       
	#elif AM==100
		TftWrite(0x0020,0x00ef);
		TftWrite(0x0021,0x0000);      
	#elif AM==101  
		TftWrite(0x0020,0x00ef);
		TftWrite(0x0021,0x0000);      
	#elif AM==110
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x0000);      
	#elif AM==111
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x0000);         
	#endif  
	//-----Partial Display Control------------	
		TftWrite(0x0080, 0x0000);	
		TftWrite(0x0081, 0x0000);
		TftWrite(0x0082, 0x0000);
		TftWrite(0x0083, 0x0000);
		TftWrite(0x0084, 0x0000);	
		TftWrite(0x0085, 0x0000);
	//-----Panel Control----------------------
		TftWrite(0x0090, 0x0010);	
		TftWrite(0x0092, 0x0000);
		TftWrite(0x0093, 0x0003);
		TftWrite(0x0095, 0x0110);
		TftWrite(0x0097, 0x0000);	
		TftWrite(0x0098, 0x0000);
	//-----Display on-----------------------	
		TftWrite(0x0007, 0x0173);
	}
	else if(id==0x9331||id==0x0101) 
	{
		TftWrite(0x00E7,0x1014);
		//  DeviceCode = ili9331_ReadRegister(0x00E7);
		TftWrite(0x0001,0x0100); //Set ss(1)��sm(0),S720 to S1 
		TftWrite(0X0002,0x0200); //set 1 line inversion ?
	#if   ID_AM==000       
		TftWrite(0x0003,0x1000);//��Ļ��ת���� TFM=0,TRI=0,SWAP=1,16 bits system interface  swap RGB to BRG���˴�ORG��HWM Ϊ0
	#elif ID_AM==001        
		TftWrite(0x0003,0x1008);      
	#elif ID_AM==010  
		TftWrite(0x0003,0x1010);        
	#elif ID_AM==011
		TftWrite(0x0003,0x1018);
	#elif ID_AM==100  
		TftWrite(0x0003,0x1020);      
	#elif ID_AM==101  
		TftWrite(0x0003,0x1028);      
	#elif ID_AM==110  
		TftWrite(0x0003,0x1030);      
	#elif ID_AM==111  
		TftWrite(0x0003,0x1038);
	#endif  
		TftWrite(0x0003,0x1008); //����GRAMд����,bgr=1(SWAT RGB TO BGR)// 65K���� 
		TftWrite(0x0008,0x0202); //display control2����ǰ��porch 2line
		TftWrite(0x0009,0x0000); //display control3 (set nodisplay area cycle)
		TftWrite(0x000A,0X0000); //display control4 FMARK function
		TftWrite(0x000C,0X0001); //RGB interface 16bit ��̬��ͼƬ����̬����Ҫ����Ϊdm��rm
		TftWrite(0x000D,0X0000); //Frame marker
		TftWrite(0x000F,0X0000); //RGB interface polarity

		/* power on sequence*/
		TftWrite(0x0010,0x0000); //slp,stb,
		TftWrite(0x0011,0x0007);
		TftWrite(0x0012,0x0000);
		TftWrite(0x0013,0x0000);
		delay_ms(200);
		delay_ms(200);
		TftWrite(0x0010,0x1690); //slp,stb,
		TftWrite(0x0011,0x0227);
		delay_ms(200);
		TftWrite(0x0012,0x000C);
		delay_ms(200);
		TftWrite(0x0013,0x0800);

		TftWrite(0x0029,0x0011); //slp,stb,
		TftWrite(0x002B,0x000B); //fram rate
		delay_ms(200);
	#if   ID_AM==000         
		TftWrite(0x0020,0x00ef);//GRAMˮƽ��ʼλ��
		TftWrite(0x0021,0x013f);      
	#elif ID_AM==001
		TftWrite(0x0020,0x00ef);
		TftWrite(0x0021,0x013f);      
	#elif ID_AM==010
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x013f);      
	#elif ID_AM==011
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x013f);       
	#elif ID_AM==100
		TftWrite(0x0020,0x00ef);
		TftWrite(0x0021,0x0000);      
	#elif ID_AM==101  
		TftWrite(0x0020,0x00ef);
		TftWrite(0x0021,0x0000);      
	#elif ID_AM==110
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x0000);      
	#elif ID_AM==111
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x0000);         
	#endif  
	TftWrite(0x0020,0x00ef);//GRAMˮƽ��ʼλ��
		TftWrite(0x0021,0x013f);  
		/* adjust the gamma curve */
		TftWrite(0x0030,0x0000);
		TftWrite(0x0031,0x0106);
		TftWrite(0x0032,0x0000);

		TftWrite(0x0035,0x0204);

		TftWrite(0x0036,0x160A);
		TftWrite(0x0037,0x0707);
		TftWrite(0x0038,0x0106);
		TftWrite(0x0039,0x0707);
		TftWrite(0x003C,0x0402);
		TftWrite(0x003D,0x0C0F);
		/* set gram area */
		TftWrite(0x0050,0x0000); //Horizontal gram start addr
		TftWrite(0x0050,0x00EF); //Horizontal gram end   addr  
		TftWrite(0x0051,0x0000); //vertical gram start addr
		TftWrite(0x0052,0x013F); //vertical gram end   addt
		TftWrite(0x0060,0x2700); //gate scan
		TftWrite(0x0061,0x0001); //ndl vle rev
		TftWrite(0x006A,0x0000); //scrolling line
		/*partial dispaly */
		TftWrite(0x0080,0x0000);
		TftWrite(0x0081,0x0000);
		TftWrite(0x0082,0x0000);
		TftWrite(0x0083,0x0000);
		TftWrite(0x0084,0x0000);
		TftWrite(0x0085,0x0000);
		/* panel control */
		TftWrite(0x0090,0x0010);
		TftWrite(0x0092,0x0600);

		TftWrite(0x0007,0x0133);  //262 or8  Color and display on
		}
	 else if(id==0x9320||id==0x9328||id==0x9321)
	  {
	  	    TftWrite(0x00e5, 0x8000);	
			TftWrite(0x0000, 0x0001);	
			TftWrite(0x0001, 0x0100);
			TftWrite(0x0002, 0x0700);
		#if AM==000       
			TftWrite(0x0003,0x1000);//��Ļ��ת���� TFM=0,TRI=0,SWAP=1,16 bits system interface  swap RGB to BRG���˴�ORG��HWM Ϊ0
		#elif AM==001        
			TftWrite(0x0003,0x1008);      
		#elif AM==010  
		    TftWrite(0x0003,0x1010);        
		#elif AM==011
			TftWrite(0x0003,0x1018);
		#elif AM==100  
			TftWrite(0x0003,0x1020);      
		#elif AM==101  
			TftWrite(0x0003,0x1028);      
		#elif AM==110  
			TftWrite(0x0003,0x1030);      
		#elif AM==111  
			TftWrite(0x0003,0x1038);
		#endif
			TftWrite(0x0004, 0x0000);
			TftWrite(0x0008, 0x0202);	
			TftWrite(0x0009, 0x0000);	
			TftWrite(0x000A, 0x0000);
			TftWrite(0x000C, 0x0000);	
			TftWrite(0x000D, 0x0000);	
			TftWrite(0x000F, 0x0000);	
		//-----Power On sequence-----------------------	
			TftWrite(0x0010, 0x0000);	
			TftWrite(0x0011, 0x0007);	
			TftWrite(0x0012, 0x0000);	
			TftWrite(0x0013, 0x0000);	
			delay_ms(1000);
			TftWrite(0x0010, 0x17B0);	
			TftWrite(0x0011, 0x0007);	
			delay_ms(1000);
			TftWrite(0x0012, 0x013A);	
		delay_ms(1000);
			TftWrite(0x0013, 0x1A00);	
			TftWrite(0x0029, 0x000c);		
		delay_ms(1000);
		//-----Gamma control-----------------------	
			TftWrite(0x0030, 0x0000);	
			TftWrite(0x0031, 0x0505);	
			TftWrite(0x0032, 0x0004);	
			TftWrite(0x0035, 0x0006);	
			TftWrite(0x0036, 0x0707);	
			TftWrite(0x0037, 0x0105);	
			TftWrite(0x0038, 0x0002);	
			TftWrite(0x0039, 0x0707);	
			TftWrite(0x003C, 0x0704);	
			TftWrite(0x003D, 0x0807);	
		//-----Set RAM area-----------------------	
			TftWrite(0x0050, 0x0000);
			TftWrite(0x0051, 0x00EF);
			TftWrite(0x0052, 0x0000);
			TftWrite(0x0053, 0x013F);
			TftWrite(0x0060, 0x2700);
			TftWrite(0x0061, 0x0001);
			TftWrite(0x006A, 0x0000);
		#if AM==000         
			TftWrite(0x0020,0x00ef);//GRAMˮƽ��ʼλ��
			TftWrite(0x0021,0x013f);      
		#elif AM==001
			TftWrite(0x0020,0x00ef);
			TftWrite(0x0021,0x013f);      
		#elif AM==010
			TftWrite(0x0020,0x0000);
			TftWrite(0x0021,0x013f);      
		#elif AM==011
			TftWrite(0x0020,0x0000);
			TftWrite(0x0021,0x013f);       
		#elif AM==100
			TftWrite(0x0020,0x00ef);
			TftWrite(0x0021,0x0000);      
		#elif AM==101  
			TftWrite(0x0020,0x00ef);
			TftWrite(0x0021,0x0000);      
		#elif AM==110
			TftWrite(0x0020,0x0000);
			TftWrite(0x0021,0x0000);      
		#elif AM==111
			TftWrite(0x0020,0x0000);
			TftWrite(0x0021,0x0000);         
		#endif  
		//-----Partial Display Control------------	
			TftWrite(0x0080, 0x0000);	
			TftWrite(0x0081, 0x0000);
			TftWrite(0x0082, 0x0000);
			TftWrite(0x0083, 0x0000);
			TftWrite(0x0084, 0x0000);	
			TftWrite(0x0085, 0x0000);
		//-----Panel Control----------------------
			TftWrite(0x0090, 0x0010);	
			TftWrite(0x0092, 0x0000);
			TftWrite(0x0093, 0x0003);
			TftWrite(0x0095, 0x0110);
			TftWrite(0x0097, 0x0000);	
			TftWrite(0x0098, 0x0000);
		//-----Display on-----------------------	
			TftWrite(0x0007, 0x0173);	
	}
	else if(id==0x4535)
	{
		TftWrite(0X0015 ,0X0030);
		TftWrite(0X009a ,0X0010);
		TftWrite(0X0011 ,0X0020);
		TftWrite(0X0010 ,0X3428);
		TftWrite(0X0012 ,0X0004);
		TftWrite(0X0013 ,0X1050);
		delay_ms(100);
		TftWrite(0X0012 ,0X0014);
		delay_ms(100);
		TftWrite(0X0010 ,0X3420);
		TftWrite(0X0013 ,0X3050);
		delay_ms(100);
		TftWrite(0X0030 ,0X0003);
		TftWrite(0X0031 ,0X0305);
		TftWrite(0X0032 ,0X0004);
		TftWrite(0X0033 ,0X0304);
		TftWrite(0X0034 ,0X0004);
		TftWrite(0X0035 ,0X0303);
		TftWrite(0X0036 ,0X0606);
		TftWrite(0X0037 ,0X0403);
		TftWrite(0X0038 ,0X050f);
		TftWrite(0X0039 ,0X0510);
		delay_ms(100);
		TftWrite(0X0001 ,0X0100);
		TftWrite(0X0002 ,0X0300);
	#if   ID_AM==000       
		TftWrite(0x0003,0x1000);//��Ļ��ת���� TFM=0,TRI=0,SWAP=1,16 bits system interface  swap RGB to BRG���˴�ORG��HWM Ϊ0
	#elif ID_AM==001        
		TftWrite(0x0003,0x1008);      
	#elif ID_AM==010  
	    TftWrite(0x0003,0x1010);        
	#elif ID_AM==011
		TftWrite(0x0003,0x1018);
	#elif ID_AM==100  
		TftWrite(0x0003,0x1020);      
	#elif ID_AM==101  
		TftWrite(0x0003,0x1028);      
	#elif ID_AM==110  
		TftWrite(0x0003,0x1030);      
	#elif ID_AM==111  
		TftWrite(0x0003,0x1038);
	#endif 
		TftWrite(0x0003,0x1018);
		TftWrite(0X0008 ,0X0808);
		TftWrite(0X000a ,0X0008);
		delay_ms(100);
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x0000);//ԭ��0x0000
		TftWrite(0x0050,0x0000);//Horizontal RAM Address Position//HEA=0xAf, HSA=0
		TftWrite(0x0051,0x00EF);
		TftWrite(0x0052,0x0000);
		TftWrite(0x0053,0x013F);//Vertical RAM Address Position//VEA=0xDB, VSA=0  

		TftWrite(0X0060 ,0X2700);
		TftWrite(0X0061 ,0X0001);
		TftWrite(0X0090 ,0X013e);
		TftWrite(0X0092 ,0X010f);
		TftWrite(0X0093 ,0X0001);
		TftWrite(0X00a0 ,0X3000);
		TftWrite(0X00a3 ,0X0010);
		delay_ms(100);
		TftWrite(0X0007 ,0X0001);
		TftWrite(0X0007 ,0X0021);
		TftWrite(0X0007 ,0X0023);
		TftWrite(0X0007 ,0X0033);
		TftWrite(0X0007 ,0X0133);
	#if ID_AM==000         
		TftWrite(0x0020,0x00ef);//GRAMˮƽ��ʼλ��
		TftWrite(0x0021,0x013f);      
	#elif ID_AM==001
		TftWrite(0x0020,0x00ef);
		TftWrite(0x0021,0x013f);      
	#elif ID_AM==010
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x013f);      
	#elif ID_AM==011
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x013f);       
	#elif ID_AM==100
		TftWrite(0x0020,0x00ef);
		TftWrite(0x0021,0x0000);      
	#elif ID_AM==101  
		TftWrite(0x0020,0x00ef);
		TftWrite(0x0021,0x0000);      
	#elif ID_AM==110
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x0000);      
	#elif ID_AM==111
		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x0000);         
	#endif  

		TftWrite(0x0020,0x0000);
		TftWrite(0x0021,0x013f);  

	}
		delay_ms(1000);

  
}

/***************************************************************************
��    �ƣ�void TftClear(unsigned int Color)
��    �ܣ�����Ļ����ָ������ɫ
��ڲ����������ɫֵ
���ڲ������� 
˵    ����
���÷�����TftClear(RED);
***************************************************************************/
void TftClear(unsigned int Color)
{
  	unsigned long index = 0;

	TftWrite(0x0050,0x00);
	TftWrite(0x0051,239);
	TftWrite(0x0052,0x00);
	TftWrite(0x0053,319);
	TftWrite(0x0020,0x0000);
	TftWrite(0x0021,0x0000);  
	TftWrite16(0x0022);    

  	for(index = 0; index < 76800; index++)
	{
		Tft_WR_DATA16(Color);
   
	} 
 
}

/***************************************************************************
��    �ƣ�void TftWR_SingleStr(unsigned char inputdata,unsigned int color,unsigned int xcolor)
��    �ܣ���ʾһ��8x16�����ascii�ַ�
��ڲ�����inputdata   �ַ�
          color       �ַ�����ɫ
          xcolor      �ַ�������ɫ
���ڲ������� 
˵    ����
���÷�����TftWR_SingleStr('a',RED,BLACK);
***************************************************************************/
void TftWR_SingleStr(unsigned char inputdata,unsigned int color,unsigned int xcolor)
{

	unsigned char avl,i,n;
	TftWrite16(0x0022);  
	for (i=0;i<16;i++)
	{ 
	  avl=(english[inputdata-32][i]);
	  for (n=0;n<8;n++)
	   {
	     if(avl&0x80) Tft_WR_DATA16(color);  //�ַ���ɫ
	         else Tft_WR_DATA16(xcolor);     //������ɫ
       
	     avl<<=1;
	   }
	}
	}


/***************************************************************************
��    �ƣ�void TftWR_Str(unsigned int x,unsigned int y,unsigned char *s,unsigned int color,unsigned int xcolor)
��    �ܣ���ָ��������ʾһ��8x16�����ascii�ַ�
��ڲ�����x           ������
          y           ������
          inputdata   �ַ�
          color       �ַ�����ɫ
          xcolor      �ַ�������ɫ
���ڲ������� 
˵    ����
���÷�����TftWR_SingleStr(100,200,'abcdefg',RED,BLACK);
***************************************************************************/
void TftWR_Str(unsigned int x,unsigned int y,unsigned char *s,unsigned int color,unsigned int xcolor)
{
	unsigned int k=0;
	while (*s) 
	{
		 Tft_SetBackground(y,x+k,15,8);
		 TftWR_SingleStr( *s,color,xcolor);
		 k=k+8;
		 s++;

	}

}  

/***************************************************************************
��    �ƣ�void Tft_SetBackground(unsigned int StartX,unsigned int StartY,unsigned int LongX,unsigned int LongY)
��    �ܣ����ô�������
��ڲ�����StartX           ����ʼ����
          StartY           ����ʼ����
          LongX            �г���
          LongY            �г���
���ڲ������� 
˵    ����
���÷�����Tft_SetBackground(0,0,200,200);
***************************************************************************/
void Tft_SetBackground(unsigned int StartX,unsigned int StartY,unsigned int LongX,unsigned int LongY)
{
  
	#if AM==000    
		Tft_SetCursor(StartX+LongX-1,312-StartY+LongY-1);

	#elif AM==001
		Tft_SetCursor(StartX+LongX-1,312-StartY+LongY-1);
     
	#elif AM==010
		Tft_SetCursor(StartX,312-StartY+LongY-1);
     
	#elif AM==011 
		Tft_SetCursor(StartX,312-StartY+LongY-1);
     
	#elif AM==100
		Tft_SetCursor(StartX+LongX-1,312-StartY);     
     
	#elif AM==101
		Tft_SetCursor(StartX+LongX-1,312-StartY);     
     
	#elif AM==110
		Tft_SetCursor(StartX,312-StartY); 
     
	#elif AM==111
		Tft_SetCursor(StartX,312-StartY);  
     
	#endif
     
	TftWrite(0x0050,StartX);
	TftWrite(0x0051,StartX+LongX-1);
	TftWrite(0x0052,312-StartY);
	TftWrite(0x0053,312-StartY+LongY-1);
}

/***************************************************************************
��    �ƣ�void Tft_SetCursor(unsigned int Xpos, unsigned int Ypos)
��    �ܣ�������Ļ����
��ڲ�����Xpos           ������
          Ypos           ������
���ڲ������� 
˵    ����
���÷�����Tft_SetCursor(0,0);
***************************************************************************/
void Tft_SetCursor(unsigned int Xpos, unsigned int Ypos)
{
 
	TftWrite(0x20, Xpos);
	TftWrite(0x21, Ypos);
}
