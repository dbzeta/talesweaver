#include "stdafx.h"
#include "create.h"
#include "player.h"
#include "mapManager.h"
#include "itemManager.h"


create::create()
{
}


create::~create()
{
}

HRESULT create::init()
{
	
	_type = P_TYPE_MIX;
	_background = IMAGEMANAGER->findImage("물리복합");
	_count = 0;
	_frameX = _frameY = 0;
	_rc = RectMake(0, 0, WINSIZEX, WINSIZEY);

	setBtn();
	selectType();

	_isClick = false;
	_isPlaySound = false;
	_isWriteNickName = false;

	strcpy_s(_nickName, "");


	// 파일 이름

	for (int i = 0; i < 8; ++i)
	{
		DWORD read;
		HANDLE file;

		char fileNum[128];
		strcpy_s(_fileName, "playerData");
		strcpy_s(_nickName, "player");
		strcat_s(_fileName, itoa(i, fileNum, 10));
		strcat_s(_nickName, itoa(i, fileNum, 10));
		strcat_s(_fileName, ".txt");


		file = CreateFile(_fileName, GENERIC_READ, 0, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		// 없는 파일이면
		if (file == INVALID_HANDLE_VALUE)
		{
			CloseHandle(file);
			break;
		}
		// 있는 파일이면 숫자를 붙여서 다른 이름을 생성
		else
		{

			CloseHandle(file);
			continue;
		}
	}

	return S_OK;
}

void create::release()
{

}

void create::update()
{
	if (++_count % 7 == 0) _frameY++;
	if (_frameY > _background->getMaxFrameY()) _frameY = _background->getMaxFrameY();

	if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		isOnceClickDown();
		_isClick = true;
	}
	if(KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		isOnceClickUp();
		_isClick = false;
	}

	if (!_isClick) checkBtn();

	if (_isWriteNickName)
	{

	}



}

void create::render()
{
	_background->frameRender(getMemDC(), 0, 0, 0, _frameY);
	
	// 버튼 이미지 랜더
	_returnBtn->btnImage->frameRender(getMemDC(), _returnBtn->rc.left, _returnBtn->rc.top, _returnBtn->frameX, _returnBtn->frameY);
	// _initBtn.btnImage->frameRender(getMemDC(), _initBtn.rc.left, _initBtn.rc.top, _initBtn.frameX, _initBtn.frameY);
	_createCharacterBtn->btnImage->frameRender(getMemDC(), _createCharacterBtn->rc.left, _createCharacterBtn->rc.top, _createCharacterBtn->frameX, _createCharacterBtn->frameY);

	// _selectTypeBtn.selectTypeBtn[0].btnImage->frameRender(getMemDC(), _selectTypeBtn.selectTypeBtn[0].rc.left, _selectTypeBtn.selectTypeBtn[0].rc.top, _selectTypeBtn.selectTypeBtn[0].frameX, _selectTypeBtn.selectTypeBtn[0].frameY);
	// Rectangle(getMemDC(), _selectTypeBtn.selectTypeBtn[1].rc.left, _selectTypeBtn.selectTypeBtn[1].rc.top, _selectTypeBtn.selectTypeBtn[1].rc.right, _selectTypeBtn.selectTypeBtn[1].rc.bottom);
	// Rectangle(getMemDC(), _selectTypeBtn.selectTypeBtn[2].rc.left, _selectTypeBtn.selectTypeBtn[2].rc.top, _selectTypeBtn.selectTypeBtn[2].rc.right, _selectTypeBtn.selectTypeBtn[2].rc.bottom);

	// Rectangle(getMemDC(), _writeNickName.left, _writeNickName.top, _writeNickName.right, _writeNickName.bottom);
	// Rectangle(getMemDC(), _checkNickName.left, _checkNickName.top, _checkNickName.right, _checkNickName.bottom);
	TextOut(getMemDC(), _writeNickName.left, _writeNickName.top, _nickName, strlen(_nickName));
}

void create::selectType()
{

	// 선택했을때 초기 스텟
	switch (_type)
	{
	case P_TYPE_MIX:
	{
		// 물리복합		
		_background = IMAGEMANAGER->findImage("물리복합");		
		_maxHp = 220;
		_maxMp = 50;
		_maxSp = 1000;


	} break;
	case P_TYPE_HACK:
	{
		// 베기		
		_background = IMAGEMANAGER->findImage("베기형");
		_maxHp = 240;
		_maxMp = 55;
		_maxSp = 900;
		
		
	} break;
	case P_TYPE_STAB:
	{
		// 찌르기				
		_background = IMAGEMANAGER->findImage("찌르기형");
		_maxHp = 200;
		_maxMp = 55;
		_maxSp = 1100;
		
	} break;
	default:
		break;
	}

	
	

}

