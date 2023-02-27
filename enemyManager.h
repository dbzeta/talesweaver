#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "jellyppi.h"
#include "poisonJellyppi.h"

class player;
class mapManager;
class uiManager;

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vEnemyList;

	player* _player;
	mapManager* _mm;
	uiManager* _um;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setMinion();


	void setPlayerAddressLink(player* player) { _player = player; }
	void setMmAddressLink(mapManager* mm) { _mm = mm; }
	void setUmAddressLink(uiManager* um) { _um = um; }

	vector<enemy*>& getVEnemyList() { return _vEnemyList; }

	bool isOnceClick();

	void addDamage(int damage);

};

