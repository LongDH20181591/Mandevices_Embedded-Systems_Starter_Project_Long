/*
 * hs1101_LCD.cpp
 *
 * Created: 10/22/2021 4:38:10 PM
 * Author : Zbook 15 G3
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Include/Src/myLCD.c"


volatile unsigned int count_xung = 0;
volatile unsigned char count_time = 0;
char humid[10];
char freq[10];
uint16_t HS[101]={7410, 7392, 7374, 7357, 7340, 7323, 7307, 7290, 7274, 7259,
			 7243, 7228, 7213, 7198, 7183, 7169, 7155, 7140, 7127, 7113,
			 7099, 7086, 7072, 7059, 7046, 7033, 7020, 7007, 6995, 6982,
			 6969, 6957, 6945, 6932, 6920, 6908, 6896, 6884, 6872, 6860,
			 6848, 6836, 6824, 6812, 6800, 6788, 6776, 6764, 6752, 6740,
			 6728, 6716, 6704, 6692, 6680, 6668, 6656, 6643, 6631, 6619,
			 6606, 6594, 6581, 6568, 6556, 6543, 6530, 6517, 6504, 6491,
			 6477, 6464, 6450, 6437, 6423, 6409, 6395, 6381, 6367, 6352,
			 6338, 6323, 6309, 6294, 6279, 6264, 6248, 6233, 6217, 6202,
			 6186, 6170, 6154, 6137, 6121, 6104, 6087, 6070, 6053, 6036, 6019};

void turnOn_INT0(void);
void turnOn_TC1(void);

int main(void)
{	
	/* Turn on LCD */
	khoitao_LCD();
	char str[] = "Do am:";
	char str1[] = "Tan so:";
	display_stringxy(0, 0, str);
	display_stringxy(1, 0, str1);
	/* Turn on Interrupt 0 */
	turnOn_INT0();
	/* Turn on Timer/Counter 1 */
	turnOn_TC1();
    while (1) 
    {
		//
    }
}

void turnOn_INT0(){
	DDRD = (0 << PIND2); // set pin D2 input
	GICR = (1 << INT0);  // Turn on INT_0
	/*
		Select mode for INT_0 
		MODE: Falling edge
	*/
	MCUCR = (1 << ISC01)|(0 << ISC00);
	sei();
}

/* Ne555 truyen 1 xung toi VDK, bien count tang len 1 don vi */
ISR(INT0_vect){
	count_xung++;
}

/* Tao khoang thoi gian dinh thi 50ms bang Timer/Counter1 
	Clock select: Prescaler = 8
	Luu gia tri dem: TCNT1
	Khai bao ngat tran T/C1
	Set bit I cho phep ngat toan cuc
*/

void turnOn_TC1(){
	TCCR1B = (0 << CS12)|(1 << CS11)|(0 << CS10);
	TCNT1 = 15535;
	TIMSK = (1 << TOIE1);
	sei();
}

/*
	Khoi tao bien dem count_time de dem khoang thoi gian 1s 
	count_time = 20, doi chieu gia tri count_xung voi mang HS[101]
	Sau do, dua count_xung va count_time ve = 0 de bat dau qua trinh moi
 */

ISR(TIMER1_OVF_vect){
	TCNT1 = 15535;
	count_time++;
	if(count_time == 20){
		for(int i = 0; i < 100; i++){
			if((count_xung <= HS[i]) && (count_xung >= HS[i+1])){
					sprintf(humid, " %d %%", i);
					display_stringxy(0, 8, humid);
					sprintf(freq, " %d Hz", count_xung);
					display_stringxy(1, 8, freq);
			} 
		}
		/* Dua count_xung va count_time ve = 0 de bat dau qua trinh moi */
		count_time = 0;
		count_xung = 0;
	}
}


