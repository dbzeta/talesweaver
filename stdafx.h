#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <tchar.h>
#include <commdlg.h>					// 파일 불러오기 할수 있지

#include "randomFunction.h"
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "effectManager.h"
#include "soundManager.h"
#include "sceneManager.h"
#include "keyAniManager.h"
#include "timeManager.h"
#include "txtData.h"
#include "database.h"
#include "utils.h"

#include "drawManager.h"

using namespace std;
using namespace BLUE_UTIL;

//====================================
// - 2017. 02. 28 ## 디파인문 ##
//====================================

#define WINNAME (LPTSTR)(TEXT("SGA TalesWeaver"))
#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX 1024
#define WINSIZEY 768
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define KEYANIMANAGER keyAniManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define DATABASE database::getSingleton()

#define DRAWMANAGER drawManager::getSingleton()

//======================================
// - 2017. 02. 28 ## 매크로 함수 ##
//======================================

#define SAFE_DELETE(p)			{if(p) { delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) { delete[](p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) { (p)->Release(); (p) = NULL;}}

//========================================
// - 2017. 02. 28 ## 전역 변수 ##
//========================================

extern HWND _hWnd;
extern HINSTANCE _hInstance;

extern POINT _ptMouse;

extern BOOL _leftButtonDown;
extern BOOL _rightButtonDown;

extern BOOL _debug;						// 디버깅 확인용 변수
extern RECT _focus;						// 포커스 좌표만 사용할 것이므로 좌표로 빼준다.

extern BOOL _isUseBgm;					// 배경음 끄고 킬수 있는 bool값	
extern BOOL _isUseSoundEffect;			// 효과음 끄고 킬수 있는 bool값
extern float _bgmVolume;				// 배경음 볼륨값
extern float _soundEffectVolume;		// 효과음 볼륨값
extern float _tempBgmVolume;			// 배경음을 꺼놓았을 때 그 값을 들고있을 임시 배경음 변수
extern float _tempSoundEffectVolume;	// 배경음을 꺼놓았을 때 그 값을 들고있을 임시 효과음 변수

extern string _currentBgm;				// 현재 bgm 키네임
extern string _currentCharacter;		// 현재 선택된 캐릭터