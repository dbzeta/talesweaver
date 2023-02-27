#include "stdafx.h"
#include "isometricTile.h"


isometricTile::isometricTile()
{
}


isometricTile::~isometricTile()
{
}


HRESULT isometricTile::init(int idX, int idY, int width, int height)
{
	_idX = idX;
	_idY = idY;

	_width = width * 2;
	_height = height;
	
	_center = PointMake((_idX - _idY) * width + WINSIZEX / 2, (_idX + _idY) * height/2 + height);

	_rc = RectMakeCenter(_center.x, _center.y, _width, _height);

	_terrain = TR_CEMENT;
	_obj = OBJ_NONE;

	_terrainFrameX = _terrainFrameY = 0;

	_isThereTile = _isThereObject = false;

	return S_OK;
}

void isometricTile::release(void)
{
}

void isometricTile::update(void)
{
}

void isometricTile::tileRender(RECT focus)
{
	// Ŭ���� ����� ����Ͽ� ȭ�鿡 �Ⱥ��̴� �ֵ��� ���� ����
	RECT temp;
	if (!IntersectRect(&temp, &focus, &_rc)) return;

	if (_terrain == TR_NONE)
	{
		LineMake(getMemDC(), _center.x - focus.left, _center.y - focus.top - _height / 2,
			_center.x - _width / 2 - focus.left, _center.y - focus.top);
		LineMake(getMemDC(), _center.x - focus.left, _center.y - focus.top - _height / 2,
			_center.x + _width / 2 - focus.left, _center.y - focus.top);
		LineMake(getMemDC(), _center.x - _width / 2 - focus.left, _center.y - focus.top,
			_center.x - focus.left, _center.y + _height / 2 - focus.top);
		LineMake(getMemDC(), _center.x + _width / 2 - focus.left, _center.y - focus.top,
			_center.x - focus.left, _center.y + _height / 2 - focus.top);
	}
	else
	{
		IMAGEMANAGER->findImage("�⺻Ÿ��")->frameRender(getMemDC(), _rc.left - focus.left, _rc.top - focus.top, _terrainFrameX, _terrainFrameY);
	}																

}


void isometricTile::objectRender(RECT focus)
{
	// Ŭ���� ����� ����Ͽ� ȭ�鿡 �Ⱥ��̴� �ֵ��� ���� ����

	RECT temp;
	image* objImage = IMAGEMANAGER->findImage("�⺻������Ʈ");
	RECT objRect = RectMake(_rc.left, _rc.top - objImage->getFrameHeight() + IMAGEMANAGER->findImage("�⺻Ÿ��")->getFrameHeight(),
		objImage->getFrameWidth(), objImage->getFrameHeight());

	if (!IntersectRect(&temp, &focus, &objRect)) return;

	if (_isThereObject) objImage->frameRender(getMemDC(), _rc.left - focus.left,
		_rc.top - objImage->getFrameHeight() + IMAGEMANAGER->findImage("�⺻Ÿ��")->getFrameHeight() - focus.top,
		_objFrameX, _objFrameY);


}

void isometricTile::selectTerrain(int frameX, int frameY)
{
	_isThereTile = true;

	if (frameY == 0)
	{
		_terrain = TR_CEMENT;
		_terrainFrameX = frameX;
		_terrainFrameY = frameY;
	}
	if (frameY == 1)
	{

	}

}

void isometricTile::selectObject(int frameX, int frameY)
{
	_isThereObject = true;

	if (frameY == 0)
	{
		_obj = OBJ_WALL;
		_objFrameX = frameX;
		_objFrameY = frameY;
	}
	if (frameY == 1)
	{
		_obj = OBJ_WALL;
		_objFrameX = frameX;
		_objFrameY = frameY;
	}
	if (frameY == 2)
	{
		_obj = OBJ_WALL;
		_objFrameX = frameX;
		_objFrameY = frameY;
	}
	if (frameY == 3)
	{
		_obj = OBJ_WALL;
		_objFrameX = frameX;
		_objFrameY = frameY;
	}

	if (frameY == 4)
	{
		_obj = OBJ_WALL;
		_objFrameX = frameX;
		_objFrameY = frameY;
	}
}

void isometricTile::eraseObject()
{
	_isThereObject = false;
	_obj = OBJ_NONE;
	_objFrameX = _objFrameY = 0;

}
