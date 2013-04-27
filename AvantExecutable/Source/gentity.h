#ifndef _GAME_ENTITY_
#define _GAME_ENTITY_

namespace Avant
{
	class GameEngine;

	class GameEntity
	{
	public:
		virtual ~GameEntity() {}
		void attach(GameEngine * const engine) { gameEngine = engine; }
		int x,y;

	protected:
		GameEngine * gameEngine;
		
	};

};

#endif