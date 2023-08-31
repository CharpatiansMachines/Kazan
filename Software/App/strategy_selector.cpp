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
const StrategySelectoScreenrData selectorScreenData[] = {
		{"Search And Attack", &Strategist::Strategy_Search_And_Attack}
};

void StrategySelector::run()
{
	Strategy_Selector_Screen_Type screen;
	bool start = false;
	while(true)
	{
		userInputs.readInputs();
		if(start){
			if(userInputs.isAnyKey()){
				start = false;
			}else{
				strategist.runCurrentSrategy();
			}
			break;
		}
		const uint8_t screenIndex = static_cast<int>(screen);
		const StrategySelectoScreenrData screenData = selectorScreenData[screenIndex];

		strategist.setStrategy(screenData.strategy);
		Display_Title_Screen(screenData.title);

		if(userInputs.isBackRequest()){
			screen--;
		}
		if(userInputs.isNextRequest()){
			screen++;
		}
		if(userInputs.isSetValueRequest()){
			start = true;
			Display_Clear();
			break;
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




