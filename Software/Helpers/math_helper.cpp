/*
 * Math.cpp
 *
 *  Created on: Aug 27, 2023
 *      Author: BRG
 */

#include <math_helper.hpp>

/**
 * Linearly interpolates between two points (x1, y1) and (x2, y2) given an x value.
 *
 * @param x1 The x-coordinate of the first point.
 * @param y1 The y-coordinate of the first point.
 * @param x2 The x-coordinate of the second point.
 * @param y2 The y-coordinate of the second point.
 * @param x  The x value for which the y value is to be interpolated.
 * @return   The interpolated y value corresponding to the provided x.
 */
float MathHelper::linearInterpolation(float x1, float y1, float x2, float y2, float x){
	   // Handling the case where x1 is equal to x2 to prevent division by zero
		if (x1 == x2) {
			return (y1 + y2) / 2.0f; // Return average of y1 and y2
		}
		return y1 + (x - x1) * (y2 - y1) / (x2 - x1);
}

/**
 * Normalizes the given data value to a range between 0 and 1 based
 * If minRange and maxRange are the same, a value of 1 is returned.
 *
 * @param data     The data value to be normalized.
 * @param minRange The minimum bound for normalization.
 * @param maxRange The maximum bound for normalization.
 * @return         The normalized data value between 0 and 1.
 */
float MathHelper::normalizeData(float data, float minRange, float maxRange){
	if(maxRange == minRange)
		return 1;
	data = constraintData(data, minRange, maxRange);
	data -= minRange;
	return data / (maxRange - minRange);
}



/**
 * Constrains the given data value to lie between minLimit and maxLimit.
 *
 * @param data     The data value to be constrained.
 * @param minLimit The minimum allowable value for the data.
 * @param maxLimit The maximum allowable value for the data.
 * @return         The constrained data value.
 */
float MathHelper::constraintData(float data, float minLimit, float maxLimit){
	if(data < minLimit)
		return  minLimit;
	if(data > maxLimit)
		return maxLimit;
	return data;
}


