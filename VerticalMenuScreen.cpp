// 
// 
// 

#include "VerticalMenuScreen.h"
#include "Button.h"
#include "Math.h"

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

	delete this->tag;
	delete this->m_items;
}

void VerticalMenuScreen::AddMenuItem(VerticalMenuItem* item)
{
	this->m_items->Push(item);
}

VerticalMenuItem* VerticalMenuScreen::SelectedItem()
{
	return this->m_items->Get(this->m_selectedIndex);
}

void VerticalMenuScreen::CancelChanges()
{
	this->m_delayedAction = 1;
}

void VerticalMenuScreen::ConfirmChanges()
{
	this->m_delayedAction = 2;
}

void VerticalMenuScreen::DrawToScreen(FishLightProgram* program)
{
	if (this->m_items->EntryCount() == 0)
		return;

	auto controlPanel = program->ControlPanel();
	
	controlPanel->clear();
	VerticalMenuItem* selectedItem = this->m_items->Get(this->m_selectedIndex);
	selectedItem->DrawToScreen(program, this, true);
	
	if ((this->m_selectedIndex + 1) < this->m_items->EntryCount())
	{
		controlPanel->setCursor(0, 1);
		VerticalMenuItem* nextItem = this->m_items->Get(this->m_selectedIndex + 1);
		nextItem->DrawToScreen(program, this, false);
	}
}

void VerticalMenuScreen::ButtonPressed(FishLightProgram* program, Button button)
{
	if (this->m_items->EntryCount() == 0)
		return;

	if (button == Button::Left || button == Button::Right)
	{
		VerticalMenuItem* selectedItem = this->m_items->Get(this->m_selectedIndex);

		if (button == Button::Left)
			selectedItem->OnPressLeft(program, this);

		else if (button == Button::Right)
			selectedItem->OnPressRight(program, this);

		auto changeAction = selectedItem->changeAction;
		if (changeAction != nullptr)
			changeAction(program, this->m_selectedIndex);

		return;
	}

#if (FIVE_BUTTON_BUILD)
	if (button == Button::Enter)
		this->m_items->Get(this->m_selectedIndex)->OnPressEnter(program, this);
#endif

	if (button == Button::Up || button == Button::Down)
	{
		if (button == Button::Up)
			this->m_selectedIndex = Math<int8_t>::Clamp(this->m_selectedIndex - 1, 0, this->m_items->EntryCount() - 1);

		else if (button == Button::Down)
			this->m_selectedIndex = Math<int8_t>::Clamp(this->m_selectedIndex + 1, 0, this->m_items->EntryCount() - 1);

		return;
	}

}

void VerticalMenuScreen::Update(FishLightProgram* program)
{
	if (this->m_delayedAction > 0)
	{
		if (this->m_delayedAction == 1)
		{
			for (uint8_t i = 0; i < this->m_items->EntryCount(); ++i)
			{
				auto cancelAction = this->m_items->Get(i)->cancelAction;

				if (cancelAction != nullptr)
					cancelAction(program, i);
			}
		}
		else if (this->m_delayedAction == 2)
		{
			for (uint8_t i = 0; i < this->m_items->EntryCount(); ++i)
			{
				auto confirmAction = this->m_items->Get(i)->confirmAction;

				if (confirmAction != nullptr)
					confirmAction(program, i);

			}
		}

		this->m_delayedAction = 0;
		program->RemoveTopScreen();
		program->CancelRefreshScreen();
	}
}

