#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	

	// setItem();
	
	load();
	
	return S_OK;
}

void itemManager::release()
{

}

void itemManager::update() 
{
	//if (KEYMANAGER->isOnceKeyDown(VK_F12))
	//{
	//	save();
	//}
	
	//if (KEYMANAGER->isOnceKeyDown(VK_F12))
	//{
	//	load();
	//}

}

void itemManager::render() 
{
	for (int i = 0; i < _vItemList.size(); ++i)
	{
		// _vItemList[i]->getItemImage()->render(getMemDC(), 100 + i * 50, 100);
	}
}

void itemManager::setItem()
{
	// �޾ƿ;��ϴ� ������ ������ imageName 
	
	// �������
	item* _item0 = new item;
	_item0->init();
	_item0->makeConsumptionItem("�������", "�������", TYPE_HP + 1, 0, 30, 0, 0, 100, false);
	_vItemList.push_back(_item0);

	// ����÷�
	item* _item1 = new item;	
	_item1->init();
	_item1->makeConsumptionItem("����÷�", "����÷�", TYPE_HP + 2, 0, 60, 0, 0, 200, false);
	_vItemList.push_back(_item1);

	// �׸����
	item* _item2 = new item;
	_item2->init();	
	_item2->makeConsumptionItem("�׸����", "�׸����", TYPE_MP + 1, 0, 0, 10, 0, 100, false);
	_vItemList.push_back(_item2);

	// Ű���÷�
	item* _item3 = new item;
	_item3->init();	
	_item3->makeConsumptionItem("Ű���÷�", "Ű���÷�", TYPE_MP + 2, 0, 0, 20, 0, 200, false);
	_vItemList.push_back(_item3);

	// ���׹̳����� ��
	item* _item4 = new item;
	_item4->init();
	_item4->makeConsumptionItem("���¹̳����Ǽ�", "���¹̳����Ǽ�", TYPE_SP + 1, 0, 0, 0, 250, 150, false);
	_vItemList.push_back(_item4);
	
	// ������ ���� �ΰ�(�̺�Ʈ)		1 1 1 2 2 0 0	
	item* _item5 = new item;
	_item5->init();
	_item5->makeEquipmentItem("�����Ǻ����ΰ�����","�����Ǹ���", "�����Ǹ���", TYPE_HAT + 1, 0, 1, 1, 1, 2, 2, 0, 0, 0, true);
	_vItemList.push_back(_item5);
	
	// ������						0 0 0 13 0 1 0
	item* _item6 = new item;
	_item6->init();
	_item6->makeEquipmentItem("������", "������", TYPE_MAIL + 1, 0, 0, 0, 0, 13, 0, 1, 0, 2000, false);
	_vItemList.push_back(_item6);

	// �ϵ巹�� �Ƹ�				0 0 0 8 4 0 2
	item* _item7 = new item;
	_item7->init();
	_item7->makeEquipmentItem("�ϵ巹���Ƹ�", "�ϵ巹���Ƹ�", TYPE_LIGHTARMOR + 1, 0, 0, 0, 0, 8, 4, 0, 2, 3000, false);
	_vItemList.push_back(_item7);

	// ���ð�						9 8 0 1 0 1 0
	item* _item8 = new item;
	_item8->init();
	_item8->makeEquipmentItem("���ð�����", "���ð�", "���ð�", TYPE_SWORD + 1, 0, 9, 8, 0, 1, 0, 1, 0, 1500, false);
	_vItemList.push_back(_item8);

	// Ÿ��							7 15 3 0 0 2 3
	item* _item9 = new item;
	_item9->init();
	_item9->makeEquipmentItem("Ÿ������", "Ÿ��", "Ÿ��", TYPE_KNIFE + 1, 0, 7, 15, 3, 0, 0, 2, 3, 1500, false);
	_vItemList.push_back(_item9);

	// ��Ŭ��						0 0 0 3 0 0 0
	item* _item10 = new item;
	_item10->init();
	_item10->makeEquipmentItem("��Ŭ������", "��Ŭ��", "��Ŭ��", TYPE_SHIELD + 1, 0, 0, 0, 0, 3, 0, 0, 0, 1600, false);
	_vItemList.push_back(_item10);

	// ��ӹ��						4 4 4 0 0 1 0
	item* _item11 = new item;
	_item11->init();
	_item11->makeEquipmentItem("��ӹ��", "��ӹ��", TYPE_BAND + 1, 0, 4, 4, 4, 0, 0, 1, 0, 2200, false);
	_vItemList.push_back(_item11);

	// ���� �������� �����			0 0 0 3 2 0 2
	item* _item12 = new item;
	_item12->init();
	_item12->makeEquipmentItem("��������������", "�����������Ǹ����", TYPE_NECKLACE + 1, 0, 0, 0, 0, 3, 2, 0, 2, 900, false);
	_vItemList.push_back(_item12);

	// ���� ���ڷ�					0 0 0 2 2 1 0
	item* _item13 = new item;
	_item13->init();
	_item13->makeEquipmentItem("�����������ڷ�����", "�����������ڷ�", "�����������ڷ�", TYPE_BROOM + 1, 0, 0, 0, 0, 2, 2, 1, 0, 900, false);
	_vItemList.push_back(_item13);

	// ���尩						1 1 1 0 1 0 1
	item* _item14 = new item;
	_item14->init();
	_item14->makeEquipmentItem("���尩", "���尩", TYPE_GLOVE + 1, 0, 1, 1, 1, 0, 1, 0, 1, 1000, false);
	_vItemList.push_back(_item14);

	// ����							0 0 0 0 0 1 2
	item* _item15 = new item;
	_item15->init();
	_item15->makeEquipmentItem("����", "����", TYPE_SHOES + 1, 0, 0, 0, 0, 0, 0, 1, 2, 1000, false);
	_vItemList.push_back(_item15);


	// �⺻ ���� ǰ
	// 103101 ���ð� 
	// 107101 ���尩
	// 104101 ��Ŭ�� 
	// 108101 ���� 

	// �Ǹ�ǰ	
	// 102101 ������
	// 102201 �ϵ巹�� �Ƹ�
	// 103201 Ÿ��
	// 104201 ��ӹ��
	// 105101 ���� �������� �����
	// 106101 ���� ���� ���ڷ�

	// �̺�Ʈ ������
	// 101101 ������ ���� �ΰ� ( �̺�Ʈ )

}

