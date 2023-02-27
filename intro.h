#pragma once
#include "gameNode.h"

struct introExitScreen
{
	image* background;
	RECT rc;
	tagButton yesBtn;
	tagButton noBtn;
	bool isUse;
};

class intro : public gameNode
{
private:
	image* _background;
	tagButton _exitBtn;
	tagButton _startBtn;
	tagButton _optionBtn;

	tagButton _maptoolBtn;
	tagButton _openingVideoBtn;

	introExitScreen _programExitScreen;

	bool _isClick;

	bool _isPlaySound;

	bool _isUseOption;

	RECT _bgmValue;
	RECT _soundEffectValue;
	
public:
	intro();
	~intro();

	HRESULT init();
	void release();
	void update();
	void render();


};

