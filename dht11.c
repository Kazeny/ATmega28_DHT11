/*
 * dht11.c
 *
 * Created: 2016/8/1 20:46:05
 *  Author: XU
 */ 


#include "util/delay.h"
#include "dht11.h"


unsigned char dht_data[5];
unsigned int a,s1,s0,t1,t0,sd,wd,wsd;

static void init_dht11(void)
{
	DDR_1;														//设置主机输出
	PORTC_0;
	_delay_ms(20);												//总线拉低至少18ms
	PORTC_1;
	_delay_us(30);
	DDR_0;
	while(DQ);													//检测DHT11响应输出为0时结束循环
	//OLED_ShowString(0,2,"init:ok");
}

static void getnum(void)
{
	unsigned char i,j;
	for (i=0;i<5;i++)
	{
		dht_data[i]=0x00;										//数组元素初始为0
		for (j=0;j<8;j++)
		{
			while (!DQ);										//等待DQ为1
			_delay_us(50);										
			if (DQ)
			{
				dht_data[i]|=1<<(7-j);							//如果DQ高电平持续超过50us，数据为1；反之数据为0.
				while(DQ);										//发送完数据DQ为低电平
				//OLED_ShowString(0,6,"getnum:ok");
			}
			
		}
	}
}

static long int getdht11(void)
{
	init_dht11();
	if (!DQ)													//DQ=0进入条件语句
	{
		while(!DQ);												//DQ is 1
		while(DQ);												//DQ is 0
		getnum();												//输出模式，电平为高
		DDR_1;
		PORTC_1;
		a=dht_data[0]+dht_data[1]+dht_data[2]+dht_data[3];		//校验数据
		if (a==dht_data[4])
		{
			s1=dht_data[0];										//湿度整数部分
			s0=dht_data[1];										//湿度小数部分
			t1=dht_data[2];										//温度整数部分
			t0=dht_data[3];										//温度小数部分
		}
		sd=s1;
		sd<<=8;
		sd|=s0;
		wd=t1;
		wd<<=8;
		wd|=t0;
		wsd=sd<<10;
		wsd|=wd;
	}
	//else
	//	OLED_ShowString(0,6,"jiaoyan:no");
	return wsd;													//返回温湿度
}
