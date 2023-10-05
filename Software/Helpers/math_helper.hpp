/*
 * math.h
 *
 *  Created on: Aug 27, 2023
 *      Author: BRG
 */

#ifndef HELPERS_MATH_HELPER_HPP_
#define HELPERS_MATH_HELPER_HPP_

class MathHelper{
public:
	static float linearInterpolation(float x1, float y1, float x2, float y2, float x);
	static float normalizeData(float data, float minBound, float maxBound);
	static float constraintData(float data, float minConstraint, float maxConstraint);
};




#endif /* HELPERS_MATH_HELPER_HPP_ */
