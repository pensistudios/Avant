#include "rectangle.h"

Avant::Rectangle::Rectangle(int xd, int yd, int w, int h)
{
	x = xd;
	y = yd;
	width = w;
	height = h;
}

bool Avant::Rectangle::contains(int xd, int yd)
{
	if(x >= 0 && y >= 0)
	{
		return (((xd >= x) && (xd <= (x + width))) && ((yd >= y) && (yd <= (y + height))));	
	}
	else if(x < 0 && y >= 0)
	{
		return (((xd <= x) && (xd >= (x - width))) && ((yd >= y) && (yd <= (y + height))));
	}
	else if(x < 0 && y < 0)
	{
		return (((xd <= x) && (xd >= (x - width))) && ((yd <= y) && (yd >= (y - height))));
	}
	else if(x >= 0 && y < 0)
	{
		return (((xd >= x) && (xd <= (x + width))) && ((yd <= y) && (yd >= (y - height))));
	}

	return false;
}

void Avant::Rectangle::shape(int xd, int yd, int w, int h)
{
	x = xd;
	y = yd;
	width = w;
	height = h;
}

void Avant::Rectangle::resize(int w, int h)
{
	width = w;
	height = h;
}