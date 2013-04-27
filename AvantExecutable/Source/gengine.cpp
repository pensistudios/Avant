#include "gengine.h"

Avant::GameEngine::GameEngine()
{
	
}

Avant::GameEngine::~GameEngine()
{
	delete player;
	delete enemies;
	delete weapons;
	delete objectives;
	delete trees;
	delete bullets;
}


void Avant::GameEngine::update(float d, int h, int w, Input *input)
{
	deltaTime = d;

	height = h;
	width =  w;

	if(state == GAMESTATE_RUNNING)
	{
		//get all input do stuff with it
	}
	if(state == GAMESTATE_MENU)
	{
		if(input->mouse)
		{
			bool x = input->mouse;
		}
	}
}

bool Avant::GameEngine::init()
{
	state = GAMESTATE_MENU;
	player = new Player();
	enemies = new EnemyList();
	weapons = new WeaponList();
	objectives = new ObjectiveList();
	trees = new TreeList();
	bullets = new BulletList();
	menuChoice = 0;
	return true;
}