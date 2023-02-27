#include "stdafx.h"
#include "aStarTestScene.h"


aStarTestScene::aStarTestScene()
{
}


aStarTestScene::~aStarTestScene()
{
}

HRESULT aStarTestScene::init()
{
	// _ast = new aStarTest;
	// _ast->init();

	return S_OK;
}

void aStarTestScene::release()
{

}

void aStarTestScene::update()
{
	_ast->update();
}

void aStarTestScene::render()
{
	_ast->render();
}