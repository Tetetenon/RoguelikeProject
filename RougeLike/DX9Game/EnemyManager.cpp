#include "EnemyManager.h"
#include "Unit.h"

//�ÓI�ϐ��錾
UNIT_MAP*	CEnemyManager::m_pEnemyManager = NULL;
int			CEnemyManager::m_NowProcUnitID = 0;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEnemyManager::CEnemyManager()
{
	//���X�g�̏�����
	m_pEnemyManager->clear();

	//�U�����イ�̃G�l�~�[�̔ԍ��̏�����
	m_NowProcUnitID = 0;
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CEnemyManager::~CEnemyManager()
{
	//���X�g�̏�����
	m_pEnemyManager->clear();

	//�U�����イ�̃G�l�~�[�̔ԍ��̏�����
	m_NowProcUnitID = 0;
}

//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̍쐬
//---------------------------------------------------------------------------------------
void CEnemyManager::Create()
{
	//�܂��쐬���s���Ă��Ȃ������ꍇ�A��������
	if (!m_pEnemyManager)
	{
		m_pEnemyManager = new UNIT_MAP();
	}
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̍폜
//---------------------------------------------------------------------------------------
void CEnemyManager::Destroy()
{
	//NULL�̃`�F�b�N
	if (m_pEnemyManager)
	{
		//���g�����݂���΍폜

		//�I������
		Fin();
		//�폜
		delete m_pEnemyManager;
		//���g�����ꂢ��
		m_pEnemyManager = NULL;
	}
}

//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̒ǉ�
//---------------------------------------------------------------------------------------
void CEnemyManager::Add(int UnitID,CUnit* pAddUnit)
{
	//ID�����ɓo�^����Ă��邩�ǂ����m�F����
	auto UnitIterator = m_pEnemyManager->find(UnitID);

	//����ID���o�^����Ă��邩�ǂ����ŏ�����ύX����
	if (UnitIterator != m_pEnemyManager->end())
	{
		//ID�����ɓo�^����Ă����Ԃ̂��߁A���̈ʒu�ɃI�u�W�F�N�g�f�[�^���i�[����
		UnitIterator->second.push_back(pAddUnit);
	}
	else
	{
		//ID���o�^����Ă��Ȃ����߁A�����̃f�[�^��o�^����
		UNIT_LIST NewUnitList;
		NewUnitList.push_back(pAddUnit);

		UNIT_PAIR NewUnitPair(UnitID, NewUnitList);
		m_pEnemyManager->insert(NewUnitPair);
	}
}

//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̍폜
//---------------------------------------------------------------------------------------
void CEnemyManager::Del(int UnitID)
{
	//ID�ŃI�u�W�F�N�g�̑F�����s��
	auto UnitIterator = m_pEnemyManager->find(UnitID);

	//�w�肳�ꂽ�I�u�W�F�N�gID�̃f�[�^�����݂��Ă���ꍇ�A���̃f�[�^���폜����
	if (UnitIterator != m_pEnemyManager->end())
	{
		auto ListIterator = UnitIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		UnitIterator->second.erase(ListIterator);
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̃f�[�^��Ԃ�
//---------------------------------------------------------------------------------------
CUnit* CEnemyManager::Find(int UnitID)
{
	//ID�ŃI�u�W�F�N�g�̌������s��
	auto UnitIterator = m_pEnemyManager->find(UnitID);

	//���̎w�肳�ꂽID�̃f�[�^�����݂���ꍇ�A�f�[�^��Ԃ�
	if (UnitIterator != m_pEnemyManager->end())
	{
		return UnitIterator->second[0];
	}
	else
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̏�����
//---------------------------------------------------------------------------------------
void CEnemyManager::Init()
{
	//���X�g�̐擪���擾
	auto UnitIterator = m_pEnemyManager->begin();

	for (; UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Init();
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̑ҋ@�X�V
//---------------------------------------------------------------------------------------
void CEnemyManager::WaitUpdate()
{
	for (auto UnitIterator = m_pEnemyManager->begin(); UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			//�ҋ@��Ԃ̍X�V���s��
			(*ListIterator)->WaitUpdate();
			(*ListIterator)->Update();
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̃^�[���X�V
//---------------------------------------------------------------------------------------
void CEnemyManager::TurnUpdate()
{
	//�S���j�b�g�̃^�[���������I��������
	bool bAllUnitUpdateEndFlg = true;

	for (auto UnitIterator = m_pEnemyManager->begin(); UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			//�^�[���������I�����Ă��Ȃ���Ώ������s��
			if (!(*ListIterator)->GetTurnEndFlg())
			{
				//�S�Ẵ��j�b�g�̍X�V���܂��I�����Ă��Ȃ�
				bAllUnitUpdateEndFlg = false;

				//�^�[���X�e�[�g�ɂ���čX�V���e��ύX����
				switch ((*ListIterator)->GetUnitTurnState())
				{
					//���͑҂�
				case CTurn::GAME_STATE_STAND_BY:
					(*ListIterator)->InputUpdate();
					break;
					//�A�C�e���̎g�p
				case CTurn::GAME_STATE_ITEM_USE:
					(*ListIterator)->ItemUpdate();
					break;
					//�ړ�
				case CTurn::GAME_STATE_MOVE:
					(*ListIterator)->MoveUpdate();
					break;
					//�s��
				case CTurn::GAME_STATE_ACT:
					(*ListIterator)->ActUpdate();
					break;
					//�U��
				case CTurn::GAME_STATE_ATTACK:
					//���݂̍U���X�V���j�b�g�̔ԍ������g�ł���A���͒N���������s���Ă��Ȃ���΍X�V
					if (m_NowProcUnitID == (*ListIterator)->GetNumber() || m_NowProcUnitID == 0)
					{
						//���g���������s���Ă���ƁA�o�^����
						m_NowProcUnitID = (*ListIterator)->GetNumber();
						//�U���̍X�V���I�������ꍇ�A�����Ԃ�
						if ((*ListIterator)->AttackUpdate())
							m_NowProcUnitID = 0;
					}
					break;
					//�^�[���I������
				case CTurn::GAME_STATE_TURN_END:
					(*ListIterator)->TurnEndUpdate();
					break;
				default:
					break;
				}
			}
		}
	}
	//�S�Ẵ��j�b�g�̍X�V���I�����Ă����ꍇ�A�X�e�[�g��ύX����
	if (bAllUnitUpdateEndFlg)
	{
		for (auto UnitIterator = m_pEnemyManager->begin(); UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
		{
			for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
			{
				//���j�b�g�̃^�[���̏�����Ԃ�������
				(*ListIterator)->setTurnEndFlg(false);
			}
		}

		//�X�e�[�g�̕ύX
		CTurn::ChangeUnitState(CTurn::UNIT_TURN_PLAYER);
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̕`��
//---------------------------------------------------------------------------------------
void CEnemyManager::Draw()
{
	//���X�g�̐擪���擾
	auto UnitIterator = m_pEnemyManager->begin();

	for (; UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Draw();
		}
	}

	//�r���{�[�h�̕`��
	UnitIterator = m_pEnemyManager->begin();
	
	for (; UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->BillBordDraw();
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̏I������
//---------------------------------------------------------------------------------------
void CEnemyManager::Fin()
{
	//���X�g�̐擪���擾;
	for (auto UnitIterator = m_pEnemyManager->begin();UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end();)
		{
			(*ListIterator)->Fin();
			delete (*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = UnitIterator->second.erase(ListIterator);
		}
	}
	m_NowProcUnitID = 0;
	//���X�g�̑|��
	m_pEnemyManager->clear();
}