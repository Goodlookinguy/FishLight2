// 
// 
// 

#include "VerticalMenuItemCancelConfirm.h"
#include "VerticalMenuScreen.h"

VerticalMenuItemCancelConfirm::VerticalMenuItemCancelConfirm() : VerticalMenuItem("")
{
}

void VerticalMenuItemCancelConfirm::DrawToScreen(FishLightProgram* program, VerticalMenuScreen* screen, bool isSelected)
{
	//0123456789ABCDEF
	//[Cancel] Confirm
	//Cancel [Confirm]
	
	auto cp = program->ControlPanel();
	
	if (isSelected)
	{
		if (cancelConfirm)
			cp->print("Cancel [Confirm]");
		else
			cp->print("[Cancel] Confirm");
	}
	else
	{
		if (cancelConfirm)
			cp->print("Cancel  Confirm");
		else
			cp->print(" Cancel  Confirm");
	}
}

void VerticalMenuItemCancelConfirm::OnPressRight(FishLightProgram* program, VerticalMenuScreen* screen)
{
#if FIVE_BUTTON_BUILD
	cancelConfirm = true;
#else
	if (cancelConfirm)
		return screen->ConfirmChanges();
	else
		cancelConfirm = true;
#endif
}

void VerticalMenuItemCancelConfirm::OnPressLeft(FishLightProgram* program, VerticalMenuScreen* screen)
{
#if FIVE_BUTTON_BUILD
	cancelConfirm = false;
#else
	if (!cancelConfirm)
		return screen->CancelChanges();
	else
		cancelConfirm = false;
#endif
}

#if FIVE_BUTTON_BUILD
void VerticalMenuItemCancelConfirm::OnPressEnter(FishLightProgram* program, VerticalMenuScreen* screen)
{
	if (cancelConfirm)
		return screen->ConfirmChanges();
	screen->CancelChanges();
}
#endif
