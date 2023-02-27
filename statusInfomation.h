#pragma once
#include "uiScreen.h"

class player;
class enemyManager;
class enemy;

class statusInfomation : public uiScreen
{
private:
	player* _player;
	enemyManager* _em;

	image* _hpBar;
	RECT _hpRc;
	bool _isHpPercent;
	bool _isHpValue;

	image* _mpBar;
	RECT _mpRc;
	bool _isMpPercent;
	bool _isMpValue;

	image* _spBar;
	RECT _spRc;
	bool _isSpPercent;
	bool _isSpValue;

	image* _expBar;
	RECT _expRc;

	image* _comboScreen;

	enemy* _targetEnemy;


public:
	statusInfomation();
	~statusInfomation();

	HRESULT init();
	void release();
	void update();
	void render();

	bool isOnceClick();												// Once
	bool isOnceClickUp();
	bool isStayClick() { return false; }								// Stay 사용안하므로 false 반환


	void setTargetEnemy(enemy* target) { _targetEnemy = target; }

	void setPlayerAddressLink(player* player) { _player = player; }
	void setEmAddressLink(enemyManager* em) { _em = em; }
};

