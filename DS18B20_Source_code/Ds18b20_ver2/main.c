/*
 * Ds18b20_ver2.c
 *
 * Created: 10/13/2021 9:58:58 AM
 * Author : Administrator
 */ 

#include "main.h"

#if (__MAIN_H!=5072014)
#error "Include Sai File main.h"
#endif

int main(void)
{
	char str[16];
	
    DDRD = 0x00;
	PORTD = 0x80;
	
	 // Qua trinh khoi tao lcd
	 init_LCD();
	 clr_LCD();
	 move_LCD(1,1);
	 print_LCD("bui truong",10);
	 putChar_LCD('H');
	 Read_temp();
	 _delay_ms(1000);
    while (1) 
    {
		   Read_temp();  // cap nhat nhiet do
		   
		   temp_Register = ds18b20_Read_Byte();
		   temp_Register = (ds18b20_Read_Byte() <<8) |temp_Register;

		   temp = (temp_Register >> 4)+ ((float)(temp_Register & 0x000F))*1.0/16; //lay nhiet do tu temp_Register

			 sprintf(str,"nhietdo:%.2fC", temp);
			move_LCD(2,1);
			print_LCD(str, 16);
			_delay_ms(200);
	}
}

