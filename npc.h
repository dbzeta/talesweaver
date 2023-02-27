#pragma once
#include "gameNode.h"

enum NPCTYPE
{
	N_TYPE_MERCHANT = 1000,
	N_TYPE_NORMAL = 2000,
};

enum NPCSTATE
{
	N_STATE_STOP,
	N_STATE_IDLE,
	N_STATE_MOVE,
};

enum NPCDIRECTION
{
	N_DIR_DOWN,
	N_DIR_LEFT_DOWN,
	N_DIR_LEFT,
	N_DIR_LEFT_UP,
	N_DIR_UP,
	N_DIR_RIGHT_UP,
	N_DIR_RIGHT,
	N_DIR_RIGHT_DOWN,
};

class npc : public gameNode
{
protected:
	int _npcNum;							// NPC �ѹ� ( TYPE + ���° NPC�ΰ� )
	image* _image;							// NPC �̹���
	int _frameX, _frameY;					// NPC �̹����� ������X Y
	int _count;								// NPC �̹��� �������� ������ ���� count
	RECT _rc;								// NPC rect

	NPCDIRECTION _dir;						// NPC DIRECTION
	NPCSTATE _state;						// NPC STATE
	int _cx, _by;							// NPC centerX, bottomY
	bool _isFocusing;						// NPC�� ���� ��Ŀ���� �ǰ� �ִ°� ( Ŭ���� ó�� )
	bool _isClick;							// NPC�� Ŭ�������� TRUE�� �������ش�.
public:
	npc();
	~npc();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeDirection(RECT playerRC) {};		// NPC�� ��� ���� �ɰ�� ����� �ٲ��ش�.

	virtual void setNpc(int cx, int by) {}; 
	virtual bool isOnceClick() { return false; }

	virtual void setIsClick(bool isClick) { _isClick = isClick; }
	
	virtual int getX() { return _cx; }
	virtual int getY() { return _by; }

	int getFrameX() { return _frameX; }
	int getFrameY() { return _frameY; }

};

