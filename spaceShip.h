#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"

//���漱�� -> �����Ϸ����� �������� �ϴ� ����
//��ȣ������ ���� ���漱��
//��ó���� �ܰ迡�� ��Ű�� ���� ����
class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;
	missile* _missile;
	modenMissile* _mdMissile;
	
	enemyManager* _em;

	progressBar* _hpBar;
	float _maxHP, _currentHP;

	int _alphaValue;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//�浹ó�� ���� �Ծ�
	void collision();

	//�̻��� ���� �� �Լ�
	void removeMissile(int arrNum);

	void hitDamage(float damage);

	//���߿� �� �̹��� ���� �ҷ��� ������
	image* getShipImage() { return _ship; }

	modenMissile* getModenMissile() { return _mdMissile; }

	//���߿� �޸� �ּҰ��� ã���ֱ� ���� �Լ�
	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

	spaceShip();
	~spaceShip();
};

