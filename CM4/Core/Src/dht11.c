#include "dht11.h"
#include "stdio.h"
#include "main.h"
#include "delay.h"
#include "oled.h"
#include "tim.h"

uint8_t fan = 0;					//风扇档位
uint8_t fan_state = 1;
/**************************************************************
*功  能：复位DHT11
*参  数: 无
*返回值: 无
**************************************************************/
void DHT11_Rst(void)
{
	DHT11_IO_OUT(); 	//SET OUTPUT
    DHT11_DQ_OUT(0); 	//拉低DQ
    Delay_ms(20);    	//拉低至少18ms
    DHT11_DQ_OUT(1); 	//DQ=1
	Delay_us(40);     	//主机拉高20~40us
}

/**************************************************************
*功  能：等待DHT11的回应
*参  数: 无
*返回值: 返回1:未检测到DHT11的存在； 返回0:存在
**************************************************************/
uint8_t DHT11_Check(void)
{
	uint8_t retry=0;
	DHT11_IO_IN();						//SET INPUT
    while (DHT11_DQ_IN()&&retry<100)		//DHT11会拉低40~80us
	{
		retry++;
		Delay_us(1);
	}
	if(retry>=100)return 1;
	else retry=0;
    while (!DHT11_DQ_IN()&&retry<100)		//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		Delay_us(1);
	}
	if(retry>=100)return 1;
	return 0;
}

/**************************************************************
*功  能：从DHT11读取一个位
*参  数: 无
*返回值: 1/0
**************************************************************/
uint8_t DHT11_Read_Bit(void)
{
	// ToDo
}

/**************************************************************
*功  能：从DHT11读取一个字节
*参  数: 无
*返回值: 读到的数据
**************************************************************/
uint8_t DHT11_Read_Byte(void)
{
	// ToDo
}

/**************************************************************
*功  能：从DHT11读取一次数据
*参  数: temp:温度值(范围:0~50°)；humi:湿度值(范围:20%~90%)
*返回值: 0,正常;1,读取失败
**************************************************************/
uint8_t DHT11_Read_Data(uint16_t *temp,uint16_t *humi)
{
	// ToDo
}

/**************************************************************
*功  能：初始化DHT11的IO口 DQ，同时检测DHT11的存在
*参  数: 无
*返回值: 返回1:不存在；返回0:存在
**************************************************************/
uint8_t DHT11_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	/*Configure GPIO pin : PA1 */
	GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);

	DHT11_Rst();  			//复位DHT11
	return DHT11_Check();	//等待DHT11的回应
}

/**************************************************************
*功  能：初始化输出端口
*参  数: 无
*返回值: 无
**************************************************************/
void DQ_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD; //开漏输出
    HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
}

/**************************************************************
*功  能：初始化输入端口
*参  数: 无
*返回值: 无
**************************************************************/
void DQ_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;	//浮空输入
    HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
}

/**************************************************************
*功  能：DHT11传感器检测
*参  数: 无
*返回值: 无
**************************************************************/
void DHT11_WHILE(void)
{
	while(DHT11_Init())
	{
		Delay_ms(50);
	}
}
