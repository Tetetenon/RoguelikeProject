#include "UnitManager.h"
#include "Unit.h"				//���j�b�g

#include "EnemyManager.h"


//�ÓI�ϐ��̏�����
UNIT_MAP*		CUnitManager::m_pUnitManager = NULL;

CUnit*	CUnitManager::m_pPlayer = NULL;			//�v���C���[�|�C���^�[
int		CUnitManager::m_nMakeNumber = OBJ_NUM_PLAYER;	//�����������j�b�g�̐�
bool	CUnitManager::m_bMoveCanFlg;			//�ړ��\�t���O


//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CUnitManager::CUnitManager()
{
	//���X�g�̏�����
	m_pUnitManager->clear();

	//�����������j�b�g�̐�������
	m_nMakeNumber = OBJ_NUM_PLAYER;
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CUnitManager::~CUnitManager()
{
	//�����������j�b�g�̐�������
	m_nMakeNumber = OBJ_NUM_PLAYER;

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
		m_pUnitManager = new UNIT_MAP();

		//�G�l�~�[�}�l�[�W���[�̍쐬
		CEnemyManager::Create();
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
		//�G�l�~�[�}�l�[�W���[�̍폜
		CEnemyManager::Destroy();
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
	//ID�ɂ���ēo�^���������肷��
	if (UnitID >= OBJ_NUM_ENEMY)
	{
		//�G�l�~�[�̏ꍇ�A�G�l�~�[�}�l�[�W���[���ɓo�^������
		CEnemyManager::Add(UnitID,pAddUnit);
	}

	else if (UnitID >= OBJ_NUM_PARTY)
	{
		//�p�[�e�B�[�����o�[�̏ꍇ�A�p�[�e�B�[�}�l�[�W���[��
	}
	
	if (UnitID == OBJ_NUM_PLAYER)
	{
		//�v���C���[�̏ꍇ�A���g�̃��X�g�֓o�^����

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
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̍폜
//---------------------------------------------------------------------------------------
void CUnitManager::Del(int UnitID)
{
	//ID�ɂ���č폜����f�[�^�̐��ύX����
	if (UnitID >= OBJ_NUM_ENEMY)
	{
		//�G�l�~�[�̏ꍇ�A�G�l�~�[�}�l�[�W���[���̃f�[�^���폜
		CEnemyManager::Del(UnitID);
	}

	else if (UnitID >= OBJ_NUM_PARTY)
	{
		//�p�[�e�B�[�����o�[�̏ꍇ�A�p�[�e�B�[�}�l�[�W���[��
	}

	if (UnitID == OBJ_NUM_PLAYER)
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
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̒�����A�w�肳�ꂽID�̃��j�b�g��Ԃ�
//---------------------------------------------------------------------------------------
CUnit* CUnitManager::Find(int UnitID)
{
	//ID�ɂ���ĒT�����������肷��
	if (UnitID >= OBJ_NUM_ENEMY)
	{
		//�G�l�~�[�̏ꍇ�A�G�l�~�[�}�l�[�W���[����T��������
		return CEnemyManager::Find(UnitID);
	}

	else if (UnitID >= OBJ_NUM_PARTY)
	{
		//�p�[�e�B�[�����o�[�̏ꍇ�A�p�[�e�B�[�}�l�[�W���[��
	}

	if (UnitID == OBJ_NUM_PLAYER)
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
	return NULL;
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

	//�G�l�~�[�̏�����
	CEnemyManager::Init();
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̍X�V
//---------------------------------------------------------------------------------------
void CUnitManager::Update()
{
	//���݂̃^�[�����j�b�g���擾
	CTurn::UnitTurnState NowTurnUnit = CTurn::GetUnitTurn();

	//�S���j�b�g�̑ҋ@�X�V���s��
	for (auto UnitIterator = m_pUnitManager->begin(); UnitIterator != m_pUnitManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			//�ҋ@��Ԃ̍X�V���s��
			(*ListIterator)->WaitUpdate();
			(*ListIterator)->Update();
		}
	}

	//�G�l�~�[�̑ҋ@�X�V���s��
	CEnemyManager::WaitUpdate();

	//���݂̃^�[�����j�b�g�̃I�u�W�F�N�g�̂݃^�[���̍X�V���s��
	switch (NowTurnUnit)
	{
		//�v���C���[�̃^�[���X�V
	case CTurn::UNIT_TURN_PLAYER:
		for (auto UnitIterator = m_pUnitManager->begin(); UnitIterator != m_pUnitManager->end(); ++UnitIterator)
		{
			for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
			{
				//�^�[���̍X�V���s��
				(*ListIterator)->TurnUpdate();
			}
		}
		break;
		//�p�[�e�B�[�����o�[�̃^�[��
	case CTurn::UNIT_TURN_PARTY:
		break;
		//�G�l�~�[�̃^�[���X�V
	case CTurn::UNIT_TURN_ENEMY:
		CEnemyManager::TurnUpdate();
		break;
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

	//�G�l�~�[�̕`��
	CEnemyManager::Draw();
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

	//�G�l�~�[�}�l�[�W���[�̏I������
	CEnemyManager::Fin();
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