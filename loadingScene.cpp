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
		SCENEMANAGER->changeScene("�����׹����");
	}

	int a = 0;
}

void loadingScene::render()
{
	_loading->render();
}

void loadingScene::loadingImage()
{
	// ����Ʈ 
	_loading->loadPngFrameImage("Ÿ������Ʈ", "image\\����Ʈ\\Ÿ������Ʈ.png", 508, 123, 4, 1, false, false);
	_loading->loadEffectImage("Ÿ������Ʈ", "Ÿ������Ʈ", 508, 123, 123, 123, 2, 0.1f, 100);

	// �Ϲ� ���ݸ�� ����Ʈ ( �̰�� ��Ÿ�� �÷��̾ ����ϱ⶧���� effect�� ����� ���ߴ�.)
	_loading->loadPngFrameImage("�������Ʈ", "image\\����Ʈ\\���.png", 656, 1592, 4, 8, false, false);
	_loading->loadPngFrameImage("Ⱦ��������Ʈ", "image\\����Ʈ\\Ⱦ����.png", 552, 840, 3, 8, false, false);
	_loading->loadPngFrameImage("����������Ʈ", "image\\����Ʈ\\������.png", 546, 1424, 3, 8, false, false);




	// ������
	_loading->loadImage("�ε�ȭ��", "image\\�ε���\\�ε�ȭ��.png", WINSIZEX, WINSIZEY);
	_loading->loadPngFrameImage("�⺻Ÿ��", "image\\������\\Ÿ��.png", 384, 288, 2, 3, false, false);
	_loading->loadFrameImage("�⺻������Ʈ", "image\\������\\��.bmp", 576, 1410, 3, 5, true, RGB(255, 0, 255));
	_loading->loadPngFrameImage("�⺻������Ʈ2", "image\\������\\������Ʈ2.png", 384, 288, 2, 3, false, false);

	_loading->loadPngFrameImage("���ư����ư", "image\\������\\���ư����ư.png", 190, 33, 2, 1, false, false);
	_loading->loadPngFrameImage("�����ϱ��ư", "image\\������\\�����ϱ��ư.png", 190, 33, 2, 1, false, false);
	_loading->loadPngFrameImage("�ҷ������ư", "image\\������\\�ҷ������ư.png", 190, 33, 2, 1, false, false);
	_loading->loadPngFrameImage("������ư", "image\\������\\������ư.png", 190, 33, 2, 1, false, false);
	_loading->loadPngImage("���찳", "image\\������\\���찳.png", 16, 14, false, false);
	_loading->loadPngImage("����UI", "image\\������\\����UI.png", 252, 552, false, false);
	_loading->loadPngFrameImage("�߰���ư", "image\\������\\�߰���ư.png", 99, 23, 2, 1, false, false);
	_loading->loadPngFrameImage("������ư", "image\\������\\������ư.png", 99, 23, 2, 1, false, false);
	_loading->loadPngFrameImage("Ÿ�Ϲ�ư", "image\\������\\Ÿ�Ϲ�ư2.png", 152, 18, 2, 1, false, false);
	_loading->loadPngFrameImage("������Ʈ��ư", "image\\������\\������Ʈ��ư1.png", 152, 18, 2, 1, false, false);
	_loading->loadPngFrameImage("����Ÿ��", "image\\������\\Ÿ��.png", 384 / 2, 288 / 2, 2, 3, false, false);
	_loading->loadFrameImage("���ÿ�����Ʈ", "image\\������\\��.bmp", 576 / 3, 1410 / 4, 3, 5, true, RGB(255, 0, 255));
	_loading->loadPngFrameImage("���ÿ�����Ʈ2", "image\\������\\������Ʈ2.png", 384 / 2, 288 / 2, 2, 3, false, false);


	// ��Ʈ�ξ�
	_loading->loadPngImage("��Ʈ�ξ����", "image\\��Ʈ�ξ�\\��Ʈ�ξ����.png", WINSIZEX, WINSIZEY, false, false);
	_loading->loadPngFrameImage("�����ư", "image\\��Ʈ�ξ�\\�����ư.png", 318, 31, 3, 1, false, false);
	_loading->loadPngFrameImage("���۹�ư", "image\\��Ʈ�ξ�\\��ŸƮ��ư.png", 435, 41, 3, 1, false, false);
	_loading->loadPngFrameImage("ȯ�漳����ư", "image\\��Ʈ�ξ�\\ȯ�漳����ư.png", 318, 31, 3, 1, false, false);
	_loading->loadPngFrameImage("������ư", "image\\��Ʈ�ξ�\\������ư.png", 288, 27, 3, 1, false, false);
	_loading->loadPngFrameImage("�����׺�����ư", "image\\��Ʈ�ξ�\\�����׹����ư.png", 288, 27, 3, 1, false, false);
	_loading->loadPngImage("��Ʈ�ξ����α׷�����â", "image\\��Ʈ�ξ�\\���α׷�����â.png", 220, 70, false, false);
	_loading->loadPngFrameImage("��Ʈ�ξ����α׷�����â��ҹ�ư", "image\\��Ʈ�ξ�\\no��ư.png", 276, 23, 3, 1, false, false);
	_loading->loadPngFrameImage("��Ʈ�ξ����α׷�����âȮ�ι�ư", "image\\��Ʈ�ξ�\\yes��ư.png", 276, 23, 3, 1, false, false);
	_loading->loadPngImage("��Ʈ�ξ�ȯ�漳��", "image\\��Ʈ�ξ�\\ȯ�漳��.png", 346, 345, false, false);
	_loading->loadPngFrameImage("��Ʈ�ξ�ȯ�漳��Ŭ��", "image\\��Ʈ�ξ�\\ȯ�漳��Ŭ��.png", 30, 15, 2, 1, false, false);


	// ����Ʈ��
	_loading->loadPngImage("����Ʈ�����", "image\\����Ʈ��\\����Ʈ�����.png", WINSIZEX, WINSIZEY, false, false);
	_loading->loadPngImage("��þȾ�", "image\\����Ʈ��\\��þȾ�.png", 85, 100, false, false);
	_loading->loadPngFrameImage("�ڷι�ư", "image\\����Ʈ��\\�ڷι�ư.png", 318, 31, 3, 1, false, false);
	_loading->loadPngFrameImage("���۹�ư", "image\\����Ʈ��\\��ŸƮ��ư.png", 435, 41, 3, 1, false, false);
	_loading->loadPngFrameImage("ĳ���ͻ�����ư", "image\\����Ʈ��\\ĳ���ͻ�����ư.png", 318, 31, 3, 1, false, false);
	_loading->loadPngFrameImage("ĳ���ͻ�����ư", "image\\����Ʈ��\\ĳ���ͻ�����ư.png", 318, 31, 3, 1, false, false);
	_loading->loadPngFrameImage("ĳ���ͼ���", "image\\����Ʈ��\\ĳ���ͼ���.png", 2412, 51, 18, 1, false, false);

	// ũ������Ʈ��
	_loading->loadPngFrameImage("�������չ�ư", "image\\ũ������Ʈ��\\�������չ�ư.png", 332, 28, 2, 1, false, false);
	// �̹��� ũ�Ⱑ �ʹ�Ŀ�� BMP�� ����
	_loading->loadFrameImage("��������", "image\\ũ������Ʈ��\\��������.bmp", 1024, 47616, 1, 62, false, false);
	_loading->loadFrameImage("������", "image\\ũ������Ʈ��\\������.bmp", 1024, 26112, 1, 34, false, false);
	_loading->loadFrameImage("�����", "image\\ũ������Ʈ��\\�����.bmp", 1024, 49152, 1, 64, false, false);

	// ���Ӿ�
	// ĳ���� ����â
	_loading->loadPngFrameImage("���Ӿ�up��ư", "image\\���Ӿ�\\UI�Ŵ���\\ĳ���ͻ���â\\up��ư.png", 33, 11, 3, 1, false, false);
	_loading->loadPngFrameImage("ĳ���ͽ���â", "image\\���Ӿ�\\UI�Ŵ���\\ĳ���ͻ���â\\ĳ���ͻ���â.png", 736, 346, 2, 1, false, false);
	
	// UI�Ŵ���
	_loading->loadPngImage("�޺�â��ư", "image\\���Ӿ�\\UI�Ŵ���\\�޺�â��ư.png", 30, 29, false, false);
	_loading->loadPngImage("�޺�â", "image\\���Ӿ�\\UI�Ŵ���\\�޺�â\\�޺�â.png", 280, 160, false, false);
	_loading->loadPngImage("�޺���ų����", "image\\���Ӿ�\\UI�Ŵ���\\�޺�â\\�޺���ų����.png", 98, 30, false, false);


	// ��������â
	_loading->loadPngImage("��������â", "image\\���Ӿ�\\UI�Ŵ���\\��������â\\��������â.png", 178, 101, false, false);
	_loading->loadPngImage("��������âHP��", "image\\���Ӿ�\\UI�Ŵ���\\��������â\\Hp��.png", 80, 12, false, false);
	_loading->loadPngImage("��������âMP��", "image\\���Ӿ�\\UI�Ŵ���\\��������â\\Mp��.png", 80, 12, false, false);
	_loading->loadPngImage("��������âSP��", "image\\���Ӿ�\\UI�Ŵ���\\��������â\\Sp��.png", 80, 12, false, false);
	_loading->loadPngImage("��������â����ġ��", "image\\���Ӿ�\\UI�Ŵ���\\��������â\\����ġ��.png", 107, 4, false, false);
	_loading->loadPngImage("��������â�޺�â", "image\\���Ӿ�\\UI�Ŵ���\\��������â\\��������â�޺�â.png", 116, 26, false, false);
	_loading->loadPngImage("���ʹ̻�������â", "image\\���Ӿ�\\UI�Ŵ���\\��������â\\���ʹ̻�������â.png", 233, 71, false, false);
	_loading->loadPngImage("���ʹ̻�������âHP��", "image\\���Ӿ�\\UI�Ŵ���\\��������â\\���ʹ̻�������âhp��.png", 163, 16, false, false);

	// ��ų�Ŵ���
	_loading->loadPngImage("��⽺ų������", "image\\���Ӿ�\\��ų�Ŵ���\\���.png", 24, 24, false, false);
	_loading->loadPngImage("�����⽺ų������", "image\\���Ӿ�\\��ų�Ŵ���\\������.png", 24, 24, false, false);
	_loading->loadPngImage("Ⱦ���⽺ų������", "image\\���Ӿ�\\��ų�Ŵ���\\Ⱦ����.png", 24, 24, false, false);


	// �÷��̾�
	_loading->loadPngFrameImage("��þ�_IDLE", "image\\���Ӿ�\\player\\idle.png", 660, 728, 12, 8, false, false);
	_loading->loadPngFrameImage("��þ�_RUN", "image\\���Ӿ�\\player\\run.png", 530, 640, 10, 8, false, false);
	_loading->loadPngFrameImage("��þ�_ATTACK_STAB", "image\\���Ӿ�\\player\\���.png", 256, 792, 4, 8, false, false);
	_loading->loadPngFrameImage("��þ�_ATTACK_VERTICAL_HACK", "image\\���Ӿ�\\player\\������.png", 438, 752, 6, 8, false, false);
	_loading->loadPngFrameImage("��þ�_ATTACK_HORIZONTAL_HACK", "image\\���Ӿ�\\player\\Ⱦ����.png", 350, 744, 5, 8, false, false);





	// ������ �Ŵ��� ������
	_loading->loadPngImage("�������", "image\\���Ӿ�\\�����۸Ŵ���\\������\\�������.png", 24, 20, false, false);
	_loading->loadPngImage("����÷�", "image\\���Ӿ�\\�����۸Ŵ���\\������\\����÷�.png", 16, 19, false, false);
	_loading->loadPngImage("�׸����", "image\\���Ӿ�\\�����۸Ŵ���\\������\\�׸����.png", 24, 20, false, false);
	_loading->loadPngImage("Ű���÷�", "image\\���Ӿ�\\�����۸Ŵ���\\������\\Ű���÷�.png", 16, 19, false, false);
	_loading->loadPngImage("���¹̳����Ǽ�", "image\\���Ӿ�\\�����۸Ŵ���\\������\\���¹̳����Ǽ�.png", 15, 20, false, false);
	_loading->loadPngImage("�����Ǹ���", "image\\���Ӿ�\\�����۸Ŵ���\\������\\0.�����Ǹ���.png", 22, 23, false, false);
	_loading->loadPngImage("������", "image\\���Ӿ�\\�����۸Ŵ���\\������\\1.������.png", 22, 23, false, false);
	_loading->loadPngImage("�ϵ巹���Ƹ�", "image\\���Ӿ�\\�����۸Ŵ���\\������\\2.�ϵ巹���Ƹ�.png", 20, 23, false, false);
	_loading->loadPngImage("���ð�", "image\\���Ӿ�\\�����۸Ŵ���\\������\\3.���ð�.png", 24, 24, false, false);
	_loading->loadPngImage("Ÿ��", "image\\���Ӿ�\\�����۸Ŵ���\\������\\4.Ÿ��.png", 26, 24, false, false);
	_loading->loadPngImage("��Ŭ��", "image\\���Ӿ�\\�����۸Ŵ���\\������\\5.��Ŭ��.png", 24, 24, false, false);
	_loading->loadPngImage("��ӹ��", "image\\���Ӿ�\\�����۸Ŵ���\\������\\6.��ӹ��.png", 18, 21, false, false);
	_loading->loadPngImage("��������������", "image\\���Ӿ�\\�����۸Ŵ���\\������\\7.��������������.png", 22, 21, false, false);
	_loading->loadPngImage("�����������ڷ�", "image\\���Ӿ�\\�����۸Ŵ���\\������\\8.�����������ڷ�.png", 22, 22, false, false);
	_loading->loadPngImage("���尩", "image\\���Ӿ�\\�����۸Ŵ���\\������\\9.���尩.png", 17, 19, false, false);
	_loading->loadPngImage("����", "image\\���Ӿ�\\�����۸Ŵ���\\������\\10.����.png", 18, 13, false, false);

	// ������ �Ŵ��� �ΰ���
	_loading->loadPngFrameImage("��Ŭ������", "image\\���Ӿ�\\�����۸Ŵ���\\������\\���\\��Ŭ��.png", 660, 728, 12, 8, false, false);
	_loading->loadPngFrameImage("���ð�����", "image\\���Ӿ�\\�����۸Ŵ���\\������\\���\\���ð�_IDLE.png", 1860, 728, 12, 8, false, false);
	_loading->loadPngFrameImage("���ð�����_ATTACK_STAB", "image\\���Ӿ�\\�����۸Ŵ���\\������\\���\\���ð�_���.png", 656, 1592, 4, 8, false, false);
	_loading->loadPngFrameImage("���ð�����_ATTACK_VERTICAL_HACK", "image\\���Ӿ�\\�����۸Ŵ���\\������\\���\\���ð�_������.png", 1038, 1552, 6, 8, false, false);
	_loading->loadPngFrameImage("���ð�����_ATTACK_HORIZONTAL_HACK", "image\\���Ӿ�\\�����۸Ŵ���\\������\\���\\���ð�_Ⱦ����.png", 850, 904, 5, 8, false, false);


}

