#ifndef __DS18B20_H__
#define __DS18B20_H__
//20090101�޸�
sbit DQ = P2^4;   //����ͨ�Ŷ˿� 
bit flag_Negative_number = 0;//������־


unsigned char wl=0,wh=0;
//float  temper=0;
unsigned int temper=0;

//����22MHz  
void delay_18B20(unsigned int i)
{
 	while(i--);
}



//��һ���ֽ�  
ReadOneChar(void)
{
	unsigned char i=0;
	unsigned char dat=0;
	for (i=8;i>0;i--)
	 {
		  DQ = 0; // �������ź�
		  dat>>=1;
		  DQ = 1; // �������ź�
		  if(DQ)
		  dat|=0x80;
		  delay_18B20(60);
	 }
 	return(dat);
}

//дһ���ֽ�  
WriteOneChar(unsigned char dat)
{
 unsigned char i=0;
 for (i=8; i>0; i--)
 {
  DQ = 0;
  DQ = dat&0x01;
  delay_18B20(60);
  DQ = 1;
  dat>>=1;
 }
}

//��ʼ������
Init_DS18B20(void) 
  {
	 //unsigned char x=0;
	 DQ = 1;          //DQ��λ
	 delay_18B20(5);  //������ʱ
	 DQ = 0;          //��Ƭ����DQ����
	 delay_18B20(150); //��ȷ��ʱ ���� 480us
	 DQ = 1;          //��������
	 delay_18B20(150);	

  }

//��ȡ�¶�
ReadTemperature(void)
{
  
    EA = 0;		 
    Init_DS18B20();
    WriteOneChar(0xCC); //����������кŵĲ���
    WriteOneChar(0x44); // �����¶�ת��
    delay_18B20(5000);
   // delay_18B20(5000);

    Init_DS18B20();
    WriteOneChar(0xCC); //����������кŵĲ���
    WriteOneChar(0xBE); //��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�
    wl=ReadOneChar();
    wh=ReadOneChar(); 
    temper=wh;
    temper<<=8;
    temper=temper|wl;	
	 //temper=((wh*256)+wl)*0.0625;	 
    flag_Negative_number = 0;
    if(temper>0x0fff) 
     {
	   temper=~temper+1;
	   flag_Negative_number = 1;
	   //disc(6,2,hen);
      }


     //18b20��t=d*0.0625
    // t = t*5; //��Чλ��С�����2λ��
	 ///t = temp*0.0625;
    // temper = t*10+0.5;
	// temper = temper*0.0625;
	 
	  temper=((temper+1)*0.0625)*10;
	 
     EA = 1;
   return(temper);	  

}
#endif
