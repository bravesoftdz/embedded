#include<reg52.h>

#define uchar unsigned  char
#define uint  unsigned  int
sbit RS=P1^5;
sbit RW=P1^6;
sbit E=P1^7;                        
sbit PSB=P1^4;   //Ӳ���ϵĴ���,����ѡ��λ,�˿������õ��ǲ���,��λ��1Ϊ����




uchar code table_1[]={"У԰һ��ͨ�з�"};
uchar code table_2[]={"����:"};
uchar code table_3[]={"����:"};
uchar code table_4[]={"���:"};

uchar code table_5[]={"."};
uchar code table_6[]={"Ԫ"};

uchar code table_7[]={"("};
uchar code table_8[]={")"};

uchar code table_9[]={"                "};

uchar code table_a[]={"���ݺ��컶ӭ��"};
uchar code table_b[]={"��ˢ��"};
uchar code table_c[]={"�����!"};
uchar code table_d[]={"�����Ƶ��ģ��!"};
/////��ʱ����//////////////////////////////////
void delay1(unsigned int z)
{
	unsigned int x,y;
	for(x=z;x>0;x--)
	for(y=110;y>0;y--);	
}
///////////////////////////////////////////////
//////д����////////////////////////////////////
void WriteCommand(uchar a)
{
	 E=0;  //1��ȡ��Ϣ��1-0�½���ִ��ָ��
	 RS=0;  //0=дָ�1=д����
	 RW=0;  //0=дָ������ݣ�1=��LCD��Ϣ
	 E=1;  //����Ϣ
	 P2=a;  //дָ��
	 delay1(5);           //��ʱ 
	 E=0;    //ִ��ָ��
	 delay1(5);           //��ʱ 
}
//////////////////////////////////////////////////


//////д����//////////////////////////////////////
void WriteData(uchar b)  
{

     E=0;   //ִ��ָ��
	 RS=1;   //д����
	 RW=0;   //д����
	 E=1;   //��ȡ��Ϣ
	 P2=b;   //д����
	 delay1(5);      //��ʱ 
	 E=0;     //ִ��ָ��
	 delay1(5);      //��ʱ 
}
//////////////////////////////////////////////////



///////��ʼ��////////////////////////////////////
void initial_LCD()      
{   

   	 PSB=1;      //ѡ��Ϊ����
	 WriteCommand(0x01);  //����
	 WriteCommand(0x30);  //�������á�8�ֽڽ��棬����ָ�����0011 x0xx��
	 WriteCommand(0x0c);  //��ʾ���á�������ʾ����겻��ʾ����겻���򡣣�0000 1110��
	 WriteCommand(0x06);   //���뷽ʽ���á�������ƣ���ַλ��1���������ơ���0000 0110)
	// WriteCommand(0x14);   //������ơ�
}
/////////////////////////////////////////////////



///////Ҫ��ʾ������//////////////////////////////

void DispalyLcd()
{
	 unsigned char i;
	 WriteCommand(0x81);  		//ҳ��ַ,��80��ʼ,����μ�����//
	 for (i=1;i<=14;i++)		//��һ����ʾ����7������,1������Ϊ2���ֽ�,��������Ҫ����14���ֽ�//
	 WriteData(table_1[i-1])  ;   

	 WriteCommand(0x90);  		//ҳ��ַ,��92��ʼ,����μ�����//
	 for (i=1;i<=5;i++)		
	 WriteData(table_2[i-1])  ; 


	 WriteCommand(0x88);  		//ҳ��ַ,��88��ʼ,����μ�����//
	 for (i=1;i<=5;i++)		    //������
	 WriteData(table_3[i-1])  ; 


	 WriteCommand(0x98);  	
	 for (i=1;i<=16;i++)		
	 WriteData(table_9[i-1])  ; 




	 WriteCommand(0x98);  		//ҳ��ַ,��88��ʼ,����μ�����//
	 for (i=1;i<=5;i++)		
	 WriteData(table_4[i-1])  ; 

}
/////////////////////////////////////////////////////

//////////��ֵ��ת����ʽ  \ ��ʾ��ֵ ////////////////

void LCD_Data(uchar LCDbyte )
{
	 unsigned char count;
	 count=(LCDbyte&0xf0)>>4;
	 if (count>0x9) WriteData(count%9+0x40);
	 else WriteData(count+0x30);
	 count=LCDbyte&0x0f;
	 if (count>9) WriteData(count%9+0x40);
	 else WriteData(count+0x30);
}
/////////////////////////////////////////////////////

void displaymun(uchar temp1,uchar temp2,uchar temp3,uchar temp4,uchar temp5,uchar buff1,uchar buff2,uchar buff3)
{
		uchar i;
		WriteCommand(temp1);
		LCD_Data(buff1); 

		WriteCommand(temp2);
		LCD_Data(buff2); 


		 WriteCommand(temp4);  	//С����
		 for (i=1;i<=1;i++)		
		 WriteData(table_5[i-1])  ;

		WriteCommand(temp3);
		LCD_Data(buff3); 

		 WriteCommand(temp5);  	//Ԫ
		 for (i=1;i<=2;i++)		
		 WriteData(table_6[i-1])  ; 
	
}

void dis_Request1()
{
		uchar i;
		 WriteCommand(0x9b); 
		 for (i=1;i<=1;i++)		
		 WriteData(table_7[i-1])  ;

		 WriteCommand(0x9c); 
		 for (i=1;i<=1;i++)		
		 WriteData(table_8[i-1])  ;
}

void dis_Request2()
{
		uchar i;
		 WriteCommand(0x9a); 
		 for (i=1;i<=1;i++)		
		 WriteData(table_7[i-1])  ;

		 WriteCommand(0x9d); 
		 for (i=1;i<=1;i++)		
		 WriteData(table_8[i-1])  ;
}

void dis_Request3()
{
		uchar i;
		 WriteCommand(0x99); 
		 for (i=1;i<=1;i++)		
		 WriteData(table_7[i-1])  ;

		 WriteCommand(0x9e); 
		 for (i=1;i<=1;i++)		
		 WriteData(table_8[i-1])  ;
}
void DispalyLcd1()
{
	 unsigned char i;
	 WriteCommand(0x98);  	
	 for (i=1;i<=16;i++)		
	 WriteData(table_9[i-1])  ; 
}


void DispalyLcd_home()
{
	 unsigned char i;
	 WriteCommand(0x81);  	//dis  ���ݺ��컶ӭ��
	 for (i=1;i<=14;i++)	
	 WriteData(table_a[i-1])  ;   

 

	 WriteCommand(0x93);  		//dis:��ˢ��
	 for (i=1;i<=6;i++)		
	 WriteData(table_b[i-1])  ; 

	 
}

void dis_passerror()
{
	 unsigned char i;

	 WriteCommand(0x88);  	
	 for (i=1;i<=16;i++)		
	 WriteData(table_9[i-1])  ; 
	 DispalyLcd1();

	 WriteCommand(0x9a);  		
	 for (i=1;i<=7;i++)		
	 WriteData(table_c[i-1])  ; 	
}

void DispalyLcd_RF()
{
	 unsigned char i;
	 WriteCommand(0x80);  	
	 for (i=1;i<=15;i++)	
	 WriteData(table_d[i-1])  ;   

	 
}
