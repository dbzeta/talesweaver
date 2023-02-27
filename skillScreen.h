#pragma once
#include "uiScreen.h"
#include "skillNode.h"

struct tagSkillButton
{
	SKILLTYPE skillType;
	RECT rc;						
	image* btnImage;				
	image* selectSkillImage;	
	int selectSkillFrameX, selectSkillFrameY;
};	

struct tagSkill
{
	SKILLTYPE skillType;			// 스킬 타입 ( 검계열 , 베기계열 등 등 ... )
	image* skillImage;				// 스킬 이미지
	string name;					// 스킬 이름
	int damage;						// 데미지
	int requirePoint;				// 스킬을 올리기위한 필요 경험치
};

class skillScreen : public uiScreen
{
private:
	// 스킬을 벡터에 담고
	vector<tagSkill*> _vSkillList;
	// 그 담겨져 있는 벡터를 맵에 담는다.
	// map<SKILLTYPE, vector<tagSkill*>> _mTotalSkillList;

	vector<tagSkillButton*> _vSkillBtnList;

	// 스킬 타입 버튼
	tagSkillButton* _fireType;
	tagSkillButton* _windType;
	tagSkillButton* _electricType;
	tagSkillButton* _commonType;
	tagSkillButton* _swordType;
	tagSkillButton* _knifeType;

	// 그 외 버튼
	tagButton _levelUpBtn;
	tagButton _selectSkillBtn;
	tagButton _plusBtn;
	tagButton _minusBtn;
	tagButton _exitBtn;

	SKILLTYPE _currentSkillType;
	tagSkill* _currentSkill;				

	image* _selectSkillType;						// 스킬 주변 테두리 이미지


public:
	skillScreen();
	~skillScreen();

	HRESULT init();
	void release();
	void update();
	void render();

	void setSkill();
	void setBtn();

	bool isOnceClick();				// Once
	bool isStayClick();				// Stay
	bool isOnceClickUp() { return false; }

};



// 스킬을 사용 -> 스킬매니저 -> 스킬 판별 후 스킬을 사용 ( 클래스로 만든다 )

// -> 스킬 하나하나를 일일히 구현 할것인가?