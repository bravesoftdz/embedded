#include"systemInit.h"
//#include <hidef.h>
#include <stdio.h> 
#include <math.h>
//#include <MC9S12XS128.h>        /* common defines and macros */
//#include "derivative.h"      /* derivative-specific definitions */
#include "nAsciidot.h"

#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xCF


/*
����SPIʹ��˵����
VBT ���ڲ�DC-DC��ѹ��3.3~4.3V�����ʹ��5V��ѹ��Ϊ���������һ��100~500ŷ�ĵ���
VCC ���ڲ��߼���ѹ 1.8~6V
PEN �߼���ѹʹ�ܿ��أ��ߵ�ƽΪ�򿪣�����MCU���ƻ�ֱ�ӽӵ�VCC
GND ��

BS0 �ߵ�ƽ
BS1 �͵�ƽ
BS2 �͵�ƽ
CS  �͵�ƽ �����Ҫ����MCU��SCLK��MOSI�ܽţ�CS��MCU����

DC  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ
RES ������ģ���ϵ縴λ������MCU���ƣ�Ӧ��MCUͬʱ�ϵ磩
RD  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ
RW  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ
RD  �͵�ƽ ��Ҳ�����գ��������Ϊ�͵�ƽ

D0��SCLK�� ��ʱ�ӽţ���MCU����
D1��MOSI�� ����������������ݽţ���MCU����
D2 ����

D3-D7 �� �͵�ƽ �� Ҳ�����գ��������Ϊ�͵�ƽ

WriteCommand() WriteData()�ڲ���������ʱ����uDelay()�����ڵ���ʱ����ٶ�,
�ɸ���MCU���ٶȵ���uDelay()�Ĳ�����ʵ�ֵ����������ٶ�

*/

/*----------------------------------------------------------------------------
���º�����Ӳ���й�
----------------------------------------------------------------------------*/

void PortInit(void)
{
   //�����������룬������SCLK��D0����MOSI��D1���������ܽž��ж�����������

}
void SetSclk(unsigned char val)
{
    if (val==0)
    {
        // �����������룬����SCLK��D0���ܽ�Ϊ�͵�ƽ
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2,0);
    }
    else
    {
        // �����������룬����SCLK��D0���ܽ�Ϊ�ߵ�ƽ
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2,~0);
    }
}


void SetMosi(unsigned char val)
{
    if (val==0)
    {
        // �����������룬����MOSI��D1���ܽ�Ϊ�͵�ƽ
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,0);	
    }
    else
    {
        // �����������룬����MOSI��D1���ܽ�Ϊ�ߵ�ƽ
		GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3,~0);	
    }
}


/*----------------------------------------------------------------------------
���º�����Ӳ���޹أ���Ϊ��SSD0306�Ŀ��ƺ���
----------------------------------------------------------------------------*/
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

void WriteCommand(unsigned char Data)
{
    unsigned char i;

    SetSclk(0);
    SetMosi(0);
    uDelay(15);
    SetSclk(1);
    uDelay(15);

    for (i=0; i<8; i++)
    {
        SetSclk(0);
        if ((Data&0x80)>>7)
        {
            SetMosi(1);
        }
        else
        {
            SetMosi(0);
        }
        Data = Data << 1;
        uDelay(15);
        SetSclk(1);
        uDelay(15);
    }
}


void WriteData(unsigned char Data)
{
    unsigned char i;

    SetSclk(0);
    SetMosi(1);
    uDelay(15);
    SetSclk(1);
    uDelay(15);

    for (i=0; i<8; i++)
    {
        SetSclk(0);
        if ((Data&0x80)>>7)
        {
            SetMosi(1);
        }
        else
        {
            SetMosi(0);
        }
        Data = Data << 1;
        uDelay(15);
        SetSclk(1);
        uDelay(15);
    }

}

