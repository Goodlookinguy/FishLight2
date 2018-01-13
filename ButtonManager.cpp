// 
// 
// 

#include "BuildConsts.h"
#include "ButtonManager.h"
#include "FishLightProgram.h"

bool ButtonManager::InRange(int32_t value, int32_t low, int32_t high)
{
	return value >= low && value <= high;
}

Button ButtonManager::ButtonPressToButton(int16_t button) const
{
	if (InRange(button, ButtonRanges[0], ButtonRanges[0 + 1]))
		return Button::None;

	if (InRange(button, ButtonRanges[1 * 2], ButtonRanges[1 * 2 + 1]))
		return Button::Left;

	if (InRange(button, ButtonRanges[2 * 2], ButtonRanges[2 * 2 + 1]))
		return Button::Right;

	if (InRange(button, ButtonRanges[3 * 2], ButtonRanges[3 * 2 + 1]))
		return Button::Up;

	if (InRange(button, ButtonRanges[4 * 2], ButtonRanges[4 * 2 + 1]))
		return Button::Down;
	
#if FIVE_BUTTON_BUILD
	if (InRange(button, ButtonRanges[5 * 2], ButtonRanges[5 * 2 + 1]))
		return Button::Enter;
#endif

	return Button::None;
}

void ButtonManager::Update(FishLightProgram* program)
{
	if (ButtonPin == -1)
		return; // when no button pins defined

	int16_t rawButton = analogRead(this->ButtonPin);
	Button button = this->ButtonPressToButton(rawButton);
	bool sameButton = this->LastButtonPressed == button;
	
	if (!sameButton)
	{
		this->LastButtonPressed = button;
		this->LastButtonPressTime = millis();
		this->LastButtonActivateTime = 0;
	}

	if (button == Button::None)
		return;

	uint64_t timeActive = millis() - this->LastButtonPressTime;
	uint64_t waitTime = millis() - this->LastButtonActivateTime;
	if (timeActive >= this->RegisterTime && waitTime > this->SameButtonRegisterWaitTime)
	{
		this->LastButtonActivateTime = millis();
		program->OnButtonPressed(button);
	}
}

//void ButtonManager::Update(NduinoProgram* program)
//{
//	//Serial.write("ButtonManager::Update");
//	this->UpdateButtonsStatus(program);
//}

void ButtonManager::RegisterButtonsPin(uint8_t pin)
{
	this->ButtonPin = pin;
}

//NduinoEvent<ButtonPressedEventArgs>* ButtonManager::ButtonPressed()
//{
//	return this->m_buttonPressed;
//}

