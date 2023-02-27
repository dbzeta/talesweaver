#include "stdafx.h"
#include "quickSlot.h"


quickSlot::quickSlot()
{
}


quickSlot::~quickSlot()
{
}

HRESULT quickSlot::init()
{

	_isQuickSlot1 = true;;
	_isQuickSlot2 = false;

	_background = IMAGEMANAGER->addPngFrameImage("Äü½½·Ô", "UI\\Äü½½·Ô\\Äü½½·Ô.png", 270, 101, 2, 1, false, false);


	return S_OK;
}

void quickSlot::release()
{

}

void quickSlot::update() 
{
	_isQuickSlot2 = !_isQuickSlot1;

	if (_isQuickSlot1) _background->setFrameX(0);
	else if (_isQuickSlot2) _background->setFrameX(1);
}

void quickSlot::render() 
{
	_background->frameRender(getMemDC(), 0, WINSIZEY - _background->getFrameHeight(), _background->getFrameX(), 0);
}

void quickSlot::addSkill()
{
}
