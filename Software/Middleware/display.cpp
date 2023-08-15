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

void Display_Init(){
//	ssd1306_Init();
}

void Draw_Center_Text( char *text, FontDef* font, uint16_t height){
//	uint16_t length = strlen(text);
//	uint16_t textWidth = length * font->FontWidth;
//
//    if(textWidth <= SSD1306_WIDTH) {
//    	uint16_t startX = (SSD1306_WIDTH - textWidth) / 2;
//    	SSD1306_GotoXY (startX, height);
//		SSD1306_Puts(text, font, SSD1306_COLOR_WHITE);
//		SSD1306_GotoXY (0, height + font->FontHeight + 1);
//    } else {
//        // Handle the scenario where the text is too wide for the display. Perhaps truncate or wrap the text.
//    	char* secondText = strchr(text, ' ');
//    	if(secondText != NULL){
//    		int k = secondText - text;
//    		char firstText[50];
//    		sprintf(firstText, "%.*s", k, text);
//
//    		Draw_Center_Text(firstText, font, height);
//    		Draw_Center_Text(secondText + 1, font, SSD1306.CurrentY);
//
//
//    	}else{
//        	Draw_Center_Text(text, font, height);
//    	}
//    }
}

void Draw_Left_Text(char *text, FontDef* font, uint16_t height){
//	SSD1306_GotoXY (0, height);
//	SSD1306_Puts(text, font, SSD1306_COLOR_WHITE);
//	SSD1306_GotoXY (0, height + font->FontHeight + 1);
}

void Draw_Right_Text(char *text, FontDef* font, uint16_t height){
//	uint16_t length = strlen(text);
//	uint16_t textWidth = length * font->FontWidth;
//	if(textWidth <= SSD1306_WIDTH){
//		uint16_t startX = (SSD1306_WIDTH - textWidth -1);
//		SSD1306_GotoXY (startX, height);
//		SSD1306_Puts(text, font, SSD1306_COLOR_WHITE);
//		SSD1306_GotoXY (0, height + font->FontHeight + 1);
//
//	}else{
//		Draw_Left_Text(text, font, height);
//	}
}

void Display_Title_Screen(char * title){
//	SSD1306_Clear();
//
//	Draw_Center_Text((char *)"Start", &Font_7x10, 0);
//
//	Draw_Center_Text(title, &Font_11x18, SSD1306.CurrentY);
//
//	uint16_t yPosition = Display_Get_Bottom_YPosition(&Font_7x10);
//
//	Draw_Left_Text ((char *)"<Back", &Font_7x10, yPosition);
//
//	Draw_Right_Text ((char *)"Next>", &Font_7x10, yPosition);
//
//	SSD1306_UpdateScreen();
}

void Display_Small_Title_Screen(char*  title){
//	SSD1306_Clear();
//
//	Draw_Center_Text((char *)"Start", &Font_7x10, 0);
//
//	Draw_Center_Text(title, &Font_7x10, SSD1306.CurrentY);
//
//	uint16_t yPosition = Display_Get_Bottom_YPosition(&Font_7x10);
//
//	Draw_Left_Text ((char *)"<Back", &Font_7x10, yPosition);
//
//	Draw_Right_Text ((char *)"Next>", &Font_7x10, yPosition);
//
//	SSD1306_UpdateScreen();
}

void Display_2_Numbers(char * title, double number1, double number2){
//	char s[40];
//
//	SSD1306_Clear();
//
//	Draw_Center_Text(title, &Font_7x10, 0);
//
//	sprintf(s,"%f", number1);
//	Draw_Center_Text(s, &Font_7x10, SSD1306.CurrentY);
//
//
//	sprintf(s,"%f", number2);
//	Draw_Center_Text(s, &Font_7x10, SSD1306.CurrentY);
//
//	SSD1306_UpdateScreen();
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
//	char s[80];
//	SSD1306_Clear();
//
//	Draw_Center_Text("Enemy Sensors", &Font_7x10, 0);
//	sprintf(s, "s0=%d, s1=%d, s2=%d, s3=%d, s4=%d, s5=%d, s6=%d, s7=%d",
//	    value & 0x01 ? 1 : 0,
//	    (value & 0x02) >> 1,
//	    (value & 0x04) >> 2,
//	    (value & 0x08) >> 3,
//	    (value & 0x10) >> 4,
//	    (value & 0x20) >> 5,
//	    (value & 0x40) >> 6,
//	    (value & 0x80) >> 7
//	);
//	Draw_Center_Text(text, font, height)00

}

void Display_Line_Output_Screen(LinePosition lineOutput,uint8_t whiteFilter, uint8_t darkFilter, char *descrition){
//	char X[] = "X";
//	char O[] = "O";
//	char s[40];
//
//
//
//	SSD1306_Clear();
//
//	bool values1[] = {lineOutput.isFrontLeft(),lineOutput.isFront(), lineOutput.isFrontRight()};
//	bool values2[] = {lineOutput.isLeft(),lineOutput.isNone(), lineOutput.isRight()};
//	bool values3[] = {lineOutput.isBackLeft(),lineOutput.isBack(), lineOutput.isBackRight()};
//	Draw_3_Points_Line(values1, X, O, 0);
//
//	sprintf(s,"white = %d", whiteFilter);
//	Draw_Center_Text(s, &Font_7x10, SSD1306.CurrentY);
//	Draw_3_Points_Line(values2, X, O,  SSD1306.CurrentY);
//
//	sprintf(s,"black = %d", darkFilter);
//	Draw_Center_Text(s, &Font_7x10, SSD1306.CurrentY);
//
//	if(descrition != NULL){
//		Draw_Center_Text(descrition, &Font_7x10, SSD1306.CurrentY);
//	}
//
//
//	Draw_3_Points_Line(values3, X, O, Display_Get_Bottom_YPosition(&Font_7x10));
//
//
//	SSD1306_UpdateScreen();
}


void Display_Error(){
//	Display_Title_Screen((char *)"Default Error");
}


uint16_t Display_Get_Bottom_YPosition(FontDef* font){
//	return SSD1306_HEIGHT - font->FontHeight -1;
}





#endif /* DISPLAY_CPP_ */
