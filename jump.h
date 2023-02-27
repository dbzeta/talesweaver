#pragma once
#include "gameNode.h"

class jump : public gameNode
{
private:
	float _power;
	float _gravity;

	float* _x;
	float* _y;
	float _startX;
	float _startY;

	bool _isJumping;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void jumping(float* x, float* y, float power, float gravity);

	bool getIsJumping(void) { return _isJumping; }

	jump();
	~jump();
};

