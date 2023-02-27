#include "stdafx.h"
#include "jump.h"


jump::jump()
{
}


jump::~jump()
{
}

HRESULT jump::init()
{
	_isJumping = _power = _gravity = 0.0f;


	return S_OK;
}

void jump::release()
{

}

void jump::update()
{
	if (!_isJumping) return;

	*_y -= _power;
	_power -= _gravity;

	//뛴 지점보다 더 내려가면
	if (_startY < *_y)
	{
		*_y = _startY;
		_isJumping = false;
	}


}

void jump::render()
{

}

void jump::jumping(float* x, float* y, float power, float gravity)
{
	if (_isJumping) return;

	_isJumping = true;

	_x = x;
	_y = y;

	_startX = *x;
	_startY = *y;

	_gravity = gravity;
	_power = power;
}