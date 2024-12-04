/*
 * myLCD.c
 *
 * Created: 10/29/2021 3:48:12 PM
 * Author : Zbook 15 G3
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

/* Define for LCD */
#define DC DDRC
#define PC PORTC
#define DA DDRA
#define PA PORTA
#define RS PINC0
#define RW PINC1
#define RE PINC2

/* Functions for LCD */
void setup_LCD(unsigned char);
void display_char(unsigned char);
void khoitao_LCD(void);
void display_string(char []);
void display_stringxy(char, char, char []);
void clear_LCD(void);



int myfunc(void)
{
	return 0;
}
/* Functions for LCD */
void setup_LCD(unsigned char x){
	PA = x;
	PC &=~(1 << RS); // RS = 0 chon thanh ghi lenh IR (PC = 0b00000000)
	PC &=~(1 << RW); // RW = 0 hoat dong o MODE READ (PC = 0b00000000) 
	PC |= (1 << RE); // Set chan Enable len 1 de bat dau khung truyen (PC = 0b00000100)
	_delay_us(1);
	PC &=~(1 << RE); // Set chan Enable ve 0 de ket thuc khung truyen (PC = 0b00000000)
	_delay_ms(3);
}

/* Display char function */
void display_char(unsigned char x){
	/* PORT D output du lieu */
	PA = x;
	PC |= (1 << RS); // Chon thanh ghi du lieu DR
	PC &=~(1 << RW); // Chon MODE READ cho thanh ghi DR
	PC |= (1 << RE); // Set chan Enable len 1 de bat dau khung truyen (PC = 0b00000100)
	_delay_us(1);
	PC &=~(1 << RE); // Set chan Enable ve 0 de ket thuc khung truyen (PC = 0b00000000)
	_delay_ms(1);
}

void khoitao_LCD(){
	DA = 0xFF; // Set PORT D output du lieu
	DC = 0xFF;
	_delay_ms(1);
	setup_LCD(0x38); // Ham truyen 8 bit va su dung 2 hang
	setup_LCD(0x0C); // Bat man hinh va tat con tro
	setup_LCD(0x06); // Con tro dich sang phai
	setup_LCD(0x01); // Ham Clear du lieu
	setup_LCD(0x80); // Dua con tro ve vi tri ban dau
}

/* Display string function */
void display_string(char str[]){
	for(int i = 0; str[i] != 0; i++){
		display_char(str[i]);
	}
}

/* Display string at xy position function 
	LCD 16x02 co 16 cot, 2 hang
*/

void display_stringxy(char row, char pos, char str[]){
	if(row == 0 && pos < 16){
		setup_LCD((pos & 0x0F)|0x80);
	}else{
		if(row == 1 && pos < 16){
			setup_LCD((pos & 0x0F)|0xC0);
		}
	}
	display_string(str);
}

/* Clear LCD function */
void clear_LCD(){
	setup_LCD(0x01); // Xoa du lieu
	setup_LCD(0x80); // Dua tro ve vi tri ban dau
}


