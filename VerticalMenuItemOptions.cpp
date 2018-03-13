// 
// 
// 

#include "VerticalMenuItemOptions.h"
#include "Math.h"

VerticalMenuItemOptions::VerticalMenuItemOptions(const String& name, const uint8_t size) : VerticalMenuItem(name)
{
	this->m_displayValueItems = new TinyArray<String>(size);
	this->m_valueItems = new TinyArray<int8_t>(size);
}

VerticalMenuItemOptions::~VerticalMenuItemOptions()
{
	delete this->m_displayValueItems;
	delete this->m_valueItems;
}

void VerticalMenuItemOptions::AddOption(const String& displayValue, int8_t value)
{
	this->m_displayValueItems->Push(displayValue);
	this->m_valueItems->Push(value);
}

void VerticalMenuItemOptions::DrawToScreen(FishLightProgram* program, VerticalMenuScreen* screen, bool isSelected)
{
	auto cp = program->ControlPanel();

	if (isSelected)
		cp->print(">");

	cp->print(this->name);
	cp->print(" ");

	cp->print(this->m_displayValueItems->Get(this->m_selectedIndex));
}

void VerticalMenuItemOptions::OnPressLeft(FishLightProgram* program, VerticalMenuScreen* screen)
{
	this->m_selectedIndex = Math<int8_t>::Clamp(this->m_selectedIndex - 1, 0, this->m_displayValueItems->EntryCount() - 1);
}

void VerticalMenuItemOptions::OnPressRight(FishLightProgram* program, VerticalMenuScreen* screen)
{
	this->m_selectedIndex = Math<int8_t>::Clamp(this->m_selectedIndex + 1, 0, this->m_displayValueItems->EntryCount() - 1);
}
