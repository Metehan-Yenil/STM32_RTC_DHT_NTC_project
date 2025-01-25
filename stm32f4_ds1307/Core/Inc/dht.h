
#ifndef DHT_H_
#define DHT_H_

//void DHT_GetData (DHT_DataTypedef *DHT_Data);
//uint8_t DHT_GetData (void);


//GPIO_TypeDef* DHT_PORT=GPIOA;
#define DHT_PORT GPIOA
#define DHT_PIN GPIO_PIN_4

//extern void delay_us (uint16_t delay);
extern float temperature,humidity;

//extern DHT_DataTypedef DHT11_Data;

/*******************************************     NO CHANGES AFTER THIS LINE      ****************************************************/

void setpin_outputmode(void){
GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

 }

void setpin_inputmode(void){
GPIO_InitTypeDef GPIO_InitStruct = {0};

 GPIO_InitStruct.Pin = GPIO_PIN_4;
 GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
 GPIO_InitStruct.Pull = GPIO_NOPULL;
 HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

 }

void DHT_Start (void)
{
	//setpin_outputmode();
	HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, 1);
	HAL_Delay(10);
	HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, 0);

	//delay_us (18000);   // wait for 18ms
	HAL_Delay(1);

    HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, 1);
    delay_us (30);   // wait for 30 us

}

uint8_t DHT_Check_Response (void)
{
	uint8_t Response = 0, timeout=0;

	 //setpin_inputmode();

	delay_us (40);
	if (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)))
	{
		delay_us (80);
		if ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN))) Response = 1;
		else Response = 0;
	}
	while(timeout<40){
		timeout++;
	    delay_us (1);
	    if ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN))==0) break;

	}

	return Response;
}

uint8_t DHT_Read (void)
{
	uint8_t j,timeout=0;
	uint8_t veri = 0;

	 //setpin_inputmode();

	for (j=0;j<8;j++)
	{  // wait for the pin to go high
		timeout=0;
		while (timeout<100){
			timeout++;
		    delay_us (1);
		    if ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN))==1) break;
		}
		delay_us(50);   // wait for 40 us
		veri <<= 1;
		if ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)))   // if the pin is high
		{
			veri |= 1;
		}

		// wait for the pin to go low
		//while ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));
		timeout=0;
		while (timeout<100){
					timeout++;
				    delay_us (1);
				    if ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN))==0) break;
		}

	}
	return veri;
}


//void DHT_GetData (DHT_DataTypedef *DHT_Data)
uint8_t DHT_GetData (void)
{
	uint16_t rh_byte1, rh_byte2, temp_byte1, temp_byte2;
	uint8_t dht_sum;
	uint8_t presence = 0;

    DHT_Start ();
	presence = DHT_Check_Response ();
	if(presence==0) return 0;

	rh_byte1 = DHT_Read ();
	rh_byte2 = DHT_Read ();
	temp_byte1 = DHT_Read ();
	temp_byte2 = DHT_Read ();
	dht_sum = DHT_Read();

	temperature = (temp_byte1<<8 | temp_byte2)/10.0;
	humidity = (rh_byte1<<8 | rh_byte2)/10.0;

	return presence;

}


#endif /* INC_DHT_H_ */