void itemManager::load()
{
	HANDLE file;
	DWORD read;

	while (_vItemList.size() > 0)
	{
		// �ҷ����� �� �ҷ����� ������ �����µ� ������ ����??
		SAFE_DELETE(_vItemList[0]);
		_vItemList.erase(_vItemList.begin());
	}

	int vectorSize;

	file = CreateFile("itemdata.txt", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &vectorSize, sizeof(int), &read, NULL);

	for (int k = 0; k < vectorSize; ++k)
	{
		item* _item = new item;
		ReadFile(file, _item, sizeof(item), &read, NULL);
		_vItemList.push_back(_item);

	}

	CloseHandle(file);
}

void itemManager::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("itemdata.txt", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int size = _vItemList.size();

	WriteFile(file, &size, sizeof(int), &write, NULL);

	for (int i = 0; i < _vItemList.size(); ++i)
	{
		WriteFile(file, _vItemList[i], sizeof(item), &write, NULL);
	}

	CloseHandle(file);
}

item* itemManager::getItem(int itemNum)
{
	item* _item = new item;

	for (int i = 0; i < _vItemList.size(); ++i)
	{
		if (_vItemList[i]->getItemNum() == itemNum)
		{
			return _vItemList[i];
		}
	}

	return nullptr;
}

item * itemManager::makeItem(int itemNum)
{
	item* _item = new item;

	for (int i = 0; i < _vItemList.size(); ++i)
	{
		if (_vItemList[i]->getItemNum() == itemNum)
		{
			// ���
			if (itemNum / TYPE_EQUIPMENT == 1)
			{
				_item->makeEquipmentItem(
					_vItemList[i]->getUseImageName(),
					_vItemList[i]->getIconImageName(),
					_vItemList[i]->getItemName(),
					_vItemList[i]->getItemNum(),
					_vItemList[i]->getEquipItem()._requireLevel,
					_vItemList[i]->getEquipItem()._stab,
					_vItemList[i]->getEquipItem()._hack,
					_vItemList[i]->getEquipItem()._int,
					_vItemList[i]->getEquipItem()._def,
					_vItemList[i]->getEquipItem()._mr,
					_vItemList[i]->getEquipItem()._dex,
					_vItemList[i]->getEquipItem()._agi,
					_vItemList[i]->getCost(),
					_vItemList[i]->getEquipItem()._isEventItem
				);
			}
			// �Ҹ�
			else if (itemNum / TYPE_EQUIPMENT == 2)
			{
				_item->makeConsumptionItem(
					_vItemList[i]->getUseImageName(),
					_vItemList[i]->getIconImageName(),
					_vItemList[i]->getItemName(),
					_vItemList[i]->getItemNum(),
					0,
					_vItemList[i]->getConsumptionItem()._hp,
					_vItemList[i]->getConsumptionItem()._mp,
					_vItemList[i]->getConsumptionItem()._sp,
					_vItemList[i]->getCost(),
					_vItemList[i]->getConsumptionItem()._isEventItem
				);
			}
			// ��Ÿ
			else if (itemNum / TYPE_EQUIPMENT == 3)
			{
				_item->makeEtcItem(
					_vItemList[i]->getUseImageName(),
					_vItemList[i]->getItemName(),
					_vItemList[i]->getItemNum(),
					_vItemList[i]->getEtcItem()._isEventItem
				);
			}
			break;
		}
	}

	return _item;
}
