#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{
	_select = new select;
	_select->init();

	return S_OK;
}

void selectScene::release()
{
	_select->release();
}

void selectScene::update() 
{
	_select->update();
}

void selectScene::render()
{
	_select->render();
}