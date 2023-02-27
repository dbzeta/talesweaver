#pragma once
#include "singletonBase.h"

enum DRAWTYPE
{
	DRAW_RENDER,
	DRAW_ALPHARENDER,
	DRAW_FRAMERENDER,
	DRAW_ALPHAFRAMERENDER,
};
struct tagDrawGameScene
{
	DRAWTYPE type;
	string attritute;
	image* image;
	int frameX, frameY;
	RECT rc;
	BYTE alpha;
};


class drawManager : public singletonBase<drawManager>
{
private:
	vector<tagDrawGameScene> _vDrawList;

public:
	drawManager();
	~drawManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addDrawList(DRAWTYPE type, string attritute, image* image, int frameX, int frameY, RECT rc, BYTE alpha);
};

