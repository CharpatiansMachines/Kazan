/*
 * display.h
 *
 *  Created on: Jul 25, 2023
 *      Author: BRG
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "ssd1306_fonts.h"

#include "enemy_detection.h"
#include "line_detection.h"

void Display_Init();
void Display_Clear();

uint16_t Display_Get_Bottom_YPosition(FontDef* font);
void Draw_Center_Text(char *text, FontDef* font, uint16_t height);
void Draw_Left_Text(char *text, FontDef* font, uint16_t height);
void Draw_Right_Text(char *text, FontDef* font, uint16_t height);

void Display_Title_Screen(char*  title);
void Display_Small_Title_Screen(char*  title);
void Display_2_Numbers(char * title, double number1, double number2);
void Display_Line_Sensors_Output(uint8_t *values, uint8_t valuesNo);
void Display_Enemy_Sensors_Output(uint32_t value);
void Display_Line_Position_Screen(LinePosition lineOutput,uint8_t whiteFilter, uint8_t darkFilter,char *descrition);
void Display_Error();





#endif /* DISPLAY_H_ */
