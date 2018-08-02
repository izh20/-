#include "voice.h"
#include "string.h"
/******************************************************************
 - 功能描述：将一个32位的变量dat转为字符串，比如把1234转为"1234"
 - 隶属模块：公开函数模块
 - 函数属性：外部，用户可调用
 - 参数说明：dat:带转的long型的变量
             str:指向字符数组的指针，转换后的字节串放在其中           
 - 返回说明：无
 ******************************************************************/

void u32tostr(unsigned long dat,char *str) 
{
 char temp[10];//20
 unsigned char i=0,j=0;
 i=0;
 while(dat)
 {
  temp[i]=dat%10+0x30;
  i++;
  dat/=10;
 }
 j=i;
 for(i=0;i<j;i++)
 {
  str[i]=temp[j-i-1];
 }
 if(!i) {str[i++]='0';}
 str[i]=0;
}
/******************************************************************
 - 功能描述：和校验，不读超过256的溢出值
 - 隶属模块：公开函数模块
 - 函数属性：外部，用户可调用
 - 参数说明：pBuf:需要和校验的数据
             numByte:校验字节数           
 - 返回说明：和校验结果
 ******************************************************************/
unsigned char CheckSum(unsigned char *pBuf,unsigned char numByte)
{
	unsigned char i;
	unsigned char ret=0;
	for(i=0;i<numByte;i++)
	{
		ret += pBuf[i];
	}
	return ret;
}

