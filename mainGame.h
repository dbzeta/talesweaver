#pragma once
#include "gameNode.h"
#include "loadingScene.h"
#include "maptoolScene.h"
#include "introScene.h"
#include "openingVideoScene.h"
#include "selectScene.h"
#include "createScene.h"
#include "gameScene.h"

class mainGame : public gameNode
{
private:
	image* _mousePointer;
	int _count;
	int _frameX, _frameY;

	bool _isPlayVideo;


public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render();



	mainGame();
	~mainGame();
};

