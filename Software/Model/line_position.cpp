/*
 * line_position.cpp
 *
 *  Created on: Aug 14, 2023
 *      Author: BRG
 */

#include "line_position.h"

LinePosition::LinePosition() : linePosition(LinePositionType::None) {}

void LinePosition::setLinePosition(LinePositionType position) {
    linePosition = position;
}

LinePosition::LinePositionType LinePosition::getLinePosition() const {
    return linePosition;
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

bool LinePosition::isNotNone() const {
    return linePosition != LinePositionType::None;
}
