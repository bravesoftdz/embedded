#ifndef _oled_H_
#define _oled_H_
#include <iom16v.h>
#include <macros.h>
#define uint unsigned int
#define uchar unsigned char
#define  LCD_CLK_1();      (PORTD |=  BIT(3));   
#define  LCD_CLK_0();      (PORTD &= ~BIT(3));
   
#define  LCD_MOSI_1();      (PORTB |=  BIT(5));   
#define  LCD_MOSI_0();      (PORTB &= ~BIT(5));

#define  LCD_CS_1();      (PORTB |=  BIT(6));   
#define  LCD_CS_0();      (PORTB &= ~BIT(6));

#define  LCD_DC_1();      (PORTB |=  BIT(7));   
#define  LCD_DC_0();      (PORTB &= ~BIT(7));
void OLED_Init(void) ;                             //��ʼ��
void LCD_Fill(uchar bmp_dat);				      //ȫ������
void LCD_P6x8Str(uchar x,uchar y,uchar ch[]);    //ASIIC
void LCD_shuzi(uchar x,uchar y,uchar ch);	    //��ʾ����
#endif