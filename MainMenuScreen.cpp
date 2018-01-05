// 
// 
// 

#include "MainMenuScreen.h"
#include "FishLightProgram.h"
#include "Button.h"
//#include "MenuAnimation.h"

void MainMenuScreen::DrawToScreen(FishLightProgram* program)
{
	MainMenuItem* menuItem;
	MainMenuItem* focusedItem = GetItem(m_selectedIndex);
	this->m_charsLoaded = 0;
	auto cp = program->ControlPanel();
	cp->clear();

	cp->print(focusedItem->name);
	cp->print(this->m_selectedIndex);
	cp->setCursor(0, 1);

	for (int i = 3; i > 0; --i)
	{
		menuItem = GetItem(m_selectedIndex - i);
		
		cp->print(menuItem->animation->DisplayCharId());
		cp->print(" ");
	}
	cp->print("[");
	cp->print(focusedItem->animation->DisplayCharId());
	cp->print("] ");
	for (int i = 1; i < 4; ++i)
	{
		menuItem = GetItem(m_selectedIndex + i);
		cp->print(menuItem->animation->DisplayCharId());
		cp->print(" ");
	}
}

void MainMenuScreen::ButtonPressed(Button button)
{
	if (button == Button::Left || button == Button::Right)
	{
		GetItem(m_selectedIndex)->animation->Stop();

		if (button == Button::Left)
			m_selectedIndex = ((m_selectedIndex - 1) + m_items->EntryCount()) % m_items->EntryCount();
		else if (button == Button::Right)
			m_selectedIndex = (m_selectedIndex + 1) % m_items->EntryCount();

		GetItem(m_selectedIndex)->animation->Play();
	}

	//0123456789ABCDEF
	//A B C [D] E F G
}

int8_t MainMenuScreen::GetItemIndex(int8_t index)
{
	if (index < 0)
		return (index + m_items->EntryCount() * 3) % m_items->EntryCount();
	return index % m_items->EntryCount();
}

MainMenuItem* MainMenuScreen::GetItem(int8_t index)
{
	int8_t itemIndex = GetItemIndex(index);
	MainMenuItem* item = (*m_items)[itemIndex];
	
	// hacky hacky hacky / lazy
	if (!((this->m_charsLoaded >> itemIndex) & 1))
	{
		item->animation->LoadCharIntoDisplay(FishLightProgram::Instance()->ControlPanel());
		this->m_charsLoaded = this->m_charsLoaded | (1 << itemIndex);
	}

	return item;
}

void MainMenuScreen::AddMenuItem(MainMenuItem* menuItem)
{
	this->m_items->Push(menuItem);
}
