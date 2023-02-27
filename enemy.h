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

	int _exp;						// �׾��� �� �÷��̾�� �� exp;
	int _money;						// �׾��� �� ����� ��;
	int _itemNum;					// �׾��� �� ����� ������ ( ���� �� ���� �� �Һ��۵��� �ε��� ��ȣ );

	POINT _target;

	// ����
	int _maxHp, _maxMp;
	int _currentHp, _currentMp;
	
	// ����
	float _atk, _phisicalDefense, _magicDefense;

	bool _isLive;
	bool _isTarget;

	bool _isMove;
	bool _isAttack;

	// ���̽�Ÿ ���� ����� ���
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

