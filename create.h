#pragma once
#include "gameNode.h"
#include "player.h"

struct tagSelectTypeButton
{
	int characterNum;				// ¾î¶² Ä³¸¯ÅÍ¸¦ °ñ¶ú´Â°¡
	tagButton selectTypeBtn[3];
};

class create : public gameNode
{
	image* _background;
	RECT _rc;
	int _count;
	int _frameX, _frameY;

	bool _isClick;

	CHARACTERTYPE _type;

	char _nickName[128];
	char _fileName[128];

	// ½ºÅÈ
	int _hack;										// 
	int _stab;										// 
	int _int;										// 
	int _def;										// 
	int _mr;										// 
	int _dex;										// 
	int _agi;										// 

													// ¹èÆ²
	int _maxHp;
	int _maxMp;
	int _maxSp;

	tagButton* _returnBtn;
	tagButton* _initBtn;
	tagButton* _createCharacterBtn;

	tagButton* _currentSelectBtn;

	RECT _writeNickName;
	RECT _checkNickName;

	tagSelectTypeButton _selectTypeBtn;

	bool _isPlaySound;
	bool _isWriteNickName;

public:
	create();
	~create();

	HRESULT init();
	void release();
	void update();
	void render();

	void selectType();
	void checkBtn();

	void setBtn();

	bool isOnceClickDown();
	bool isOnceClickUp();

	void createCharacter();

};

