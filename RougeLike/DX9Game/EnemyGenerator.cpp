#include "EnemyGenerator.h"
#include "Enemy.h"
#include "Input.h"

#include "Turn.h"

#define MAKEPERCENTAGE 15

//�ÓI�����o���̒�`
int CEnemyGenerator::m_FieldEnemyCounter;			//�t�B�[���h��̃G�l�~�[�̐����J�E���g����
int CEnemyGenerator::m_MaxFieldEnemy;				//�t�B�[���h�̃G�l�~�[�̍ő吶������ݒ�
bool CEnemyGenerator::m_bMakeFlg = false;			//�G�l�~�[���������t���O

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEnemyGenerator::CEnemyGenerator(CGameScene *pScene):
CMeshObj(pScene)
{
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CEnemyGenerator::~CEnemyGenerator(void)
{
}
//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void CEnemyGenerator::Init()
{
	//�e�N���X�̏������Ăяo��
	CMeshObj::Init();

}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CEnemyGenerator::Fin()
{
	//�e�N���X�̏I�������Ăяo��
	CMeshObj::Fin();
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CEnemyGenerator::Update()
{
	//�^�[���X�e�[�g�����̃X�e�[�g�̍ہA�G�l�~�[���m���Ő�������
	if(CTurn::GetState() == CTurn::GameState::GAME_STATE_STAND_BY_PLAYER)
	{
		int nRand = rand()%100;
		//�����m��5%���t�B�[���h�ɔz�u�ł���ő�G�l�~�[���ɓ��B���Ă��Ȃ�
		if(nRand < MAKEPERCENTAGE && m_FieldEnemyCounter < m_MaxFieldEnemy && !m_bMakeFlg)
		{
			//�G�l�~�[�̐���
			CEnemy::Generation(this);
			//���������Z
			m_FieldEnemyCounter++;
		}

		//���̃^�[���ł̐����m�F��������������
		m_bMakeFlg = true;
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
	int nMakeNum = rand()%8;

	//����
	for(int i = 0;i < nMakeNum;i++)
	{
		CEnemy::Generation(this);
		//���������Z
		m_FieldEnemyCounter++;
	}
}