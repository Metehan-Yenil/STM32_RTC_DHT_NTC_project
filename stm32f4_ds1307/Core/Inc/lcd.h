/**********************************************
*Dosya          :lcd.h
*Amaç           :4x20 LCD kullanma
*Yazar          :Salih GÖRGÜNOĞLU
*Versiyon       :V1.0
* LCD Pin bağlantısı :
*LCD_RS
*LCD_EN
*LCD_D4
*LCD_D5
*LCD_D6
*LCD_D7
*LCD_RW    ->Toprak
************************************************/

#ifndef __LCD_H       //Daha once tanımlı değil ise
#define __LCD_H       //lcd.h kullan

extern void delay_us (uint16_t delay);

GPIO_TypeDef* GPIO_LCD=GPIOB; //LCD nin bağlı olduğu port

//LCD nin RS, EN ve D4 D5 D6 D7 nin bağlı olduğu pin tanımları
#define LCD_RS GPIO_PIN_4
#define LCD_EN GPIO_PIN_5

#define LCD_D4 GPIO_PIN_6
#define LCD_D5 GPIO_PIN_7
#define LCD_D6 GPIO_PIN_8
#define LCD_D7 GPIO_PIN_9

#define t1 10        // gecikme zaman degerleri

/*
void delay_us (uint16_t delay)
{
  __HAL_TIM_SET_COUNTER(&htim1, 0);
  while (__HAL_TIM_GET_COUNTER(&htim1) < delay);
}

void DelayMicroSeconds(uint32_t uSec)
{
	uint32_t uSecVar = uSec;
	uSecVar = uSecVar* ((SystemCoreClock/1000000)/3);
	while(uSecVar--);
}
void delay_us(uint16_t n){
	uint16_t j;
    while (n--) { for(j=0;j<7;j++); }  //48Mhz de 7 olursa  1.1 mikrosaniye
}

 
void delay_ms(uint16_t n){  //48Mhz
	uint16_t j;
    while (n--) { for(j=0;j<222;j++); }  //48Mhz de 1 milisaniye 2666
}
*/

void clockLcd()
{
  GPIO_LCD->BSRR=LCD_EN;
  delay_us(t1);
  GPIO_LCD->BSRR=LCD_EN << 16;
  delay_us(t1);
}


void yuklelcd(uint8_t deger)
{

 HAL_Delay(1);
 if((deger & 0x10)==0x10) GPIO_LCD->BSRR=LCD_D4;  else GPIO_LCD->BSRR=LCD_D4 << 16;
 if((deger & 0x20)==0x20) GPIO_LCD->BSRR=LCD_D5;  else GPIO_LCD->BSRR=LCD_D5 << 16;
 if((deger & 0x40)==0x40) GPIO_LCD->BSRR=LCD_D6;  else GPIO_LCD->BSRR=LCD_D6 << 16;
 if((deger & 0x80)==0x80) GPIO_LCD->BSRR=LCD_D7;  else GPIO_LCD->BSRR=LCD_D7 << 16;

}

void sendCmdLcd(uint16_t cmd)
{

GPIO_LCD->BSRR=LCD_RS << 16; //RS=0
yuklelcd(cmd);
clockLcd();
yuklelcd(cmd<<4);
clockLcd();
HAL_Delay(1);

}


void sendDataLcd(uint16_t veri)
{
yuklelcd(veri);
GPIO_LCD->BSRR=LCD_RS; //RS=1
clockLcd();
yuklelcd(veri<<4);
clockLcd();
HAL_Delay(1);
}

void writeStr(uint16_t sat, uint16_t sut, char * str)
{
	uint16_t adr=0;

	if(sat==1) adr=0x80+sut;
	if(sat==2) adr=0xC0+sut;
	if(sat==3) adr=0x94+sut;
	if(sat==4) adr=0xD4+sut;
	sendCmdLcd(adr);
 	while(*str!=0){
  		sendDataLcd(*str++);

	}
}

void writeStr1(uint16_t sat, uint16_t sut, char *str)
{
  uint16_t adr=0,j=0;

  if(sat==1) adr=0x80+0x00+sut;
  if(sat==2) adr=0x80+0x40+sut;
  if(sat==3) adr=0x80+0x14+sut;
  if(sat==4) adr=0x80+0x54+sut;
    sendCmdLcd(adr);
  //while(*str!='\0'){ String sonununa 0 konursa "merhaba\0" gibi
  while(str[j]!=0){
      sendDataLcd(str[j]);j++;

  }
}

void clearLcd(void)
{
   sendCmdLcd(0x01);
   delay_us(t1);
}


void clearLcd2(void)
{
   writeStr(1,0,"                    ");
   writeStr(2,0,"                    ");
   writeStr(3,0,"                    ");
   writeStr(4,0,"                    ");
}

void setCursor(uint16_t sat, uint16_t sut)
{
   uint16_t adr=0;
  if(sat==1) adr=0x80+0x00+sut;
  if(sat==2) adr=0x80+0x40+sut;
  if(sat==3) adr=0x80+0x14+sut;
  if(sat==4) adr=0x80+0x54+sut;
  sendCmdLcd(adr);
  delay_us(t1);
}

void cursorOn(void)
{
  sendCmdLcd(0x0F); //0x0E display control:turn display on, cursor on, no blinking
  delay_us(t1);
}

