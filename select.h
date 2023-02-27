#pragma once
#include "gameNode.h"

#define MAXCHARACTER 8

class player;

struct tagSelectCharacter
{
	image* image;
	RECT rc;
	int frameX;
	char fileName[128];
	int boxNum;
	char nickName[128];
	int level;
	int type;
	BYTE alpha;
	bool isUse = false;
};

class select : public gameNode
{
private:
	image* _background;
	RECT _rc;
	
	int _count;

	tagButton _startBtn;
	tagButton _returnBtn;
	tagButton _createCharacterBtn;

	tagButton _deleteButton; // 

	tagSelectCharacter* _arrSelectCharacter[MAXCHARACTER];

	tagSelectCharacter* _currentSelect;
	
	vector<string> _vSelectCharacter;

	bool _isClick;
	bool _isPlaySound;

public:
	select();
	~select();

	HRESULT init();
	void release();
	void update();
	void render();
};

