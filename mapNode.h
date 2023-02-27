#pragma once

// 지형 ( 타일 )
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_NONE
};

// 오브젝트
enum OBJECT
{
	OBJ_WALL, OBJ_BLOCK3, OBJ_BLOCKS, OBJ_FLAG, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2, OBJ_NONE
};

// 아이소메트리 타일 구조체
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