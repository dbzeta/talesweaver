#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_loading = new loading;
	_loading->init();

	_isPlay = _isStop = false;

	loadingSound();
	loadingImage();


	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	_loading->update();

	if (_loading->loadingDone())
	{
		SCENEMANAGER->changeScene("오프닝무비씬");
	}

	int a = 0;
}

void loadingScene::render()
{
	_loading->render();
}

void loadingScene::loadingImage()
{
	// 이펙트 
	_loading->loadPngFrameImage("타격이펙트", "image\\이펙트\\타격이펙트.png", 508, 123, 4, 1, false, false);
	_loading->loadEffectImage("타격이펙트", "타격이펙트", 508, 123, 123, 123, 2, 0.1f, 100);

	// 일반 공격모션 이펙트 ( 이경우 평타는 플레이어만 사용하기때문에 effect로 등록은 안했다.)
	_loading->loadPngFrameImage("찌르기이펙트", "image\\이펙트\\찌르기.png", 656, 1592, 4, 8, false, false);
	_loading->loadPngFrameImage("횡베기이펙트", "image\\이펙트\\횡베기.png", 552, 840, 3, 8, false, false);
	_loading->loadPngFrameImage("종베기이펙트", "image\\이펙트\\종베기.png", 546, 1424, 3, 8, false, false);




	// 맵툴씬
	_loading->loadImage("로딩화면", "image\\로딩씬\\로딩화면.png", WINSIZEX, WINSIZEY);
	_loading->loadPngFrameImage("기본타일", "image\\맵툴씬\\타일.png", 384, 288, 2, 3, false, false);
	_loading->loadFrameImage("기본오브젝트", "image\\맵툴씬\\벽.bmp", 576, 1410, 3, 5, true, RGB(255, 0, 255));
	_loading->loadPngFrameImage("기본오브젝트2", "image\\맵툴씬\\오브젝트2.png", 384, 288, 2, 3, false, false);

	_loading->loadPngFrameImage("돌아가기버튼", "image\\맵툴씬\\돌아가기버튼.png", 190, 33, 2, 1, false, false);
	_loading->loadPngFrameImage("저장하기버튼", "image\\맵툴씬\\저장하기버튼.png", 190, 33, 2, 1, false, false);
	_loading->loadPngFrameImage("불러오기버튼", "image\\맵툴씬\\불러오기버튼.png", 190, 33, 2, 1, false, false);
	_loading->loadPngFrameImage("지우기버튼", "image\\맵툴씬\\지우기버튼.png", 190, 33, 2, 1, false, false);
	_loading->loadPngImage("지우개", "image\\맵툴씬\\지우개.png", 16, 14, false, false);
	_loading->loadPngImage("맵툴UI", "image\\맵툴씬\\맵툴UI.png", 252, 552, false, false);
	_loading->loadPngFrameImage("추가버튼", "image\\맵툴씬\\추가버튼.png", 99, 23, 2, 1, false, false);
	_loading->loadPngFrameImage("삭제버튼", "image\\맵툴씬\\삭제버튼.png", 99, 23, 2, 1, false, false);
	_loading->loadPngFrameImage("타일버튼", "image\\맵툴씬\\타일버튼2.png", 152, 18, 2, 1, false, false);
	_loading->loadPngFrameImage("오브젝트버튼", "image\\맵툴씬\\오브젝트버튼1.png", 152, 18, 2, 1, false, false);
	_loading->loadPngFrameImage("샘플타일", "image\\맵툴씬\\타일.png", 384 / 2, 288 / 2, 2, 3, false, false);
	_loading->loadFrameImage("샘플오브젝트", "image\\맵툴씬\\벽.bmp", 576 / 3, 1410 / 4, 3, 5, true, RGB(255, 0, 255));
	_loading->loadPngFrameImage("샘플오브젝트2", "image\\맵툴씬\\오브젝트2.png", 384 / 2, 288 / 2, 2, 3, false, false);


	// 인트로씬
	_loading->loadPngImage("인트로씬배경", "image\\인트로씬\\인트로씬배경.png", WINSIZEX, WINSIZEY, false, false);
	_loading->loadPngFrameImage("종료버튼", "image\\인트로씬\\종료버튼.png", 318, 31, 3, 1, false, false);
	_loading->loadPngFrameImage("시작버튼", "image\\인트로씬\\스타트버튼.png", 435, 41, 3, 1, false, false);
	_loading->loadPngFrameImage("환경설정버튼", "image\\인트로씬\\환경설정버튼.png", 318, 31, 3, 1, false, false);
	_loading->loadPngFrameImage("맵툴버튼", "image\\인트로씬\\맵툴버튼.png", 288, 27, 3, 1, false, false);
	_loading->loadPngFrameImage("오프닝비디오버튼", "image\\인트로씬\\오프닝무비버튼.png", 288, 27, 3, 1, false, false);
	_loading->loadPngImage("인트로씬프로그램종료창", "image\\인트로씬\\프로그램종료창.png", 220, 70, false, false);
	_loading->loadPngFrameImage("인트로씬프로그램종료창취소버튼", "image\\인트로씬\\no버튼.png", 276, 23, 3, 1, false, false);
	_loading->loadPngFrameImage("인트로씬프로그램종료창확인버튼", "image\\인트로씬\\yes버튼.png", 276, 23, 3, 1, false, false);
	_loading->loadPngImage("인트로씬환경설정", "image\\인트로씬\\환경설정.png", 346, 345, false, false);
	_loading->loadPngFrameImage("인트로씬환경설정클릭", "image\\인트로씬\\환경설정클릭.png", 30, 15, 2, 1, false, false);


	// 셀렉트씬
	_loading->loadPngImage("셀렉트씬배경", "image\\셀렉트씬\\셀렉트씬배경.png", WINSIZEX, WINSIZEY, false, false);
	_loading->loadPngImage("루시안얼굴", "image\\셀렉트씬\\루시안얼굴.png", 85, 100, false, false);
	_loading->loadPngFrameImage("뒤로버튼", "image\\셀렉트씬\\뒤로버튼.png", 318, 31, 3, 1, false, false);
	_loading->loadPngFrameImage("시작버튼", "image\\셀렉트씬\\스타트버튼.png", 435, 41, 3, 1, false, false);
	_loading->loadPngFrameImage("캐릭터생성버튼", "image\\셀렉트씬\\캐릭터생성버튼.png", 318, 31, 3, 1, false, false);
	_loading->loadPngFrameImage("캐릭터삭제버튼", "image\\셀렉트씬\\캐릭터삭제버튼.png", 318, 31, 3, 1, false, false);
	_loading->loadPngFrameImage("캐릭터선택", "image\\셀렉트씬\\캐릭터선택.png", 2412, 51, 18, 1, false, false);

	// 크리에이트씬
	_loading->loadPngFrameImage("물리복합버튼", "image\\크리에이트씬\\물리복합버튼.png", 332, 28, 2, 1, false, false);
	// 이미지 크기가 너무커서 BMP로 수정
	_loading->loadFrameImage("물리복합", "image\\크리에이트씬\\물리복합.bmp", 1024, 47616, 1, 62, false, false);
	_loading->loadFrameImage("베기형", "image\\크리에이트씬\\베기형.bmp", 1024, 26112, 1, 34, false, false);
	_loading->loadFrameImage("찌르기형", "image\\크리에이트씬\\찌르기형.bmp", 1024, 49152, 1, 64, false, false);

	// 게임씬
	// 캐릭터 상태창
	_loading->loadPngFrameImage("게임씬up버튼", "image\\게임씬\\UI매니저\\캐릭터상태창\\up버튼.png", 33, 11, 3, 1, false, false);
	_loading->loadPngFrameImage("캐릭터스탯창", "image\\게임씬\\UI매니저\\캐릭터상태창\\캐릭터상태창.png", 736, 346, 2, 1, false, false);
	
	// UI매니저
	_loading->loadPngImage("콤보창버튼", "image\\게임씬\\UI매니저\\콤보창버튼.png", 30, 29, false, false);
	_loading->loadPngImage("콤보창", "image\\게임씬\\UI매니저\\콤보창\\콤보창.png", 280, 160, false, false);
	_loading->loadPngImage("콤보스킬선택", "image\\게임씬\\UI매니저\\콤보창\\콤보스킬선택.png", 98, 30, false, false);


	// 상태정보창
	_loading->loadPngImage("상태정보창", "image\\게임씬\\UI매니저\\상태정보창\\상태정보창.png", 178, 101, false, false);
	_loading->loadPngImage("상태정보창HP바", "image\\게임씬\\UI매니저\\상태정보창\\Hp바.png", 80, 12, false, false);
	_loading->loadPngImage("상태정보창MP바", "image\\게임씬\\UI매니저\\상태정보창\\Mp바.png", 80, 12, false, false);
	_loading->loadPngImage("상태정보창SP바", "image\\게임씬\\UI매니저\\상태정보창\\Sp바.png", 80, 12, false, false);
	_loading->loadPngImage("상태정보창경험치바", "image\\게임씬\\UI매니저\\상태정보창\\경험치바.png", 107, 4, false, false);
	_loading->loadPngImage("상태정보창콤보창", "image\\게임씬\\UI매니저\\상태정보창\\상태정보창콤보창.png", 116, 26, false, false);
	_loading->loadPngImage("에너미상태정보창", "image\\게임씬\\UI매니저\\상태정보창\\에너미상태정보창.png", 233, 71, false, false);
	_loading->loadPngImage("에너미상태정보창HP바", "image\\게임씬\\UI매니저\\상태정보창\\에너미상태정보창hp바.png", 163, 16, false, false);

	// 스킬매니저
	_loading->loadPngImage("찌르기스킬아이콘", "image\\게임씬\\스킬매니저\\찌르기.png", 24, 24, false, false);
	_loading->loadPngImage("종베기스킬아이콘", "image\\게임씬\\스킬매니저\\종베기.png", 24, 24, false, false);
	_loading->loadPngImage("횡베기스킬아이콘", "image\\게임씬\\스킬매니저\\횡베기.png", 24, 24, false, false);


	// 플레이어
	_loading->loadPngFrameImage("루시안_IDLE", "image\\게임씬\\player\\idle.png", 660, 728, 12, 8, false, false);
	_loading->loadPngFrameImage("루시안_RUN", "image\\게임씬\\player\\run.png", 530, 640, 10, 8, false, false);
	_loading->loadPngFrameImage("루시안_ATTACK_STAB", "image\\게임씬\\player\\찌르기.png", 256, 792, 4, 8, false, false);
	_loading->loadPngFrameImage("루시안_ATTACK_VERTICAL_HACK", "image\\게임씬\\player\\종베기.png", 438, 752, 6, 8, false, false);
	_loading->loadPngFrameImage("루시안_ATTACK_HORIZONTAL_HACK", "image\\게임씬\\player\\횡베기.png", 350, 744, 5, 8, false, false);





	// 아이템 매니저 아이콘
	_loading->loadPngImage("레드허브", "image\\게임씬\\아이템매니저\\아이콘\\레드허브.png", 24, 20, false, false);
	_loading->loadPngImage("딸기시럽", "image\\게임씬\\아이템매니저\\아이콘\\딸기시럽.png", 16, 19, false, false);
	_loading->loadPngImage("그린허브", "image\\게임씬\\아이템매니저\\아이콘\\그린허브.png", 24, 20, false, false);
	_loading->loadPngImage("키위시럽", "image\\게임씬\\아이템매니저\\아이콘\\키위시럽.png", 16, 19, false, false);
	_loading->loadPngImage("스태미너포션소", "image\\게임씬\\아이템매니저\\아이콘\\스태미너포션소.png", 15, 20, false, false);
	_loading->loadPngImage("마인의모자", "image\\게임씬\\아이템매니저\\아이콘\\0.마인의모자.png", 22, 23, false, false);
	_loading->loadPngImage("본메일", "image\\게임씬\\아이템매니저\\아이콘\\1.본메일.png", 22, 23, false, false);
	_loading->loadPngImage("하드레더아머", "image\\게임씬\\아이템매니저\\아이콘\\2.하드레더아머.png", 20, 23, false, false);
	_loading->loadPngImage("수련검", "image\\게임씬\\아이템매니저\\아이콘\\3.수련검.png", 24, 24, false, false);
	_loading->loadPngImage("타도", "image\\게임씬\\아이템매니저\\아이콘\\4.타도.png", 26, 24, false, false);
	_loading->loadPngImage("버클러", "image\\게임씬\\아이템매니저\\아이콘\\5.버클러.png", 24, 24, false, false);
	_loading->loadPngImage("고속밴드", "image\\게임씬\\아이템매니저\\아이콘\\6.고속밴드.png", 18, 21, false, false);
	_loading->loadPngImage("수습마법사목걸이", "image\\게임씬\\아이템매니저\\아이콘\\7.수습마법사목걸이.png", 22, 21, false, false);
	_loading->loadPngImage("나무마법빗자루", "image\\게임씬\\아이템매니저\\아이콘\\8.나무마법빗자루.png", 22, 22, false, false);
	_loading->loadPngImage("면장갑", "image\\게임씬\\아이템매니저\\아이콘\\9.면장갑.png", 17, 19, false, false);
	_loading->loadPngImage("샌들", "image\\게임씬\\아이템매니저\\아이콘\\10.샌들.png", 18, 13, false, false);

	// 아이템 매니저 인게임
	_loading->loadPngFrameImage("버클러장착", "image\\게임씬\\아이템매니저\\아이템\\장비\\버클러.png", 660, 728, 12, 8, false, false);
	_loading->loadPngFrameImage("수련검장착", "image\\게임씬\\아이템매니저\\아이템\\장비\\수련검_IDLE.png", 1860, 728, 12, 8, false, false);
	_loading->loadPngFrameImage("수련검장착_ATTACK_STAB", "image\\게임씬\\아이템매니저\\아이템\\장비\\수련검_찌르기.png", 656, 1592, 4, 8, false, false);
	_loading->loadPngFrameImage("수련검장착_ATTACK_VERTICAL_HACK", "image\\게임씬\\아이템매니저\\아이템\\장비\\수련검_종베기.png", 1038, 1552, 6, 8, false, false);
	_loading->loadPngFrameImage("수련검장착_ATTACK_HORIZONTAL_HACK", "image\\게임씬\\아이템매니저\\아이템\\장비\\수련검_횡베기.png", 850, 904, 5, 8, false, false);


}

