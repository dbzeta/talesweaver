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
	// 받아와야하는 아이템 데이터 imageName 
	
	// 레드허브
	item* _item0 = new item;
	_item0->init();
	_item0->makeConsumptionItem("레드허브", "레드허브", TYPE_HP + 1, 0, 30, 0, 0, 100, false);
	_vItemList.push_back(_item0);

	// 딸기시럽
	item* _item1 = new item;	
	_item1->init();
	_item1->makeConsumptionItem("딸기시럽", "딸기시럽", TYPE_HP + 2, 0, 60, 0, 0, 200, false);
	_vItemList.push_back(_item1);

	// 그린허브
	item* _item2 = new item;
	_item2->init();	
	_item2->makeConsumptionItem("그린허브", "그린허브", TYPE_MP + 1, 0, 0, 10, 0, 100, false);
	_vItemList.push_back(_item2);

	// 키위시럽
	item* _item3 = new item;
	_item3->init();	
	_item3->makeConsumptionItem("키위시럽", "키위시럽", TYPE_MP + 2, 0, 0, 20, 0, 200, false);
	_vItemList.push_back(_item3);

	// 스테미너포션 소
	item* _item4 = new item;
	_item4->init();
	_item4->makeConsumptionItem("스태미너포션소", "스태미너포션소", TYPE_SP + 1, 0, 0, 0, 250, 150, false);
	_vItemList.push_back(_item4);
	
	// 마인의 붉은 두건(이벤트)		1 1 1 2 2 0 0	
	item* _item5 = new item;
	_item5->init();
	_item5->makeEquipmentItem("마인의붉은두건장착","마인의모자", "마인의모자", TYPE_HAT + 1, 0, 1, 1, 1, 2, 2, 0, 0, 0, true);
	_vItemList.push_back(_item5);
	
	// 본메일						0 0 0 13 0 1 0
	item* _item6 = new item;
	_item6->init();
	_item6->makeEquipmentItem("본메일", "본메일", TYPE_MAIL + 1, 0, 0, 0, 0, 13, 0, 1, 0, 2000, false);
	_vItemList.push_back(_item6);

	// 하드레더 아머				0 0 0 8 4 0 2
	item* _item7 = new item;
	_item7->init();
	_item7->makeEquipmentItem("하드레더아머", "하드레더아머", TYPE_LIGHTARMOR + 1, 0, 0, 0, 0, 8, 4, 0, 2, 3000, false);
	_vItemList.push_back(_item7);

	// 수련검						9 8 0 1 0 1 0
	item* _item8 = new item;
	_item8->init();
	_item8->makeEquipmentItem("수련검장착", "수련검", "수련검", TYPE_SWORD + 1, 0, 9, 8, 0, 1, 0, 1, 0, 1500, false);
	_vItemList.push_back(_item8);

	// 타도							7 15 3 0 0 2 3
	item* _item9 = new item;
	_item9->init();
	_item9->makeEquipmentItem("타도장착", "타도", "타도", TYPE_KNIFE + 1, 0, 7, 15, 3, 0, 0, 2, 3, 1500, false);
	_vItemList.push_back(_item9);

	// 버클러						0 0 0 3 0 0 0
	item* _item10 = new item;
	_item10->init();
	_item10->makeEquipmentItem("버클러장착", "버클러", "버클러", TYPE_SHIELD + 1, 0, 0, 0, 0, 3, 0, 0, 0, 1600, false);
	_vItemList.push_back(_item10);

	// 고속밴드						4 4 4 0 0 1 0
	item* _item11 = new item;
	_item11->init();
	_item11->makeEquipmentItem("고속밴드", "고속밴드", TYPE_BAND + 1, 0, 4, 4, 4, 0, 0, 1, 0, 2200, false);
	_vItemList.push_back(_item11);

	// 수습 마법사의 목걸이			0 0 0 3 2 0 2
	item* _item12 = new item;
	_item12->init();
	_item12->makeEquipmentItem("수습마법사목걸이", "수습마법사의목걸이", TYPE_NECKLACE + 1, 0, 0, 0, 0, 3, 2, 0, 2, 900, false);
	_vItemList.push_back(_item12);

	// 나무 빗자루					0 0 0 2 2 1 0
	item* _item13 = new item;
	_item13->init();
	_item13->makeEquipmentItem("나무마법빗자루장착", "나무마법빗자루", "나무마법빗자루", TYPE_BROOM + 1, 0, 0, 0, 0, 2, 2, 1, 0, 900, false);
	_vItemList.push_back(_item13);

	// 면장갑						1 1 1 0 1 0 1
	item* _item14 = new item;
	_item14->init();
	_item14->makeEquipmentItem("면장갑", "면장갑", TYPE_GLOVE + 1, 0, 1, 1, 1, 0, 1, 0, 1, 1000, false);
	_vItemList.push_back(_item14);

	// 샌들							0 0 0 0 0 1 2
	item* _item15 = new item;
	_item15->init();
	_item15->makeEquipmentItem("샌들", "샌들", TYPE_SHOES + 1, 0, 0, 0, 0, 0, 0, 1, 2, 1000, false);
	_vItemList.push_back(_item15);


	// 기본 지급 품
	// 103101 수련검 
	// 107101 면장갑
	// 104101 버클러 
	// 108101 샌들 

	// 판매품	
	// 102101 본메일
	// 102201 하드레더 아머
	// 103201 타도
	// 104201 고속밴드
	// 105101 수습 마법사의 목걸이
	// 106101 나무 마법 빗자루

	// 이벤트 아이템
	// 101101 마인의 붉은 두건 ( 이벤트 )

}

void itemManager::load()
{
	HANDLE file;
	DWORD read;

	while (_vItemList.size() > 0)
	{
		// 불러오기 후 불러오기 누르면 터지는데 이유가 뭐지??
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
			// 장비
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
			// 소모
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
			// 기타
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
