#ifndef _LEVEL_
#define _LEVEL_

namespace Avant
{
	struct LevelHeader
	{
		unsigned char version;
		bool isLocked;
		bool isSingleLevel;
		unsigned int numEnemies;
		unsigned int numVehicles;
		unsigned int numBuilding;
		unsigned int numWeapons;
		unsigned int numObjectives;
		unsigned int size;
		char fileName[64];
		char nextFileName[64];
	};

	struct PlayerData
	{
		unsigned char version;
		int x;
		int y;
	};

	struct EnemyData
	{
		unsigned char version;
		int x;
		int y;
		int health;
		int weapon;
	};

	struct VehicleData
	{
		unsigned char version;
	};

	struct BuildingData
	{
		unsigned char version;
	};

	struct WeaponData
	{
		unsigned char version;
		int x;
		int y;
		int type;
	};

	struct ObjectiveData
	{
		unsigned char version;
	};
};
		
#endif