void SetStartColumn(unsigned char d)
{
	WriteCommand(0x00+d%16);		// Set Lower Column Start Address for Page Addressing Mode
						//   Default => 0x00
	WriteCommand(0x10+d/16);		// Set Higher Column Start Address for Page Addressing Mode
						//   Default => 0x10
}

void SetAddressingMode(unsigned char d)
{
	WriteCommand(0x20);			// Set Memory Addressing Mode
	WriteCommand(d);			//   Default => 0x02
						//     0x00 => Horizontal Addressing Mode
						//     0x01 => Vertical Addressing Mode
						//     0x02 => Page Addressing Mode
}

void SetColumnAddress(unsigned char a, unsigned char b)
{
	WriteCommand(0x21);			// Set Column Address
	WriteCommand(a);			//   Default => 0x00 (Column Start Address)
	WriteCommand(b);			//   Default => 0x7F (Column End Address)
}

void SetPageAddress(unsigned char a, unsigned char b)
{
	WriteCommand(0x22);			// Set Page Address
	WriteCommand(a);			//   Default => 0x00 (Page Start Address)
	WriteCommand(b);			//   Default => 0x07 (Page End Address)
}

void SetStartLine(unsigned char d)
{
	WriteCommand(0x40|d);			// Set Display Start Line
						//   Default => 0x40 (0x00)
}

void SetContrastControl(unsigned char d)
{
	WriteCommand(0x81);			// Set Contrast Control
	WriteCommand(d);			//   Default => 0x7F
}

void Set_Charge_Pump(unsigned char d)
{
	WriteCommand(0x8D);			// Set Charge Pump
	WriteCommand(0x10|d);			//   Default => 0x10
						//     0x10 (0x00) => Disable Charge Pump
						//     0x14 (0x04) => Enable Charge Pump
}

void Set_Segment_Remap(unsigned char d)
{
	WriteCommand(0xA0|d);			// Set Segment Re-Map
						//   Default => 0xA0
						//     0xA0 (0x00) => Column Address 0 Mapped to SEG0
						//     0xA1 (0x01) => Column Address 0 Mapped to SEG127
}

void Set_Entire_Display(unsigned char d)
{
	WriteCommand(0xA4|d);			// Set Entire Display On / Off
						//   Default => 0xA4
						//     0xA4 (0x00) => Normal Display
						//     0xA5 (0x01) => Entire Display On
}

void Set_Inverse_Display(unsigned char d)
{
	WriteCommand(0xA6|d);			// Set Inverse Display On/Off
						//   Default => 0xA6
						//     0xA6 (0x00) => Normal Display
						//     0xA7 (0x01) => Inverse Display On
}

void Set_Multiplex_Ratio(unsigned char d)
{
	WriteCommand(0xA8);			// Set Multiplex Ratio
	WriteCommand(d);			//   Default => 0x3F (1/64 Duty)
}

void Set_Display_On_Off(unsigned char d)
{
	WriteCommand(0xAE|d);			// Set Display On/Off
						//   Default => 0xAE
						//     0xAE (0x00) => Display Off
						//     0xAF (0x01) => Display On
}

void SetStartPage(unsigned char d)
{
	WriteCommand(0xB0|d);			// Set Page Start Address for Page Addressing Mode
						//   Default => 0xB0 (0x00)
}

void Set_Common_Remap(unsigned char d)
{
	WriteCommand(0xC0|d);			// Set COM Output Scan Direction
						//   Default => 0xC0
						//     0xC0 (0x00) => Scan from COM0 to 63
						//     0xC8 (0x08) => Scan from COM63 to 0
}

void Set_Display_Offset(unsigned char d)
{
	WriteCommand(0xD3);			// Set Display Offset
	WriteCommand(d);			//   Default => 0x00
}

void Set_Display_Clock(unsigned char d)
{
	WriteCommand(0xD5);			// Set Display Clock Divide Ratio / Oscillator Frequency
	WriteCommand(d);			//   Default => 0x80
						//     D[3:0] => Display Clock Divider
						//     D[7:4] => Oscillator Frequency
}

