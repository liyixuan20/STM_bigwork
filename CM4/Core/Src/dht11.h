/*
 * dht11.h
 *
 *  Created on: Dec 15, 2021
 *      Author: BKRC-YZF
 */

#ifndef USER_DHT11_DHT11_H_
#define USER_DHT11_DHT11_H_

#include "main.h"

//IO方向设置
#define DHT11_IO_IN()    DQ_IN()
#define DHT11_IO_OUT()   DQ_OUT()

////IO操作函数
#define	DHT11_DQ_OUT(X)  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,(GPIO_PinState)X)	//数据端口	PA4
#define	DHT11_DQ_IN() 	 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)  		//数据端口	PA4

uint8_t DHT11_Init(void);					//初始化DHT11
uint8_t DHT11_Read_Data(uint16_t *temp,uint16_t *humi);	//读取温湿度
uint8_t DHT11_Read_Byte(void);				//读出一个字节
uint8_t DHT11_Read_Bit(void);				//读出一个位
uint8_t DHT11_Check(void);					//检测是否存在DHT11
void DHT11_Rst(void);						//复位DHT11
void DQ_OUT(void);
void DQ_IN(void);
void DHT11_Test(void);
void DHT11_WHILE(void);
extern uint8_t fan;
extern uint8_t fan_state;
#endif /* USER_DHT11_DHT11_H_ */
