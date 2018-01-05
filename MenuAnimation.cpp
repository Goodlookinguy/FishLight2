// 
// 
// 

#include "MenuAnimation.h"
#include "LiquidCrystal.h"

MenuAnimation::MenuAnimation(const uint8_t charId, const uint8_t totalFrames)
{
	this->m_charId = charId;
	this->totalFrames = totalFrames;
	this->frames = new TinyArray<uint8_t*>(totalFrames, true);
}

MenuAnimation::MenuAnimation(const uint8_t charId, const uint8_t totalFrames, const uint8_t hertz)
{
	this->m_charId = charId;
	this->totalFrames = totalFrames;
	this->hertz = hertz;
	this->frames = new TinyArray<uint8_t*>(totalFrames, true);
}

void MenuAnimation::SetFrame(const uint8_t id, uint8_t* frameData) const
{
	(*this->frames)[id] = frameData;
}

void MenuAnimation::Play(const uint8_t initFrame)
{
	this->curIndex = initFrame;
	this->m_startTime = millis();
	this->m_active = true;
}

void MenuAnimation::Stop()
{
	this->curIndex = -1;
	this->m_active = false;
}

void MenuAnimation::Update(LiquidCrystal* lcdDisplay)
{
	if (!this->m_active)
		return;

	double updateRate = 1000.0 / (double)hertz;
	uint64_t timeRunning = millis() - this->m_startTime;
	
	int8_t newIndex = ((int8_t)((double)timeRunning / updateRate) % totalFrames);

	if (newIndex == curIndex)
		return;

	this->curIndex = newIndex;
	//lcdDisplay->createChar(this->m_charId, (*this->frames)[this->curIndex]);
	this->LoadCharIntoDisplay(lcdDisplay);
}

void MenuAnimation::LoadCharIntoDisplay(LiquidCrystal* lcdDisplay)
{
	this->curIndex = this->curIndex == -1 ? 0 : this->curIndex;
	lcdDisplay->createChar(this->m_charId, (*this->frames)[this->curIndex]);
}

int8_t MenuAnimation::DisplayCharId()
{
	return this->m_charId;
}



