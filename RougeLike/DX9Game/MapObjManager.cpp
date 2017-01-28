#include "MapObjManager.h"

#include"FieldObj.h"
#include"Unit.h"
#include "UnitManager.h"

FIELDOBJ_MAP* CMapObjManager::m_pMapObjManager = NULL;

CUnit*			CMapObjManager::m_pPlayer = NULL;			//�v���C���[�̈ʒu�擾�p
bool			CMapObjManager::m_bDeleteFlg = false;		//�S�I�u�W�F�N�g�폜�t���O
int				CMapObjManager::m_nNextObjNumber = 0;	//���ɐ������ꂽ�I�u�W�F�N�g�ɂ���ԍ�

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CMapObjManager::CMapObjManager()
{
	//������
	m_pMapObjManager->clear();
	m_pPlayer = NULL;
	m_bDeleteFlg = false;
	m_nNextObjNumber = 0;
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CMapObjManager::~CMapObjManager()
{
	//�ϐ��̏�����
	m_bDeleteFlg = false;

	//�v���C���[�|�C���^�̊J��
	m_pPlayer = NULL;
	m_nNextObjNumber = 0;

	//���g�̑|��
	m_pMapObjManager->clear();
}

//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̍쐬
//---------------------------------------------------------------------------------------
void CMapObjManager::Create()
{
	//�}�l�[�W���[���쐬����ĂȂ���΍쐬
	if (!m_pMapObjManager)
	{
		m_pMapObjManager = new FIELDOBJ_MAP();
	}
}

//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̍폜
//---------------------------------------------------------------------------------------
void CMapObjManager::Delete()
{
	//NULL�`�F�b�N
	if (m_pMapObjManager)
	{
		//�I������
		Fin();
		//�폜
		delete m_pMapObjManager;
		//���g�̑|��
		m_pMapObjManager = NULL;
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̒ǉ�
//---------------------------------------------------------------------------------------
void CMapObjManager::Add(int ObjID,CFieldObj* pAddObj)
{
	//ID�ŃI�u�W�F�N�g�̌���
	auto ObjIterator = m_pMapObjManager->find(ObjID);

	//����ID�̃I�u�W�F�N�g�����ɓo�^����Ă��邩�m�F����
	if (ObjIterator != m_pMapObjManager->end())
	{
		//�o�^����Ă��邽�߁A�I�u�W�F�f�[�^�̂ݑ}��
		ObjIterator->second.push_back(pAddObj);
	}
	else
	{
		//ID���o�^����Ă��Ȃ����߁AID,�I�u�W�F�f�[�^�Ƃ��ɓo�^����
		FIELDOBJ_LIST NewObjList;
		NewObjList.push_back(pAddObj);


		FIELDOBJ_PAIR NewObjPair(ObjID,NewObjList);
		m_pMapObjManager->insert(NewObjPair);
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̍폜
//---------------------------------------------------------------------------------------
void CMapObjManager::Del(int ObjID)
{
	//ID�ŃI�u�W�F�N�g�̌���
	auto ObjIterator = m_pMapObjManager->find(ObjID);

	//���̃I�u�W�F�N�g��ID�����݂��Ă�ꍇ�A�폜
	if (ObjIterator != m_pMapObjManager->end())
	{
		auto ListIterator = ObjIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		ObjIterator->second.erase(ListIterator);
		//m_pMapObjManager->erase(ObjIterator);
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̒�����A�w�肳�ꂽID�̃I�u�W�F�N�g��Ԃ�
//---------------------------------------------------------------------------------------
CFieldObj* CMapObjManager::Find(int ObjID)
{
	//ID�ŃI�u�W�F�N�g�̌���
	auto ObjIterator = m_pMapObjManager->find(ObjID);

	//���̃I�u�W�F�N�g��ID�����݂��Ă�ꍇ�A�f�[�^��Ԃ�
	if (ObjIterator != m_pMapObjManager->end())
	{
		return ObjIterator->second[0];
	}
	else
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̏�����
//---------------------------------------------------------------------------------------
void CMapObjManager::Init()
{
	//���X�g�̐擪���擾
	auto MapIterator = m_pMapObjManager->begin();

	for (; MapIterator != m_pMapObjManager->end(); ++MapIterator)
	{
		for (auto ListIterator = MapIterator->second.begin(); ListIterator != MapIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Init();
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̍X�V
//---------------------------------------------------------------------------------------
void CMapObjManager::Update()
{
	//���X�g�̐擪���擾
	auto MapIterator = m_pMapObjManager->begin();

	for (; MapIterator != m_pMapObjManager->end(); ++MapIterator)
	{
		for (auto ListIterator = MapIterator->second.begin(); ListIterator != MapIterator->second.end();)
		{
			//�폜�t���O�������Ă����ꍇ�A�폜�������s��
			if (m_bDeleteFlg)
			{
				//�폜����
				(*ListIterator)->Fin();
				delete (*ListIterator);
				ListIterator = MapIterator->second.erase(ListIterator);
			}
			else
			{
				//�X�V
				(*ListIterator)->Update();
				 ListIterator++;
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̕`��
//---------------------------------------------------------------------------------------
void CMapObjManager::Draw(bool Alpha)//Alpha:�������`������邩
{
	//�v���C���[�̈ʒu
	D3DXVECTOR3 PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�v���C���[�̃|�C���^�����݂��邩�m�F����
	if (m_pPlayer)
	{
		//�v���C���[�̈ʒu���擾����
		PlayerPos = m_pPlayer->GetPos();
	}


	//���X�g�̐擪���擾����
	auto MapIterator = m_pMapObjManager->begin();

	//���X�g��̃t�B�[���h�I�u�W�F�N�g�S�Ă̕`�揈�����s��
	for (; MapIterator != m_pMapObjManager->end(); ++MapIterator)
	{
		for (auto ListIterator = MapIterator->second.begin(); ListIterator != MapIterator->second.end(); ++ListIterator)
		{
			//�v���C���[�̃|�C���^�����݂��Ă��Ȃ��ꍇ�A�`�揈�������ׂĕs�����ōs��
			if (!m_pPlayer)
			{
				if(!Alpha)
					(*ListIterator)->Draw();
			}
			else
			{
				//�I�u�W�F�N�g�̈ʒu�ƁA�v���C���[�̈ʒu�̋������v�Z����
				//�I�u�W�F�N�g�̈ʒu���擾
				D3DXVECTOR3 ObjPos = (*ListIterator)->GetPos();

				//�I�u�W�F�N�g�̈ʒu�ƃv���C���[�̈ʒu�̔�r
				float DistanceX = abs(ObjPos.x - PlayerPos.x);
				float DistanceZ = ObjPos.z - PlayerPos.z;

				//�������`��t���O
				bool AlphaDrawFlg = true;

				//���g�̈ʒu�ƁA�v���C���[�̈ʒu���߂���΁A���f���𔼓����̕��ɕύX����
				if (DistanceX <= GRIDSIZE)
				{
					if (DistanceZ < 0 && DistanceZ > -GRIDSIZE * 1.5)
					{
						if (Alpha)
							(*ListIterator)->DrawAlpha();
					}
					else
					{
						if (!Alpha)
							(*ListIterator)->Draw();
					}
				}
				else
				{
					if (!Alpha)
						(*ListIterator)->Draw();
				}
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̏I������
//---------------------------------------------------------------------------------------
void CMapObjManager::Fin()
{
	//���X�g�̐擪���擾
	auto MapIterator = m_pMapObjManager->begin();

	for (; MapIterator != m_pMapObjManager->end();++MapIterator)
	{
		for (auto ListIterator = MapIterator->second.begin(); ListIterator != MapIterator->second.end();)
		{
			//�I������
			(*ListIterator)->Fin();
			delete(*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = MapIterator->second.erase(ListIterator);
		}
	}

	//���X�g��|��
	m_pMapObjManager->clear();
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̃f�o�C�X��n��
//---------------------------------------------------------------------------------------
FIELDOBJ_MAP* CMapObjManager::GetPointer()
{
	return m_pMapObjManager;
}
//---------------------------------------------------------------------------------------
//�t�B�[���h�I�u�W�F�N�g�̍폜�t���O��ύX����
//---------------------------------------------------------------------------------------
void CMapObjManager::ChangeDeleteFlg(bool ChangeFlg)
{
	m_bDeleteFlg = ChangeFlg;
}
//---------------------------------------------------------------------------------------
//�v���C���[�̃|�C���^��ݒ肷��
//---------------------------------------------------------------------------------------
void CMapObjManager::PlayerSet()
{
	//�v���C���[�ւ̃|�C���^���擾����
	m_pPlayer = CUnitManager::Find(OBJ_NUM_PLAYER);
}