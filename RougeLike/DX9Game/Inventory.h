#pragma once
#include"Item.h"
#include<tchar.h>
//�����ł���ő�A�C�e����
#define ITEM_NUM_MAX 10

class CInventory:
	public CItem
{
private:
	CItem	m_Item[ITEM_NUM_MAX];	//�A�C�e���f�[�^(�A�C�e���̎��Ă鐔)
public:
	CInventory();							//�R���X�g���N�^
	~CInventory();							//�f�X�g���N�^

	//�w�肳�ꂽ�A�C�e���f�[�^��n��
	CItem GetItem(int Coefficient) 
	{
		return m_Item[Coefficient]; 
	}

	//�w�肳�ꂽ�A�C�e���̖��O��Ԃ�
	_TCHAR* GetInventoryItemName(int Coefficient) { return m_Item[Coefficient].GetName(); }

	bool SetItem(CItem Item);		//�X�g���[�W�ɃA�C�e�����Z�b�g

	void DelInventory(int Receipt);				//�w�肵���ԍ��̃A�C�e��������

	int GetEffect(int Receipt);					//�w�肳�ꂽ�A�C�e���̌��ʃW��������ԋp

	int GetEffectValue(int Receipt);			//�w�肳�ꂽ�A�C�e���̌��\��ԋp����

};

