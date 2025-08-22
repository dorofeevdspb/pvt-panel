# IO

```
     ___USB___
PD1 |         | VIN
PD0 |         | GND
PC6 |         | PC6
GND |         | 5V
PD2 |         | ADC7
PD3 |         | ADC6
PD4 |         | PC5
PD5 |         | PC4
PD6 |         | PC3 
PD7 |         | PC2
PB0 |         | PC1
PB1 |         | PC0 
PB2 |         | AREF
PB3 |         | 3.3
PB4 |_________| PB5
``` 

|на плате|прошив |	Возможности       | Использован     |
|-------:|:------|-------------------|----------------:|
|TX1     | 1	  | D-I/O, Serial TX  |     tohim       |
|RX0     | 0	  | D-I/O, Serial RX  | t ohim           |
|RST     |	  | Пин перезагрузки  |                 |
|GND     |	  | Земля/V-      |                 |
|D2	    | 2	  | D-I/O
|D3      | 3     | D-I/O, ШИМ      
|D4      | 4     | D-I/O
|D5	    | 5	  | D-I/O, ШИМ
|D6	    | 6	  | D-I/O, ШИМ
|D7	    | 7	  | D-I/O
|D8	    | 8	  | D-I/O
|D9      | 9	  | D-I/O, ШИМ
|D10     | 10	  | D-I/O, ШИМ, SPI SS
|D11     | 11	  | D-I/O, ШИМ, SPI MOSI
|D12     | 12	  | D-I/O, SPI MISO
|D13     | 13	  | D-I/O, LED, SPI SCK
|3.3V    |	  | 3.3 В
|REF     | 	  | analog referenc
|A0      | A0/14 | A-in ADC 8bit
|A1	    | A1/15 | A-in ADC 8bit
|A2	    | A2/16 | A-in ADC 8bit          |
|A3	    | A3/17 | A-in ADC 8bit          |
|A4	    | A4/18 | A-in ADC 8bit, I2C SDA |
|A5	    | A5/19 | A-in ADC 8bit, I2C SCL |
|A6	    | A6	  | A-in ADC 8bit          |
|A7	    | A7	  | A-in ADC 8bit          |
|5V	    |       | 5В/V+              |
|RES     |	  | Пин перезагрузки       |
|GND     |	  | Земля/V-           |
|VIN     |	  | Пин питания            |
