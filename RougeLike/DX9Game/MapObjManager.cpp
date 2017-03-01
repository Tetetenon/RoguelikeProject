#include "MapObjManager.h"

#include"FieldObj.h"

CMapObjManager* CMapObjManager::m_pMapObjManager = NULL;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CMapObjManager::CMapObjManager()
{
	m_pMapObjMap = new FIELDOBJ_MAP();
	//������
	m_pMapObjMap->clear();
	m_bDeleteFlg = false;
	m_nNextObjNumber = 0;
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CMapObjManager::~CMapObjManager()
{
	//�I������
	Fin();
	//�폜
	delete m_pMapObjMap;
	//���g�̑|��
	m_pMapObjMap = NULL;

	//�ϐ��̏�����
	m_bDeleteFlg = false;

	//�v���C���[�|�C���^�̊J��
	m_nNextObjNumber = 0;
}

//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̍쐬
//---------------------------------------------------------------------------------------
void CMapObjManager::Create()
{
	//�}�l�[�W���[���쐬����ĂȂ���΍쐬
	if (!m_pMapObjManager)
	{
		m_pMapObjManager = new CMapObjManager;
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
		delete m_pMapObjManager;
		m_pMapObjManager = NULL;
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̒ǉ�
//---------------------------------------------------------------------------------------
void CMapObjManager::Add(int ObjID,CFieldObj* pAddObj)
{
	//ID�ŃI�u�W�F�N�g�̌���
	auto ObjIterator = m_pMapObjMap->find(ObjID);

	//����ID�̃I�u�W�F�N�g�����ɓo�^����Ă��邩�m�F����
	if (ObjIterator != m_pMapObjMap->end())
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
		m_pMapObjMap->insert(NewObjPair);
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̍폜
//---------------------------------------------------------------------------------------
void CMapObjManager::Del(int ObjID)
{
	//ID�ŃI�u�W�F�N�g�̌���
	auto ObjIterator = m_pMapObjMap->find(ObjID);

	//���̃I�u�W�F�N�g��ID�����݂��Ă�ꍇ�A�폜
	if (ObjIterator != m_pMapObjMap->end())
	{
		auto ListIterator = ObjIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		ObjIterator->second.erase(ListIterator);
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̒�����A�w�肳�ꂽID�̃I�u�W�F�N�g��Ԃ�
//---------------------------------------------------------------------------------------
CFieldObj* CMapObjManager::Find(int ObjID)
{
	//ID�ŃI�u�W�F�N�g�̌���
	auto ObjIterator = m_pMapObjMap->find(ObjID);

	//���̃I�u�W�F�N�g��ID�����݂��Ă�ꍇ�A�f�[�^��Ԃ�
	if (ObjIterator != m_pMapObjMap->end())
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
	auto MapIterator = m_pMapObjMap->begin();

	for (; MapIterator != m_pMapObjMap->end(); ++MapIterator)
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
	auto MapIterator = m_pMapObjMap->begin();

	for (; MapIterator != m_pMapObjMap->end(); ++MapIterator)
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
	//���X�g�̐擪���擾����
	auto MapIterator = m_pMapObjMap->begin();

	//���X�g��̃t�B�[���h�I�u�W�F�N�g�S�Ă̕`�揈�����s��
	for (; MapIterator != m_pMapObjMap->end(); ++MapIterator)
	{
		for (auto ListIterator = MapIterator->second.begin(); ListIterator != MapIterator->second.end(); ++ListIterator)
		{
			//�`�悷��I�u�W�F�N�g�̏�Ƀ��j�b�g�����݂��邩�ǂ����ŁA�`���؂�ւ���
			if ((*ListIterator)->GetNearUnitFlg())
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
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̏I������
//---------------------------------------------------------------------------------------
void CMapObjManager::Fin()
{
	//���X�g�̐擪���擾
	auto MapIterator = m_pMapObjMap->begin();

	for (; MapIterator != m_pMapObjMap->end();++MapIterator)
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
	m_pMapObjMap->clear();
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̃f�o�C�X��n��
//---------------------------------------------------------------------------------------
CMapObjManager* CMapObjManager::GetPointer()
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