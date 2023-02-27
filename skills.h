#pragma once
#include "gameNode.h"
#include "skillNode.h"

class skills : public gameNode
{
protected:
	int _skillNum;						// 스킬 넘버

	image* _skillIconImage;				// 스킬 아이콘 이미지
	image* _skillUsingImage;			// 스킬 사용 이미지


	string _skillName;					// 스킬 이름
	SKILLTYPE _skillType;				// 스킬 타입 ( 검계열 , 베기계열 등 등 ... )
	int _damage;						// 데미지
	int _requirePoint;					// 스킬을 올리기위한 필요 경험치
	int _maxSkillLevel;					// 최대 스킬레벨
	int _currentSkillLevel;				// 현재 스킬레벨
	
	bool _isUse;						// 스킬을 사용하기위한 bool변수

public:
	skills();
	~skills();

	HRESULT init();
	void release();
	void update();
	void render();


};

