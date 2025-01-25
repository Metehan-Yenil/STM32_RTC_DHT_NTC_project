# STM32_RTC_DHT_NTC_project
Real time clock application with stm32f401cc microcontroller sets rtc time and date with the data received from ui. It also measures temperature and humidity values from dht22 and ntc.
These data are instantly displayed in Ui. Usart communication is used between Ui and Stm. I2C is used for RTC.

You will also need modules:
      - Uart usb ttl (ex:PL2303HX 4 Pin)
      - one 10k ntc
      - one dht22 sensor
      - ds1307 RTC
      - 2x16 LCD screen

Note: Links are based on libraries. Do not forget to change the pins in the libraries to your own.
      
      
