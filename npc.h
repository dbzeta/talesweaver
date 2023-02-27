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
	int _npcNum;							// NPC 넘버 ( TYPE + 몇번째 NPC인가 )
	image* _image;							// NPC 이미지
	int _frameX, _frameY;					// NPC 이미지의 프레임X Y
	int _count;								// NPC 이미지 프레임을 돌리기 위한 count
	RECT _rc;								// NPC rect

	NPCDIRECTION _dir;						// NPC DIRECTION
	NPCSTATE _state;						// NPC STATE
	int _cx, _by;							// NPC centerX, bottomY
	bool _isFocusing;						// NPC가 현재 포커싱이 되고 있는가 ( 클리핑 처리 )
	bool _isClick;							// NPC를 클릭했을때 TRUE로 설정해준다.
public:
	npc();
	~npc();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void changeDirection(RECT playerRC) {};		// NPC의 경우 말을 걸경우 모습을 바꿔준다.

	virtual void setNpc(int cx, int by) {}; 
	virtual bool isOnceClick() { return false; }

	virtual void setIsClick(bool isClick) { _isClick = isClick; }
	
	virtual int getX() { return _cx; }
	virtual int getY() { return _by; }

	int getFrameX() { return _frameX; }
	int getFrameY() { return _frameY; }

};

