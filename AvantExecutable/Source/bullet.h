#ifndef _BULLET_
#define _BULLET_

#include "actor.h"

namespace Avant
{

	class Bullet : public Actor
	{
	public:
		Bullet(int d) { damage = d; }
		void kill() {}
		int damage;
	};

};

#endif