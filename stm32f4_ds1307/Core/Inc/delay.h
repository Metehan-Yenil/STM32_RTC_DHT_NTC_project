/*
 * delay.h
 *
 *  Created on: Jan 18, 2025
 *      Author: SG
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

TIM_HandleTypeDef htim1;

// timer1 bölücü değeri PSC clk değerine göre 1 Mhz olacak sekilde ayarlanmalıdır
// örneğin 64MHZ için PSC=63 verilir. 64/(63+1) = 1MHz olur
void delay_us2 (uint16_t delay)
{
  __HAL_TIM_SET_COUNTER(&htim1, 0);
  while (__HAL_TIM_GET_COUNTER(&htim1) < delay);
}

//void DelayMicroSeconds(uint32_t uSec)
//{
//	uint32_t uSecVar = uSec;
//	uSecVar = uSecVar* ((SystemCoreClock/1000000)/3);
//	while(uSecVar--);
//}

//Aşağıda verilenler gecikme rutinleri döngü ile yapılan gecikmelerdir
//clk frekans değiştiğinde istenen gecikmeleri vermez
void delayUs(uint16_t n){
	uint16_t j;
    while (n--) { for(j=0;j<7;j++); }  //48Mhz de 7 olursa  1.1 mikrosaniye
}


void delayMs(uint16_t n){  //48Mhz
	uint16_t j;
    while (n--) { for(j=0;j<222;j++); }  //48Mhz de 1 milisaniye 2666
}


#endif /* INC_DELAY_H_ */
