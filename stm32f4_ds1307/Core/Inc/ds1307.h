#ifndef __DS1307_H
#define __DS1307_H

extern uint8_t sn,dak,saat,gun,haftagun,ay,yil;
extern void delay_us (uint16_t delay);

GPIO_TypeDef* GPIO_RTC =GPIOB;

#define SDA GPIO_PIN_12
#define SCL GPIO_PIN_13

#define I2C_DELAY 10



void i2cStart()
{
	GPIO_RTC->BSRR=SDA;        //SDA=1
	GPIO_RTC->BSRR=SCL;        //SCL=1
	//delay_us(I2C_DELAY);
	GPIO_RTC->BSRR=SDA<<16;    //SDA=0
    delay_us(I2C_DELAY);
    GPIO_RTC->BSRR=SCL<<16;    //SCL=0
    delay_us(I2C_DELAY);
}

void i2cStop()
{
	GPIO_RTC->BSRR=SDA<<16;   //SDA=0
	GPIO_RTC->BSRR=SCL<<16;   //SCL=0
	delay_us(I2C_DELAY);
	GPIO_RTC->BSRR=SCL;       //SCL=1
	delay_us(I2C_DELAY);
	GPIO_RTC->BSRR=SDA;       //SDA=1
	delay_us(I2C_DELAY);

}


//------------------------------------------------------------------------------
uint8_t i2cwrite(uint8_t veri)
{
	uint8_t ack, j;
    for (j=0; j<8; j++) {
		if((veri & 0x80)==0x80)  
			GPIO_RTC->BSRR=SDA;       //SDA=1
		else
			GPIO_RTC->BSRR=SDA<<16;   //SDA=0

		GPIO_RTC->BSRR=SCL;       	//SCL=1
		delay_us(I2C_DELAY);
		GPIO_RTC->BSRR=SCL<<16;     //SCL=0
		delay_us(I2C_DELAY);

		veri=veri<<1;
	}
	// get Ack or Nak
    GPIO_RTC->BSRR=SCL;     //SCL=1
    delay_us(I2C_DELAY);
    ack=(GPIO_RTC->IDR & SDA)>>13;
    GPIO_RTC->BSRR=SCL<<16;     //SCL=0
    delay_us(I2C_DELAY);
	return ack;
}


// read a byte and send Ack if last is false else Nak to terminate read
uint8_t i2cread(uint8_t ack)
{

   uint8_t veri = 0;
   for (uint8_t i = 0; i < 8; i++) {

		veri <<= 1;
		delay_us(I2C_DELAY);
		GPIO_RTC->BSRR=SCL;    //SCL=1
		//delay_us(I2C_DELAY);
		if((GPIO_RTC->IDR & SDA) !=0) veri |= 1;
		GPIO_RTC->BSRR=SCL<<16;        //SCL=0
    }

   if(ack==0) GPIO_RTC->BSRR=SDA<<16;      // SDA=0 ack=0 ise DS1307 ye ack gonderilmis olur
   else GPIO_RTC->BSRR=SDA;           	   // SDA=1  ack=1 ise ds1307 ye noack gonderilmis olur
   delay_us(I2C_DELAY);
   GPIO_RTC->BSRR=SCL;       	//SCL=1
   delay_us(I2C_DELAY);
   GPIO_RTC->BSRR=SCL<<16;      //SCL=0
   delay_us(I2C_DELAY);
   GPIO_RTC->BSRR=SDA;          //SDA=1
   return veri;
}


 uint8_t decimaltobcd(uint8_t dec) {
 	return (dec % 10 + ((dec / 10) << 4));
 }


uint8_t bcdtodecimal(uint8_t bcd) {
 	return (((bcd & 0xf0) >> 4) * 10) + (bcd & 0x0f);
}

