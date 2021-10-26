/*
 * lcd16x2.h
 *
 * Created: 10/13/2021 1:22:26 PM
 *  Author: Administrator
 */ 

#ifndef __LCD16X2_H
#define __LCD16X2_H    14032014
#include "main.h"


// ??c 2 nibbles t? LCD //
char Read2Nib();

// Ghi 2 nibbles vào LCD //
void Write2Nib(uint8_t chr);

// Ghi 8 bit tr?c ti?p vào LCD //
void Write8Bit(uint8_t chr);

//Hàm ch? LCD r?nh //
void wait_LCD();

// Hàm kh?i ??ng LCD //
void init_LCD();

// Di chuy?n con tr? //
void home_LCD();
void move_LCD(uint8_t y,uint8_t x);

// Hi?n th? lên LCD //
void clr_LCD() ;              // clear man hinh

void putChar_LCD(uint8_t chr);    //hi?n th? 1 ký t? chr lên LCD

void print_LCD(char* str, unsigned char len);    //Hi?n th? 1 chu?i ký t?


#endif