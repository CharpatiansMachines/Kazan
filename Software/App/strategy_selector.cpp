/*
 * strategy_selector.cpp
 *
 *  Created on: Aug 31, 2023
 *      Author: BRG
 */
#include "strategy_selector.h"
#include "display.h"
#include "strategist.h"

struct StrategySelectoScreenrData{
	const char *const title;
	void (Strategist::*strategy)(void);
};
const StrategySelectoScreenrData selectorScreenData[] __attribute__((section(".rodata"))) = {
	{"Search And Attack", &Strategist::Strategy_Search_And_Attack},
};

void StrategySelector::run()
{
	Strategy_Selector_Screen_Type screen = Search_And_Attack_Screen;
	bool start = false;
	while(true)
	{
		userInputs.readButtons();

		if(start)
		{
			if(userInputs.isAnyKey()){
				start = false;
			}else{
				strategist.runCurrentSrategy();
			}
			continue;
		}
		const uint8_t screenIndex = static_cast<int>(screen);
		const StrategySelectoScreenrData screenData = selectorScreenData[screenIndex];

		strategist.setStrategy(screenData.strategy);
		Display_Title_Screen(screenData.title);

		if(userInputs.isReturnBackRequest()){
			return;
		}
		if(userInputs.isBackRequest()){
			screen--;
		}
		if(userInputs.isNextRequest()){
			screen++;
		}
		if(userInputs.isSetValueRequest()){
			start = true;
			Display_Clear();
		}
	}


}




inline Strategy_Selector_Screen_Type operator++(Strategy_Selector_Screen_Type& screen, int) {
	Strategy_Selector_Screen_Type original = screen;

    if (screen == Search_And_Attack_Screen) {
        screen = Search_And_Attack_Screen;
    } else {
        screen = static_cast<Strategy_Selector_Screen_Type>(static_cast<int>(screen) + 1);
    }

    return original; // Return old value for postfix increment
}

inline Strategy_Selector_Screen_Type operator--(Strategy_Selector_Screen_Type& screen, int) {
	Strategy_Selector_Screen_Type original = screen;

    if (screen == Search_And_Attack_Screen) {
        screen = Search_And_Attack_Screen;
    } else {
        screen = static_cast<Strategy_Selector_Screen_Type>(static_cast<int>(screen) - 1);
    }
    return original;
}




