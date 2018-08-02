#include "common.h"

//�豸ͨ��·��������Զ�ͨ�ţ�����������õ�����ͨ��WiFichuan�������Զ�
//����·�������˺ţ�         ���룺
//�˿ں�Ϊ8086

//�û�������


//���Ӷ˿ں�:8086,�������޸�Ϊ�����˿�.
const u8* portnum="8086";		 

//WIFI STAģʽ,����Ҫȥ���ӵ�·�������߲���,��������Լ���·��������,�����޸�.
const u8* wifista_ssid="ALIENTEK";			//·����SSID��
const u8* wifista_encryption="wpawpa2_aes";	//wpa/wpa2 aes���ܷ�ʽ
const u8* wifista_password="15902020353"; 	//��������


//ATK-ESP8266ģ�����������
void atk_8266_test(void)
{
	//u8 key;
	//u8 timex; 
	while(atk_8266_send_cmd("AT","OK",20))//���WIFIģ���Ƿ�����
	{	
		
		atk_8266_quit_trans();//�˳�͸��
		atk_8266_send_cmd("AT+CIPMODE=0","OK",200);  //�ر�͸��ģʽ	
		OLED_ShowString(10,20,"δ��⵽ģ��!!!",12);
		delay_ms(800);
		OLED_ShowString(10,35,"��������ģ��...",12); 
		OLED_Refresh_Gram();
	} 
		while(atk_8266_send_cmd("ATE0","OK",20));//�رջ���
	while(1)
	{
		delay_ms(10); 
		atk_8266_at_response(1);//���ATK-ESP8266ģ�鷢�͹���������,��ʱ�ϴ�������
		OLED_Clear();
					OLED_ShowString(0,0,"ATK-ESP WIFI-STA ",12);
				//	OLED_ShowString(0,20,"��������ATK-ESP8266ģ�飬���Ե�...",12);
			OLED_Refresh_Gram();		
		atk_8266_wifista_test();//WIFI STA����
					

		} 	 
 
	} 
u8 netpro=1;	//����ģʽ
//0,TCP������
//1,TCP�ͻ���
//2,UDPģʽ
u8 atk_8266_wifista_test(void)
{
	//u8 netpro=0;	//����ģʽ
//	u8 key;
//	u8 timex=0; 
	u8 ipbuf[16]; 	//IP����
	u8 *p;
	//u16 t=999;		//���ٵ�һ�λ�ȡ����״̬
	u8 res=0;
//	u16 rlen=0;
//	u8 constate=0;	//����״̬
	
	p=mymalloc(SRAMIN,32);							//����32�ֽ��ڴ�
	atk_8266_send_cmd("AT+CWMODE=1","OK",50);		//����WIFI STAģʽ
	atk_8266_send_cmd("AT+RST","OK",20);		//DHCP�������ر�(��APģʽ��Ч) 
	delay_ms(1000);         //��ʱ3S�ȴ������ɹ�
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	//�������ӵ���WIFI��������/���ܷ�ʽ/����,�⼸��������Ҫ�������Լ���·�������ý����޸�!! 
	sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);//�������߲���:ssid,����
	while(atk_8266_send_cmd(p,"WIFI GOT IP",300));					//����Ŀ��·����,���һ��IP
	// atk_8266_at_response(1);
				OLED_Clear();
				OLED_ShowString(0,0,"ATK-ESP_WIFI-STA_ces",12); 
				OLED_ShowString(0,20,"loading_ATK-ESP...",12);
				atk_8266_send_cmd("AT+CIPMUX=1","OK",50);   //0�������ӣ�1��������
				sprintf((char*)p,"AT+CIPSERVER=1,%s",(u8*)portnum);    //����Serverģʽ(0���رգ�1����)���˿ں�Ϊportnum
				atk_8266_send_cmd(p,"OK",50); 
			//atk_8266_get_wanip(ipbuf);//������ģʽ,��ȡWAN IP
		//	sprintf((char*)p,"IP:%s port:%s",ipbuf,(u8*)portnum);
			//OLED_ShowString(0,35,p,12);				//��ʾIP��ַ�Ͷ˿�	
			OLED_Refresh_Gram();
			while(1)
			{
//				key=KEY_Scan(0);
//				if(key==WKUP_PRES)			//WK_UP �˳�����		 
//				{ 
//					res=0;					
//					atk_8266_quit_trans();	//�˳�͸��
//					atk_8266_send_cmd("AT+CIPMODE=0","OK",20);   //�ر�͸��ģʽ
//					break;												 
//				}
//				else if(key==KEY0_PRES)	//KEY0 �������� 
//				{
				
						int temp2;
						//sprintf((char*)p,"ATK-8266%s����%02d\r\n",ATK_ESP8266_WORKMODE_TBL[netpro],t/10);//��������
						//Show_Str(30+54,100,200,12,p,12,0);
					temp2=RX_Buffer[4];
							temp2<<=8;
							temp2+=RX_Buffer[3];	
					sprintf((char*)p,"%d",temp2/10);
						atk_8266_send_cmd("AT+CIPSEND=0,25","OK",200);  //����ָ�����ȵ�����
						delay_ms(200);
						atk_8266_send_data(p,"OK",100);  //����ָ�����ȵ�����
						//timex=100;

//				}else;
//			

			}
	myfree(SRAMIN,p);		//�ͷ��ڴ� 
	return res;		
} 
