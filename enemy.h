#pragma once
#include "gameNode.h"



enum ENEMYDIRECTION
{
	E_DIR_LEFT,
	E_DIR_RIGHT,
	E_DIR_UP,
	E_DIR_DOWN,
	E_DIR_LEFT_UP,
	E_DIR_LEFT_DOWN,
	E_DIR_RIGHT_UP,
	E_DIR_RIGHT_DOWN
};

enum ENEMYSTATE
{
	E_MOVE,
	E_ATTACK,
	E_COLLISION
};

class enemy : public gameNode
{
protected:
	image* _image;
	RECT _rc;
	ENEMYDIRECTION _dir;
	ENEMYSTATE _state;
	int _frameX, _frameY;

	char _enemyName[128];

	float _angle;

	float _cx, _by;

	int _enemyNum;

	int _range;

	int _speed;

	int _exp;						// 죽었을 시 플레이어에게 줄 exp;
	int _money;						// 죽었을 시 드랍한 돈;
	int _itemNum;					// 죽었을 시 드랍할 아이템 ( 잡템 밑 장비류 나 소비템들의 인덱스 번호 );

	POINT _target;

	// 스텟
	int _maxHp, _maxMp;
	int _currentHp, _currentMp;
	
	// 스텟
	float _atk, _phisicalDefense, _magicDefense;

	bool _isLive;
	bool _isTarget;

	bool _isMove;
	bool _isAttack;

	// 에이스타 사용시 저장될 경로
	int _reSpawnCount;

	vector<int> _vPath;

public:
	enemy();
	~enemy();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual	void setPlayerRect(RECT rc) {};

	virtual void attack() {};
	virtual void move();

	void setMinion(int cx, int by){}

	void setReSpawnCount(int count) { _reSpawnCount = count; }

	int getEnemyNum() { return _enemyNum; }
	int getReSpawnCount() { return _reSpawnCount; }

	bool getIsLive() { return _isLive; }
	image* getImage() { return _image; }

	virtual int getX() { return _cx; }
	virtual int getY() { return _by; }

	virtual bool isOnceClick() { return false; }

	int getFrameX() { return _frameX; }
	int getFrameY() { return _frameY; }

	RECT getRect() { return _rc; }

	int getCurrentHp() { return _currentHp; }
	int getMaxHp() { return _maxHp; }

	virtual void addDamage(int damage);
	virtual char* getEnemyName() { return _enemyName; }


};

