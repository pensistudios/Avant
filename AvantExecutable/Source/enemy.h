#ifndef _ENEMY_
#define _ENEMY_

#include "actor.h"
#include "weapon.h"

namespace Avant
{
	class Enemy : public Actor
	{
	public:
		Enemy();
		void kill();
		~Enemy();

	private:

		Weapon * weapon;
	};
};

#endif