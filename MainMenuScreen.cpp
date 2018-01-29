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

	// issue: library, trying to do setCursor and then createChar = fail, so it has to be done ahead of time
	// pg 30, 31, etc. in HD44780 datasheets give explanations for what might be going on, but forget it

	int8_t charId{ 0 };
	for (int8_t i = -3; i < 4; ++i)
	{
		const auto itemIndex = GetItemIndex(m_selectedIndex + i);
		menuItem = GetItem(itemIndex);

		// I only need to load the character into the display once per event update,
		// so this is to prevent reloading every update tick, but...
		if (!((this->m_charsLoaded >> itemIndex) & 1))
		{
			menuItem->animation->charId = charId++;
			menuItem->animation->LoadCharIntoDisplay(cp);
			this->m_charsLoaded = this->m_charsLoaded | (1 << itemIndex);
		}
	}

	cp->setCursor(0, 1);

	// display before selected item
	for (int8_t i = 3; i > 0; --i)
	{
		menuItem = GetItem(m_selectedIndex - i);
		cp->write(menuItem->animation->charId);
		cp->print(" ");
	}

	// display selected item
	cp->print("[");
	cp->write(focusedItem->animation->charId);
	cp->print("] ");

	// display after selected item
	for (int8_t i = 1; i < 4; ++i)
	{
		menuItem = GetItem(m_selectedIndex + i);
		cp->write(menuItem->animation->charId);
		cp->print(" ");
	}

}

void MainMenuScreen::ButtonPressed(FishLightProgram* program, Button button)
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

void MainMenuScreen::Update(FishLightProgram* program)
{
	for (uint8_t i = 0; i < this->m_items->EntryCount(); ++i)
		GetItem(i)->animation->Update(program->ControlPanel());
}

int8_t MainMenuScreen::GetItemIndex(int8_t index)
{
	// If there was only 1 item, it would spaz from byte overflow and display lines
	// where the displayed character should be. So I multiplied the max entries by
	// 3 to make sure it never overflows.
	if (index < 0)
		return (index + m_items->EntryCount() * 2) % m_items->EntryCount();
	return index % m_items->EntryCount();
}

MainMenuItem* MainMenuScreen::GetItem(int8_t index)
{
	int8_t itemIndex = GetItemIndex(index);
	MainMenuItem* item = (*m_items)[itemIndex];

	return item;
}

void MainMenuScreen::AddMenuItem(MainMenuItem* menuItem)
{
	this->m_items->Push(menuItem);
}
