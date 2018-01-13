// 
// 
// 

#include "Math.h"
#include "VerticalMenuItemPercent.h"

VerticalMenuItemPercent::VerticalMenuItemPercent(const String& name, const int8_t percent) : VerticalMenuItem(name)
{
	this->percent = percent;
}

VerticalMenuItemPercent::VerticalMenuItemPercent(const String& name, const int8_t percent, const int8_t incrementalChange) : VerticalMenuItem(name)
{
	this->percent = percent;
	this->incrementalChange = incrementalChange;
}

void VerticalMenuItemPercent::OnPressRight()
{
	this->percent = Math<int8_t>::Clamp(this->percent + this->incrementalChange, 0, 100);
}

void VerticalMenuItemPercent::OnPressLeft()
{
	this->percent = Math<int8_t>::Clamp(this->percent - this->incrementalChange, 0, 100);
}

