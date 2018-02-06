// 
// 
// 

#include "VerticalMenuScreen.h"
#include "Button.h"

VerticalMenuScreen::VerticalMenuScreen() : MenuScreen()
{
}

VerticalMenuScreen::~VerticalMenuScreen()
{
	while (this->m_items->EntryCount() > 0)
	{
		auto item = this->m_items->Pop();
		delete item;
	}
	
	delete this->m_items;
}

void VerticalMenuScreen::AddMenuItem(VerticalMenuItem* item)
{
	this->m_items->Push(item);
}

void VerticalMenuScreen::DrawToScreen(FishLightProgram* program)
{
	if (this->m_items->EntryCount() == 0)
		return;

	auto controlPanel = program->ControlPanel();
	
	controlPanel->clear();
	VerticalMenuItem* item = (*this->m_items)[this->m_selectedIndex];
	item->DrawToScreen(program, this, true);
}

void VerticalMenuScreen::ButtonPressed(FishLightProgram* program, Button button)
{
	if (this->m_items->EntryCount() == 0)
		return;

	if (button == Button::Up)
		return this->m_items->Top()->OnPressUp(program, this);

	if (button == Button::Down)
		return this->m_items->Top()->OnPressDown(program, this);

	if (button == Button::Left)
		return this->m_items->Top()->OnPressLeft(program, this);

	if (button == Button::Right)
		return this->m_items->Top()->OnPressRight(program, this);

#if (FIVE_BUTTON_BUILD)
	if (button == Button::Enter)
		return this->m_items->Top()->OnPressEnter(program, this);
#endif
}

void VerticalMenuScreen::Update(FishLightProgram* program)
{

}

