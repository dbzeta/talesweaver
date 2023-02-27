#include "stdafx.h"
#include "npcManager.h"
#include "player.h"


npcManager::npcManager()
{
}


npcManager::~npcManager()
{
}

HRESULT npcManager::init()	  
{

	return S_OK;
}

void npcManager::release()	  
{
	for (int i = 0; i < _vTotalNpcList.size(); ++i)
	{
		_vTotalNpcList[i]->release();
	}
}

void npcManager::update()	  
{
	for (int i = 0; i < _vTotalNpcList.size(); ++i)
	{
		_vTotalNpcList[i]->update();
	}
}

void npcManager::render()	  
{
	for (int i = 0; i < _vTotalNpcList.size(); ++i)
	{
		_vTotalNpcList[i]->render();
	}
}

bool npcManager::isOnceClick()
{
	// UI
	// PLAYER
	// NPC ENEMY
	// TILE PICKING
	
	for (int i = 0; i < _vTotalNpcList.size(); ++i)
	{
		if (_vTotalNpcList[i]->isOnceClick())
		{
			_vTotalNpcList[i]->changeDirection(_player->getRect());
			return true;
		}
	}

	return false;
}

void npcManager::setNpc()
{
	_wanderingCat = new wanderingCat;
	_wanderingCat->init();
	_wanderingCat->setUmAddressLink(_um);
	_wanderingCat->setNpc(500, 500);
	_vTotalNpcList.push_back(_wanderingCat);

	_kanakeu = new kanakeu;
	_kanakeu->init();
	_kanakeu->setUmAddressLink(_um);
	_kanakeu->setNpc(500, 700);
	_vTotalNpcList.push_back(_kanakeu);

	_maria = new maria;
	_maria->init();
	_maria->setNpc(300, 500);
	_vTotalNpcList.push_back(_maria);
}
