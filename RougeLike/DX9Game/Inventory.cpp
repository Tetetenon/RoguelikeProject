#include "Inventory.h"
#include "Item.h"
#include"define.h"


//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CInventory::CInventory()
{
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CInventory::~CInventory()
{
}

//---------------------------------------------------------------------------------------
//�X�g���[�W�ɃA�C�e�����Z�b�g
//---------------------------------------------------------------------------------------
bool CInventory::SetItem(CItem Item)
{
	for (int i = 0; i < ITEM_NUM_MAX; i++)
	{
		//�X�g���[�W���󔒂̕�����T��
		if (m_Item[i].GetID() == 0)
		{
			//�A�C�e���f�[�^���R�s�[
			m_Item[i] = Item;


			//���\�̐ݒ肪����Ă��Ȃ���΁A�����I�ɐݒ肷��
			if (Item.GetValue() == 0)
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
//�w�肳�ꂽ�A�C�e��������
//---------------------------------------------------------------------------------------
void CInventory::DelInventory(int Receipt)
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
int CInventory::GetEffect(int Receipt)
{
	return m_Item[Receipt].GetType();
}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�A�C�e���̌��\?��ԋp����
//---------------------------------------------------------------------------------------
int CInventory::GetEffectValue(int Receipt)
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