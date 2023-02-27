#include "stdafx.h"
#include "select.h"
#include "player.h"


select::select()
{
}


select::~select()
{
}

HRESULT select::init()
{
	_currentCharacter = "";

	_background = IMAGEMANAGER->findImage("����Ʈ�����");
	_rc = RectMake(0, 0, WINSIZEX, WINSIZEY);

	_returnBtn.btnImage = IMAGEMANAGER->findImage("�ڷι�ư");
	_returnBtn.rc = RectMake(10, WINSIZEY - 46, _returnBtn.btnImage->getFrameWidth(), _returnBtn.btnImage->getFrameHeight());
	_returnBtn.frameX = _returnBtn.frameY = 0;


	_startBtn.btnImage = IMAGEMANAGER->findImage("���۹�ư");
	_startBtn.rc = RectMake(WINSIZEX - 10 - _startBtn.btnImage->getFrameWidth(), WINSIZEY - 52, _startBtn.btnImage->getFrameWidth(), _startBtn.btnImage->getFrameHeight());
	_startBtn.frameX = _startBtn.frameY = 0;

	_createCharacterBtn.btnImage = IMAGEMANAGER->findImage("ĳ���ͻ�����ư");
	_createCharacterBtn.rc = RectMake(_startBtn.rc.left - 14 - _createCharacterBtn.btnImage->getFrameWidth(), _startBtn.rc.top + 8, _createCharacterBtn.btnImage->getFrameWidth(), _createCharacterBtn.btnImage->getFrameHeight());
	_createCharacterBtn.frameX = _createCharacterBtn.frameY = 0;

	_deleteButton.btnImage = IMAGEMANAGER->findImage("ĳ���ͻ�����ư");
	_deleteButton.rc = RectMake(_returnBtn.rc.right + 14 , _returnBtn.rc.top, _deleteButton.btnImage->getFrameWidth(), _deleteButton.btnImage->getFrameHeight());
	_deleteButton.frameX = _deleteButton.frameY = 0;

	_isClick = false;
	_isPlaySound = false;

	_currentSelect = NULL;

	// ���� �̸�

	for (int i = 0; i < 8; ++i)
	{
		HANDLE file;
		char tempFileName[128];
		char fileNum[128];
		strcpy_s(tempFileName, "playerData");
		strcat_s(tempFileName, itoa(i, fileNum, 10));
		strcat_s(tempFileName, ".txt");

		file = CreateFile(tempFileName, GENERIC_READ, 0, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		
		// ������ ������
		if (file == INVALID_HANDLE_VALUE)
		{
			CloseHandle(file);
			continue;
		}
		// ������ ������
		else
		{
			string fileName = tempFileName;
			_vSelectCharacter.push_back(fileName);
			CloseHandle(file);
		}
	}

	for(int i = 0 ; i < MAXCHARACTER; ++i)
	{
		_arrSelectCharacter[i] = new tagSelectCharacter;
	}

	for (int i = 0; i < _vSelectCharacter.size(); ++i)
	{
		HANDLE file;
		DWORD read;
		file = CreateFile(_vSelectCharacter[i].c_str(), GENERIC_READ, 0, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		strcpy_s(_arrSelectCharacter[i]->fileName,_vSelectCharacter[i].c_str());
		_arrSelectCharacter[i]->boxNum = i;
		_arrSelectCharacter[i]->frameX = 0;
		_arrSelectCharacter[i]->isUse = true;
		_arrSelectCharacter[i]->image = IMAGEMANAGER->findImage("��þ�_IDLE");
		_arrSelectCharacter[i]->alpha = 150;
		// �г���
		ReadFile(file, _arrSelectCharacter[i]->nickName, sizeof(char) * 128, &read, NULL);
		// ����
		ReadFile(file, &_arrSelectCharacter[i]->level, sizeof(int), &read, NULL);
		// Ÿ��
		ReadFile(file, &_arrSelectCharacter[i]->type, sizeof(PLAYERATTACKTYPE), &read, NULL);
		CloseHandle(file);
	}


	_arrSelectCharacter[0]->rc = RectMake(_rc.left + WINSIZEX / 2 + 32, _rc.bottom - 250, 100, 100);
	_arrSelectCharacter[1]->rc = RectMake(_rc.left + WINSIZEX / 2 - 122, _rc.bottom - 275, 100, 100);
	_arrSelectCharacter[2]->rc = RectMake(_rc.left + WINSIZEX / 2 - 212, _rc.bottom - 350, 100, 100);
	_arrSelectCharacter[3]->rc = RectMake(_rc.left + WINSIZEX / 2 - 122, _rc.bottom - 425, 100, 100);
	_arrSelectCharacter[4]->rc = RectMake(_rc.left + WINSIZEX / 2 + 32, _rc.bottom - 450, 100, 100);
	_arrSelectCharacter[5]->rc = RectMake(_rc.left + WINSIZEX / 2 + 182, _rc.bottom - 425, 100, 100);
	_arrSelectCharacter[6]->rc = RectMake(_rc.left + WINSIZEX / 2 + 272, _rc.bottom - 350, 100, 100);
	_arrSelectCharacter[7]->rc = RectMake(_rc.left + WINSIZEX / 2 + 182, _rc.bottom - 275, 100, 100);
	
	
	return S_OK;
}

void select::release()
{

}

void select::update() 
{

	for (int i = 0; i < MAXCHARACTER; ++i)
	{
		if (_currentSelect == _arrSelectCharacter[i]) _arrSelectCharacter[i]->alpha = 255;
		else
		{
			_arrSelectCharacter[i]->alpha = 150;
			_arrSelectCharacter[i]->frameX = 0;
		}
	}

	if (!_isClick)
	{
		if (PtInRect(&_returnBtn.rc, _ptMouse))
		{
			if (!_isPlaySound) SOUNDMANAGER->play("ȿ������ư�浹", _soundEffectVolume);
			_isPlaySound = true;
			_returnBtn.frameX = 1;
		}
		else if (PtInRect(&_startBtn.rc, _ptMouse))
		{
			if (!_isPlaySound) SOUNDMANAGER->play("ȿ������ư�浹", _soundEffectVolume);
			_isPlaySound = true;
			_startBtn.frameX = 1;
		}
		else if (PtInRect(&_createCharacterBtn.rc, _ptMouse))
		{
			if (!_isPlaySound) SOUNDMANAGER->play("ȿ������ư�浹", _soundEffectVolume);
			_isPlaySound = true;
			_createCharacterBtn.frameX = 1;
		}
		else
		{
			_isPlaySound = false;
			_returnBtn.frameX = 0;
			_startBtn.frameX = 0;
			_createCharacterBtn.frameX = 0;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_isClick = true;

		if (PtInRect(&_returnBtn.rc, _ptMouse))
		{
			SOUNDMANAGER->play("ȿ������ưŬ��", _soundEffectVolume);
			_returnBtn.frameX = 2;
		}
		else if (PtInRect(&_startBtn.rc, _ptMouse))
		{
			SOUNDMANAGER->play("ȿ������ŸƮ��ưŬ��", _soundEffectVolume);
			_startBtn.frameX = 2;
		}
		else if (PtInRect(&_createCharacterBtn.rc, _ptMouse))
		{
			SOUNDMANAGER->play("ȿ������ưŬ��", _soundEffectVolume);
			_createCharacterBtn.frameX = 2;
		}
		else
		{
			for (int i = 0; i < MAXCHARACTER; ++i)
			{
				if (PtInRect(&_arrSelectCharacter[i]->rc, _ptMouse))
				{
					if (_arrSelectCharacter[i]->isUse)
					{
						_currentSelect = _arrSelectCharacter[i];
						_currentSelect->frameX = 0;
						_currentCharacter = _currentSelect->fileName;
						break;
					}
					else
					{
						_currentCharacter = "";
						_currentSelect = NULL;
					}
				}
			}

		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_isClick = false;

		if (PtInRect(&_returnBtn.rc, _ptMouse))
		{
			SCENEMANAGER->changeScene("��Ʈ�ξ�");
			SOUNDMANAGER->stop("����Ʈ��");
		}
		else if (PtInRect(&_startBtn.rc, _ptMouse))
		{
			SOUNDMANAGER->stop("����Ʈ��");
			if (_currentCharacter != "")
			{
				SCENEMANAGER->changeScene("���Ӿ�");
			}
		}
		else if (PtInRect(&_deleteButton.rc, _ptMouse))
		{
			if (_currentCharacter != "")
			{
				HANDLE file;
				file = CreateFile(_currentCharacter.c_str(),
					0,
					FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
					NULL,
					OPEN_EXISTING,
					FILE_FLAG_DELETE_ON_CLOSE,
					0);
				for (int i = 0; i < MAXCHARACTER; ++i)
				{
					if (!_arrSelectCharacter[i]->isUse) continue;
					if (!strcmp(_arrSelectCharacter[i]->fileName, _currentCharacter.c_str()))
					{
						_arrSelectCharacter[i]->isUse = false;
						strcpy_s(_arrSelectCharacter[i]->fileName, "");
						strcpy_s(_arrSelectCharacter[i]->nickName, "");
						_arrSelectCharacter[i]->frameX = 0;
						_arrSelectCharacter[i]->image = NULL;
						_arrSelectCharacter[i]->level = 0;
						_arrSelectCharacter[i]->type = NULL;
					}
				}

				_currentCharacter = "";
				_currentSelect = NULL;

				CloseHandle(file);
			}

		}
		else if (PtInRect(&_createCharacterBtn.rc, _ptMouse))
		{
			// �ִ�� ���� �� �մ� ĳ���� ������ 8���̹Ƿ� �Ѿ�� ����ȭ�� �ȵǰ� �����.
			if(_vSelectCharacter.size() < MAXCHARACTER) SCENEMANAGER->changeScene("ũ������Ʈ��");
		}
	}



}

void select::render()
{
	// ���
	_background->render(getMemDC());

	// ��ư
	_returnBtn.btnImage->frameRender(getMemDC(), _returnBtn.rc.left, _returnBtn.rc.top, _returnBtn.frameX, _returnBtn.frameY);
	_startBtn.btnImage->frameRender(getMemDC(), _startBtn.rc.left, _startBtn.rc.top, _startBtn.frameX, _startBtn.frameY);
	_createCharacterBtn.btnImage->frameRender(getMemDC(), _createCharacterBtn.rc.left, _createCharacterBtn.rc.top, _createCharacterBtn.frameX, _createCharacterBtn.frameY);

	if (_currentCharacter != "") _deleteButton.btnImage->frameRender(getMemDC(), _deleteButton.rc.left, _deleteButton.rc.top, _deleteButton.frameX, _deleteButton.frameY);

	// ĳ���� ���ý� Ŭ�� ��Ʈ����
	if (_debug)
	{
		Rectangle(getMemDC(), _arrSelectCharacter[0]->rc.left, _arrSelectCharacter[0]->rc.top, _arrSelectCharacter[0]->rc.right, _arrSelectCharacter[0]->rc.bottom);
		Rectangle(getMemDC(), _arrSelectCharacter[1]->rc.left, _arrSelectCharacter[1]->rc.top, _arrSelectCharacter[1]->rc.right, _arrSelectCharacter[1]->rc.bottom);
		Rectangle(getMemDC(), _arrSelectCharacter[2]->rc.left, _arrSelectCharacter[2]->rc.top, _arrSelectCharacter[2]->rc.right, _arrSelectCharacter[2]->rc.bottom);
		Rectangle(getMemDC(), _arrSelectCharacter[3]->rc.left, _arrSelectCharacter[3]->rc.top, _arrSelectCharacter[3]->rc.right, _arrSelectCharacter[3]->rc.bottom);
		Rectangle(getMemDC(), _arrSelectCharacter[4]->rc.left, _arrSelectCharacter[4]->rc.top, _arrSelectCharacter[4]->rc.right, _arrSelectCharacter[4]->rc.bottom);
		Rectangle(getMemDC(), _arrSelectCharacter[5]->rc.left, _arrSelectCharacter[5]->rc.top, _arrSelectCharacter[5]->rc.right, _arrSelectCharacter[5]->rc.bottom);
		Rectangle(getMemDC(), _arrSelectCharacter[6]->rc.left, _arrSelectCharacter[6]->rc.top, _arrSelectCharacter[6]->rc.right, _arrSelectCharacter[6]->rc.bottom);
		Rectangle(getMemDC(), _arrSelectCharacter[7]->rc.left, _arrSelectCharacter[7]->rc.top, _arrSelectCharacter[7]->rc.right, _arrSelectCharacter[7]->rc.bottom);
	}

	// ���� ������ ���� ��ġ�ٲ���

	// ĳ���� ������ �Ǿ��ٸ�
	if (_currentSelect != NULL)
	{
		static int frameX = 0;
		static int count = 0;

		if (++count % 10 == 0)
		{
			frameX++;
			_currentSelect->frameX++;
		}
		if (frameX > IMAGEMANAGER->findImage("ĳ���ͼ���")->getMaxFrameX()) frameX = 0;
		if (_currentSelect->frameX > IMAGEMANAGER->findImage("��þ�_IDLE")->getMaxFrameX()) _currentSelect->frameX = 0;

		char str[128];
		RECT tempRc = RectMakeCenter(
			(_currentSelect->rc.left + _currentSelect->rc.right) / 2,
			_currentSelect->rc.bottom - 30,
			IMAGEMANAGER->findImage("ĳ���ͼ���")->getFrameWidth(),
			IMAGEMANAGER->findImage("ĳ���ͼ���")->getFrameHeight());
		IMAGEMANAGER->findImage("ĳ���ͼ���")->frameRender(getMemDC(), tempRc.left, tempRc.top, frameX, 0);

		IMAGEMANAGER->findImage("��þȾ�")->render(getMemDC(), _rc.left + 16, _rc.top + 167);
		sprintf_s(str, "�̸� : %s", _currentSelect->nickName);
		TextOut(getMemDC(), _rc.left + 104, _rc.top + 180, str, strlen(str));
		sprintf_s(str, "���� : %3d", _currentSelect->level);
		TextOut(getMemDC(), _rc.left + 104, _rc.top + 210, str, strlen(str));
		if (_currentSelect->type == P_TYPE_MIX) sprintf_s(str, "Ÿ�� : %s", "��������");
		else if (_currentSelect->type == P_TYPE_HACK) sprintf_s(str, "Ÿ�� : %s", "������");
		else if (_currentSelect->type == P_TYPE_STAB) sprintf_s(str, "Ÿ�� : %s", "�����");
		TextOut(getMemDC(), _rc.left + 104, _rc.top + 240, str, strlen(str));
	}

	// ������� ĳ���Ͱ� �����Ѵٸ�
	for (int i = 0; i < MAXCHARACTER; ++i)
	{
		if (!_arrSelectCharacter[i]->isUse) continue;
		_arrSelectCharacter[i]->image->alphaFrameRender(getMemDC(),
			_arrSelectCharacter[i]->rc.left + (IMAGEMANAGER->findImage("��þ�_IDLE")->getFrameWidth() / 2),
			_arrSelectCharacter[i]->rc.top - 4,
			_arrSelectCharacter[i]->frameX, 0, _arrSelectCharacter[i]->alpha);
	}



}