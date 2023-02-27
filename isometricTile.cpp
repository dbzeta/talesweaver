#include "stdafx.h"
#include "isometricTile.h"


isometricTile::isometricTile()
	:_terrain(TR_CEMENT),_obj(OBJ_NONE),_objFrameX(0),_objFrameY(0)
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
	_objFrameX = _objFrameY = 0;

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
	// 클리핑 기법을 사용하여 화면에 안보이는 애들은 랜더 안해
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
		IMAGEMANAGER->findImage("기본타일")->frameRender(getMemDC(), _rc.left - focus.left, _rc.top - focus.top, _terrainFrameX, _terrainFrameY);
	}																

}


void isometricTile::objectRender(RECT focus)
{
	// 클리핑 기법을 사용하여 화면에 안보이는 애들은 랜더 안해
	RECT temp;
	
	image* objImage;

	if (_obj == OBJ_WALL) objImage = IMAGEMANAGER->findImage("기본오브젝트");
	else if (_obj == OBJ_FLAG) objImage = IMAGEMANAGER->findImage("기본오브젝트2");
	else if (_obj == OBJ_NONE) return;	

	RECT objRect = RectMake(_rc.left, _rc.top - objImage->getFrameHeight() + IMAGEMANAGER->findImage("기본타일")->getFrameHeight(),
		objImage->getFrameWidth(), objImage->getFrameHeight());

	if (!IntersectRect(&temp, &focus, &objRect)) return;

	if (_isThereObject && _obj == OBJ_WALL)
	{
		objImage->frameRender(getMemDC(), _rc.left - focus.left,
			_rc.top - objImage->getFrameHeight() + IMAGEMANAGER->findImage("기본타일")->getFrameHeight() - focus.top,
			_objFrameX, _objFrameY);
	}
	else if (_isThereObject && _obj == OBJ_FLAG)
	{
		objImage->frameRender(getMemDC(), _rc.left - focus.left, _rc.top - focus.top,
			_objFrameX, _objFrameY);
	}

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
		_terrain = TR_GRASS;
		_terrainFrameX = frameX;
		_terrainFrameY = frameY;
	}
	if (frameY == 2)
	{
		_terrain = TR_DESERT;
		_terrainFrameX = frameX;
		_terrainFrameY = frameY;
	}

}

void isometricTile::selectObject(int objNum, int frameX, int frameY)
{
	_isThereObject = true;

	if (objNum == 1)
	{
		_obj = OBJ_WALL;
		_objFrameX = frameX;
		_objFrameY = frameY;
	}
	else
	{
		_obj = OBJ_FLAG;
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
