#include "stdafx.h"
#include "drawManager.h"


drawManager::drawManager()
{
}


drawManager::~drawManager()
{
}

HRESULT drawManager::init()
{

	return S_OK;
}

void drawManager::release()
{
}

void drawManager::update()
{
}

void drawManager::render(HDC hdc)
{

	for (int i = 0; i < (int)_vDrawList.size() - 1; ++i)
	{
		for (int k = 1; k < _vDrawList.size(); ++k)
		{
			if (_vDrawList[k - 1].attritute == "PLAYER" && _vDrawList[k].attritute == "SUBARMSITEM")
			{ 
				// 3 ,4 ,5
				if (_vDrawList[k - 1].frameY == 3 || _vDrawList[k - 1].frameY == 4 || _vDrawList[k - 1].frameY == 5)
				{
					swap(_vDrawList[k - 1], _vDrawList[k]);
				}
			}
			// 오브젝트
			else if (_vDrawList[k - 1].attritute == "OBJECT" && _vDrawList[k].attritute != "OBJECT")
			{
				if (_vDrawList[k - 1].rc.bottom > _vDrawList[k].rc.bottom)
				{
					swap(_vDrawList[k - 1], _vDrawList[k]);
				}
			}
			else
			{
				// 앞에있는 애가 뒤에보다 크면
				if (_vDrawList[k - 1].rc.bottom > _vDrawList[k].rc.bottom)
				{
					if((_vDrawList[k - 1].rc.bottom - _vDrawList[k - 1].rc.top))
					swap(_vDrawList[k - 1], _vDrawList[k]);
				}
			}
		}
	}

	for (int i = 0; i < _vDrawList.size();)
	{
		// 랜더 해주고 지워서 초기화 해준다.

		if (_vDrawList[i].type == DRAW_RENDER) _vDrawList[i].image->render(hdc, _vDrawList[i].rc.left - _focus.left , _vDrawList[i].rc.top - _focus.top);
		else if (_vDrawList[i].type == DRAW_FRAMERENDER) _vDrawList[i].image->frameRender(hdc, _vDrawList[i].rc.left - _focus.left, _vDrawList[i].rc.top - _focus.top, _vDrawList[i].frameX, _vDrawList[i].frameY);
		else if (_vDrawList[i].type == DRAW_ALPHARENDER) _vDrawList[i].image->alphaRender(hdc, _vDrawList[i].rc.left - _focus.left, _vDrawList[i].rc.top - _focus.top, _vDrawList[i].alpha);
		else if (_vDrawList[i].type == DRAW_ALPHAFRAMERENDER) _vDrawList[i].image->alphaFrameRender(hdc, _vDrawList[i].rc.left - _focus.left, _vDrawList[i].rc.top - _focus.top, _vDrawList[i].frameX, _vDrawList[i].frameY, _vDrawList[i].alpha);

		//IMAGEMANAGER->findImage("버클러장착")->frameRender(hdc, _vDrawList[i].rc.left - _focus.left, _vDrawList[i].rc.top - _focus.top, _vDrawList[i].frameX, 0);

		_vDrawList.erase(_vDrawList.begin());
	}

	
}

void drawManager::addDrawList(DRAWTYPE type, string attritute, image* image, int frameX, int frameY, RECT rc, BYTE alpha)
{
	RECT temp;

	if (!IntersectRect(&temp, &rc, &_focus)) return;

	tagDrawGameScene draw;
	draw.type = type;
	draw.attritute = attritute;
	draw.image = image;
	draw.frameX = frameX;
	draw.frameY = frameY;
	draw.rc = rc;
	draw.alpha = alpha;

	_vDrawList.push_back(draw);

}
