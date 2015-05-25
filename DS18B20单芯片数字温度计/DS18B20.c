/***********ds18b20�ӳ���*************************/

/***********ds18b20�ӳ��Ӻ���������11.0592MHz ��*******/

void delay_18B20(unsigned int i)
{
while(i--);
}

/**********ds18b20��ʼ������**********************/

void Init_DS18B20(void)
{
unsigned char x=0;
DQ = 1;          //DQ��λ
delay_18B20(80); //������ʱ
DQ = 0;          //��Ƭ����DQ����
delay_18B20(800); //��ȷ��ʱ ���� 480us
DQ = 1;          //��������
delay_18B20(140);
x=DQ;   delay_18B20(200);
}

/***********ds18b20��һ���ֽ�**************/

unsigned char ReadOneChar(void)
{
uchar i=0;
uchar dat = 0;
for (i=8;i>0;i--)
{
    DQ = 0; // �������ź�
    dat>>=1;
    DQ = 1; // �������ź�
    if(DQ)
    dat|=0x80;
    delay_18B20(40);     //40
}
   return(dat);
}

/*************ds18b20дһ���ֽ�****************/

void WriteOneChar(uchar dat)
{
   unsigned char i=0;
   for (i=8; i>0; i--)
   {
   DQ = 0;
    DQ = dat&0x01;
    delay_18B20(50); //50
    DQ = 1;
    dat>>=1;
}
}

/**************��ȡds18b20��ǰ�¶�************/

unsigned int ReadTemp(void)
{
unsigned char a=0;
unsigned char b=0;
unsigned int temp_value=0;

Init_DS18B20();
WriteOneChar(0xCC);     

WriteOneChar(0x44);  

delay_18B20(1000);      

Init_DS18B20();
WriteOneChar(0xCC);  
WriteOneChar(0xBE);  

delay_18B20(1000);

a=ReadOneChar();    //��ȡ�¶�ֵ��λ
b=ReadOneChar();      //��ȡ�¶�ֵ��λ

temp_value = b<<8;
temp_value |= a;
return temp_value;
       
}