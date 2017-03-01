#include "ItemManager.h"
#include "FieldItem.h"

//�ÓI�ϐ��̏�����
CItemManager*	CItemManager::m_pItemManager = NULL;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CItemManager::CItemManager()
{
	//���X�g���쐬
	m_pItemMap = new ITEM_MAP();
	//���X�g�̏�����
	m_pItemMap->clear();

	//�ϐ��̏�����
	m_Delete = false;
	m_MakeItemNum = 1;
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CItemManager::~CItemManager()
{
	//�I������
	Fin();
	//�폜
	delete m_pItemMap;
	//���g�����ꂢ�ɂ���
	m_pItemMap = NULL;

	m_Delete = false;

	m_MakeItemNum = 1;
}

//---------------------------------------------------------------------------------------
//�A�C�e���}�l�[�W���[�̍쐬
//---------------------------------------------------------------------------------------
void CItemManager::Create()
{
	//�A�C�e���}�l�[�W�����쐬����Ă��Ȃ���΁A�쐬���s��
	if (!m_pItemManager)
	{
		m_pItemManager = new CItemManager;
	}
}

//---------------------------------------------------------------------------------------
//�A�C�e���}�l�[�W���[�̍폜
//---------------------------------------------------------------------------------------
void CItemManager::Delete()
{
	//NULL�`�F�b�N
	if (m_pItemManager)
	{
		delete m_pItemManager;
		m_pItemManager = NULL;
	}
}

//---------------------------------------------------------------------------------------
//�A�C�e����ǉ�
//---------------------------------------------------------------------------------------
void CItemManager::Add(int ItemID,CFieldItem* pAddItem)
{
	//ID�ŃI�u�W�F�N�g���o�^����Ă��邩�m�F���s��
	auto ItemItewrator = m_pItemMap->find(ItemID);

	//ID�����Ƀ��X�g��ɓo�^����Ă��邩�m�F���s��
	if (ItemItewrator != m_pItemMap->end())
	{
		//���ɓo�^���s���Ă��邽�߁A�I�u�W�F�f�[�^�݂̂���������
		ItemItewrator->second.push_back(pAddItem);
	}
	else
	{
		//ID���o�^������Ă��Ȃ����߁A�����Ƃ��ɓo�^���s��
		ITEM_LIST NewItemList;
		NewItemList.push_back(pAddItem);

		ITEM_PAIR NewItemPair(ItemID, NewItemList);
		m_pItemMap->insert(NewItemPair);
	}
}
//---------------------------------------------------------------------------------------
//�A�C�e���폜
//---------------------------------------------------------------------------------------
void CItemManager::Del(int ItemID)
{
	//ID�ɂăf�[�^�̌���
	auto ItemIterator = m_pItemMap->find(ItemID);

	//����ID�̃I�u�W�F�N�g�����݂��Ă����ꍇ�A�폜���s��
	if (ItemIterator != m_pItemMap->end())
	{
		auto ListIterator = ItemIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		ItemIterator->second.erase(ListIterator);
	}
}

//---------------------------------------------------------------------------------------
//�A�C�e���T��
//---------------------------------------------------------------------------------------
CFieldItem* CItemManager::Find(int ItemID)
{
	//ID�ŃI�u�W�F�N�g������
	auto ItemIterator = m_pItemMap->find(ItemID);

	//���̃I�u�W�F�N�g�f�[�^�����݂���ꍇ�A���̃f�[�^��Ԃ�
	if (ItemIterator != m_pItemMap->end())
		return ItemIterator->second[0];
	//������΁ANULL��Ԃ�
	else
		return NULL;
}
//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void CItemManager::Init()
{
	//���X�g�̐擪���擾
	auto ItemIterator = m_pItemMap->begin();

	for (; ItemIterator != m_pItemMap->end(); ++ItemIterator)
	{
		for (auto ListIterator = ItemIterator->second.begin(); ListIterator != ItemIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Init();
		}
	}
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CItemManager::Update()
{
	//���X�g�̐擪���擾
	auto ItemIterator = m_pItemMap->begin();

	for (; ItemIterator != m_pItemMap->end(); ++ItemIterator)
	{
		for (auto ListIterator = ItemIterator->second.begin(); ListIterator != ItemIterator->second.end();)
		{
			//�S�I�u�W�F�N�g�폜�t���O�������Ă����ꍇ�A�폜
			if (m_Delete)
			{
				(*ListIterator)->Fin();
				delete (*ListIterator);
				ListIterator = ItemIterator->second.erase(ListIterator);
			}
			else
			{
				(*ListIterator)->Update();
				ListIterator++;
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CItemManager::Draw()
{
	//���X�g�\���̐擪���擾����
	auto ItemIterator = m_pItemMap->begin();

	for (; ItemIterator != m_pItemMap->end(); ++ItemIterator)
	{
		for (auto ListIterator = ItemIterator->second.begin(); ListIterator != ItemIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Draw();
		}
	}
}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CItemManager::Fin()
{
	//���X�g�̐擪���擾
	auto ItemIterator = m_pItemMap->begin();

	for (; ItemIterator != m_pItemMap->end();++ItemIterator)
	{
		for (auto ListIterator = ItemIterator->second.begin(); ListIterator != ItemIterator->second.end();)
		{
			(*ListIterator)->Fin();
			delete (*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = ItemIterator->second.erase(ListIterator);
		}
	}

	//������������������
	m_MakeItemNum = 1;

	//���X�g��|��
	m_pItemMap->clear();
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�f�o�C�X�̃|�C���^��n��
//---------------------------------------------------------------------------------------
CItemManager* CItemManager::GetPointer()
{
	return m_pItemManager;
}