/*
 * display.cpp
 *
 *  Created on: Jul 25, 2023
 *      Author: BRG
 */

#ifndef DISPLAY_CPP_
#define DISPLAY_CPP_
#include "display.h"

#include "ssd1306.h"
#include "stdio.h"
#include "string.h"
#include <cmath>

void Draw_Full_Black(){
	ssd1306_Fill(Black);
}
void Display_Clear(){
	ssd1306_Fill(Black);
	ssd1306_UpdateScreen();
}

void Display_Init(){
	ssd1306_Init();
}

void Draw_Center_Text( char *text, FontDef* font, uint16_t height){
	uint16_t length = strlen(text);
	uint16_t textWidth = length * font->FontWidth;

    if(textWidth <= SSD1306_WIDTH) {
    	uint16_t startX = (SSD1306_WIDTH - textWidth) / 2;
    	ssd1306_SetCursor (startX, height);
    	ssd1306_WriteString(text, *font, White);
    	ssd1306_SetCursor (0, height + font->FontHeight + 1);
    } else {
        // Handle the scenario where the text is too wide for the display. Perhaps truncate or wrap the text.
    	//Find the most closest space to center
    	char* secondText = NULL;
    	char *p = text + length/2;
    	for(uint8_t i = 0; i < length /2 - length % 2 ;i++){
    		if(*(p + i) == ' '){
    			secondText = p + i;
    			break;
    		}else if(*(p - i) == ' '){
    			secondText = p - i;
    			break;
    		}
    	}
    	if(secondText != NULL){
    		int k = secondText - text;
    		char firstText[50];
    		sprintf(firstText, "%.*s", k, text);

    		Draw_Center_Text(firstText, font, height);
    		Draw_Center_Text(secondText + 1, font, SSD1306.CurrentY);


    	}else{
        	Draw_Left_Text(text, font, height);
    	}
    }
}

void Draw_Left_Text(char *text, FontDef* font, uint16_t height){
	ssd1306_SetCursor (0, height);
	ssd1306_WriteString(text, *font, White);
	ssd1306_SetCursor (0, height + font->FontHeight + 1);
}

void Draw_Right_Text(char *text, FontDef* font, uint16_t height){
	uint16_t length = strlen(text);
	uint16_t textWidth = length * font->FontWidth;
	if(textWidth <= SSD1306_WIDTH){
		uint16_t startX = (SSD1306_WIDTH - textWidth -1);
		ssd1306_SetCursor (startX, height);
		ssd1306_WriteString(text, *font, White);
		ssd1306_SetCursor (0, height + font->FontHeight + 1);

	}else{
		Draw_Left_Text(text, font, height);
	}
}

void Display_Title_Screen(char * title){
	Draw_Full_Black();

	Draw_Center_Text((char *)"Start", &Font_7x10, 0);

	Draw_Center_Text(title, &Font_11x18, SSD1306.CurrentY);

	uint16_t yPosition = Display_Get_Bottom_YPosition(&Font_7x10);

	Draw_Left_Text ((char *)"<Back", &Font_7x10, yPosition);

	Draw_Right_Text ((char *)"Next>", &Font_7x10, yPosition);

	ssd1306_UpdateScreen();
}

void Display_Small_Title_Screen(char*  title){
	Draw_Full_Black();

	Draw_Center_Text((char *)"Start", &Font_7x10, 0);

	Draw_Center_Text(title, &Font_7x10, SSD1306.CurrentY);

	uint16_t yPosition = Display_Get_Bottom_YPosition(&Font_7x10);

	Draw_Left_Text ((char *)"<Back", &Font_7x10, yPosition);

	Draw_Right_Text ((char *)"Next>", &Font_7x10, yPosition);

	ssd1306_UpdateScreen();
}

void Display_2_Numbers(char * title, double number1, double number2){
	char s[40];

	Draw_Full_Black();

	Draw_Center_Text(title, &Font_7x10, 0);

	sprintf(s,"%f", number1);
	Draw_Center_Text(s, &Font_7x10, SSD1306.CurrentY);


	sprintf(s,"%f", number2);
	Draw_Center_Text(s, &Font_7x10, SSD1306.CurrentY);

	ssd1306_UpdateScreen();
}


void Draw_3_Points_Line(bool t[3], char* trueString, char*falseString,uint16_t height){
	if(t[0]){
		Draw_Left_Text(trueString,&Font_7x10, height);
	}else{
		Draw_Left_Text(falseString, &Font_7x10, height);
	}
	if(t[1]){
		Draw_Center_Text(trueString,&Font_7x10, height);
	}else{
		Draw_Center_Text(falseString, &Font_7x10, height);
	}
	if(t[2]){
		Draw_Right_Text(trueString,&Font_7x10, height);
	}else{
		Draw_Right_Text(falseString, &Font_7x10, height);
	}

}

void Display_Enemy_Sensors_Output(uint32_t value){
	char s[80];
	Draw_Full_Black();

	Draw_Center_Text((char *)"Enemy Sensors", &Font_7x10, 0);
	sprintf(s, "s0=%d, s1=%d, s2=%d, s3=%d, s4=%d, s5=%d, s6=%d, s7=%d",
	    value & 0x01 ? 1 : 0,
	    (value & 0x02) >> 1,
	    (value & 0x04) >> 2,
	    (value & 0x08) >> 3,
	    (value & 0x10) >> 4,
	    (value & 0x20) >> 5,
	    (value & 0x40) >> 6,
	    (value & 0x80) >> 7
	);
	ssd1306_UpdateScreen();

}

