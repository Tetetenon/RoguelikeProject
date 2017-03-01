#include "ParticleManager.h"

#include"Particle.h"

//�ÓI�ϐ��錾
CParticleManager*	CParticleManager::m_pParticleManager = NULL;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CParticleManager::CParticleManager()
{
	//���X�g�̍쐬
	m_pParticleMap = new PARTICLE_MAP();
	//������
	m_nNextID = 0;

	//���X�g������
	m_pParticleMap->clear();
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CParticleManager::~CParticleManager()
{
	//������
	m_nNextID = 0;

	//�I������
	Fin();
	//�폜
	delete m_pParticleMap;
	//���g�̑|��
	m_pParticleMap = NULL;
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̍쐬
//---------------------------------------------------------------------------------------
void CParticleManager::Create()
{
	//�}�l�[�W���[�|�C���^�̒��g���܂��Ȃ���΍쐬����
	if (!m_pParticleManager)
	{
		m_pParticleManager = new CParticleManager;
	}
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̍폜
//---------------------------------------------------------------------------------------
void CParticleManager::Delete()
{
	//NULL�`�F�b�N
	if (m_pParticleManager)
	{
		delete m_pParticleManager;
		m_pParticleManager = NULL;
	}
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̎��̂�n��
//---------------------------------------------------------------------------------------
CParticleManager* CParticleManager::GetPointer()
{
	//�O�̂��ߍ쐬�֐����Ă�
	Create();
	return m_pParticleManager;
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̒ǉ�
//---------------------------------------------------------------------------------------
void CParticleManager::Add(int ID, CParticle* pAdd)
{
	//ID�����ɓo�^����Ă��邩�m�F���s��
	auto ParticleIterator = m_pParticleMap->find(ID);

	//����ID���o�^����Ă��邩�m�F���s��
	if (ParticleIterator != m_pParticleMap->end())
	{
		//ID�����ɓo�^����Ă��邽�߁A�I�u�W�F�N�g�f�[�^�̂ݓo�^
		ParticleIterator->second.push_back(pAdd);
	}
	else
	{
		//ID���o�^���s���Ă��Ȃ����߁AID,�I�u�W�F�N�g�f�[�^�Ƃ��ɓo�^���s��
		PARTICLE_LIST NewList;
		NewList.push_back(pAdd);

		PARTICLE_PAIR NewParticlePair(ID,NewList);
		m_pParticleMap->insert(NewParticlePair);
	}
}

//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̍폜
//---------------------------------------------------------------------------------------
void CParticleManager::Del(int ID)
{
	//ID�ŃI�u�W�F�N�g�̌���
	auto ParticleIterator = m_pParticleMap->find(ID);

	//���������I�u�W�F�N�g�����݂��Ă����ꍇ�A�폜���s��
	if (ParticleIterator != m_pParticleMap->end())
	{
		auto ListIterator = ParticleIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		ParticleIterator->second.erase(ListIterator);
	}
}

//---------------------------------------------------------------------------------------
//�Ǘ�����I�u�W�F�N�g����A�w�肳�ꂽID�̃I�u�W�F�N�g��Ԃ�
//---------------------------------------------------------------------------------------
CParticle* CParticleManager::Find(int ID)
{
	//ID�ŃI�u�W�F�N�g�̒T��
	auto ParticleIterator = m_pParticleMap->find(ID);

	//����ID�̃I�u�W�F�N�g�����݂��Ă���ꍇ�A�f�[�^��Ԃ�
	if (ParticleIterator != m_pParticleMap->end())
	{
		return ParticleIterator->second[0];
	}
	else
	{
		//�f�[�^�����݂��Ă��Ȃ��ꍇNULL��Ԃ�
		return NULL;
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̏�����
//---------------------------------------------------------------------------------------
void CParticleManager::Init()
{
	//���X�g�̐擪���擾
	auto ParticleIterator = m_pParticleMap->begin();

	for (; ParticleIterator != m_pParticleMap->end(); ++ParticleIterator)
	{
		for (auto ListIterator = ParticleIterator->second.begin(); ListIterator != ParticleIterator->second.end();)
		{
			//������
			(*ListIterator)->Init();
			ListIterator++;
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̍X�V
//---------------------------------------------------------------------------------------
void CParticleManager::Update()
{
	//���X�g�̐擪���擾
	auto ParticleIterator = m_pParticleMap->begin();

	for (; ParticleIterator != m_pParticleMap->end(); ++ParticleIterator)
	{
		for (auto ListIterator = ParticleIterator->second.begin(); ListIterator != ParticleIterator->second.end();)
		{
			//�X�V
			(*ListIterator)->Update();

			//�폜�t���O�������Ă��邩�m�F
			if ((*ListIterator)->GetDeleteFlg())
			{
				//�����Ă�����A�폜���s��
				//�폜����
				(*ListIterator)->Fin();
				delete (*ListIterator);
				ListIterator = ParticleIterator->second.erase(ListIterator);
			}
			else
			{
				//�����Ă��Ȃ���΁A���̃I�u�W�F�N�g�̏������s��
				ListIterator++;
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̕`��
//---------------------------------------------------------------------------------------
void CParticleManager::Draw()
{
	//���X�g�̐擪���擾
	auto ParticleIterator = m_pParticleMap->begin();

	for (; ParticleIterator != m_pParticleMap->end(); ++ParticleIterator)
	{
		for (auto ListIterator = ParticleIterator->second.begin(); ListIterator != ParticleIterator->second.end();)
		{
			//�`��
			(*ListIterator)->DrawAlpha();
			ListIterator++;
		}
	}
}
//---------------------------------------------------------------------------------------
//�Ǘ��I�u�W�F�N�g�̏I������
//---------------------------------------------------------------------------------------
void CParticleManager::Fin()
{
	//���X�g�̐擪���擾
	auto ParticleIterator = m_pParticleMap->begin();

	for (; ParticleIterator != m_pParticleMap->end(); ++ParticleIterator)
	{
		for (auto ListIterator = ParticleIterator->second.begin(); ListIterator != ParticleIterator->second.end();)
		{
			//�I������
			(*ListIterator)->Fin();
			delete(*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = ParticleIterator->second.erase(ListIterator);
		}
	}

	//���X�g�̑|��
	m_pParticleMap->clear();
}