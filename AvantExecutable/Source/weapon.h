#ifndef _WEAPON_
#define _WEAPON_

#include "prop.h"

namespace Avant
{
	class Weapon : public Prop
	{
	public:
		Weapon() {}
		Weapon(int type) { weaponType = type;}
		bool isOnGround;
		bool isInInventory;
		void setType(int type);
		int getType();
		void fire();
		~Weapon() {}

		enum WeaponType
		{
		Pistol,
		Rifle = 2,
		Sniper = 4,
		Rocket = 8
		};

	private:
		int weaponType;
		float startTime;
	};
};

#endif