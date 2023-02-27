#pragma once
#include "npc.h"

class maria : public npc
{

public:
	maria();
	~maria();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void changeDirection(RECT playerRC);		// NPC�� ��� ���� �ɰ�� ����� �ٲ��ش�.
	virtual void setNpc(int cx, int by);
	
	virtual bool isOnceClick();

	virtual int getX() { return _cx; }
	virtual int getY() { return _by; }

};

