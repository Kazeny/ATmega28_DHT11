/*
 * dht11.h
 *
 * Created: 2016/8/1 21:34:16
 *  Author: XU
 */ 

#include "avr/io.h"
#ifndef DHT11_H_
#define DHT11_H_

#define DDR_1 DDRC|=_BV(PC0);		//PC0为输出
#define DDR_0 DDRC&=~(1<<PC0)		//PC0为输入
#define PORTC_1 PORTC|=1<<PC0		//PC0为1
#define PORTC_0 PORTC&=~(1<<PC0)	//PC0为0

#define DQ (PINC&0x01)

static void getnum(void);
static void init_dht11(void);
static long int getdht11(void);


#endif /* DHT11_H_ */
