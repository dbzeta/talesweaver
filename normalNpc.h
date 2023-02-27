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

	virtual void changeDirection(RECT playerRC);		// NPC의 경우 말을 걸경우 모습을 바꿔준다.
	virtual void setNpc(int cx, int by);
	
	virtual bool isOnceClick();

	virtual int getX() { return _cx; }
	virtual int getY() { return _by; }

};

