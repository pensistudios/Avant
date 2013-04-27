#ifndef _PLAYER_
#define _PLAYER_

#include "actor.h"
#include "weapon.h"

namespace Avant
{
	class Player : public Actor
	{
	public:
		Player();
		Player(GameEngine * engine);
		bool selectWeapon(int type);
		void fireWeapon();
		int radius; // Player is a circle
		~Player();

	private:
		
		void kill();
		Weapon * current;
		Weapon * inventory;
	}; 
};

#endif 