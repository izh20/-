#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include <stdio.h>
#include "voice.h"
#include "rtc.h"
#include "usmart.h"
#include "sram.h"
#include "sdio_sdcard.h"
#include "malloc.h"
#include "key.h"
//#include "w25qxx.h"
#include	"common.h"
//ALIENTEK 探索者STM32F407开发板 实验12
//OLED显示实验-库函数版本 
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

void show_sdcard_info(void)
{
	switch(SDCardInfo.CardType)
	{
		case SDIO_STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
		case SDIO_STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
		case SDIO_HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
		case SDIO_MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
	}	
  	printf("Card ManufacturerID:%d\r\n",SDCardInfo.SD_cid.ManufacturerID);	//制造商ID
 	printf("Card RCA:%d\r\n",SDCardInfo.RCA);								//卡相对地址
	printf("Card Capacity:%d MB\r\n",(u32)(SDCardInfo.CardCapacity>>20));	//显示容量
 	printf("Card BlockSize:%d\r\n\r\n",SDCardInfo.CardBlockSize);			//显示块大小
}

int main(void)
{ 
	extern int temp2;
	extern char voice_flag;
	u8 key;
	char key_flag=0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);     //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	usart3_init(115200);
	usmart_dev.init(84); 	//初始化USMART	
	KEY_Init();					//初始化按键
	LED_Init();					//初始化LED
 	OLED_Init();				//初始化OLED
	My_RTC_Init();		 		//初始化RTC
	my_mem_init(SRAMIN);		//初始化内部内存池 
	my_mem_init(SRAMCCM);		//初始化CCM内存池
	
	
	RTC_Set_AlarmA(3||2,16,19,15);
	RTC_Set_AlarmB(3,6,0 ,0);
  OLED_ShowString(10,0,"decibelmeter",16);  
	OLED_Refresh_Gram();//更新显示到OLED	 
	
//	while(SD_Init())//检测不到SD卡
//	{
//		OLED_ShowString(10,20,"Error",12);
//		delay_ms(500);					
//		OLED_ShowString(10,40,"PleaseCheck",12);
//		delay_ms(500);
//		LED3=!LED3;//DS0闪烁
//		OLED_Refresh_Gram();
//	}
//	show_sdcard_info();	//打印SD卡相关信息
//	//检测SD卡成功 											    
//	OLED_ShowString(30,20,"SDCardOK",12);
//	OLED_ShowString(30,36,"SDCardSize",12);
//	OLED_ShowNum(30,52,(SDCardInfo.CardCapacity>>20)/1024,5,12);//显示SD卡容量
//	OLED_ShowString(60,52,"GB",12);
//	OLED_Refresh_Gram();
	while(1) 
	{			
		key=KEY_Scan(1);
		if(key==KEY0_PRES)
		{
			OLED_Clear();
			key_flag=1;
		}
		if(key_flag)
		{
			rtc_display();
		}
			if(voice_flag)
			{
					if(temp2>0x0352)  //当室内噪声达到85dB时
					{
							LED3=0;
						
					}
					else 
						LED3=1;
			}
			atk_8266_test();
	}
}


