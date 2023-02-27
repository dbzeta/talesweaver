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
	_background = IMAGEMANAGER->findImage("��������");
	_count = 0;
	_frameX = _frameY = 0;
	_rc = RectMake(0, 0, WINSIZEX, WINSIZEY);

	setBtn();
	selectType();

	_isClick = false;
	_isPlaySound = false;
	_isWriteNickName = false;

	strcpy_s(_nickName, "");


	// ���� �̸�

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
		// ���� �����̸�
		if (file == INVALID_HANDLE_VALUE)
		{
			CloseHandle(file);
			break;
		}
		// �ִ� �����̸� ���ڸ� �ٿ��� �ٸ� �̸��� ����
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
	
	// ��ư �̹��� ����
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

	// ���������� �ʱ� ����
	switch (_type)
	{
	case P_TYPE_MIX:
	{
		// ��������		
		_background = IMAGEMANAGER->findImage("��������");		
		_maxHp = 220;
		_maxMp = 50;
		_maxSp = 1000;


	} break;
	case P_TYPE_HACK:
	{
		// ����		
		_background = IMAGEMANAGER->findImage("������");
		_maxHp = 240;
		_maxMp = 55;
		_maxSp = 900;
		
		
	} break;
	case P_TYPE_STAB:
	{
		// ���				
		_background = IMAGEMANAGER->findImage("�����");
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
		if (!_isPlaySound) SOUNDMANAGER->play("ȿ������ư�浹", _soundEffectVolume);
		_isPlaySound = true;
		_returnBtn->frameX = 1;
	}
	// else if (PtInRect(&_initBtn->rc, _ptMouse))
	// {
	//  if (!_isPlaySound) SOUNDMANAGER->play("ȿ������ư�浹", _soundEffectVolume);
	//  _isPlaySound = true;
	// 	_initBtn->frameX = 1;
	// }
	else if (PtInRect(&_createCharacterBtn->rc, _ptMouse))
	{
		if (!_isPlaySound) SOUNDMANAGER->play("ȿ������ư�浹", _soundEffectVolume);
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
	_returnBtn->btnImage = IMAGEMANAGER->findImage("�ڷι�ư");
	_returnBtn->frameX = _returnBtn->frameY = 0;
	_returnBtn->rc = RectMake(_rc.left + 13, _rc.bottom - 45, _returnBtn->btnImage->getFrameWidth(), _returnBtn->btnImage->getFrameHeight());
	
	// _initBtn = new tagButton;
	// _initBtn.btnImage = IMAGEMANAGER->findImage("�ʱ�ȭ��ư");
	// _initBtn.frameX = _initBtn.frameY = 0;
	// _initBtn.rc = RectMake(_rc.right - 100, _rc.bottom - 20, _initBtn.btnImage->getFrameWidth(), _initBtn.btnImage->getFrameHeight());
	
	_createCharacterBtn = new tagButton;
	_createCharacterBtn->btnImage = IMAGEMANAGER->findImage("ĳ���ͻ�����ư");
	_createCharacterBtn->frameX = _createCharacterBtn->frameY = 0;
	_createCharacterBtn->rc = RectMake(_rc.right - 116, _rc.bottom - 45, _createCharacterBtn->btnImage->getFrameWidth(), _createCharacterBtn->btnImage->getFrameHeight());

	_selectTypeBtn.characterNum = 0;
	_selectTypeBtn.selectTypeBtn[0].btnImage = IMAGEMANAGER->findImage("�������չ�ư");
	_selectTypeBtn.selectTypeBtn[0].frameX = _selectTypeBtn.selectTypeBtn[0].frameY = 0;
	_selectTypeBtn.selectTypeBtn[0].rc = RectMake(_rc.right - 216, _rc.top + 354, _selectTypeBtn.selectTypeBtn[0].btnImage->getFrameWidth(), _selectTypeBtn.selectTypeBtn[0].btnImage->getFrameHeight());
	_selectTypeBtn.selectTypeBtn[1].rc = RectMake(_rc.right - 216, _selectTypeBtn.selectTypeBtn[0].rc.bottom + 3, _selectTypeBtn.selectTypeBtn[0].btnImage->getFrameWidth(), _selectTypeBtn.selectTypeBtn[0].btnImage->getFrameHeight());
	_selectTypeBtn.selectTypeBtn[2].rc = RectMake(_rc.right - 216, _selectTypeBtn.selectTypeBtn[1].rc.bottom + 3, _selectTypeBtn.selectTypeBtn[0].btnImage->getFrameWidth(), _selectTypeBtn.selectTypeBtn[0].btnImage->getFrameHeight());

	// �ð� ����� �̹��� ����.
	_writeNickName = RectMake(_rc.right - 223, _rc.top + 460, 136, 20);
	_checkNickName = RectMake(_rc.right - 80, _rc.top + 458, 58, 24);

	
}

bool create::isOnceClickDown()
{

	// _isWriteNickName = false;
	// setIsWrite(false);

	if (PtInRect(&_returnBtn->rc, _ptMouse))
	{
		SOUNDMANAGER->play("ȿ������ưŬ��", _soundEffectVolume);
		_currentSelectBtn = _returnBtn;
		_currentSelectBtn->frameX = 2;

		return true;
	}
	//else if (PtInRect(&_initBtn->rc, _ptMouse))
	//{
	//		SOUNDMANAGER->play("ȿ������ưŬ��", _soundEffectVolume);
	//	_currentSelectBtn = _initBtn;
	//	_currentSelectBtn->frameX = 2;
	//
	//	return true;
	//}
	else if (PtInRect(&_createCharacterBtn->rc, _ptMouse))
	{
		SOUNDMANAGER->play("ȿ������ưŬ��", _soundEffectVolume);
		_currentSelectBtn = _createCharacterBtn;
		_currentSelectBtn->frameX = 2;

		return true;
	}
	else if (PtInRect(&_selectTypeBtn.selectTypeBtn[0].rc, _ptMouse))
	{
		SOUNDMANAGER->play("ȿ������ưŬ��", _soundEffectVolume);
		_selectTypeBtn.selectTypeBtn[0].frameX = 0;
		_type = P_TYPE_MIX;
		selectType();
		_frameY = 0;
		return true;
	}
	else if (PtInRect(&_selectTypeBtn.selectTypeBtn[1].rc, _ptMouse))
	{
		SOUNDMANAGER->play("ȿ������ưŬ��", _soundEffectVolume);
		_type = P_TYPE_HACK;
		selectType();
		_frameY = 0;
		return true;
	}
	else if (PtInRect(&_selectTypeBtn.selectTypeBtn[2].rc, _ptMouse))
	{
		SOUNDMANAGER->play("ȿ������ưŬ��", _soundEffectVolume);
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
		SOUNDMANAGER->play("ȿ�����޴�âȮ��", _soundEffectVolume);
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
		if (_currentSelectBtn == _returnBtn) SCENEMANAGER->changeScene("����Ʈ��");
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
			SCENEMANAGER->changeScene("����Ʈ��");
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


	// ���� �̸�
	file = CreateFile(_fileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// �г���	
	WriteFile(file, _nickName, sizeof(char) * 128, &write, NULL);
	// ����
	int level = 1;
	WriteFile(file, &level, sizeof(int), &write, NULL);
	// Ÿ��
	WriteFile(file, &_type, sizeof(CHARACTERTYPE), &write, NULL);
	// ����Ÿ��
	for (int i = 0; i < 3; ++i)
	{
		PLAYERATTACKTYPE attackType;

		if ((CHARACTERTYPE)_type == P_TYPE_MIX) attackType = P_ATTACK_VERTICAL_HACK;
		else if ((CHARACTERTYPE)_type == P_TYPE_HACK) attackType = P_ATTACK_HORIZONTAL_HACK;
		else if ((CHARACTERTYPE)_type == P_TYPE_STAB) attackType = P_ATTACK_STAB;
		
		WriteFile(file, &attackType, sizeof(PLAYERATTACKTYPE), &write, NULL);
	}
	// �������ͽ� ( �������� )
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
	// �κ��丮 ũ��
	WriteFile(file, &size, sizeof(int), &write, NULL);
	// �κ��丮
	for (int i = 0; i < size; ++i)
	{
		int item = TYPE_SWORD + 1;
		WriteFile(file, &item, sizeof(int), &write, NULL);
	}

	size = 0;
	// ���â ũ��
	WriteFile(file, &size, sizeof(int), &write, NULL);
	// ���â 
	

	size = 0;
	// ��ųâ ũ��
	WriteFile(file, &size, sizeof(int), &write, NULL);
	// ��ųâ 
	
	// �ʱ��
	MAP initMap = MAP_TUTORIAL01;
	WriteFile(file, &initMap, sizeof(MAP), &write, NULL);
	// ��ǥ ( CX,BY)
	float cx, by;
	cx = (float)(WINSIZEX / 2);
	by = 400.0f;
	WriteFile(file, &cx, sizeof(float), &write, NULL);
	WriteFile(file, &by, sizeof(float), &write, NULL);
	// ��
	int money = 5000;
	WriteFile(file, &money, sizeof(int), &write, NULL);
	// ���� ����ġ��
	int currentExp = 0;
	WriteFile(file, &currentExp, sizeof(int), &write, NULL);
	// ���� ����Ʈ��	
	int point = 0;
	WriteFile(file, &point, sizeof(int), &write, NULL);
	// ���� HP, MP, SP��
	int hp = _maxHp;
	int mp = _maxMp;
	int sp = _maxSp;
	WriteFile(file, &hp, sizeof(int), &write, NULL);
	WriteFile(file, &mp, sizeof(int), &write, NULL);
	WriteFile(file, &sp, sizeof(int), &write, NULL);

	CloseHandle(file);
}
