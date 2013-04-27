#ifndef _GAME_ENGINE_
#define _GAME_ENGINE_

#include "input.h"
#include "player.h"
#include "enemy.h"
#include "objective.h"
#include "tree.h"
#include "bullet.h"
#include <vector>

typedef std::vector<Avant::Enemy*> EnemyList;
typedef std::vector<Avant::Weapon*> WeaponList;
typedef std::vector<Avant::Objective*> ObjectiveList;
typedef std::vector<Avant::Tree*> TreeList;
typedef std::vector<Avant::Bullet*> BulletList;

namespace Avant
{
	class GameEngine
	{
	public:
		GameEngine();
		bool init();
		void update(float deltatime, int height, int width, Input *input);
		int state;
		~GameEngine();
		float deltaTime;
		int menuChoice;

		enum GameState
		{
		GAMESTATE_MENU,
		GAMESTATE_LOADING,
		GAMESTATE_TRANSITION,
		GAMESTATE_RUNNING,
		GAMESTATE_EXITING
		};

	private:
		int height;
		int width;
		Player * player;
		EnemyList * enemies;
		WeaponList * weapons;
		ObjectiveList * objectives;
		TreeList * trees;
		BulletList * bullets;

	};

};

#endif