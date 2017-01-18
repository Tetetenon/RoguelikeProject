#include "EffectObjManager.h"
#include "EffectObj.h"


//�ÓI�ϐ��̏�����
EFFECTOBJ_MAP*	CEffectObjManager::m_pEffectManager = NULL;
int				CEffectObjManager::m_nEffectNumber = 0;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEffectObjManager::CEffectObjManager()
{
	//���X�g�̏�����
	m_pEffectManager->clear();

	//�ϐ��̏�����
	m_nEffectNumber = 0;
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CEffectObjManager::~CEffectObjManager()
{
	//���X�g�̏�����
	m_pEffectManager->clear();

	//�ϐ��̏�����
	m_nEffectNumber = 0;
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̍쐬
//---------------------------------------------------------------------------------------
void CEffectObjManager::Create()
{
	//�܂��쐬������Ă��Ȃ��ꍇ�A�쐬����
	if (!m_pEffectManager)
	{
		m_pEffectManager = new EFFECTOBJ_MAP;
	}
}

//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̍폜
//---------------------------------------------------------------------------------------
void CEffectObjManager::Delete()
{
	//NULL�`�F�b�N
	if (m_pEffectManager)
	{
		//�I������
		Fin();
		//�폜
		delete m_pEffectManager;
		//���g�����ꂢ��
		m_pEffectManager = NULL;
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̒ǉ�
//---------------------------------------------------------------------------------------
void CEffectObjManager::Add(int ID, CEffectObj* pAdd)
{
	//ID�����ɓo�^������Ă��邩�m�F���s��
	auto EfectIterator = m_pEffectManager->find(ID);

	//����ID�����ɓo�^����Ă��邩�m�F���s��
	if (EfectIterator != m_pEffectManager->end())
	{
		//����ID���o�^����Ă��邽�߁A�I�u�W�F�f�[�^�݂̂����̏ꏊ�ɓo�^����
		EfectIterator->second.push_back(pAdd);
	}
	else
	{
		//ID���o�^������Ă��Ȃ����߁A�����̃f�[�^��o�^����
		EFFECTOBJ_LIST NewList;
		NewList.push_back(pAdd);

		EFFECTOBJ_PAIR NewEffectPair(ID, NewList);
		m_pEffectManager->insert(NewEffectPair);
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̍폜
//---------------------------------------------------------------------------------------
void CEffectObjManager::Del(int ID)
{
	//ID�ŃI�u�W�F�N�g�̌���
	auto EffectIterator = m_pEffectManager->find(ID);

	//���̃I�u�W�F�N�g�����݂��Ă���ꍇ�A�폜
	if (EffectIterator != m_pEffectManager->end())
	{
		auto ListIterator = EffectIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		EffectIterator->second.erase(ListIterator);
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g������A�w�肳�ꂽID�̃I�u�W�F�N�g��Ԃ�
//---------------------------------------------------------------------------------------
CEffectObj* CEffectObjManager::Find(int ID)
{
	//ID�ŃI�u�W�F�N�g�̌������s��
	auto EffectIterator = m_pEffectManager->find(ID);

	//���̎w�肳�ꂽID�̃f�[�^�����݂���ꍇ�A�f�[�^��Ԃ�
	if (EffectIterator != m_pEffectManager->end())
	{
		return EffectIterator->second[0];
	}
	else
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̏�����
//---------------------------------------------------------------------------------------
void CEffectObjManager::Init()
{
	//���X�g�̐擪���擾
	auto EffectIterator = m_pEffectManager->begin();

	for (; EffectIterator != m_pEffectManager->end(); ++EffectIterator)
	{
		for (auto ListIterator = EffectIterator->second.begin(); ListIterator != EffectIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Init();
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̍X�V
//---------------------------------------------------------------------------------------
void CEffectObjManager::Update()
{
	//���X�g�̐擪���擾
	auto EffectIterator = m_pEffectManager->begin();

	for (; EffectIterator != m_pEffectManager->end(); ++EffectIterator)
	{
		for (auto ListIterator = EffectIterator->second.begin(); ListIterator != EffectIterator->second.end();)
		{
			//�X�V
			(*ListIterator)->Update();

			//�c��̐������Ԃ������Ȃ�΁A�폜
			if ((*ListIterator)->GetLifeTime() <= 0)
			{
				//�폜����
				(*ListIterator)->Fin();
				delete (*ListIterator);
				ListIterator = EffectIterator->second.erase(ListIterator);

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
//�Ǘ�����I�u�W�F�N�g�̕`��
//---------------------------------------------------------------------------------------
void CEffectObjManager::Draw()
{
	//���X�g�̐擪���擾
	auto EffectIterator = m_pEffectManager->begin();

	for (; EffectIterator != m_pEffectManager->end(); ++EffectIterator)
	{
		for (auto ListIterator = EffectIterator->second.begin(); ListIterator != EffectIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Draw();
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g�̏I������
//---------------------------------------------------------------------------------------
void CEffectObjManager::Fin()
{
	//���X�g�̐擪���擾
	auto EffectIterator = m_pEffectManager->begin();

	for (; EffectIterator != m_pEffectManager->end(); ++EffectIterator)
	{
		for (auto ListIterator = EffectIterator->second.begin(); ListIterator != EffectIterator->second.end();)
		{
			(*ListIterator)->Fin();
			delete (*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = EffectIterator->second.erase(ListIterator);
		}
	}
	//���X�g�̑|��
	m_pEffectManager->clear();
}