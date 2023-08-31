/*
 * line_position.h
 *
 *  Created on: Aug 14, 2023
 *      Author: BRG
 */

#ifndef MODEL_LINE_POSITION_H_
#define MODEL_LINE_POSITION_H_

// Enum defining each possible line position
enum class LinePositionType {
	FrontLeft,
	Front,
	FrontRight,
	BackLeft,
	Back,
	BackRight,
	Left,
	Right,
	None
};
class LinePosition {
public:


    LinePosition();


    void setLinePosition(LinePositionType position);

    LinePositionType getLinePosition() const;

    bool operator==(const LinePosition& other) const;
    bool operator!=(const LinePosition& other) const;

    bool isFrontLeft() const;
    bool isFront() const;
    bool isFrontRight() const;
    bool isBackLeft() const;
    bool isBack() const;
    bool isBackRight() const;
    bool isLeft() const;
    bool isRight() const;
    bool isNone() const;
    bool isDetected() const;


private:
    LinePositionType linePosition;
};





#endif /* MODEL_LINE_POSITION_H_ */
