#pragma once
#include "gameNode.h"

// ÁöÇü
//enum TERRAIN
//{
//	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_NONE
//};
//
//enum OBJECT
//{
//	OBJ_WALL, OBJ_BLOCK3, OBJ_BLOCKS, OBJ_FLAG, OBJ_FLAG2,
//	OBJ_TANK1, OBJ_TANK2, OBJ_NONE
//};


class isometricTile : public gameNode
{
private:

	RECT _rc;
	POINT _center;

	int _idX, _idY;
	int _width, _height;
	int _tileX, _tileY;

	TERRAIN _terrain;
	OBJECT _obj;

	int _terrainFrameX, _terrainFrameY;
	int _objFrameX, _objFrameY;

	bool _isThereTile, _isThereObject;


public:

	isometricTile();
	~isometricTile();

	HRESULT init(int idX, int idY, int width, int height);
	void release(void);
	void update(void);
	void tileRender(RECT focus);
	void objectRender(RECT focus);

	RECT getRect() { return _rc; }

	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	int getIdX() { return _idX; }
	int getIdY() { return _idY; }

	void selectTerrain(int frameX, int frameY);
	void selectObject(int objNum, int frameX, int frameY);
	void eraseObject();


};

