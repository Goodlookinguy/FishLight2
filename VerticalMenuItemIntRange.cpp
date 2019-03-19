// 
// 
// 

#include "VerticalMenuItemIntRange.h"
#include "Math.h"


VerticalMenuItemIntRange::VerticalMenuItemIntRange(const String& name, int16_t initValue, int16_t min, int16_t max) : VerticalMenuItem(name)
{
	this->m_min = min;
	this->m_max = max;
	this->m_value = initValue;
	this->m_initValue = initValue;
}

void VerticalMenuItemIntRange::DrawToScreen(FishLightProgram* program, VerticalMenuScreen* screen, bool isSelected)
{
	auto cp = program->ControlPanel();

	if (isSelected)
		cp->print(">");

	cp->print(this->name);
	cp->print(" ");

	cp->print(this->m_value);
}

void VerticalMenuItemIntRange::OnPressLeft(FishLightProgram* program, VerticalMenuScreen* screen)
{
	this->Value(this->m_value - this->incrementalChange);
}

void VerticalMenuItemIntRange::OnPressRight(FishLightProgram* program, VerticalMenuScreen* screen)
{
	this->Value(this->m_value + this->incrementalChange);
}
