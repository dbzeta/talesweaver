#pragma once

// ���� ( Ÿ�� )
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_NONE
};

// ������Ʈ
enum OBJECT
{
	OBJ_WALL, OBJ_BLOCK3, OBJ_BLOCKS, OBJ_FLAG, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2, OBJ_NONE
};

// ���̼Ҹ�Ʈ�� Ÿ�� ����ü
struct tagIsometricTile
{

	RECT rc;
	POINT center;

	TERRAIN terrain;
	OBJECT obj;

	int idX, idY;
	int width, height;
	int tileX, tileY;

	int terrainFrameX, terrainFrameY;
	int objFrameX, objFrameY;

};