void cursorOn2(uint16_t sat, uint16_t sut)
{
   uint16_t adr=0;
	if(sat==1) adr=0x80+sut;
	if(sat==2) adr=0xC0+sut;
	if(sat==3) adr=0x94+sut;
	if(sat==4) adr=0xD4+sut;
	sendCmdLcd(adr);
    sendCmdLcd(0x0F); //0x0E display control:turn display on, cursor on, no blinking
    delay_us(t1);
}

void cursorOf(void)
{
  sendCmdLcd(0x0C); //0x0E display control:turn display on, cursor of, no blinking
  delay_us(t1);
}


void lcdInit(void)
{

  HAL_Delay(20);    //LCD Power ON Initialization time >15ms
  sendCmdLcd(0x02); //4bit mode
  HAL_Delay(10);
  sendCmdLcd(0x28); //Initialization of LCD in 4bit mode
  HAL_Delay(10);
  sendCmdLcd(0x06); //entry mode set: increment automatically, no display shift
  HAL_Delay(5);
  sendCmdLcd(0x0C); //0x0E display control:turn display on, cursor on, no blinking
  HAL_Delay(5);
  sendCmdLcd(0x01); //clear display, set cursor position to zero
  HAL_Delay(5);

}

void displayDigit(uint16_t sat, uint16_t sut, uint8_t x)//0-9 arası degerleri gosterir
{
    uint8_t s0;

	uint16_t adr=0;
	if(sat==1) adr=0x80+sut;
	if(sat==2) adr=0xC0+sut;
	if(sat==3) adr=0x94+sut;
	if(sat==4) adr=0xD4+sut;

	sendCmdLcd(adr);
    s0=x+48;sendDataLcd(s0);

}




void displayInt(uint16_t sat, uint16_t sut, int32_t x)//-99999 .... +99999 degerleri gosterir
{  	uint32_t sayix;
	uint16_t s4,s3,s2,s1,s0;  // 5 hane yazar

	uint16_t adr=0;
	if(sat==1) adr=0x80+sut;
	if(sat==2) adr=0xC0+sut;
	if(sat==3) adr=0x94+sut;
	if(sat==4) adr=0xD4+sut;

	   sendCmdLcd(adr);
	   HAL_Delay(1);
      if(x<0){x=-x;sendDataLcd('-');}  //gelen sayi - ise;

    sayix=x;  	              s4=sayix/10000;
    sayix=sayix%10000;	      s3=sayix/1000;
    sayix=sayix%1000;	      s2=sayix/100;
    sayix=sayix%100;	      s1=sayix/10;
    sayix=sayix%10;		      s0=sayix;

	if(x<100)
    {sendDataLcd(s1+48);	sendDataLcd(s0+48);}

	if(x>=100 && x<1000)
	{sendDataLcd(s2+48); sendDataLcd(s1+48); sendDataLcd(s0+48);}

	if(x>=1000 && x<10000)
    {sendDataLcd(s3+48);	sendDataLcd(s2+48); sendDataLcd(s1+48); sendDataLcd(s0+48);}

	if(x>=10000 && x<100000)
	{sendDataLcd(s4+48);	sendDataLcd(s3+48); sendDataLcd(s2+48); sendDataLcd(s1+48);	sendDataLcd(s0+48);}

 }


//---------------------------------------------------------------------------
void displayFloat(uint16_t sat, uint16_t sut, float x)//9999.999 degerini gosterir
{
	uint32_t sayix;
	uint16_t s5,s4,s3,s2,s1,s0;
	uint16_t adr=0;
	if(sat==1) adr=0x80+sut;
	if(sat==2) adr=0xC0+sut;
	if(sat==3) adr=0x94+sut;
	if(sat==4) adr=0xD4+sut;


	sendCmdLcd(adr);

   	if(x<0){x=-x;sendDataLcd('-');}  //gelen sayi - ise;

    sayix=x*100;		    	s5=sayix/100000;
    sayix=sayix%100000;	    	s4=sayix/10000;
    sayix=sayix%10000;	    	s3=sayix/1000;
    sayix=sayix%1000;	    	s2=sayix/100;
	sayix=sayix%100;	    	s1=sayix/10;
	sayix=sayix%10;	    		s0=sayix;


    sut=sut+1;

    if(x>=0 && x<10)  //9.99
     { sendDataLcd(s2+48);
   	   sendDataLcd('.');
       sendDataLcd(s1+48);	sendDataLcd(s0+48);
	 }


	if(x>=10 && x<100)//99.99
    {
	 sendDataLcd(s3+48); sendDataLcd(s2+48);
   	 sendDataLcd('.');
     sendDataLcd(s1+48); sendDataLcd(s0+48);

	}

	if(x>=100 && x<1000) //999.99
    {
	 sendDataLcd(s4+48); sendDataLcd(s3+48); sendDataLcd(s2+48);
   	 sendDataLcd('.');
   	 sendDataLcd(s1+48); sendDataLcd(s0+48);
	}

    if(x>=1000 && x<10000)//9999.99
    {
     sendDataLcd(s5+48); sendDataLcd(s4+48); sendDataLcd(s3+48); sendDataLcd(s2+48);
   	 sendDataLcd('.');
   	 sendDataLcd(s1+48); sendDataLcd(s0+48);
	}




 }

//---------------------------------------------------------------------------




#endif
