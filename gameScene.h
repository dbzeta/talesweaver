#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "mapManager.h"
#include "uiManager.h"
#include "itemManager.h"
#include "npcManager.h"
#include "questManager.h"
#include <map>

class gameScene : public gameNode
{
private:
	image* _image;
	int _count;
	int _frameX;

	bool _isDoubleClick;
	bool _startDoubleCount;	
	int _doubleClickCount;

	player* _player;
	enemyManager* _em;
	mapManager* _mm;
	uiManager* _um;
	itemManager* _im;
	npcManager* _nm;
	questManager* _qm;


public:
	gameScene();
	~gameScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

