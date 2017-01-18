#include "UnitManager.h"
#include "Turn.h"
#include "Unit.h"				//���j�b�g


//�ÓI�ϐ��̏�����
int				CUnitManager::m_NowProcUnitID = 0;
UNIT_MAP*		CUnitManager::m_pUnitManager = NULL;

CUnit*	CUnitManager::m_pPlayer = NULL;			//�v���C���[�|�C���^�[
bool	CUnitManager::m_bMoveCanFlg;					//�ړ��\�t���O


//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CUnitManager::CUnitManager()
{
	//���ݏ������̃��j�b�g�̔ԍ��̏�����
	m_NowProcUnitID = 0;

	//���X�g�̏�����
	m_pUnitManager->clear();
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CUnitManager::~CUnitManager()
{
	//���ݏ������̃��j�b�g�̔ԍ���������
	m_NowProcUnitID = 0;

	//���X�g�̑|��
	m_pUnitManager->clear();

	m_pPlayer = NULL;
}

//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̐���
//---------------------------------------------------------------------------------------
void CUnitManager::Create()
{
	//�܂��쐬�����Ă��Ȃ������炳����������
	if (!m_pUnitManager)
	{
		m_pUnitManager = new UNIT_MAP;
	}
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̍폜
//---------------------------------------------------------------------------------------
void CUnitManager::Destroy()
{
	//NULL�`�F�b�N
	if (m_pUnitManager)
	{
		//�I������
		Fin();
		//�폜
		delete m_pUnitManager;
		//���g�����ꂢ��
		m_pUnitManager = NULL;
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̒ǉ�
//---------------------------------------------------------------------------------------
void CUnitManager::Add(int UnitID, CUnit* pAddUnit)
{
	//����ID���o�^����Ă��邩�m�F���s��
	auto UnitIterator = m_pUnitManager->find(UnitID);

	//����ID�����ɓo�^����Ă��邩�m�F����
	if (UnitIterator != m_pUnitManager->end())
	{
		//ID�����ɓo�^����Ă��邽�߁A�I�u�W�F�N�g�f�[�^�̂ݑ}��
		UnitIterator->second.push_back(pAddUnit);
	}
	else
	{
		//ID���A�I�u�W�F�f�[�^���o�^����Ă��Ȃ����߁A�����o�^����
		UNIT_LIST NewUnitList;
		NewUnitList.push_back(pAddUnit);

		UNIT_PAIR NewUnitPair(UnitID, NewUnitList);
		m_pUnitManager->insert(NewUnitPair);
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̍폜
//---------------------------------------------------------------------------------------
void CUnitManager::Del(int UnitID)
{
	//ID�ŃI�u�W�F�N�g�̌���
	auto UnitIterator = m_pUnitManager->find(UnitID);

	//���̃I�u�W�F�N�g�����݂��Ă���ꍇ�A�폜���s��
	if (UnitIterator != m_pUnitManager->end())
	{
		auto ListIterator = UnitIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		UnitIterator->second.erase(ListIterator);
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̒�����A�w�肳�ꂽID�̃��j�b�g��Ԃ�
//---------------------------------------------------------------------------------------
CUnit* CUnitManager::Find(int UnitID)
{
	//ID�ŃI�u�W�F�N�g�̌������s��
	auto UnitIterator = m_pUnitManager->find(UnitID);

	//���̎w�肳�ꂽID�̃f�[�^�����݂���ꍇ�A�f�[�^��Ԃ�
	if (UnitIterator != m_pUnitManager->end())
	{
		return UnitIterator->second[0];
	}
	else
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̏�����
//---------------------------------------------------------------------------------------
void CUnitManager::Init()
{
	//���X�g�̐擪���擾
	auto UnitIterator = m_pUnitManager->begin();

	for (; UnitIterator != m_pUnitManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Init();
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̍X�V
//---------------------------------------------------------------------------------------
void CUnitManager::Update()
{
	//���X�g�̐擪���擾
	auto UnitIterator = m_pUnitManager->begin();

	for (; UnitIterator != m_pUnitManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			//�ҋ@��Ԃ̍X�V���s��
			(*ListIterator)->WaitUpdate();
			(*ListIterator)->Update();

			//���݂̃��j�b�g�̔ԍ����擾���A���̃��j�b�g�̔ԍ��Ȃ�΁A�^�[���̏������s��
			if (m_NowProcUnitID == (*ListIterator)->GetNumber() || m_NowProcUnitID == 0)
			{
				//�^�[�����I�����Ă��邩�m�F����
				if ((*ListIterator)->GetTurnEndFlg())
				{
					//�^�[���������������Ă���ꍇ
			
					//���݂̏��������j�b�g�ԍ���������
					//���̃��j�b�g�̏������ł���悤�ɂ���
					m_NowProcUnitID = 0;
			
					//���j�b�g�̃^�[���̏�����Ԃ�������
					(*ListIterator)->setTurnEndFlg(false);
				}
				else
				{
					//�^�[���������������Ă��Ȃ��ꍇ
			
					//���݂̏������j�b�g�����g�ɐݒ肷��
					m_NowProcUnitID = (*ListIterator)->GetNumber();
			
					//�����A�s���\�t���O�������Ă��Ȃ���΁A�������X�L�b�v
					if (!m_bMoveCanFlg)
						return;
			
					//�^�[�������̍X�V
					(*ListIterator)->TurnUpdate();
				}
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̕`��
//---------------------------------------------------------------------------------------
void CUnitManager::Draw()
{
	//���X�g�̐擪���擾
	auto UnitIterator = m_pUnitManager->begin();

	for (; UnitIterator != m_pUnitManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Draw();
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̏I������
//---------------------------------------------------------------------------------------
void CUnitManager::Fin()
{
	//���X�g�̐擪���擾
	auto UnitIterator = m_pUnitManager->begin();

	for (; UnitIterator != m_pUnitManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end();)
		{
			(*ListIterator)->Fin();
			delete (*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = UnitIterator->second.erase(ListIterator);
		}
	}
	//���X�g�̑|��
	m_pUnitManager->clear();
}
//---------------------------------------------------------------------------------------
//�G�l�~�[�̍폜
//---------------------------------------------------------------------------------------
void CUnitManager::EnemyDelete()
{
	//���X�g�̐擪���擾
	auto UnitIterator = m_pUnitManager->begin();

	for (; UnitIterator != m_pUnitManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end();)
		{
			//�G�l�~�[�̏ꍇ�폜
			if((*ListIterator)->GetNumber() >= OBJ_NUM_ENEMY)
			{
				(*ListIterator)->Fin();
				delete (*ListIterator);
				ListIterator = UnitIterator->second.erase(ListIterator);
			}
			else
			{
				ListIterator++;
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̃f�o�C�X��n��
//---------------------------------------------------------------------------------------
UNIT_MAP* CUnitManager::GetPointer()
{
	return m_pUnitManager;
}
//---------------------------------------------------------------------------------------
//���j�b�g�S�Ă̍s���\�t���O��ύX����
//---------------------------------------------------------------------------------------
void CUnitManager::ChangeMoveCanFlg(bool ChangeFlg)
{
	m_bMoveCanFlg = ChangeFlg;
}
//---------------------------------------------------------------------------------------
//�v���C���[�̃|�C���^��ݒ肷��
//---------------------------------------------------------------------------------------
void CUnitManager::SetPlayerPointer()
{
	auto UnitIterator = m_pUnitManager->find(OBJ_NUM_PLAYER);

	m_pPlayer = *(UnitIterator->second.begin());
}
//---------------------------------------------------------------------------------------
//�v���C���[�̃��x����Ԃ�
//---------------------------------------------------------------------------------------
int CUnitManager::GetPlayerLevel()
{
	//�v���C���[�|�C���^�̒��g�������Ă���̂��m�F
	if (m_pPlayer)
	{
		//�����Ă���ꍇ�A�v���C���[�̃��x����Ԃ�
		return m_pPlayer->GetLevel();
	}
	else
		//�����Ă��Ȃ���΁A0��Ԃ�
		return 0;
}
//---------------------------------------------------------------------------------------
//�v���C���[�̈ʒu����n��(��)
//---------------------------------------------------------------------------------------
int CUnitManager::GetPlayerPosX()
{
	//�v���C���[�̃|�C���^�ɒ��g�������Ă��邩�m�F����
	if (m_pPlayer)
	{
		//�����Ă���ꍇ�A�v���C���[�̈ʒu��Ԃ�
		return m_pPlayer->GetPosX();
	}
	else
	{
		//�����Ă��Ȃ��ꍇ�A0��Ԃ�
		return 0;
	}
}
//---------------------------------------------------------------------------------------
//�v���C���[�̈ʒu����Ԃ�(�c)
//---------------------------------------------------------------------------------------
int CUnitManager::GetPlayerPosZ()
{
	//�v���C���[�̃|�C���^�����݂��邩�m�F����
	if (m_pPlayer)
	{
		return m_pPlayer->GetPosZ();
	}
	else
	{
		//�����Ă��Ȃ��ꍇ�A0��Ԃ�
		return 0;
	}
}