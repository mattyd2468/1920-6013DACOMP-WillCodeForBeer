#ifndef LED_H_
#define LED_H_

enum class LEDColour {
	GREEN, YELLOW, RED
};

class LED {

public:
	unsigned int redPin;
	unsigned int greenPin;
	unsigned int bluePin;

	// Program variables
	int redVal;   // Variables to store the values to send to the pins
	int greenVal;
	int blueVal;

	LEDColour lastColour;
	LEDColour currentColour;

	LED();
	LED(int redPin, int bluePin, int greenPin);
	void setColour(int redVal, int blueVal, int greenVal);
	boolean colourHasChanged();
};
#endif
