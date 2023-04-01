/*
 * delay.c
 *
 *  Created on: Dec 15, 2021
 *      Author: BKRC-YZF
 */

#include "main.h"
#include "delay.h"
#include "oled.h"

/*
 Systick功能实现us延时，参数SYSCLK为系统时钟
 */
static uint32_t fac_us;
static uint32_t fac_ms=0;							//ms延时倍乘数
void HAL_User_Delay_init(uint8_t SYSCLK)
{
	fac_us = SYSCLK;
	fac_ms=fac_us*1000;
}
//延时nus
//nus为要延时的us数.
//注意:nus的值,不要大于798915us(最大值即2^24/fac_us@fac_us=21)
void Delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->LOAD=nus*fac_us; 				//时间加载
	SysTick->VAL=0x00;        				//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //开始倒数
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //关闭计数器
	SysTick->VAL =0X00;       				//清空计数器
}
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对168M条件下,nms<=798ms
void Delay_xms(uint16_t nms)
{
	uint32_t temp;
	SysTick->LOAD=(uint32_t)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           			//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;     		  		//清空计数器
}
//延时nms
//nms:0~65535
void Delay_ms(uint16_t nms)
{
	uint8_t repeat=nms/80;						//这里用540,是考虑到某些客户可能超频使用,
											//比如超频到248M的时候,delay_xms最大只能延时541ms左右了
	uint16_t remain=nms%80;
	while(repeat)
	{
		Delay_xms(80);
		repeat--;
	}
	if(remain)Delay_xms(remain);
}