void Set_Precharge_Period(unsigned char d)
{
	WriteCommand(0xD9);			// Set Pre-Charge Period
	WriteCommand(d);			//   Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
						//     D[3:0] => Phase 1 Period in 1~15 Display Clocks
						//     D[7:4] => Phase 2 Period in 1~15 Display Clocks
}

void Set_Common_Config(unsigned char d)
{
	WriteCommand(0xDA);			// Set COM Pins Hardware Configuration
	WriteCommand(0x02|d);			//   Default => 0x12 (0x10)
						//     Alternative COM Pin Configuration
						//     Disable COM Left/Right Re-Map
}

void Set_VCOMH(unsigned char d)
{
	WriteCommand(0xDB);			// Set VCOMH Deselect Level
	WriteCommand(d);			//   Default => 0x20 (0.77*VCC)
}

void Set_NOP(void)
{
	WriteCommand(0xE3);			// Command for No Operation
}

/******************************************************************************
  * @function name : DisplayArea
  * @brief  Display Area
  * @param  :
  * @retval :
  */
void FillArea(unsigned char spage, unsigned char epage,
                 unsigned char scolumn, unsigned char ecolumn,
                 unsigned char pt)
{
    unsigned char i = 0;
    unsigned char j = 0;
    unsigned char h = 0;
    unsigned char w = 0;

    h = epage - spage + 1;
    w = ecolumn - scolumn;

    while ( j<h )
    {
        SetStartPage(spage + j);
        SetStartColumn(scolumn);
        for (i=0; i<w; i++)
        {
              WriteData(pt);
        }

        j++;
    }
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Frame (Full Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void CheckOutline(void)
{		
    unsigned char i,j;
    FillArea(0,7,0,128,0);

    SetStartPage(0x00);
    SetStartColumn(XLevel);

    for(i=0;i<Max_Column;i++)
    {
        WriteData(0x01);
    }

    SetStartPage(0x01);
    SetStartColumn(XLevel);

    for(i=0;i<Max_Column;i++)
    {
        WriteData(0x80);
    }

    SetStartPage(0x02);
    SetStartColumn(XLevel);

    for(i=0;i<Max_Column;i++)
    {
        WriteData(0x01);
    }

    SetStartPage(0x07);
    SetStartColumn(XLevel);

    for(i=0;i<Max_Column;i++)
    {
        WriteData(0x80);
    }

    for(i=0;i<8;i++)
    {
        SetStartPage(i);

        for(j=0;j<Max_Column;j+=(Max_Column-1))
        {
            SetStartColumn(XLevel+j);
            WriteData(0xFF);
        }
    }
}

void OledInit(void)
{	
	Delay(5);
    //���ϵ絽���濪ʼ��ʼ��Ҫ���㹻��ʱ�䣬���ȴ�RC��λ���
    Set_Display_On_Off(0x00);		// Display Off (0x00/0x01)
    Set_Display_Clock(0x80);		// Set Clock as 100 Frames/Sec
    Set_Multiplex_Ratio(0x3F);		// 1/64 Duty (0x0F~0x3F)
    Set_Display_Offset(0x00);		// Shift Mapping RAM Counter (0x00~0x3F)
    SetStartLine(0x00);			    // Set Mapping RAM Display Start Line (0x00~0x3F)
    Set_Charge_Pump(0x04);		    // Enable Embedded DC/DC Converter (0x00/0x04)
    SetAddressingMode(0x02);		// Set Page Addressing Mode (0x00/0x01/0x02)
    Set_Segment_Remap(0x01);		// Set SEG/Column Mapping (0x00/0x01)
    Set_Common_Remap(0x08);			// Set COM/Row Scan Direction (0x00/0x08)
    Set_Common_Config(0x10);		// Set Sequential Configuration (0x00/0x10)
    SetContrastControl(Brightness);	// Set SEG Output Current
    Set_Precharge_Period(0xF1);		// Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    Set_VCOMH(0x40);			   // Set VCOM Deselect Level
    Set_Entire_Display(0x00);		// Disable Entire Display On (0x00/0x01)
    Set_Inverse_Display(0x00);		// Disable Inverse Display On (0x00/0x01)
    FillArea(0,7,0,128,0);			// Clear Screen
	 
    Set_Display_On_Off(0x01);		// Display On (0x00/0x01)
}

/*----------------------------------------------------------------------------
���º���ΪӦ�ú���
----------------------------------------------------------------------------*/
/******************************************************************************
  * @function name : Display8x16Str
  * @brief  Display8x16Str
  * @param  :
  * @retval :
  */
void Display8x16Str(unsigned char page, unsigned char column, unsigned char *str) //8x16Ascii�ַ�
{
    unsigned char i = 0;
    //unsigned char temp = 0;
    unsigned int padd= 0;
    while(*str != '\0')
    {
        SetStartPage(page);
        SetStartColumn(column);
        padd = (*str-32)*16;
        for (i=0; i<8; i++)
        {
             WriteData(nAsciiDot8x16[padd+i]);
        }

        SetStartPage(page+1);
        SetStartColumn(column);
        for (i=8; i<16; i++)
        {
           WriteData(nAsciiDot8x16[padd+i]);
        }
        str++;
        column += 8;
   }
}

void DisplayChinese(unsigned char page, unsigned char column, unsigned int location)//16x16�����ַ�
{ 	
		unsigned char i = 0;
		location=location*32;
        SetStartPage(page);
        SetStartColumn(column);
        for (i=0; i<16; i++)
        {
             WriteData(GB16X16[location+i]);
        }
        SetStartPage(page+1);
        SetStartColumn(column);
        for (i=16; i<32; i++)
        {
           WriteData(GB16X16[location+i]);
        }
}
  
void Displaypicture1(unsigned char page ,unsigned char column)  //���ģ�ͼƬ��
{ 	
	unsigned char i = 0;
    unsigned char const picture1[]=
	{
	0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x80,0xC0,//
	0xC0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x0F,0x1F,0x3F,0x7F,//
	0xFF,0xFF,0xFF,0xFE,0xFE,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x00,0x00,0x00,//
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x07,0x03,0x01,0x00,//
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//δ�����ļ�0
	};
        SetStartPage(page);
        SetStartColumn(column);
        for (i=0; i<24; i++){WriteData(picture1[i]);}
		SetStartPage(page+1);
        SetStartColumn(column);
		for (i=24; i<48; i++){WriteData(picture1[i]);}
		SetStartPage(page+2);
        SetStartColumn(column);
		for (i=48; i<72; i++){WriteData(picture1[i]);}
}
void Displaypictureclear1(unsigned char page ,unsigned char column)  //����(ͼƬ���)
{ 	
	unsigned char i = 0;
        SetStartPage(page);
        SetStartColumn(column);
        for (i=0; i<24; i++){WriteData(0x00);}
		SetStartPage(page+1);
        SetStartColumn(column);
		for (i=24; i<48; i++){WriteData(0x00);}
		SetStartPage(page+2);
        SetStartColumn(column);
		for (i=48; i<72; i++){WriteData(0x00);}
}	

void TestMain(void)
{	

	unsigned char i = 0;
    OledInit();
	while(1)
   {  	
   		if(i==0)
		{
		i=1;
		Displaypictureclear1(5 ,52);
		Displaypicture1(0,0);
		Displaypicture1(0,104);
		}
		else
		{
		i=0;
		Displaypictureclear1(0,0);
		Displaypictureclear1(0,104);
		Displaypicture1(5,52);
		}
	    DisplayChinese(0,60,5);	//��
		DisplayChinese(3,30,0);	//��
		DisplayChinese(3,60,1);	//��
		DisplayChinese(3,90,2);	//��
		DisplayChinese(6,0,4);	//��
		DisplayChinese(6,112,6);//��
		//Display8x16Str(3,85, "!!!!");
        Delay(10);
    }
}
