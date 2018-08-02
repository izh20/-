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
//ALIENTEK ̽����STM32F407������ ʵ��12
//OLED��ʾʵ��-�⺯���汾 
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

void show_sdcard_info(void)
{
	switch(SDCardInfo.CardType)
	{
		case SDIO_STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
		case SDIO_STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
		case SDIO_HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
		case SDIO_MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
	}	
  	printf("Card ManufacturerID:%d\r\n",SDCardInfo.SD_cid.ManufacturerID);	//������ID
 	printf("Card RCA:%d\r\n",SDCardInfo.RCA);								//����Ե�ַ
	printf("Card Capacity:%d MB\r\n",(u32)(SDCardInfo.CardCapacity>>20));	//��ʾ����
 	printf("Card BlockSize:%d\r\n\r\n",SDCardInfo.CardBlockSize);			//��ʾ���С
}

int main(void)
{ 
	extern int temp2;
	extern char voice_flag;
	u8 key;
	char key_flag=0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);     //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	usart3_init(115200);
	usmart_dev.init(84); 	//��ʼ��USMART	
	KEY_Init();					//��ʼ������
	LED_Init();					//��ʼ��LED
 	OLED_Init();				//��ʼ��OLED
	My_RTC_Init();		 		//��ʼ��RTC
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ��
	
	
	RTC_Set_AlarmA(3||2,16,19,15);
	RTC_Set_AlarmB(3,6,0 ,0);
  OLED_ShowString(10,0,"decibelmeter",16);  
	OLED_Refresh_Gram();//������ʾ��OLED	 
	
//	while(SD_Init())//��ⲻ��SD��
//	{
//		OLED_ShowString(10,20,"Error",12);
//		delay_ms(500);					
//		OLED_ShowString(10,40,"PleaseCheck",12);
//		delay_ms(500);
//		LED3=!LED3;//DS0��˸
//		OLED_Refresh_Gram();
//	}
//	show_sdcard_info();	//��ӡSD�������Ϣ
//	//���SD���ɹ� 											    
//	OLED_ShowString(30,20,"SDCardOK",12);
//	OLED_ShowString(30,36,"SDCardSize",12);
//	OLED_ShowNum(30,52,(SDCardInfo.CardCapacity>>20)/1024,5,12);//��ʾSD������
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
					if(temp2>0x0352)  //�����������ﵽ85dBʱ
					{
							LED3=0;
						
					}
					else 
						LED3=1;
			}
			atk_8266_test();
	}
}


