#pragma once
#include "enemy.h"

class mapManager;
class player;

class poisonJellyppi : public enemy
{
private:

	mapManager* _mm;
	player* _player;

	int _count;							// ������ ������ ī��Ʈ
	RECT _playerRC;						// �÷��̾��� ��Ʈ��


	int _changeDirectionCount;
public:
	poisonJellyppi();
	~poisonJellyppi();

	HRESULT init();
	void release();
	void update();
	void render();

	void attack();
	void move();

	void checkDirection(float angle);

	void setMinion(int cx, int by);

	void setPlayerRect(RECT rc) { _playerRC = rc; }

	void setImage();

	virtual void addDamage(int damage);

	virtual int getX() { return _cx; }
	virtual int getY() { return _by; }

	virtual bool isOnceClick();

	void setPlayerAddressLink(player* player) { _player = player; }
	void setMmAddressLink(mapManager* mm) { _mm = mm; }

};

