#include "DamageBillBoardManager.h"
#include "DamageNotation.h"

//�ÓI�ϐ��錾
CDamageBillBoardManager* CDamageBillBoardManager::m_pManager = NULL;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CDamageBillBoardManager::CDamageBillBoardManager()
{
	//���X�g�|�C���^�̎擾
	m_pDamageBillBoardMap = new DAMAGE_NOTATION_MAP;
	//���X�g�̏�����
	m_pDamageBillBoardMap->clear();
	//�g�p�ϐ��̏�����
	m_nNextBillBoardNumber = 0;
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CDamageBillBoardManager::~CDamageBillBoardManager()
{
	//�Ǘ��I�u�W�F�N�g�̏I������
	ManagerObjFin();
	//�폜
	delete m_pDamageBillBoardMap;
	//���g�����ꂢ��
	m_pDamageBillBoardMap = NULL;
	//�g�p�ϐ��̏�����
	m_nNextBillBoardNumber = 0;
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̍쐬
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::Create()
{
	//�}�l�[�W���[���쐬����Ă��Ȃ���΍쐬
	if (!m_pManager)
	{
		m_pManager = new CDamageBillBoardManager;
	}
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̍폜
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::Delete()
{
	//���g�����݂��Ă��邩�A�`�F�b�N���s��
	if (m_pManager)
	{
		//�}�l�[�W���[�폜
		delete m_pManager;
		m_pManager = NULL;
	}
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̃|�C���^��n��
//---------------------------------------------------------------------------------------
CDamageBillBoardManager* CDamageBillBoardManager::GetPointer()
{
	//�}�l�[�W���[�̍쐬
	Create();

	//�|�C���^��Ԃ�
	return m_pManager;
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̒ǉ�
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::Add(int ID, CDamageNotation* pAddObj)
{
	//ID�����ɓo�^������Ă��邩�m�F���s��
	auto BoardIterator = m_pDamageBillBoardMap->find(ID);

	//����ID�����ɓo�^����Ă��邩�m�F���s��
	if (BoardIterator != m_pDamageBillBoardMap->end())
	{
		//����ID���o�^����Ă��邽�߁A�I�u�W�F�f�[�^�݂̂����̏ꏊ�ɓo�^����
		BoardIterator->second.push_back(pAddObj);
	}
	else
	{
		//ID���o�^������Ă��Ȃ����߁A�����̃f�[�^��o�^����
		DAMAGE_NOTATION_LIST NewList;
		NewList.push_back(pAddObj);

		DAMAGE_NOTATION_PAIR NewEffectPair(ID, NewList);
		m_pDamageBillBoardMap->insert(NewEffectPair);
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̍폜
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::Del(int ID)
{
	//ID�ŃI�u�W�F�N�g�̌���
	auto BoardIterator = m_pDamageBillBoardMap->find(ID);

	//���̃I�u�W�F�N�g�����݂��Ă���ꍇ�A�폜
	if (BoardIterator != m_pDamageBillBoardMap->end())
	{
		auto ListIterator = BoardIterator->second.begin();
		delete (*ListIterator);
		BoardIterator->second.erase(ListIterator);
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̌���
//---------------------------------------------------------------------------------------
CDamageNotation* CDamageBillBoardManager::Find(int ID)
{
	//ID�ŃI�u�W�F�N�g�̌������s��
	auto BoardIterator = m_pDamageBillBoardMap->find(ID);

	//���̎w�肳�ꂽID�̃f�[�^�����݂���ꍇ�A�f�[�^��Ԃ�
	if (BoardIterator != m_pDamageBillBoardMap->end())
	{
		return BoardIterator->second[0];
	}
	else
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̏I������
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::ManagerObjFin()
{
	//���X�g�̐擪���擾
	auto BoardIterator = m_pDamageBillBoardMap->begin();

	for (; BoardIterator != m_pDamageBillBoardMap->end(); ++BoardIterator)
	{
		for (auto ListIterator = BoardIterator->second.begin(); ListIterator != BoardIterator->second.end();)
		{
			delete (*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = BoardIterator->second.erase(ListIterator);
		}
	}
	//���X�g�̑|��
	m_pDamageBillBoardMap->clear();
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̍X�V
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::ManagerObjUpdate()
{
	//���X�g�̐擪���擾
	auto BoardIterator = m_pDamageBillBoardMap->begin();

	for (; BoardIterator != m_pDamageBillBoardMap->end(); ++BoardIterator)
	{
		for (auto ListIterator = BoardIterator->second.begin(); ListIterator != BoardIterator->second.end();)
		{
			//�X�V
			(*ListIterator)->Update();

			//�c��̐������Ԃ������Ȃ�΁A�폜
			if ((*ListIterator)->GetLifeTime() <= 0)
			{
				//�폜����
				delete (*ListIterator);
				ListIterator = BoardIterator->second.erase(ListIterator);

			}
			else
			{
				//�������Ԃ��c���Ă���ꍇ�̓X���\
				ListIterator++;
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̕`��
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::ManagerObjDraw()
{
	//���X�g�̐擪���擾
	auto BoardIterator = m_pDamageBillBoardMap->begin();

	for (; BoardIterator != m_pDamageBillBoardMap->end(); ++BoardIterator)
	{
		for (auto ListIterator = BoardIterator->second.begin(); ListIterator != BoardIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Draw();
		}
	}
}