void create::checkBtn()
{
	if (PtInRect(&_returnBtn->rc, _ptMouse))
	{
		if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
		_isPlaySound = true;
		_returnBtn->frameX = 1;
	}
	// else if (PtInRect(&_initBtn->rc, _ptMouse))
	// {
	//  if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
	//  _isPlaySound = true;
	// 	_initBtn->frameX = 1;
	// }
	else if (PtInRect(&_createCharacterBtn->rc, _ptMouse))
	{
		if (!_isPlaySound) SOUNDMANAGER->play("효과음버튼충돌", _soundEffectVolume);
		_isPlaySound = true;
		_createCharacterBtn->frameX = 1;
	}
	else
	{
		_isPlaySound = false;
		_returnBtn->frameX = 0;
		// _initBtn->frameX = 0;
		_createCharacterBtn->frameX = 0;
	}

}

void create::setBtn()
{
	_returnBtn = new tagButton;
	_returnBtn->btnImage = IMAGEMANAGER->findImage("뒤로버튼");
	_returnBtn->frameX = _returnBtn->frameY = 0;
	_returnBtn->rc = RectMake(_rc.left + 13, _rc.bottom - 45, _returnBtn->btnImage->getFrameWidth(), _returnBtn->btnImage->getFrameHeight());
	
	// _initBtn = new tagButton;
	// _initBtn.btnImage = IMAGEMANAGER->findImage("초기화버튼");
	// _initBtn.frameX = _initBtn.frameY = 0;
	// _initBtn.rc = RectMake(_rc.right - 100, _rc.bottom - 20, _initBtn.btnImage->getFrameWidth(), _initBtn.btnImage->getFrameHeight());
	
	_createCharacterBtn = new tagButton;
	_createCharacterBtn->btnImage = IMAGEMANAGER->findImage("캐릭터생성버튼");
	_createCharacterBtn->frameX = _createCharacterBtn->frameY = 0;
	_createCharacterBtn->rc = RectMake(_rc.right - 116, _rc.bottom - 45, _createCharacterBtn->btnImage->getFrameWidth(), _createCharacterBtn->btnImage->getFrameHeight());

	_selectTypeBtn.characterNum = 0;
	_selectTypeBtn.selectTypeBtn[0].btnImage = IMAGEMANAGER->findImage("물리복합버튼");
	_selectTypeBtn.selectTypeBtn[0].frameX = _selectTypeBtn.selectTypeBtn[0].frameY = 0;
	_selectTypeBtn.selectTypeBtn[0].rc = RectMake(_rc.right - 216, _rc.top + 354, _selectTypeBtn.selectTypeBtn[0].btnImage->getFrameWidth(), _selectTypeBtn.selectTypeBtn[0].btnImage->getFrameHeight());
	_selectTypeBtn.selectTypeBtn[1].rc = RectMake(_rc.right - 216, _selectTypeBtn.selectTypeBtn[0].rc.bottom + 3, _selectTypeBtn.selectTypeBtn[0].btnImage->getFrameWidth(), _selectTypeBtn.selectTypeBtn[0].btnImage->getFrameHeight());
	_selectTypeBtn.selectTypeBtn[2].rc = RectMake(_rc.right - 216, _selectTypeBtn.selectTypeBtn[1].rc.bottom + 3, _selectTypeBtn.selectTypeBtn[0].btnImage->getFrameWidth(), _selectTypeBtn.selectTypeBtn[0].btnImage->getFrameHeight());

	// 시간 관계상 이미지 생략.
	_writeNickName = RectMake(_rc.right - 223, _rc.top + 460, 136, 20);
	_checkNickName = RectMake(_rc.right - 80, _rc.top + 458, 58, 24);

	
}

bool create::isOnceClickDown()
{

	// _isWriteNickName = false;
	// setIsWrite(false);

	if (PtInRect(&_returnBtn->rc, _ptMouse))
	{
		SOUNDMANAGER->play("효과음버튼클릭", _soundEffectVolume);
		_currentSelectBtn = _returnBtn;
		_currentSelectBtn->frameX = 2;

		return true;
	}
	//else if (PtInRect(&_initBtn->rc, _ptMouse))
	//{
	//		SOUNDMANAGER->play("효과음버튼클릭", _soundEffectVolume);
	//	_currentSelectBtn = _initBtn;
	//	_currentSelectBtn->frameX = 2;
	//
	//	return true;
	//}
	else if (PtInRect(&_createCharacterBtn->rc, _ptMouse))
	{
		SOUNDMANAGER->play("효과음버튼클릭", _soundEffectVolume);
		_currentSelectBtn = _createCharacterBtn;
		_currentSelectBtn->frameX = 2;

		return true;
	}
	else if (PtInRect(&_selectTypeBtn.selectTypeBtn[0].rc, _ptMouse))
	{
		SOUNDMANAGER->play("효과음버튼클릭", _soundEffectVolume);
		_selectTypeBtn.selectTypeBtn[0].frameX = 0;
		_type = P_TYPE_MIX;
		selectType();
		_frameY = 0;
		return true;
	}
	else if (PtInRect(&_selectTypeBtn.selectTypeBtn[1].rc, _ptMouse))
	{
		SOUNDMANAGER->play("효과음버튼클릭", _soundEffectVolume);
		_type = P_TYPE_HACK;
		selectType();
		_frameY = 0;
		return true;
	}
	else if (PtInRect(&_selectTypeBtn.selectTypeBtn[2].rc, _ptMouse))
	{
		SOUNDMANAGER->play("효과음버튼클릭", _soundEffectVolume);
		_type = P_TYPE_STAB;
		selectType();
		_frameY = 0;
		return true;
	}
	else if (PtInRect(&_writeNickName,_ptMouse))
	{
		_isWriteNickName = true;
		setIsWrite(true);
		return true;
	}
	else if (PtInRect(&_checkNickName, _ptMouse))
	{
		SOUNDMANAGER->play("효과음메뉴창확인", _soundEffectVolume);
		return true;
	}
	else 
	{
		_isWriteNickName = false;
		//setIsWrite(false);
		return true;
	}

	return false;
}