void loadingScene::loadingSound()
{
	// mp3
	_loading->loadSound("��Ʈ�ξ�", "sound\\00.mp3", true, true);
	_loading->loadSound("����Ʈ��", "sound\\01.mp3", true, true);
	_loading->loadSound("����_��", "sound\\02.mp3", true, true);
	_loading->loadSound("����_��", "sound\\03.mp3", true, true);
	_loading->loadSound("�ʵ�_��", "sound\\04.mp3", true, true);
	_loading->loadSound("�ʵ�_��", "sound\\05.mp3", true, true);
	
	// wav ����
	_loading->loadSound("ȿ������ư�浹", "sound\\ȿ����\\��ư�浹.wav", false, false);
	_loading->loadSound("ȿ������ưŬ��", "sound\\ȿ����\\��ưŬ��.wav", false, false);
	_loading->loadSound("ȿ������ŸƮ��ưŬ��", "sound\\ȿ����\\��ŸƮ��ưŬ��.wav", false, false);
	_loading->loadSound("ȿ�����޴�â���", "sound\\ȿ����\\�޴�â���.wav", false, false);
	_loading->loadSound("ȿ�����޴�âȮ��", "sound\\ȿ����\\�޴�âȮ��.wav", false, false);
	_loading->loadSound("ȿ��������â���Ǳ���", "sound\\ȿ����\\����â���Ǳ���.wav", false, false);

	
}
