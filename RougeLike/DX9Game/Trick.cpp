#include "Trick.h"
#include "define.h"
#include <string>

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CTrick::CTrick(void)
{
	//�����񏉊���
	for(int i = 0;i < TRICK_FONT_NUM_MAX;i++)
	{
		lstrcpyn(m_szName,_T("����"),sizeof(_TCHAR) * TRICK_FONT_NUM_MAX / 2);
	}
	//ID�̏�����
	m_ID = 0;
	//���\�l�̏�����
	m_nEffectValue = 0;
	//���\�̎�ނ̏�����
	m_nEffectType = -99;
	//�Z�͈͂̏�����
	m_nEffectRange = 0;
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CTrick::~CTrick(void)
{
}
//---------------------------------------------------------------------------------------
//���O��ݒ�
//---------------------------------------------------------------------------------------
void CTrick::SetName(_TCHAR Name[])
{
	lstrcpyn(m_szName,Name,sizeof(_TCHAR) * TRICK_FONT_NUM_MAX / 2);
}

//---------------------------------------------------------------------------------------
//ID���疼�O�������A���O���i�[
//---------------------------------------------------------------------------------------
void CTrick::FindName	(int nID)
{
	switch(nID)
	{
	case TRICK_NAME_1:
		SetName(_T("�O���R�}�X�ɍU��"));
		break;
	case TRICK_NAME_2:
		SetName(_T("�����S�̍U��"));
		break;
	case TRICK_NAME_3:
		SetName(_T("��"));
		break;
	case TRICK_NAME_4:
		SetName(_T("�U��P�A�b�v"));
		break;
	default:
		break;
	}
}
//---------------------------------------------------------------------------------------
//ID������ʂ������A�ݒ�
//---------------------------------------------------------------------------------------
void CTrick::EffectSetting(int nID)
{
	//�Z��ID�ɂ���Č��ʂ�ύX����
	switch(nID)
	{
		//1
	case TRICK_NAME_1:
		//�O���R�}�X�ɍU��
		m_nEffectType = TRICK_EFFECT_ATTACK;
		break;
		//2
	case TRICK_NAME_2:
		//�����S�̂ɍU��
		m_nEffectType =  TRICK_EFFECT_ATTACK;
		break;
		//��
	case TRICK_NAME_3:
		//4
		m_nEffectType =  TRICK_EFFECT_RECOVERY;
		break;
		//�X�e�[�^�X����
	case TRICK_NAME_4:
		//�h��̓A�b�v
		m_nEffectType =  TRICK_EFFECT_STATES_UP;
		break;
		//�o�O�����p
	default:
		//���ʂȂ�
		m_nEffectType =  TRICK_EFFECT_MAX;
		break;
	}
}
//---------------------------------------------------------------------------------------
//ID����Z�͈̔͂�ݒ�
//---------------------------------------------------------------------------------------
void CTrick::SetRange(int nID)
{
	//�Z��ID�ɂ���Ĕ͈͂�ύX����
	switch(nID)
	{
		//1
	case TRICK_NAME_1:
		//�O���R�}�X�ɍU��
		m_nEffectRange = TRICK_RANGE_WIDE;
		break;
		//2
	case TRICK_NAME_2:
		//�����S�̂ɍU��
		m_nEffectRange =  TRICK_RANGE_ALL;
		break;
		//��
	case TRICK_NAME_3:
		//����
		m_nEffectRange =  TRICK_RANGE_ME;
		break;
		//�X�e�[�^�X����
	case TRICK_NAME_4:
		//����
		m_nEffectRange =  TRICK_RANGE_ME;
		break;
		//�o�O�����p
	default:
		//���ʂȂ�
		m_nEffectRange =  TRICK_RANGE_MAX;
		break;
	}
}