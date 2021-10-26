/*
 * main.h
 *
 * Created: 10/13/2021 12:55:14 PM
 *  Author: Administrator
 */ 

#ifndef __MAIN_H
#define __MAIN_H    5072014

#define F_CPU 32000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "lcd16x2.h"
#include "ds18b20.h"

#define sbi(sfr,bit) sfr |=_BV(bit)
#define cbi(sfr,bit) sfr &= ~(_BV(bit))
#define EN             2
#define RW             1
#define RS             0
#define CTRL           PORTB
#define DDR_CTRL       DDRB

#define DATA_O         PORTB
#define DATA_I         PINB
#define DDR_DATA       DDRB
#define DS18B20_PIN_DQ     PIND7
#define DS18B20_PORT_DQ    PORTD7
#define DS18B20_DDR_DQ     DDRD7

int temp_Register; //bien de luu 2 byte du lieu nhiet do
float temp; // nhiet do moi truong


#endif /* MAIN_H_ */