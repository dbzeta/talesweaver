#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"
#include "mapManager.h"
#include "uiManager.h"

enemyManager::enemyManager()
{

}

enemyManager::~enemyManager()
{

}

HRESULT enemyManager::init()
{

	return S_OK;
}

void enemyManager::release()				
{

}

void enemyManager::update()					
{
	for (int i = 0; i < _vEnemyList.size(); ++i)
	{
		_vEnemyList[i]->setPlayerRect(_player->getRect());
		_vEnemyList[i]->update();
	}
}

void enemyManager::render()					
{
	for (int i = 0; i < _vEnemyList.size(); ++i)
	{
		if (!_vEnemyList[i]->getIsLive()) continue;
		_vEnemyList[i]->render();
	}
}

void enemyManager::setMinion()
{
	for (int i = 0; i < 10; ++i)
	{
		jellyppi* _jelli = new jellyppi;
		_jelli->init();
		_jelli->setMinion(300, 700);
		_jelli->setPlayerAddressLink(_player);
		_jelli->setMmAddressLink(_mm);
		_vEnemyList.push_back(_jelli);
		
		//
		//poisonJellyppi* _poisonJelli = new poisonJellyppi;
		//_poisonJelli->init();
		//_poisonJelli->setMinion(600, 400);
		//_poisonJelli->setPlayerAddressLink(_player);
		//_poisonJelli->setMmAddressLink(_mm);
		//_vEnemyList.push_back(_poisonJelli);

	}
}


bool enemyManager::isOnceClick()
{
	for (int i = 0; i < _vEnemyList.size(); ++i)
	{
		if (!_vEnemyList[i]->getIsLive()) continue;
		if(_vEnemyList[i]->isOnceClick())
		{
			_um->getStatusInfoScreen()->setTargetEnemy(_vEnemyList[i]);
			_player->setTarget(_vEnemyList[i]->getX(), _vEnemyList[i]->getY());
			_player->setAttackTarget(_vEnemyList[i]);
			return true;
		}
	}
	return false;
}

void enemyManager::addDamage(int damage)
{
}
