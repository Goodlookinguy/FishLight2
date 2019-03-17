// 
// 
// 

#include "Math.h"
#include "VerticalMenuItemPercent.h"
#include "VerticalMenuScreen.h"

VerticalMenuItemPercent::VerticalMenuItemPercent(const String& name, const int8_t percent) : VerticalMenuItem(name)
{
	this->percent = percent;
}

VerticalMenuItemPercent::VerticalMenuItemPercent(const String& name, const int8_t percent, const int8_t incrementalChange) : VerticalMenuItem(name)
{
	this->percent = percent;
	this->incrementalChange = incrementalChange;
}

void VerticalMenuItemPercent::DrawToScreen(FishLightProgram* program, VerticalMenuScreen* screen, bool isSelected)
{
	auto controlPanel = program->ControlPanel();

	if (isSelected)
		controlPanel->print(">");

	controlPanel->print(this->name);
	controlPanel->print(" ");
	controlPanel->print(this->percent);
	controlPanel->print("%");
}

void VerticalMenuItemPercent::OnPressRight(FishLightProgram* program, VerticalMenuScreen* screen)
{
	this->percent = Math<int8_t>::Clamp(this->percent + this->incrementalChange, 0, 100);
}

void VerticalMenuItemPercent::OnPressLeft(FishLightProgram* program, VerticalMenuScreen* screen)
{
	this->percent = Math<int8_t>::Clamp(this->percent - this->incrementalChange, 0, 100);
}

