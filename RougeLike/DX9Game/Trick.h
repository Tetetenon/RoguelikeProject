#pragma once

//�Z�N���X

#include <Windows.h>
#include <tchar.h>

//�Z�̕�����
#define TRICK_FONT_NUM_MAX 256

class CTrick
{
protected:
	int		m_ID;					//�Z��ތʂ�ID
	_TCHAR	m_szName[TRICK_FONT_NUM_MAX];	//�Z�̖��O
	int		m_nEffectValue;			//�Z�̌��ʂ̐��l
	int		m_nEffectType;			//�Z���ʂ̎��
	int		m_nEffectRange;			//�Z�̌��ʔ͈�
public:
	CTrick(void);
	~CTrick(void);
	
	_TCHAR* GetName()	{return m_szName;}				//���O���擾
	int	GetID()			{return m_ID;}					//ID���擾
	int	GetValue()		{return m_nEffectValue;}		//���ʂ̐��l��n��
	int GetType()		{return m_nEffectType;}			//���ʂ̎�ނ�Ԃ�
	int GetRange()		{return m_nEffectRange;}		//�Z�̌��ʔ͈�

	//���O��ݒ�
	void SetName(_TCHAR Name[]);

	//ID�̐ݒ�
	void SetID(int nID)		{m_ID = nID;}

	//�Z�̌��\�ݒ�
	void SetValue(int nValue)			{m_nEffectValue = nValue;}

	//ID����Z���̔���
	void FindName	(int nID);

	//ID������ʂ̎�ނ̐ݒ�
	void EffectSetting(int nID);

	//ID����A�Z�͈͂̐ݒ�
	void SetRange(int nID);
};

