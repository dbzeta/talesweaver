#include "stdafx.h"
#include "introScene.h"


introScene::introScene()
{
}


introScene::~introScene()
{
}


HRESULT introScene::init()
{
	SOUNDMANAGER->play("��Ʈ�ξ�", _bgmVolume);

	_intro = new intro;
	_intro->init();


	return S_OK;
}

void introScene::release()
{
	SOUNDMANAGER->stop("��Ʈ�ξ�");
	_intro->release();

}

void introScene::update() 
{
	_intro->update();
}

void introScene::render() 
{
	_intro->render();
}
