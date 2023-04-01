/*
 * delay.h
 *
 *  Created on: Dec 15, 2021
 *      Author: BKRC-YZF
 */

#ifndef DELAY_DELAY_H_
#define DELAY_DELAY_H_

void HAL_User_Delay_init(uint8_t SYSCLK);
void Delay_us(uint32_t nus);
void Delay_xms(uint16_t nms);
void Delay_ms(uint16_t nms);

#endif /* DELAY_DELAY_H_ */
