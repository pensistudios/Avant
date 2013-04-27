#include "player.h"

Avant::Player::Player()
{
	current = 0;
	inventory = new Weapon[4];
	inventory[0].setType(Weapon::Pistol);
	inventory[0].isInInventory = false;
	inventory[1].setType(Weapon::Rifle);
	inventory[1].isInInventory = false;
	inventory[2].setType(Weapon::Sniper);
	inventory[2].isInInventory = false;
	inventory[3].setType(Weapon::Rocket);
	inventory[3].isInInventory = false;
}

Avant::Player::~Player()
{
	delete[] inventory;
}

void Avant::Player::kill()
{
	isLiving = false;
}

bool Avant::Player::selectWeapon(int type)
{
	if(isLiving)
	{
		if(type = Weapon::Pistol && inventory[0].isInInventory)
		{
			current = inventory;
			return true;
		}
		if(type = Weapon::Rifle && inventory[1].isInInventory)
		{
			current = (inventory + 1);
			return true;
		}
		if(type = Weapon::Sniper && inventory[2].isInInventory)
		{
			current = (inventory + 2);
			return true;
		}
		if(type = Weapon::Rocket && inventory[3].isInInventory)
		{
			current = (inventory + 3);
			return true;
		}
	}

	return false;
}

void Avant::Player::fireWeapon()
{
	if(isLiving)
	{
		if(current != 0)
		{
			current->fire();
		}
	}
}
