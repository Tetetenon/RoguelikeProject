#include "Equipment.h"
#include "define.h"

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEquipment::CEquipment()
{
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CEquipment::~CEquipment()
{
}

//---------------------------------------------------------------------------------------
//�X�g���[�W�ɃA�C�e�����Z�b�g
//---------------------------------------------------------------------------------------
bool CEquipment::SetItem(CItem Item)
{
	for (int i = 0; i < EQUIPMENT_NUM_MAX; i++)
	{
		//�X�g���[�W���󔒂̕�����T��
		if (m_Item[i].GetID() == 0)
		{
			//�A�C�e���̊i�[
			m_Item[i] = Item;

			//���\�̐ݒ肪����Ă��Ȃ���΁A�����I�ɐݒ肷��
			if (m_Item[i].GetValue() == 0)
			{
				//���\��ݒ�
				m_Item[i].SetValue(rand() % 10 + 5);
			}
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------------
//ID���疼�O�������A���O���i�[
//---------------------------------------------------------------------------------------
void CEquipment::FindName(int nID, int Receipt)
{
	switch (nID)
	{
	case ITEM_APPLE:
		m_Item[Receipt].SetName(_T("�ь�"));
		break;
	case ITEM_HERB:
		m_Item[Receipt].SetName(_T("��"));
		break;
	case ITEM_SWORD:
		m_Item[Receipt].SetName(_T("����"));
		break;
	case ITEM_SHIELD:
		m_Item[Receipt].SetName(_T("����"));
		break;
	default:
		break;
	}
}

//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�A�C�e��������
//---------------------------------------------------------------------------------------
void CEquipment::DelInventory(int Receipt)
{
	//���g�����������A����
	//ID�̏�����
	m_Item[Receipt].SetID(0);
	//���O�̏�����
	m_Item[Receipt].SetName(_T("0"));
	//�^�C�v�̏�����
	m_Item[Receipt].SetValue(0);
	//���ʒl�̏�����
	m_Item[Receipt].SetType(-99);

}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�A�C�e���̌��ʃW��������ԋp����
//---------------------------------------------------------------------------------------
int CEquipment::GetEffect(int Receipt)
{
	//�A�C�e����ID�ɂ���Č��ʂ�ύX����
	switch (m_Item[Receipt].GetID())
	{
		//�ь�
	case ITEM_APPLE:
		//���Ɍ��ʂȂ�
		return EFFECT_NON;
		break;
		//��
	case ITEM_HERB:
		//�̗͂̉�
		return EFFECT_RECOVERY;
		break;
		//��
	case ITEM_SWORD:
		//�U���̓A�b�v
		return EFFECT_EQUIPMENT_ATTACK;
		break;
		//��
	case ITEM_SHIELD:
		//�h��̓A�b�v
		return EFFECT_EQUIPMENT_DEFENCE;
		break;
		//�o�O�����p
	default:
		//���ʂȂ�
		return EFFECT_NON;
		break;
	}
}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�A�C�e���̌��\?��ԋp����
//---------------------------------------------------------------------------------------
int CEquipment::GetEffectValue(int Receipt)
{
	//�A�C�e����ID�ɂ���Č��ʂ�ύX����
	switch (m_Item[Receipt].GetID())
	{
		//�ь�
	case ITEM_APPLE:
		//���Ɍ��ʂȂ�
		return EFFECT_NON;
		break;
		//��
	case ITEM_HERB:
		//�̗͂̉�
		return m_Item[Receipt].GetValue();
		break;
		//��
	case ITEM_SWORD:
		//�U���̓A�b�v
		return m_Item[Receipt].GetValue();
		break;
		//��
	case ITEM_SHIELD:
		//�h��̓A�b�v
		return m_Item[Receipt].GetValue();
		break;

		//�o�O�����p
	default:
		//���ʂȂ�
		return EFFECT_NON;
		break;
	}
}
//---------------------------------------------------------------------------------------
//�C���x���g���ɑ��݂��邷�ׂĂ̍U�������A�C�e���̍��v�l���Z�o���A�n��
//---------------------------------------------------------------------------------------
int CEquipment::GetAttackTotalValue()
{
	//���v�l�i�[�p�ϐ�
	int nTotalNum = 0;

	//�S�ẴA�C�e�������m�F����
	for (int i = 0; i < EQUIPMENT_NUM_MAX; i++)
	{
		//���ʂ��U���⏕���m�F����
		if (m_Item[i].GetType() == EFFECT_EQUIPMENT_ATTACK)
		{
			//�U���⏕�^�Ȃ�A���̒l�����o���A���Z
			nTotalNum += m_Item[i].GetValue();
		}
	}
	return nTotalNum;
}
//---------------------------------------------------------------------------------------
//�C���x���g���ɑ��݂��邷�ׂĂ̖h�䋭���A�C�e���̍��v�l���Z�o���A�n��
//---------------------------------------------------------------------------------------
int CEquipment::GetDefenceTotalValue()
{
	//���v�l�i�[�p�ϐ�
	int nTotalNum = 0;
	//�S�ẴA�C�e�������m�F����
	for (int i = 0; i < EQUIPMENT_NUM_MAX; i++)
	{
		//���ʂ��h��⏕���m�F����
		if (m_Item[i].GetType() == EFFECT_EQUIPMENT_DEFENCE)
		{
			//�h��⏕�^�Ȃ�A���̒l�����o���A���Z
			nTotalNum += m_Item[i].GetValue();
		}
	}
	return nTotalNum;
}