void loadingScene::loadingSound()
{
	// mp3
	_loading->loadSound("인트로씬", "sound\\00.mp3", true, true);
	_loading->loadSound("셀렉트씬", "sound\\01.mp3", true, true);
	_loading->loadSound("마을_낮", "sound\\02.mp3", true, true);
	_loading->loadSound("마을_밤", "sound\\03.mp3", true, true);
	_loading->loadSound("필드_낮", "sound\\04.mp3", true, true);
	_loading->loadSound("필드_밤", "sound\\05.mp3", true, true);
	
	// wav 파일
	_loading->loadSound("효과음버튼충돌", "sound\\효과음\\버튼충돌.wav", false, false);
	_loading->loadSound("효과음버튼클릭", "sound\\효과음\\버튼클릭.wav", false, false);
	_loading->loadSound("효과음스타트버튼클릭", "sound\\효과음\\스타트버튼클릭.wav", false, false);
	_loading->loadSound("효과음메뉴창취소", "sound\\효과음\\메뉴창취소.wav", false, false);
	_loading->loadSound("효과음메뉴창확인", "sound\\효과음\\메뉴창확인.wav", false, false);
	_loading->loadSound("효과음상점창물건구입", "sound\\효과음\\상점창물건구입.wav", false, false);

	
}
