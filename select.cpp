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

	_background = IMAGEMANAGER->findImage("셀렉트씬배경");
	_rc = RectMake(0, 0, WINSIZEX, WINSIZEY);

	_returnBtn.btnImage = IMAGEMANAGER->findImage("뒤로버튼");
	_returnBtn.rc = RectMake(10, WINSIZEY - 46, _returnBtn.btnImage->getFrameWidth(), _returnBtn.btnImage->getFrameHeight());
	_returnBtn.frameX = _returnBtn.frameY = 0;


	_startBtn.btnImage = IMAGEMANAGER->findImage("시작버튼");
	_startBtn.rc = RectMake(WINSIZEX - 10 - _startBtn.btnImage->getFrameWidth(), WINSIZEY - 52, _startBtn.btnImage->getFrameWidth(), _startBtn.btnImage->getFrameHeight());
	_startBtn.frameX = _startBtn.frameY = 0;

	_createCharacterBtn.btnImage = IMAGEMANAGER->findImage("캐릭터생성버튼");
	_createCharacterBtn.rc = RectMake(_startBtn.rc.left - 14 - _createCharacterBtn.btnImage->getFrameWidth(), _startBtn.rc.top + 8, _createCharacterBtn.btnImage->getFrameWidth(), _createCharacterBtn.btnImage->getFrameHeight());
	_createCharacterBtn.frameX = _createCharacterBtn.frameY = 0;

	_deleteButton.btnImage = IMAGEMANAGER->findImage("캐릭터삭제버튼");
	_deleteButton.rc = RectMake(_returnBtn.rc.right + 14 , _returnBtn.rc.top, _deleteButton.btnImage->getFrameWidth(), _deleteButton.btnImage->getFrameHeight());
	_deleteButton.frameX = _deleteButton.frameY = 0;

	_isClick = false;
	_isPlaySound = false;

	_currentSelect = NULL;

	// 파일 이름

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
		
		// 파일이 없으면
		if (file == INVALID_HANDLE_VALUE)
		{
			CloseHandle(file);
			continue;
		}
		// 파일이 있으면
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
		_arrSelectCharacter[i]->image = IMAGEMANAGER->findImage("루시안_IDLE");
		_arrSelectCharacter[i]->alpha = 150;
		// 닉네임
		ReadFile(file, _arrSelectCharacter[i]->nickName, sizeof(char) * 128, &read, NULL);
		// 레벨
		ReadFile(file, &_arrSelectCharacter[i]->level, sizeof(int), &read, NULL);
		// 타입
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
			if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
			_isPlaySound = true;
			_returnBtn.frameX = 1;
		}
		else if (PtInRect(&_startBtn.rc, _ptMouse))
		{
			if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
			_isPlaySound = true;
			_startBtn.frameX = 1;
		}
		else if (PtInRect(&_createCharacterBtn.rc, _ptMouse))
		{
			if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
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
			SOUNDMANAGER->play("효과음버튼클릭", _soundEffectVolume);
			_returnBtn.frameX = 2;
		}
		else if (PtInRect(&_startBtn.rc, _ptMouse))
		{
			SOUNDMANAGER->play("효과음스타트버튼클릭", _soundEffectVolume);
			_startBtn.frameX = 2;
		}
		else if (PtInRect(&_createCharacterBtn.rc, _ptMouse))
		{
			SOUNDMANAGER->play("효과음버튼클릭", _soundEffectVolume);
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
			SCENEMANAGER->changeScene("인트로씬");
			SOUNDMANAGER->stop("셀렉트씬");
		}
		else if (PtInRect(&_startBtn.rc, _ptMouse))
		{
			SOUNDMANAGER->stop("셀렉트씬");
			if (_currentCharacter != "")
			{
				SCENEMANAGER->changeScene("게임씬");
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
			// 최대로 만들 수 잇는 캐릭터 갯수가 8개이므로 넘어가면 씬전화이 안되게 만든다.
			if(_vSelectCharacter.size() < MAXCHARACTER) SCENEMANAGER->changeScene("크리에이트씬");
		}
	}



}

void select::render()
{
	// 배경
	_background->render(getMemDC());

	// 버튼
	_returnBtn.btnImage->frameRender(getMemDC(), _returnBtn.rc.left, _returnBtn.rc.top, _returnBtn.frameX, _returnBtn.frameY);
	_startBtn.btnImage->frameRender(getMemDC(), _startBtn.rc.left, _startBtn.rc.top, _startBtn.frameX, _startBtn.frameY);
	_createCharacterBtn.btnImage->frameRender(getMemDC(), _createCharacterBtn.rc.left, _createCharacterBtn.rc.top, _createCharacterBtn.frameX, _createCharacterBtn.frameY);

	if (_currentCharacter != "") _deleteButton.btnImage->frameRender(getMemDC(), _deleteButton.rc.left, _deleteButton.rc.top, _deleteButton.frameX, _deleteButton.frameY);

	// 캐릭터 선택시 클릭 렉트범위
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

	// 랜더 순서를 위해 위치바꿔줌

	// 캐릭터 선택이 되었다면
	if (_currentSelect != NULL)
	{
		static int frameX = 0;
		static int count = 0;

		if (++count % 10 == 0)
		{
			frameX++;
			_currentSelect->frameX++;
		}
		if (frameX > IMAGEMANAGER->findImage("캐릭터선택")->getMaxFrameX()) frameX = 0;
		if (_currentSelect->frameX > IMAGEMANAGER->findImage("루시안_IDLE")->getMaxFrameX()) _currentSelect->frameX = 0;

		char str[128];
		RECT tempRc = RectMakeCenter(
			(_currentSelect->rc.left + _currentSelect->rc.right) / 2,
			_currentSelect->rc.bottom - 30,
			IMAGEMANAGER->findImage("캐릭터선택")->getFrameWidth(),
			IMAGEMANAGER->findImage("캐릭터선택")->getFrameHeight());
		IMAGEMANAGER->findImage("캐릭터선택")->frameRender(getMemDC(), tempRc.left, tempRc.top, frameX, 0);

		IMAGEMANAGER->findImage("루시안얼굴")->render(getMemDC(), _rc.left + 16, _rc.top + 167);
		sprintf_s(str, "이름 : %s", _currentSelect->nickName);
		TextOut(getMemDC(), _rc.left + 104, _rc.top + 180, str, strlen(str));
		sprintf_s(str, "레벨 : %3d", _currentSelect->level);
		TextOut(getMemDC(), _rc.left + 104, _rc.top + 210, str, strlen(str));
		if (_currentSelect->type == P_TYPE_MIX) sprintf_s(str, "타입 : %s", "물리복합");
		else if (_currentSelect->type == P_TYPE_HACK) sprintf_s(str, "타입 : %s", "베기형");
		else if (_currentSelect->type == P_TYPE_STAB) sprintf_s(str, "타입 : %s", "찌르기형");
		TextOut(getMemDC(), _rc.left + 104, _rc.top + 240, str, strlen(str));
	}

	// 만들어진 캐릭터가 존재한다면
	for (int i = 0; i < MAXCHARACTER; ++i)
	{
		if (!_arrSelectCharacter[i]->isUse) continue;
		_arrSelectCharacter[i]->image->alphaFrameRender(getMemDC(),
			_arrSelectCharacter[i]->rc.left + (IMAGEMANAGER->findImage("루시안_IDLE")->getFrameWidth() / 2),
			_arrSelectCharacter[i]->rc.top - 4,
			_arrSelectCharacter[i]->frameX, 0, _arrSelectCharacter[i]->alpha);
	}



}