bool create::isOnceClickUp()
{

	_returnBtn->frameX = 0;
	// _initBtn->frameX = 0;
	_createCharacterBtn->frameX = 0;

	if (PtInRect(&_returnBtn->rc, _ptMouse))
	{
		if (_currentSelectBtn == _returnBtn) SCENEMANAGER->changeScene("셀렉트씬");
		return true;
	}
	//else if (PtInRect(&_initBtn->rc, _ptMouse))
	//{
	//
	//	return true;
	//}
	else if (PtInRect(&_createCharacterBtn->rc, _ptMouse))
	{
		if (_currentSelectBtn == _createCharacterBtn)
		{
			createCharacter();
			SCENEMANAGER->changeScene("셀렉트씬");
		}
		return true;
	}
	else if (PtInRect(&_checkNickName, _ptMouse))
	{

	  //	HANDLE file;
	  //	DWORD read;


		return true;
	}
	else
	{
		return true;
	}
	

	return false;
}

void create::createCharacter()
{
	HANDLE file;
	DWORD write;


	// 파일 이름
	file = CreateFile(_fileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// 닉네임	
	WriteFile(file, _nickName, sizeof(char) * 128, &write, NULL);
	// 레벨
	int level = 1;
	WriteFile(file, &level, sizeof(int), &write, NULL);
	// 타입
	WriteFile(file, &_type, sizeof(CHARACTERTYPE), &write, NULL);
	// 공격타입
	for (int i = 0; i < 3; ++i)
	{
		PLAYERATTACKTYPE attackType;

		if ((CHARACTERTYPE)_type == P_TYPE_MIX) attackType = P_ATTACK_VERTICAL_HACK;
		else if ((CHARACTERTYPE)_type == P_TYPE_HACK) attackType = P_ATTACK_HORIZONTAL_HACK;
		else if ((CHARACTERTYPE)_type == P_TYPE_STAB) attackType = P_ATTACK_STAB;
		
		WriteFile(file, &attackType, sizeof(PLAYERATTACKTYPE), &write, NULL);
	}
	// 스테이터스 ( 직접찍은 )
	_stab = 0;
	_hack = 0;
	_int = 0;
	_def = 0;
	_mr = 0;
	_dex = 0;
	_agi = 0;
	WriteFile(file, &_stab, sizeof(int), &write, NULL);
	WriteFile(file, &_hack, sizeof(int), &write, NULL);
	WriteFile(file, &_int, sizeof(int), &write, NULL);
	WriteFile(file, &_def, sizeof(int), &write, NULL);
	WriteFile(file, &_mr, sizeof(int), &write, NULL);
	WriteFile(file, &_dex, sizeof(int), &write, NULL);
	WriteFile(file, &_agi, sizeof(int), &write, NULL);

	int size = 1;
	// 인벤토리 크기
	WriteFile(file, &size, sizeof(int), &write, NULL);
	// 인벤토리
	for (int i = 0; i < size; ++i)
	{
		int item = TYPE_SWORD + 1;
		WriteFile(file, &item, sizeof(int), &write, NULL);
	}

	size = 0;
	// 장비창 크기
	WriteFile(file, &size, sizeof(int), &write, NULL);
	// 장비창 
	

	size = 0;
	// 스킬창 크기
	WriteFile(file, &size, sizeof(int), &write, NULL);
	// 스킬창 
	
	// 초기맵
	MAP initMap = MAP_TUTORIAL01;
	WriteFile(file, &initMap, sizeof(MAP), &write, NULL);
	// 좌표 ( CX,BY)
	float cx, by;
	cx = (float)(WINSIZEX / 2);
	by = 400.0f;
	WriteFile(file, &cx, sizeof(float), &write, NULL);
	WriteFile(file, &by, sizeof(float), &write, NULL);
	// 돈
	int money = 5000;
	WriteFile(file, &money, sizeof(int), &write, NULL);
	// 현재 경험치량
	int currentExp = 0;
	WriteFile(file, &currentExp, sizeof(int), &write, NULL);
	// 현재 포인트량	
	int point = 0;
	WriteFile(file, &point, sizeof(int), &write, NULL);
	// 현재 HP, MP, SP량
	int hp = _maxHp;
	int mp = _maxMp;
	int sp = _maxSp;
	WriteFile(file, &hp, sizeof(int), &write, NULL);
	WriteFile(file, &mp, sizeof(int), &write, NULL);
	WriteFile(file, &sp, sizeof(int), &write, NULL);

	CloseHandle(file);
}
