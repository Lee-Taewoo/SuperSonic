/*
 * app.c
 *
 *  Created on: Jan 16, 2025
 *      Author: user
 */

#include "app.h"

// 장치 선언
extern TIM_HandleTypeDef htim1; // buzzer
extern TIM_HandleTypeDef htim3; // ultrasonic
extern TIM_HandleTypeDef htim11; // delay_us
extern UART_HandleTypeDef huart2;

// us동안 지연
void delay_us(uint16_t t) {
	htim11.Instance->CNT = 0;
	while(htim11.Instance->CNT < t);
}

void setSound(uint16_t frequency) {
	htim1.Instance->ARR = 1000000 / frequency - 1;
	htim1.Instance->CCR1 = htim1.Instance->ARR / 2;
	htim1.Instance->CNT = 0;
}

void stopSound() {
	htim1.Instance->CCR1 = 0;
}

void app() {
	// uart 수신 인터럽트 시작
	initUart(&huart2);
	// 타이머 시작
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_Base_Start(&htim11);
	initUltrasonic(&htim3);
	while(1) {
			printf("distance = %d\n", getDistance());
			HAL_Delay(450);
		}
}
