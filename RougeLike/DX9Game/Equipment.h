#pragma once
#include "Item.h"

//�����ł���ő�A�C�e����
#define EQUIPMENT_NUM_MAX 5

class CEquipment:
	public CItem
{
private:
	CItem	m_Item[EQUIPMENT_NUM_MAX];	//�A�C�e���f�[�^(�A�C�e���̎��Ă鐔)
public:
	CEquipment();						//�R���X�g���N�^
	~CEquipment();						//�f�X�g���N�^

	bool SetItem(CItem Item);	//�X�g���[�W�ɃA�C�e�����Z�b�g
								//�w�肳�ꂽ�A�C�e���̖��O��Ԃ�
	_TCHAR* GetInventoryItemName(int Coefficient) { return m_Item[Coefficient].GetName(); }

	//�w�肳�ꂽ�A�C�e����n��
	CItem GetItem(int Coefficient) { return m_Item[Coefficient]; }

	void DelInventory(int Receipt);				//�w�肵���ԍ��̃A�C�e��������

	int GetEffect(int Receipt);					//�w�肳�ꂽ�A�C�e���̌��ʃW��������ԋp

	int GetEffectValue(int Receipt);			//�w�肳�ꂽ�A�C�e���̌��\��ԋp����

	void FindName(int nID, int Receipt);		//ID���疼�O����������

	int GetAttackTotalValue();					//�C���x���g���ɑ��݂��邷�ׂĂ̍U�������A�C�e���̍��v�l���Z�o���A�n��
	int GetDefenceTotalValue();					//�C���x���g���ɑ��݂��邷�ׂĂ̖h�䋭���A�C�e���̍��v�l���Z�o���A�n��	

};

