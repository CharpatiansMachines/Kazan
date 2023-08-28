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
void Draw_Full_Black();
void Display_Clear();

uint16_t Display_Get_Bottom_YPosition(FontDef* font);
void Draw_Center_Text(const char *text, FontDef* font, uint16_t height);
void Draw_Left_Text(const char *text, FontDef* font, uint16_t height);
void Draw_Right_Text(const char *text, FontDef* font, uint16_t height);

void Display_Title_Screen(const char*  title);
void Display_Small_Title_Screen(const char*  title);
void Display_2_Numbers(const char * title, double number1, double number2);
void Display_N_Values_Screen(uint8_t *values, uint8_t valuesNo);
void Display_Enemy_Sensors_Output(uint32_t value);
void Display_Enemy_Sensors_Votes(int8_t votes[EnemyPosition::KNOWN_POSITIONS_NO]);
void Display_Line_Position_Screen(LinePosition lineOutput,uint8_t whiteFilter, uint8_t darkFilter,const char *descrition);
void Display_2_Power_And_Time_Screen(const char * titleScreen, int8_t leftPower, int8_t rightPower,int64_t time,const char * actionDescriptionText);

void Display_2_Power_Screen(const char *title, int8_t leftPower, int8_t rightPower,const char * description);
void Display_Error();





#endif /* DISPLAY_H_ */
