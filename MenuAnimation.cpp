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

MenuAnimation::~MenuAnimation()
{
	delete this->frames;
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
	
	// so when the byte overflowed, it caused some fun things to happen, casting to int64 prevents this for a while.
	// It will overflow eventually, but I think the number is high enough to be far out of the range of realism
	// at a rate of 4 hertz, it would overflow when reaching 2305843009213693935 updates
	int8_t newIndex = (int8_t)((int64_t)((double)timeRunning / updateRate) % (int64_t)totalFrames);

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



