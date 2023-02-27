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
	SKILLTYPE skillType;			// ��ų Ÿ�� ( �˰迭 , ����迭 �� �� ... )
	image* skillImage;				// ��ų �̹���
	string name;					// ��ų �̸�
	int damage;						// ������
	int requirePoint;				// ��ų�� �ø������� �ʿ� ����ġ
};

class skillScreen : public uiScreen
{
private:
	// ��ų�� ���Ϳ� ���
	vector<tagSkill*> _vSkillList;
	// �� ����� �ִ� ���͸� �ʿ� ��´�.
	// map<SKILLTYPE, vector<tagSkill*>> _mTotalSkillList;

	vector<tagSkillButton*> _vSkillBtnList;

	// ��ų Ÿ�� ��ư
	tagSkillButton* _fireType;
	tagSkillButton* _windType;
	tagSkillButton* _electricType;
	tagSkillButton* _commonType;
	tagSkillButton* _swordType;
	tagSkillButton* _knifeType;

	// �� �� ��ư
	tagButton _levelUpBtn;
	tagButton _selectSkillBtn;
	tagButton _plusBtn;
	tagButton _minusBtn;
	tagButton _exitBtn;

	SKILLTYPE _currentSkillType;
	tagSkill* _currentSkill;				

	image* _selectSkillType;						// ��ų �ֺ� �׵θ� �̹���


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



// ��ų�� ��� -> ��ų�Ŵ��� -> ��ų �Ǻ� �� ��ų�� ��� ( Ŭ������ ����� )

// -> ��ų �ϳ��ϳ��� ������ ���� �Ұ��ΰ�?