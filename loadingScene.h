#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingScene : public gameNode
{
private:
	loading* _loading;

	TCHAR _loadingPath[128];

	bool _isPlay, _isStop;

public:
	loadingScene();
	~loadingScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void loadingImage();
	void loadingSound();

};

