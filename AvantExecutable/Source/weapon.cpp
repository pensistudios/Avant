#include "weapon.h"

void Avant::Weapon::setType(int type)
{
	weaponType = type;
}

int Avant::Weapon::getType()
{
	return weaponType;
}

void Avant::Weapon::fire()
{
	if(weaponType == Pistol)
	{
		if(startTime == 0)
		{
			//put a new bullet in game engine
		}
	}
	else if(weaponType == Rifle)
	{

	}
	else if(weaponType == Sniper)
	{

	}
	else if(weaponType == Rocket)
	{

	}
}