void Draw_Circular_Arc_Text( char *text, FontDef* font, uint16_t height)
{
	uint16_t length = strlen(text);
	float wDistance = SSD1306_WIDTH;
		wDistance /= length;
	float heightDiff = 1;
	for(uint8_t i = 0; i< length; i++)
	{
		uint8_t x = wDistance * i;
		uint8_t y = height + std::abs(length/2 - i) * heightDiff;
		ssd1306_SetCursor(x,  y);
		ssd1306_WriteChar(text[i], *font, White);
	}
	ssd1306_SetCursor(0, height + font->FontHeight + 1);
}

//void Display_Enemy_Sensors_Votes(int8_t votes[EnemyPosition::POSITIONED_NO]){
//	FontDef font = Font_6x8;
//	char s[50] ="";
//	Display_Clear();
//	Draw_Circular_Arc_Text((char *)"0|1|2|3|4|5|6|7|8|9|A|B|C", &Font_6x8, 0);
//	for(int i = 0; i < 13; i++) {
//		char temp[12];
//		if(votes[i] < 10){
//			snprintf(temp, sizeof(temp), "%d|", votes[i]);
//		}else{
//			snprintf(temp, sizeof(temp), "%c|",'A' + votes[i]);
//		}
//
//		strcat(s, temp);
//	}
//	strcpy(s,"");
//}

void Display_Enemy_Sensors_Votes(int8_t votes[EnemyPosition::KNOWN_POSITIONS_NO]){
	FontDef font = Font_6x8;
	Draw_Full_Black();
	float hDistance = SSD1306_HEIGHT;
	hDistance/= EnemyPosition::PROXIMITY_NO;
	float wDistance = SSD1306_WIDTH;
	wDistance /= EnemyPosition::DIRECTIONS_NO;
	float rowHeight = 2;



	for(uint8_t id = 0; id <EnemyPosition::KNOWN_POSITIONS_NO; id++)
	{
		EnemyPosition pos(id);
		uint8_t x = pos.direction * wDistance;
		float yBase = (EnemyPosition::PROXIMITY_NO - pos.proximity -1) * hDistance;
		uint8_t y = yBase + pos.getDistanceFromCenterDirection() * rowHeight;

		ssd1306_SetCursor((uint8_t)x, (uint8_t) y);
		ssd1306_WriteChar('a' + id, font, White);
	}
	ssd1306_UpdateScreen();

}



void Display_N_Values_Screen(uint8_t *values, uint8_t valuesNo){
	Draw_Full_Black();
	ssd1306_SetCursor (0, 0);
	for(uint8_t i = 0; i < valuesNo; i+=2)
	{
		char s[80];
		sprintf(s, "s%d = %d, s%d =%d", i, values[i],i+1,values[i+1]);
		Draw_Center_Text(s, &Font_7x10, SSD1306.CurrentY);
	}

	ssd1306_UpdateScreen();
}

void Display_Line_Position_Screen(LinePosition lineOutput,uint8_t whiteFilter, uint8_t darkFilter, char *descrition){
	char X[] = "X";
	char O[] = "O";
	char s[40];



	Draw_Full_Black();

	bool values1[] = {lineOutput.isFrontLeft(),lineOutput.isFront(), lineOutput.isFrontRight()};
	bool values2[] = {lineOutput.isLeft(),lineOutput.isNone(), lineOutput.isRight()};
	bool values3[] = {lineOutput.isBackLeft(),lineOutput.isBack(), lineOutput.isBackRight()};
	Draw_3_Points_Line(values1, X, O, 0);

	sprintf(s,"white = %d", whiteFilter);
	Draw_Center_Text(s, &Font_7x10, SSD1306.CurrentY);
	Draw_3_Points_Line(values2, X, O,  SSD1306.CurrentY);

	sprintf(s,"black = %d", darkFilter);
	Draw_Center_Text(s, &Font_7x10, SSD1306.CurrentY);

	if(descrition != NULL){
		Draw_Center_Text(descrition, &Font_7x10, SSD1306.CurrentY);
	}


	Draw_3_Points_Line(values3, X, O, Display_Get_Bottom_YPosition(&Font_7x10));


	ssd1306_UpdateScreen();
}
void Display_2_Power_And_Time_Screen(char * title, int8_t leftPower, int8_t rightPower,int64_t time,char * description){
	char s[50];
	FontDef font = Font_7x10;
	Draw_Full_Black();
	Draw_Center_Text(title, &Font_11x18, 0);

	sprintf(s,"%d  %d",leftPower,rightPower);
	Draw_Center_Text(s, &font, SSD1306.CurrentY + Font_7x10.FontHeight /2);

	sprintf(s,"Timer = %d",time);
	Draw_Center_Text(s, &font, SSD1306.CurrentY + Font_7x10.FontHeight / 2);

	Draw_Center_Text(description, &font, Display_Get_Bottom_YPosition(&font));
	ssd1306_UpdateScreen();
}

void Display_2_Power_Screen(char *title, int8_t leftPower, int8_t rightPower,char * description)
{
	char s[50];
	FontDef font = Font_7x10;
	Draw_Full_Black();
	Draw_Center_Text(title, &font, 0);

	sprintf(s,"%d  %d",leftPower,rightPower);
	Draw_Center_Text(s, &font, SSD1306.CurrentY + Font_7x10.FontHeight /2);

	Draw_Center_Text(description, &font, Display_Get_Bottom_YPosition(&font));
	ssd1306_UpdateScreen();
}


void Display_Error(){
	Display_Title_Screen((char *)"Default Error");
}


uint16_t Display_Get_Bottom_YPosition(FontDef* font){
	return SSD1306_HEIGHT - font->FontHeight -1;
}





#endif /* DISPLAY_CPP_ */