/*

void writeDS1307(unsigned char ramadr, unsigned char veri)
{  
	 	
    i2cStart();          // Start I2C communication
    i2cwrite(0xD0);      // connect to DS1307 by sending its ID on I2c Bus
    i2cwrite(ramadr);    // Request RAM address at ramadr
    i2cwrite(veri);      // Write veri to RAM address ramadr
    i2cStop();           // Stop I2C communication after Setting the Date
}


unsigned char readDS1307(unsigned char ramadr)
{   unsigned char veri;
    i2cStart();                           
    i2cwrite(0xD0);      	// connect to DS1307 by sending its ID on I2c Bus
    i2cwrite(ramadr);     // Request  RAM address at ramadr
    i2cStart();
    i2cwrite(0xD1);      // connect to DS1307 by sending its ID on I2c Bus
    	
    veri=i2cread(1);     // read veri from RAM address ramadr with noack
    i2cStop();  
    return veri;

}
*/
 
void enableDS1307_DS3231sqwout(void)
{
    i2cStart();                            
    i2cwrite(0xD0);        
    i2cwrite(0x07);  //control adress
    i2cwrite(0x90);  //enable 0x93              
    i2cStop();  
    
    i2cStart();                            
    i2cwrite(0xD0);        
    i2cwrite(0x0E);    //control adress
    i2cwrite(0x40);    //enable 0x93              
    i2cStop();    
}

void disableDS1307_DS3231sqwout(void)
{
    i2cStart();                            
    i2cwrite(0xD0);        
    i2cwrite(0x07);  //control adress
    i2cwrite(0x00);   // disable sqwout               
    i2cStop(); 
    
     i2cStart();                            
    i2cwrite(0xD0);        
    i2cwrite(0x0E);    //control adress
    i2cwrite(0x04);    // disable sqwout                
    i2cStop();    
    
}


void SetDateTime_ds1307(void)
{
	 sn=decimaltobcd(sn);
	 dak=decimaltobcd(dak);
	 saat=decimaltobcd(saat);
	 haftagun=decimaltobcd(haftagun);
	 gun=decimaltobcd(gun);
	 ay=decimaltobcd(ay);
	 yil=decimaltobcd(yil);
	
	
    i2cStart();                          // Start I2C communication
 
    i2cwrite(0xD0);       			// connect to DS1307 by sending its ID on I2c Bus
    i2cwrite(0x00);      			// Request sec RAM address at 00H
	  //write_ds1307(0x00);
    
    i2cwrite(sn);                    // Write sec from RAM address 00H
    i2cwrite(dak);                   // Write min from RAM address 01H
    i2cwrite(saat);                  // Write hour from RAM address 02H
    i2cwrite(haftagun);              // Write weekDay on RAM address 03H
    i2cwrite(gun);                   // Write date on RAM address 04H
    i2cwrite(ay);                    // Write month on RAM address 05H
    i2cwrite(yil);                   // Write year on RAM address 06h
 
    i2cStop();                              // Stop I2C communication after Setting the Date
}


void GetDateTime_ds1307(void)
{
    i2cStart();
    i2cwrite(0xD0);      // connect to DS1307 by sending its ID on I2c Bus
    i2cwrite(0x00);      // Request sec RAM address at 00H
    //i2cStop();
    i2cStart();
    i2cwrite(0xD1);      // connect to DS1307 by sending its ID on I2c Bus
    	
    sn=i2cread(0);         // Write sec from RAM address 00H
    dak=i2cread(0);        // Write min from RAM address 01H
    saat=i2cread(0);       // Write hour from RAM address 02H
    haftagun=i2cread(0);   // Write weekDay on RAM address 03H
    gun=i2cread(0);        // Write date on RAM address 04H
    ay=i2cread(0);         // Write month on RAM address 05H
    yil=i2cread(1);        // Write year on RAM address 06h with noack
    i2cStop();                     // Stop I2C communication after Setting the Date
    sn=bcdtodecimal(sn);
    dak=bcdtodecimal(dak);
    saat=bcdtodecimal(saat);
    haftagun=bcdtodecimal(haftagun);
    gun=bcdtodecimal(gun);
    ay=bcdtodecimal(ay);
    yil=bcdtodecimal(yil);

}

      

 

  

#endif
