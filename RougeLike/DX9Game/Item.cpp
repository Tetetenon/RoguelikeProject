#include "Item.h"
#include "define.h"
#include <string>

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CItem::CItem(void)
{
	//�����񏉊���
	for(int i = 0;i < ITEM_FONT_NUM_MAX;i++)
	{
		lstrcpyn(m_szName,_T("����"),sizeof(_TCHAR) * ITEM_FONT_NUM_MAX / 2);
	}
	//ID�̏�����
	m_ID = 0;
	//���\�l�̏�����
	m_nEffectValue = 0;
	//���\�̎�ނ̏�����
	m_nEffectType = -99;
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CItem::~CItem(void)
{
}
//---------------------------------------------------------------------------------------
//���O��ݒ�
//---------------------------------------------------------------------------------------
void CItem::SetName(_TCHAR Name[])
{
	lstrcpyn(m_szName,Name,sizeof(_TCHAR) * ITEM_FONT_NUM_MAX / 2);
}

//---------------------------------------------------------------------------------------
//ID���疼�O�������A���O���i�[
//---------------------------------------------------------------------------------------
void CItem::FindName	(int nID)
{
	switch(nID)
	{
	case ITEM_APPLE:
		SetName(_T("�ь�"));
		break;
	case ITEM_HERB:
		SetName(_T("��"));
		break;
	case ITEM_SWORD:
		SetName(_T("����"));
		break;
	case ITEM_SHIELD:
		SetName(_T("����"));
		break;
	default:
		break;
	}
}
void CItem::EffectSetting(int nID)
{
	//�A�C�e����ID�ɂ���Č��ʂ�ύX����
	switch(nID)
	{
		//�ь�
	case ITEM_APPLE:
		//���Ɍ��ʂȂ�
		m_nEffectType = EFFECT_NON;
		break;
		//��
	case ITEM_HERB:
		//�̗͂̉�
		m_nEffectType =  EFFECT_RECOVERY;
		break;
		//��
	case ITEM_SWORD:
		//�U���̓A�b�v
		m_nEffectType =  EFFECT_EQUIPMENT_ATTACK;
		break;
		//��
	case ITEM_SHIELD:
		//�h��̓A�b�v
		m_nEffectType =  EFFECT_EQUIPMENT_DEFENCE;
		break;
		//�o�O�����p
	default:
		//���ʂȂ�
		m_nEffectType =  EFFECT_NON;
		break;
	}
}