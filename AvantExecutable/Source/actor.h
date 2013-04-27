#ifndef _ACTOR_
#define _ACTOR_

#include "gentity.h"
#include "vector2d.h"

typedef Resource::Vector2d vec2;

namespace Avant
{
	class Actor : public GameEntity
	{
	public:
		Actor() { isLiving = true;
				  m_velocity = new vec2(); }
		virtual void move() { x += m_velocity->getX();
							  y += m_velocity->getY(); 
							}
		void setVelocity(int v) { m_velocity->setLength(v); }
		
		virtual void doDamage(int damage) { m_health -= damage; if(m_health = 0) kill(); }
		virtual ~Actor() { delete m_velocity; }
	
	protected:
		virtual void kill() {}
		vec2 * m_velocity;
		int m_health;
		bool isLiving;

	};
};

#endif