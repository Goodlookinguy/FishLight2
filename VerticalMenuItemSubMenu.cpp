// 
// 
// 

#include "VerticalMenuItemSubMenu.h"

VerticalMenuItemSubMenu::VerticalMenuItemSubMenu(const String& name, MenuScreen* screen) : VerticalMenuItem(name)
{
	this->m_screen = screen;
}

void VerticalMenuItemSubMenu::DrawToScreen(FishLightProgram* program, VerticalMenuScreen* screen, bool isSelected)
{
	auto cp = program->ControlPanel();

	if (isSelected)
		cp->print(">");

	cp->print(this->name);
}

void VerticalMenuItemSubMenu::OnPressRight(FishLightProgram* program, VerticalMenuScreen* screen)
{
#if !FIVE_BUTTON_BUILD
	program->menuScreenStack->Push(this->m_screen);
#endif
}

void VerticalMenuItemSubMenu::OnPressEnter(FishLightProgram* program, VerticalMenuScreen* screen)
{
	program->menuScreenStack->Push(this->m_screen);
}
