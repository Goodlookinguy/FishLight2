
#include "FishLightProgram.h"
/*DS3231  rtc(SDA, SCL);
Time  t;
Time oldt;
int temp;
int oldtemp;*/
uint64_t ramTime; // remove this when compiling for reals dawg

void setup()
{
	FishLightProgram::Instance()->Init();
	ramTime = millis();
}

void loop()
{
	FishLightProgram::Instance()->Update();

	if (millis() - ramTime >= 1000UL)
	{
		ramTime = millis();
		//Serial.print("Free RAM: ");
		//Serial.println(freeRam());
	}
}


//https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory
int freeRam()
{
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}


/*
const int16_t ButtonRanges[10]
{
	1015, 1023, // idle, none
	5, 20, // left (1)
	65, 80, // right (2)
	116, 131, // up (3)
	165, 180 // down (4)
};

bool InRange(int32_t value, int32_t low, int32_t high)
{
	return value >= low && value <= high;
}

int32_t ButtonPressToButton(int16_t button)
{
	if (InRange(button, ButtonRanges[0], ButtonRanges[0 + 1]))
		return FishLightButton::None;
	
	if (InRange(button, ButtonRanges[1 * 2], ButtonRanges[1 * 2 + 1]))
		return FishLightButton::Left;

	if (InRange(button, ButtonRanges[2 * 2], ButtonRanges[2 * 2 + 1]))
		return FishLightButton::Right;

	if (InRange(button, ButtonRanges[3 * 2], ButtonRanges[3 * 2 + 1]))
		return FishLightButton::Up;

	if (InRange(button, ButtonRanges[4 * 2], ButtonRanges[4 * 2 + 1]))
		return FishLightButton::Down;

	return FishLightButton::None;
}

void loop()
{
	int32_t buttonPress = analogRead(PIN_BUTTONS);
	int32_t buttonPressed = ButtonPressToButton(buttonPress);
	//controlPanel->clear();
	//controlPanel->write(buttonPressed + 48);
	//char bpn[4];
	//sprintf(bpn, "%d", buttonPress);
	//controlPanel->setCursor(0, 1);
	//controlPanel->write(bpn);
	
	t = rtc.getTime(); //gets the time

	if (t.sec != oldt.sec) //compares the seconds only
	{ 
		oldt.sec = t.sec;  //sets the old time with the new time
		controlPanel->setCursor(0, 1); //moves the cursor to the first column and second row
		controlPanel->write(rtc.getTimeStr(), 8); //gets and writes the time to the LCD
		
		temp = rtc.getTemp();//gets the temperature from the RTC
		if (temp != oldtemp) //if the temperature changes update the LCD
		{
			oldtemp = temp;//sets old temp with the new temp
			//char charTemp[3]; //creates a charecter array 
			//itoa(temp, charTemp, 3);//converts the temp value to a character array and stores it in charTemp
			controlPanel->setCursor(12, 1);//moves the cursor to write at the lower left corner of the LCD
			//controlPanel->write(charTemp, 2);//writes the temp value
			controlPanel->print(temp);
			controlPanel->print(char(0xDF));//prints the degree symbol
			controlPanel->write("C", 1);
		}
	}

	if (buttonPressed != lastButtonPressed)
	{
		controlPanel->home();
		if (buttonPressed == FishLightButton::None)
		{
			controlPanel->write("None ", 5);

			analogWrite(PIN_WHITE_LEDS, 50);
			analogWrite(PIN_RBG_LEDS_GREEN, 50);
			analogWrite(PIN_RBG_LEDS_RED, 50);
			analogWrite(PIN_RBG_LEDS_BLUE, 50);
		}
		else if (buttonPressed == FishLightButton::Left)
		{
			controlPanel->write("Left ", 5);

			analogWrite(PIN_WHITE_LEDS, 0);
			analogWrite(PIN_RBG_LEDS_GREEN, 255);
			analogWrite(PIN_RBG_LEDS_RED, 0);
			analogWrite(PIN_RBG_LEDS_BLUE, 0);
		}
		else if (buttonPressed == FishLightButton::Right)
		{
			controlPanel->write("Right", 5);

			analogWrite(PIN_WHITE_LEDS, 0);
			analogWrite(PIN_RBG_LEDS_GREEN, 0);
			analogWrite(PIN_RBG_LEDS_RED, 255);
			analogWrite(PIN_RBG_LEDS_BLUE, 0);
		}
		else if (buttonPressed == FishLightButton::Up)
		{
			controlPanel->write("Up   ", 5);

			analogWrite(PIN_WHITE_LEDS, 0);
			analogWrite(PIN_RBG_LEDS_GREEN, 0);
			analogWrite(PIN_RBG_LEDS_RED, 0);
			analogWrite(PIN_RBG_LEDS_BLUE, 255);
		}
		else if (buttonPressed == FishLightButton::Down)
		{
			controlPanel->write("Down ", 5);

			analogWrite(PIN_WHITE_LEDS, 255);
			analogWrite(PIN_RBG_LEDS_GREEN, 255);
			analogWrite(PIN_RBG_LEDS_RED, 255);
			analogWrite(PIN_RBG_LEDS_BLUE, 255);
		}
	}
	delay(10);
}*/
