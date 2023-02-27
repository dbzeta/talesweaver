#pragma once
#include "gameNode.h"

class pixelCollisionTest : public gameNode
{
private:
	image* _mountain;		//��� �̹���
	image* _ball;			//�� �̹���

	RECT _rc;				//��Ʈ

	float _x, _y;			//�� x,y

	int _probeY;			//Y�� Ž���� ����


public:
	HRESULT init();
	void release();
	void update();
	void render();

	pixelCollisionTest();
	~pixelCollisionTest();
};

