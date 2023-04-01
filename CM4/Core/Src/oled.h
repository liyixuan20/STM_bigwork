/*
 * oled.h
 *
 *  Created on: Dec 13, 2021
 *      Author: BKRC-YZF
 */

#ifndef USER_OLED_OLED_H_
#define USER_OLED_OLED_H_

#include "main.h"

#define OLED_ADDRESS        0x78
#define IIC_OLED_CMD    0x00    //写命令
#define IIC_OLED_DATA   0x40    //写数据

/*IIC 事件*/
/* --EV5 : 起始位已发送...*/
#define  I2C_EVENT_MASTER_MODE_SELECT                      ((uint32_t)0x00030001)  /* BUSY, MSL and SB flag */
/* --EV6 : 发送/接收完成...*/
#define  I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED        ((uint32_t)0x00070082)  /* 发送 BUSY, MSL, ADDR, TXE and TRA flags */
#define  I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED           ((uint32_t)0x00030002)  /* 接收 BUSY, MSL and ADDR flags */
/* Master RECEIVER mode -----------------------------*/
/* --EV7 */
#define  I2C_EVENT_MASTER_BYTE_RECEIVED                    ((uint32_t)0x00030040)  /* BUSY, MSL and RXNE flags */
/* Master TRANSMITTER mode --------------------------*/
/* --EV8 */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING                 ((uint32_t)0x00070080) /* TRA, BUSY, MSL, TXE flags */
/* --EV8_2 */
#define  I2C_EVENT_MASTER_BYTE_TRANSMITTED                 ((uint32_t)0x00070084)  /* TRA, BUSY, MSL, TXE and BTF flags */


//OLED控制用函数
void OLED_Hardware_Init(void);
void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Draw(uint8_t byte);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);

void OLED_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t wsize);
void OLED_ShowString(uint16_t x, uint16_t y, char *p, uint8_t wsize);
void OLED_ShowInt32Num(uint16_t x, uint16_t y, int32_t num, uint8_t len, uint8_t wsize);
void OLED_DrawFont16(uint16_t x, uint16_t y, char *s);
void OLED_DrawFont32(uint16_t x, uint16_t y, char *s);
void OLED_Show_Str(uint16_t x, uint16_t y, char *str, uint8_t wsize);
uint8_t I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);

#endif /* USER_OLED_OLED_H_ */
