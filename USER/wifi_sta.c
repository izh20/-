#include "common.h"

//设备通过路由器与电脑端通信，将传感器获得的数据通过WiFichuan传给电脑端
//设置路由器的账号：         密码：
//端口号为8086

//用户配置区


//连接端口号:8086,可自行修改为其他端口.
const u8* portnum="8086";		 

//WIFI STA模式,设置要去连接的路由器无线参数,请根据你自己的路由器设置,自行修改.
const u8* wifista_ssid="ALIENTEK";			//路由器SSID号
const u8* wifista_encryption="wpawpa2_aes";	//wpa/wpa2 aes加密方式
const u8* wifista_password="15902020353"; 	//连接密码


//ATK-ESP8266模块测试主函数
void atk_8266_test(void)
{
	//u8 key;
	//u8 timex; 
	while(atk_8266_send_cmd("AT","OK",20))//检查WIFI模块是否在线
	{	
		
		atk_8266_quit_trans();//退出透传
		atk_8266_send_cmd("AT+CIPMODE=0","OK",200);  //关闭透传模式	
		OLED_ShowString(10,20,"未检测到模块!!!",12);
		delay_ms(800);
		OLED_ShowString(10,35,"尝试连接模块...",12); 
		OLED_Refresh_Gram();
	} 
		while(atk_8266_send_cmd("ATE0","OK",20));//关闭回显
	while(1)
	{
		delay_ms(10); 
		atk_8266_at_response(1);//检查ATK-ESP8266模块发送过来的数据,及时上传给电脑
		OLED_Clear();
					OLED_ShowString(0,0,"ATK-ESP WIFI-STA ",12);
				//	OLED_ShowString(0,20,"正在配置ATK-ESP8266模块，请稍等...",12);
			OLED_Refresh_Gram();		
		atk_8266_wifista_test();//WIFI STA测试
					

		} 	 
 
	} 
u8 netpro=1;	//网络模式
//0,TCP服务器
//1,TCP客户端
//2,UDP模式
u8 atk_8266_wifista_test(void)
{
	//u8 netpro=0;	//网络模式
//	u8 key;
//	u8 timex=0; 
	u8 ipbuf[16]; 	//IP缓存
	u8 *p;
	//u16 t=999;		//加速第一次获取链接状态
	u8 res=0;
//	u16 rlen=0;
//	u8 constate=0;	//连接状态
	
	p=mymalloc(SRAMIN,32);							//申请32字节内存
	atk_8266_send_cmd("AT+CWMODE=1","OK",50);		//设置WIFI STA模式
	atk_8266_send_cmd("AT+RST","OK",20);		//DHCP服务器关闭(仅AP模式有效) 
	delay_ms(1000);         //延时3S等待重启成功
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	//设置连接到的WIFI网络名称/加密方式/密码,这几个参数需要根据您自己的路由器设置进行修改!! 
	sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);//设置无线参数:ssid,密码
	while(atk_8266_send_cmd(p,"WIFI GOT IP",300));					//连接目标路由器,并且获得IP
	// atk_8266_at_response(1);
				OLED_Clear();
				OLED_ShowString(0,0,"ATK-ESP_WIFI-STA_ces",12); 
				OLED_ShowString(0,20,"loading_ATK-ESP...",12);
				atk_8266_send_cmd("AT+CIPMUX=1","OK",50);   //0：单连接，1：多连接
				sprintf((char*)p,"AT+CIPSERVER=1,%s",(u8*)portnum);    //开启Server模式(0，关闭；1，打开)，端口号为portnum
				atk_8266_send_cmd(p,"OK",50); 
			//atk_8266_get_wanip(ipbuf);//服务器模式,获取WAN IP
		//	sprintf((char*)p,"IP:%s port:%s",ipbuf,(u8*)portnum);
			//OLED_ShowString(0,35,p,12);				//显示IP地址和端口	
			OLED_Refresh_Gram();
			while(1)
			{
//				key=KEY_Scan(0);
//				if(key==WKUP_PRES)			//WK_UP 退出测试		 
//				{ 
//					res=0;					
//					atk_8266_quit_trans();	//退出透传
//					atk_8266_send_cmd("AT+CIPMODE=0","OK",20);   //关闭透传模式
//					break;												 
//				}
//				else if(key==KEY0_PRES)	//KEY0 发送数据 
//				{
				
						int temp2;
						//sprintf((char*)p,"ATK-8266%s测试%02d\r\n",ATK_ESP8266_WORKMODE_TBL[netpro],t/10);//测试数据
						//Show_Str(30+54,100,200,12,p,12,0);
					temp2=RX_Buffer[4];
							temp2<<=8;
							temp2+=RX_Buffer[3];	
					sprintf((char*)p,"%d",temp2/10);
						atk_8266_send_cmd("AT+CIPSEND=0,25","OK",200);  //发送指定长度的数据
						delay_ms(200);
						atk_8266_send_data(p,"OK",100);  //发送指定长度的数据
						//timex=100;

//				}else;
//			

			}
	myfree(SRAMIN,p);		//释放内存 
	return res;		
} 
