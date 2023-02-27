#include "stdafx.h"
#include "maptoolScene.h"

maptoolScene::maptoolScene()
{
}


maptoolScene::~maptoolScene()
{
}

HRESULT maptoolScene::init(void)
{
	_maptool = new maptool;
	_maptool->init();

	return S_OK;
}

void maptoolScene::release(void)
{
	_maptool->release();
}

void maptoolScene::update(void)
{
	_maptool->update();
}

void maptoolScene::render(void)
{
	_maptool->render();
}
