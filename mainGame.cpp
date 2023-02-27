#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}
////////////////////////////////////
//������ �Ҹ��� ���̺���
////////////////////////////////////

//�ʱ�ȭ ���ִ� �Լ�
HRESULT mainGame::init(void)
{
	gameNode::init(true);
	
	_bgmVolume = 0.5f;
	_soundEffectVolume = 1.0f;

	SCENEMANAGER->addScene("�ε���", new loadingScene);
	SCENEMANAGER->addScene("��Ʈ�ξ�", new introScene);
	SCENEMANAGER->addScene("�����׹����", new openingVideoScene);
	SCENEMANAGER->addScene("������", new maptoolScene);
	SCENEMANAGER->addScene("����Ʈ��", new selectScene);
	SCENEMANAGER->addScene("ũ������Ʈ��", new createScene);
	SCENEMANAGER->addScene("���Ӿ�", new gameScene);

	SCENEMANAGER->changeScene("�ε���");


	IMAGEMANAGER->addPngFrameImage("���콺������", "image\\���콺������.png", 416, 31, 13, 1, false, false);
	IMAGEMANAGER->addPngFrameImage("���콺������Ŭ��", "image\\���콺������Ŭ��.png", 54, 25, 2, 1, false, false);

	_mousePointer = IMAGEMANAGER->findImage("���콺������");
	_count = 0;
	_frameX = _frameY = 0;
	_isPlayVideo = false;

	return S_OK;
}

//�޸� �����Լ�
void mainGame::release(void)
{
	gameNode::release();

	SCENEMANAGER->release();

}

//���� �ϴ� ��
void mainGame::update(void)
{
	gameNode::update();
	
	// ��ư Ŭ��
	if (_leftButtonDown)
	{
		_mousePointer = IMAGEMANAGER->findImage("���콺������Ŭ��");
		_frameX = 0;
		_count = 0;
	}

	if (_mousePointer == IMAGEMANAGER->findImage("���콺������Ŭ��"))
	{
		if (_mousePointer->getMaxFrameX() < _frameX)
		{
			_mousePointer = IMAGEMANAGER->findImage("���콺������");
			_frameX = 0;
			_count = 0;
		}
	}
	else
	{
		if (_mousePointer->getMaxFrameX() < _frameX) _frameX = 0;
	}

	if (++_count % 10 == 0) _frameX++;



	if (SCENEMANAGER->findScene("�����׹����") == S_OK) _isPlayVideo = true;
	else _isPlayVideo = false;

	

	SCENEMANAGER->update();
}

//�׷��ִ� ��
void mainGame::render()
{
	//��� ��ȭ�� ������ �ʿ���
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	
	SCENEMANAGER->render();
	
	_mousePointer->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frameX, _frameY);
	
	if (_isPlayVideo) return;

	if (_debug) TIMEMANAGER->render(getMemDC());

	//����ۿ� �Ű� �׷��� �� �ǵ������� ���
	this->getBackBuffer()->render(getHDC(), 0, 0);

}


