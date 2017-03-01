#pragma once

//�A�C�e���N���X

#include <Windows.h>
#include <tchar.h>

//�A�C�e���̕�����
#define ITEM_FONT_NUM_MAX 10

//�A�C�e���̖��O
enum ITEMNAME
{
	ITEM_APPLE	= 1,	//�ь�
	ITEM_HERB,			//��
	ITEM_SWORD,			//��
	ITEM_SHIELD,		//��
	ITEM_MAX
};

class CItem
{
protected:
	int		m_ID;		//�A�C�e����ތʂ�ID
	_TCHAR	m_szName[ITEM_FONT_NUM_MAX];		//�A�C�e���̖��O
	int		m_nEffectValue;				//�A�C�e���̌��ʂ̐��l
	int		m_nEffectType;				//�A�C�e�����ʂ̎��
public:
	CItem(void);
	~CItem(void);
	
	_TCHAR* GetName()	
	{
		return m_szName;
	}				//���O���擾
	int	GetID()	
	{
		return m_ID;
	}							//ID���擾
	int	GetValue()
	{
		return m_nEffectValue;
	}				//���ʂ̐��l��n��
	int GetType()	
	{
		return m_nEffectType;
	}				//�A�C�e�����ʂ̎�ނ�Ԃ�

	//���O��ݒ�
	void SetName(_TCHAR Name[]);
	//ID�̐ݒ�
	void SetID(int nID)		{m_ID = nID;}
	//�A�C�e���̌��\�ݒ�
	void SetValue(int nValue)			{m_nEffectValue = nValue;}
	//�^�C�v�̏�����
	void SetType(int nType) { m_nEffectType = nType; }

	//ID����A�C�e�����̔���
	void FindName	(int nID);

	//ID����A�C�e�����ʂ̎�ނ̐ݒ�
	void EffectSetting(int nID);
};

