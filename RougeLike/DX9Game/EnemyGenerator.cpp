#include "EnemyGenerator.h"
#include "Enemy.h"
#include "Input.h"

#include"Unit.h"
#include"UnitManager.h"
#include "MapData.h"

#define MAKEPERCENTAGE 15

//�ÓI�����o���̒�`
CEnemyGenerator* CEnemyGenerator::m_pEnemyGenerator = NULL;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEnemyGenerator::CEnemyGenerator(CGameScene *pScene):
CMeshObj(pScene)
{

	m_FieldEnemyCounter = 0;
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CEnemyGenerator::~CEnemyGenerator(void)
{
	m_FieldEnemyCounter = 0;
}
//---------------------------------------------------------------------------------------
//���̂̍쐬
//---------------------------------------------------------------------------------------
void CEnemyGenerator::Create(CGameScene *pScene)
{
	//���̂��܂��Ȃ���΍쐬
	if (!m_pEnemyGenerator)
	{
		m_pEnemyGenerator = new CEnemyGenerator(pScene);
	}
}
//---------------------------------------------------------------------------------------
//���̂̍폜
//---------------------------------------------------------------------------------------
void CEnemyGenerator::Delete()
{
	//���̂�����΍폜
	if (m_pEnemyGenerator)
	{
		delete m_pEnemyGenerator;
		m_pEnemyGenerator = NULL;
	}
}
//---------------------------------------------------------------------------------------
//���̂̃|�C���^��n��
//---------------------------------------------------------------------------------------
CEnemyGenerator* CEnemyGenerator::GetPointer()
{
	return m_pEnemyGenerator;
}
//---------------------------------------------------------------------------------------
//�����o�ϐ��̃|�C���^��ݒ�
//---------------------------------------------------------------------------------------
void CEnemyGenerator::SetPointer()
{
	//�|�C���^�̎擾
	m_pMapData = CMapData::GetPointer();

	//�v���C���[�̃|�C���^���擾
	CUnitManager* pUnitManager = CUnitManager::GetPointer();
	m_pPlayer = pUnitManager->GetPlayerPointer();
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CEnemyGenerator::Update()
{
	//�K�w�����擾
	int Hierarchy = m_pMapData->GetHierarchieNum();

	//�^�[���X�e�[�g�����̃X�e�[�g�̍ہA�G�l�~�[���m���Ő�������
	if(m_pPlayer->GetUnitTurnState() == CTurn::GAME_STATE_STAND_BY)
	{
		if (Hierarchy != GameClearNum)
		{
			int nRand = rand() % 100;
			//�t�B�[���h�ɔz�u�ł���ő�G�l�~�[���ɓ��B���Ă��Ȃ�
			if (nRand < MAKEPERCENTAGE && m_FieldEnemyCounter < m_MaxFieldEnemy && !m_bMakeFlg)
			{
				//�G�l�~�[�̐���
				CEnemy::Generation(this);
				//���������Z
				m_FieldEnemyCounter++;
			}

			//���̃^�[���ł̐����m�F��������������
			m_bMakeFlg = true;
		}
	}
	//�X�e�[�g���Ⴆ�΁A�����t���O�������Ă���
	else
	{
		m_bMakeFlg = false;
	}

	//�f�o�b�O�R�}���h(�G�l�~�[����)
	if(CInput::GetKeyPress(DIK_Z) && m_FieldEnemyCounter < m_MaxFieldEnemy)
	{
		CEnemy::Generation(this);
		
		//���������Z
		m_FieldEnemyCounter++;
	}
}

//---------------------------------------------------------------------------------------
//�G�l�~�[�����������Z
//---------------------------------------------------------------------------------------
void CEnemyGenerator::SumMakeEnemyNum()
{
	m_FieldEnemyCounter --;
}
//---------------------------------------------------------------------------------------
//�G�l�~�[�ő吶������ݒ�
//---------------------------------------------------------------------------------------
void CEnemyGenerator::SetMaxGenerator (int nMaxCount)
{
	m_MaxFieldEnemy = nMaxCount;

	//�f�o�b�O�p
	if (DebugMode)
		m_MaxFieldEnemy = 0;
}
//---------------------------------------------------------------------------------------
//�G�l�~�[���������Đݒ�
//---------------------------------------------------------------------------------------
void CEnemyGenerator::ResetMakeEnemyNum ()
{
	m_FieldEnemyCounter = 0;
}
//---------------------------------------------------------------------------------------
//�t�B�[���h��Ƀ����_���ɃG�l�~�[�𐶐�����
//---------------------------------------------------------------------------------------
void CEnemyGenerator::MakeEnemy ()
{
	//��������ݒ�
	int nMakeNum = rand()%8 + 2;

	//�f�o�b�O�p
	if (DebugMode)
		nMakeNum = 0;

	//�K�w�����擾
	int Hierarchy = m_pMapData->GetHierarchieNum();

	//�K�w�����ŏI�K�w�Ȃ�΁A����������̂ɐݒ�
	if (Hierarchy == GameClearNum)
	{
		nMakeNum = 1;
	}

	//����
	for(int i = 0;i < nMakeNum;i++)
	{
		CEnemy::Generation(this);
		//���������Z
		m_FieldEnemyCounter++;
	}
}