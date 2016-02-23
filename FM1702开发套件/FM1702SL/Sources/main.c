/* ###################################################################
**     Filename    : main.c
**     Project     : FM1702SL
**     Processor   : MKL04Z32VLF4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-02-23, 22:25, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "RST.h"
#include "NSS.h"
#include "MOSI.h"
#include "SCK.h"
#include "MISO.h"
#include "AS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "main.h"
#include "slrc1702.h"
#include "iso14443a.h"

unsigned char g_bReceOk;                                              //正确接收到上位机指令标志
unsigned char g_bRc1702Ok;                                             //RC1702复位正常标志


unsigned int  g_cReceNum;                                   //接收到上位机的字节数
unsigned int  g_cCommand;                              //接收到的命令码
unsigned char g_cSNR[4];                               //M1卡序列号
unsigned char g_cIcdevH;                                    //设备标记
unsigned char g_cIcdevL;                                    //设备标记
unsigned char g_cFWI;                                       //
unsigned char g_cCidNad;                                    //
unsigned char g_cReceBuf[64];                         //和上位机通讯时的缓冲区

LDD_TDeviceData *bitRSTPtr;
LDD_TDeviceData *bitNSSPtr;
LDD_TDeviceData *bitMOSIPtr;
LDD_TDeviceData *bitSCKPtr;
LDD_TDeviceData *bitMISOPtr;
LDD_TError Error;
LDD_TDeviceData *AS1Ptr;

///////////////////////////////////////////////////////////////////
//////
///////////////////////////////////////////////////////////////////
void Comsond()
{
	  	    	g_cReceBuf[0]=1;         //contact
		    	g_cReceBuf[1]=0;
				AnswerOk();
//		    	BELL       = 0;
//				led =0;
		    	DelayMs(100);
//				led =1;
//		    	BELL       = 1;

}


/////////////////////////////////////////////////////////////////////
//系统初始化
/////////////////////////////////////////////////////////////////////
void InitializeSystem()
{
//    TMOD &= 0x0F;
//    TMOD |= 0x21;
//    PCON |= 0x80;
//    SCON  = 0x50;
//    TH1 = TL1 = BOUND9600; 	  //默认波特率为9600
//    TR1=1;
//
//    P0 = P1 = P2 = P3 = 0xFF;
//    IE |= 0x90;

	bitRSTPtr = RST_Init((LDD_TUserData *)NULL);
	bitNSSPtr = NSS_Init((LDD_TUserData *)NULL);
	bitMOSIPtr = MOSI_Init((LDD_TUserData *)NULL);
	bitSCKPtr = SCK_Init((LDD_TUserData *)NULL);
	bitMISOPtr = MISO_Init((LDD_TUserData *)NULL);
	AS1Ptr = AS1_Init((LDD_TUserData *)NULL);
}

/////////////////////////////////////////////////////////////////////
//初始化fm1702
/////////////////////////////////////////////////////////////////////
void Rc1702Ready()
{
    char status;
    DelayMs(100);
    DelayMs(100);
	DelayMs(100);
    DelayMs(100);
    DelayMs(100);
    DelayMs(100);
    DelayMs(100);

    status = PcdReset();
    if(status != MI_OK)
    {
        DelayMs(10);
        status = PcdReset();
    }
    if(status != MI_OK)
    {
        DelayMs(10);
        status = PcdReset();
    }
    if(status == MI_OK)
    {
        g_bRc1702Ok = 1;

//        BELL       = 0;                //蜂鸣器响二声，表示fm1702复位成功
		DelayMs(100);
//		BELL       = 1;
		DelayMs(200);
//        BELL       = 0;
		DelayMs(100);
//		BELL       = 1;
    }
}



/////////////////////////////////////////////////////////////////////
//响应上位机发送的寻A卡命令
/////////////////////////////////////////////////////////////////////
void ComRequestA()
{
	char status;
	status = PcdRequest(g_cReceBuf[1], &g_cReceBuf[2]);
	if (status != MI_OK)
	{    status = PcdRequest(g_cReceBuf[1], &g_cReceBuf[2]);   }
    if (status != MI_OK)
	  {
	g_cReceBuf[0]=1;
	g_cReceBuf[1]=status;
	 AnswerOk();
	 return;
	  }

	  if(g_cReceBuf[2]==2)
	      g_cCidNad=mifarepro;     // Mifare Pro 卡
		 else  if(g_cReceBuf[2]==4)
			  g_cCidNad=mifare1;       // Mifare One 卡
				else   if(g_cReceBuf[2]==16)
				       g_cCidNad=mifarelight;   // Mifare Light 卡
					 else    	g_cCidNad=unknowncard;

			g_cReceBuf[0]=3;
			g_cReceBuf[1]=status;


	 AnswerOk();


}

/////////////////////////////////////////////////////////////////////
//响应上位机发送的A卡防冲撞命令
/////////////////////////////////////////////////////////////////////
void ComAnticoll()
{
	char status;
	status=PcdAnticoll(&g_cSNR);
    if (status!=MI_OK )
    {
	 g_cReceBuf[0]=1;
	g_cReceBuf[1]=status;
	 AnswerOk();
	 return;
	 }
	 g_cReceBuf[2]=g_cSNR[0];
	 g_cReceBuf[3]=g_cSNR[1];
	 g_cReceBuf[4]=g_cSNR[2];
	 g_cReceBuf[5]=g_cSNR[3];
			g_cReceBuf[0]=5;
			g_cReceBuf[1]=status;
    AnswerOk();
}

/////////////////////////////////////////////////////////////////////
//响应上位机发送的A卡锁定命令
/////////////////////////////////////////////////////////////////////
void ComSelect()
{
char status;
	status=PcdSelect(g_cSNR, &g_cReceBuf[2]);
    if (status!=MI_OK)
    {

		g_cReceBuf[0]=1;
		g_cReceBuf[1]=status;
	    AnswerOk();
		return;
	}
            g_cReceBuf[0]=3;
			g_cReceBuf[1]=status;
  			AnswerOk();
}
////////////////////////////////////////////////////////////////////////
///校验密码
///////////////////////////////////////////////////////////////////////
void ComM500PiccAuthE2()
{
char status;
unsigned char *pSNR;
pSNR  = &g_cSNR;
status=PcdLoadKeyE2(g_cReceBuf[1],g_cReceBuf[2]);
     if(status==0)
	      {
		    status = PcdAuthState(g_cReceBuf[1], g_cReceBuf[3], pSNR);     //验证密钥
            g_cReceBuf[0]=1;
			g_cReceBuf[1]=status;
			AnswerOk();
			return;
		  }
		  AnswerOk();
}

//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///下载密码
///////////////////////////////////////////////////////////////////////
void ComM500PcdLoadKeyE2()
{
char status;
status=M500PcdLoadKeyE2(g_cReceBuf[1],g_cReceBuf[2],&g_cReceBuf[3]);
			g_cReceBuf[0]=1;
			g_cReceBuf[1]=status;
			AnswerOk();
}

/////////////////////////////////////////////////////////////////////
//响应上位机发送的A卡休眠命令
/////////////////////////////////////////////////////////////////////
void ComHlta()
{
unsigned char status;
   status=PcdHalt();
    g_cReceBuf[0]=1;
			g_cReceBuf[1]=status;
			AnswerOk();
}

/////////////////////////////////////////////////////////////////////
//响应上位机发送的A卡验证密钥命令
/////////////////////////////////////////////////////////////////////
void ComAuthentication()
{
    char status = MI_COM_ERR;
    unsigned char *pkeys,*pSNR;
    pkeys = &g_cReceBuf[20];
    pSNR  = &g_cSNR;
    if (MI_OK == ChangeCodeKey(&g_cReceBuf[3],pkeys))                       //转换密钥格式
    {
    	if (MI_OK == PcdAuthKey(pkeys))                                     //传送密钥到FM1702 FIFO
        {
             status = PcdAuthState(g_cReceBuf[1], g_cReceBuf[3], pSNR);     //验证密钥
        }
    }
    if (status == MI_OK)
    {   g_cReceBuf[0]=1;
			g_cReceBuf[1]=status;
			 AnswerOk();
			    }

}

/////////////////////////////////////////////////////////////////////
//响应上位机读M1卡命令
/////////////////////////////////////////////////////////////////////
void ComM1Read()
{
char status;
	status=PcdRead(g_cReceBuf[1], &g_cReceBuf[2]);
    if (status==MI_OK)
    {
		if(g_cCidNad==mifare1||g_cCidNad==mifarepro)
			   g_cReceBuf[0]=17;
			else	  if(g_cCidNad==1)
					 g_cReceBuf[0]=9;
				else		  g_cReceBuf[0]=16;
		g_cReceBuf[1]=status;
    	AnswerOk();
		return;
	}
    else
    {   g_cReceBuf[0]=1;            }
		g_cReceBuf[1]=status;
		AnswerOk();
}


/////////////////////////////////////////////////////////////////////
//响应上位机写M1卡命令
/////////////////////////////////////////////////////////////////////
void ComM1Write()
{
    char status;
	status=PcdWrite(g_cReceBuf[1], &g_cReceBuf[2]);
	    g_cReceBuf[0]=1;
		g_cReceBuf[1]=status;
		AnswerOk();

}
/////////////////////////////////////////////////////////////////////
//响应上位机扣款命令
/////////////////////////////////////////////////////////////////////
void ComM1Decrement()
{
   char status;
	status=PcdValue(g_cReceBuf[1], g_cReceBuf[2], &g_cReceBuf[3]);
    if (status==MI_OK)
    {
	    g_cReceBuf[0]=1;
		g_cReceBuf[1]=status;
		AnswerOk();
		return;
     }
	 g_cReceBuf[0]=1;
		g_cReceBuf[1]=status;
		AnswerOk();
		return;

}

/////////////////////////////////////////////////////////////////////
//正确执行完上位机指令，应答（有返回数据）
//input：answerdata = 应答数据
//       answernum  = 数据长度
/////////////////////////////////////////////////////////////////////
void AnswerOk()
{
    unsigned char len, i;
//    ES=0;
//    TI=0;
//		len=g_cReceBuf[0];
//		for(i=0;i<len+1;i++)
//		{
//			SBUF=g_cReceBuf[i];
//			while(!TI);
//			TI=0;
//		}
//
//     TI = 0;
//	ES=1;
    Error = AS1_SendBlock(AS1Ptr, g_cReceBuf, sizeof(g_cReceBuf));
}

/////////////////////////////////////////////////////////////////////
//串行中断，接收上位机数据
/////////////////////////////////////////////////////////////////////
seri_int ()
{
unsigned char len, i;
unsigned int j=0;
   if (RI)
   {

	ES=0;
	len=AS1_GetReceivedDataNum(AS1Ptr);
		RI=0;
		for(i=0;i<len;i++)
		{
			while(!RI)
			{
				j++;
				if(j>1000)
				{
				   ES=1;
				    break;
				}
			}
			if(j<1000)
			{
				g_cReceBuf[i]=SBUF;
				RI=0;
				j=0;
			}
			else
			{
			   ES=1;
			    break;
			}
		}
		if(i==len)
		{
			ES=1;
			g_bReceOk  = 1;

		}
    }

}


/////////////////////////////////////////////////////////////////////
//用T2做延时子程序
/////////////////////////////////////////////////////////////////////
void DelayMs(unsigned int _MS)
{
//    RCAP2LH = RCAP2_1ms;
//    T2LH    = RCAP2_1ms;
//
//    ET2     = 0; 	                                   // Disable timer2 interrupt
//    T2CON   = 0x04;                                        // 16-bit auto-reload, clear TF2, start timer
//    TR2     = 1;
//    while (_MS--)
//    {   while (!TF2);TF2 = 0;  }
//    TR2 = 0;
	//todo
}
void Delay_50us(unsigned char _50us)
{
//    RCAP2LH = RCAP2_50us;
//    T2LH    = RCAP2_50us;
//
//    ET2     = 0; 	                                   // Disable timer2 interrupt
//    T2CON   = 0x04;	                                   // 16-bit auto-reload, clear TF2, start timer
//    while (_50us--)
//    {   while (!TF2);TF2 = 0;  }
//    TR2 = 0;
	//todo
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/

    InitializeSystem( );
    Rc1702Ready( );
    PcdConfigISOType( 'A' );
    for(;;)
    {

        if (g_bReceOk)
        {

                g_bReceOk = 0;
				 g_cCommand=g_cReceBuf[0];
                switch(g_cCommand)
                {
                    case 0x01:
                       ComHlta();                   break;
                    case 0x02:
                       ComRequestA();               break;
                    case 0x03:
                       ComAnticoll();               break;
                    case 0x04:
                       ComSelect();                 break;
					 case 0x05:
                       ComM500PiccAuthE2();         break;
					 case 0x06:
                       ComM500PcdLoadKeyE2();       break;
                    case 0x07:
                       ComAuthentication();         break;
                    case 0x08:
                       ComM1Read();                 break;
                    case 0x09:
                       ComM1Write();                break;
                    case 0x0A:
                       ComM1Decrement();            break;
					 case 0x0B:
                       Comsond();                   break;
					 case 0x0C:    // 参数设置
		               	g_cReceBuf[0]=1;	//contact
		            	g_cReceBuf[1]=0;
			                                         break;

                }

         }
    }
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
