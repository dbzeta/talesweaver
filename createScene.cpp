#include "stdafx.h"
#include "createScene.h"


createScene::createScene()
{
}


createScene::~createScene()
{
}

HRESULT createScene::init()
{
	_create = new create;
	_create->init();

	return S_OK;
}

void createScene::release()
{
	_create->release();
}

void createScene::update() 
{
	_create->update();
}

void createScene::render() 
{
	_create->render();
}