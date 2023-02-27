#include "stdafx.h"
#include "openingVideoScene.h"


openingVideoScene::openingVideoScene()
{
}


openingVideoScene::~openingVideoScene()
{
}

HRESULT openingVideoScene::init()
{

	_openingVideo = new openingVideo;
	_openingVideo->init();

	return S_OK;
}

void openingVideoScene::release()					  
{
	_openingVideo->release();
}

void openingVideoScene::update()					  
{
	_openingVideo->update();
}

void openingVideoScene::render()					  
{
	_openingVideo->render();
}