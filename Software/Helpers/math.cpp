/*
 * Math.cpp
 *
 *  Created on: Aug 27, 2023
 *      Author: BRG
 */

#include <math.hpp>

float Math::linearInterpolation(float x1, float y1, float x2, float y2, float x){
	   // Handling the case where x1 is equal to x2 to prevent division by zero
		if (x1 == x2) {
			return (y1 + y2) / 2.0f; // Return average of y1 and y2
		}
		return y1 + (x - x1) * (y2 - y1) / (x2 - x1);
}


