#pragma once

const int DISPLAY_WIDTH = 640;	
const int DISPLAY_HEIGHT = 360;
const int DISPLAY_SCALE = 2;
const float relativeToScreenWidth = (DISPLAY_WIDTH / 640);		// Makes the value multiplied by this constant, relative to the screen width
const float relativeToScreenHeight = (DISPLAY_HEIGHT / 360);	// Makes the value multiplied by this constant, relative to the screen height
const float ballSpeed = 4.5F * relativeToScreenHeight;
const float paddleSpeed = 5.0F * relativeToScreenWidth;


enum ObjectType {
	TYPE_BALL,
	TYPE_BRICK
};


