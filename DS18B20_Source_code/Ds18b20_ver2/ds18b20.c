/*
 * ds18b20.c
 *
 * Created: 10/13/2021 1:24:30 PM
 *  Author: Administrator
 */ 
#include "ds18b20.h"

void Init_18B20(void){
	PORTD = 0x80;
	_delay_us(8);
	PORTD = 0x00;
	_delay_us(65);
	PORTD = 0x80;
	_delay_us(20);
}
// ham reset:( Return 0: OK;    1: FAIL)
unsigned char ds18b20_Reset(){
	
	unsigned char result;
	DDRD = 0x80;
	PORTD &= ~(1 << PORTD7);
	_delay_us(480);
	
	PORTD |= (1 <<PORTD7);
	_delay_us(70);
	
	DDRD  = 0x00;
	result = DS18B20_PIN_DQ;
	_delay_us(410);
	
	return result;
	
}

// Ham gui 1 bit vao Slave 
void ds18b20_Write_Bit(unsigned char a)
{
	if(a == 1)
	{
		DDRD = 0x80;
		PORTD &= ~(1 << PORTD7);
		_delay_us(6);
		
		PORTD |= (1 << PORTD7);
		_delay_us(64);
	}
	else if(a == 0)
	{
		DDRD = 0x80;
		PORTD &= ~(1 << DS18B20_PORT_DQ);
		_delay_us(60);
		
		PORTD |= (1 << DS18B20_PORT_DQ);
		_delay_us(10);
	}
}

// Ham doc 1 bit nhan tu Slave
unsigned char ds18b20_Read_Bit()
{
	unsigned char result;
	DDRD = 0x80;
	PORTD &= ~(1 << DS18B20_PORT_DQ);
	_delay_us(6);
	
	PORTD |= (1 << DS18B20_PORT_DQ);
	_delay_us(9);
	
	DDRD = 0x00;
	result = DS18B20_PIN_DQ;
	_delay_us(55);
	
	return result;
}

// Ham ghi 1 byte vafo Slave
void ds18b20_Write_byte(unsigned char a)
{
	unsigned char i =8;
	while(i--)
	{
		ds18b20_Write_Bit(a & 0x01);
		a >>= 1;
	}
}

// Ham doc 1 byte tu Slave
unsigned char ds18b20_Read_Byte()
{
	unsigned char i =8, result = 0;
	while(i--)
	{
		result >>= 1;
		result |= (ds18b20_Read_Bit() << 7);
	}
	return result;
}

/*-----------------------------------------------------------------------------
Noi Dung    :   Cau hinh cho DS18B20. 
Tham Bien   :   temp_low: Gia tri nhiet do thap nhat de dua ra canh bao. 
                temp_high: Gia tri nhiet do cao nhat de dua ra canh bao.   
                resolution: Do phan giai cho DS18B20.(1|R1|R0|1|1|1|1|1)
Tra Ve      :   Khong.
  -----------------------------------------------------------------------------*/
  
void DS18B20_Config(uint8_t temp_low, uint8_t temp_high, uint8_t resolution)
{
	resolution=(resolution<<5)|0x1f;
	ds18b20_Write_byte(DS18B20_SKIP_ROM);
	ds18b20_Write_byte(DS1820_CMD_WRITESCRPAD);        // Cho phep ghi 3 byte vao bo nho nhap:
	_delay_us(90);
	ds18b20_Write_byte(temp_high);   // byte 2: Th
	ds18b20_Write_byte(temp_low);    // byte 3: Tl
	ds18b20_Write_byte(resolution);  // byte 4: configuration register
	_delay_us(100);
	ds18b20_Write_byte(DS18B20_SKIP_ROM);
	ds18b20_Write_byte(DS1820_CMD_COPYSCRPAD);        // Ghi vao EEPROM
}

/*-------------------
 Ham doc va chuyen doi temp 
 -------------------*/

//Ket noi den Slave, bat dau qua trinh chuyen doi nhiet do
unsigned char Read_temp(void)
{
	  Init_18B20();
       while(ds18b20_Reset());
            ds18b20_Write_byte(DS18B20_SKIP_ROM);
            ds18b20_Write_byte(DS18B20_CONVERT_T);
                _delay_ms(94);   //che do 12 bit mat 750ms de chuyen doi

                 //Ket noi den Slave, bat dau doc du lieu nhiet do
		Init_18B20();		 
       while(ds18b20_Reset());
            ds18b20_Write_byte(DS18B20_SKIP_ROM);
			ds18b20_Write_byte(DS18B20_READ_SCRATCH_PAD);

		//	return temp;
			
				_delay_us(50);
}