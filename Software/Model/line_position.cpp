/*
 * line_position.cpp
 *
 *  Created on: Aug 14, 2023
 *      Author: BRG
 */

#include "line_position.h"
#include <stdio.h>

LinePosition::LinePosition() : linePosition(LinePositionType::None) {}

void LinePosition::setLinePosition(LinePositionType position) {
    linePosition = position;
}

LinePositionType LinePosition::getLinePosition() const {
    return linePosition;
}

bool LinePosition::operator==(const LinePosition& other) const {
    return this->linePosition == other.linePosition;
}

bool LinePosition::operator!=(const LinePosition& other) const {
    return !(*this == other);
}

bool LinePosition::isFrontLeft() const {
    return linePosition == LinePositionType::FrontLeft;
}

bool LinePosition::isFront() const {
    return linePosition == LinePositionType::Front;
}

bool LinePosition::isFrontRight() const {
    return linePosition == LinePositionType::FrontRight;
}

bool LinePosition::isBackLeft() const {
    return linePosition == LinePositionType::BackLeft;
}

bool LinePosition::isBack() const {
    return linePosition == LinePositionType::Back;
}

bool LinePosition::isBackRight() const {
    return linePosition == LinePositionType::BackRight;
}

bool LinePosition::isLeft() const {
    return linePosition == LinePositionType::Left;
}

bool LinePosition::isRight() const {
    return linePosition == LinePositionType::Right;
}

bool LinePosition::isNone() const {
    return linePosition == LinePositionType::None;
}

bool LinePosition::isDetected() const {
    return linePosition != LinePositionType::None;
}

void LinePosition::toString(char *s) const{
	switch(linePosition){
		case LinePositionType::FrontLeft:
			sprintf(s,"Front Left");
			break;
		case LinePositionType::Front:
			sprintf(s,"Front");
			break;
		case LinePositionType::FrontRight:
			sprintf(s,"Front Right");
			break;
		case LinePositionType::BackLeft:
			sprintf(s,"Back Left");
			break;
		case LinePositionType::Back:
			sprintf(s,"Back");
			break;
		case LinePositionType::BackRight:
			sprintf(s,"Back Right");
			break;
		case LinePositionType::Left:
			sprintf(s,"Left");
			break;
		case LinePositionType::Right:
			sprintf(s,"Right");
			break;
		default:
			break;

	}
}
