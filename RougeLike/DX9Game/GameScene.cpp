//=======================================================================================
//
//	  �Q�[���V�[�� �N���X
//
//=======================================================================================

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include "define.h"
#include "GameScene.h"
#include "Input.h"

#include "Enemy.h"
#include "Item.h"
#include "FieldObj.h"
#include "ModelManager.h"
#include "Turn.h"
#include "Player.h"
#include "GameState.h"

#include"UnitManager.h"
#include "EnemyGenerator.h"
#include"ItemManager.h"
#include"MapObjManager.h"
#include"ParticleManager.h"
#include"EffectObjManager.h"
#include"EnemyManager.h"
#include "UIManager.h"
#include "Fade.h"					//�t�F�[�h�A�E�g
#include "HierarchieNum.h"			//�K�w���\��
#include "DamageBillBoardManager.h"

bool	CGameScene::m_MapMake = false;
bool	CGameScene::m_OldMapMake = false;
int		CGameScene::m_nPlayerLevel = 0;

int	CGameScene::m_nGameClaer = 0;	//�Q�[�����N���A�ł�����

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CGameScene::CGameScene():
	m_pGraph(NULL),
	m_FPS()
{
	//�f�o�b�O�����̏�����
	m_szDebug[0] = _T('\0');

	//�Q�[���̃N���A��Ԃ̏�����
	m_nGameClaer = 0;

	srand((unsigned int)time(NULL));			//���Ԃŗ����̏��������s��


	//�V���O���g���̍쐬
	CCamera::Create(this);
	CSky::Create(this);
	CUnitManager::Create();
	CItemManager::Create();
	CMapObjManager::Create();
	CParticleManager::Create();
	CEffectObjManager::Create();
	CDamageBillBoardManager::Create();
	CEnemyGenerator::Create(this);
	CFade::Create();
	CHierarchieNum::Create();
	CUIManager::Create();
	CMapData::Create();


	//�V���O���g���̃|�C���^�̎擾
	m_pCamera			= CCamera::GetPointer();					//�J����
	m_pSky				= CSky::GetPointer();						//�X�J�C�h�[��
	m_pUnitManager		= CUnitManager::GetPointer();
	m_pFieldItemManager = CItemManager::GetPointer();
	m_pMapObjManager	= CMapObjManager::GetPointer();
	m_pParticleManager	= CParticleManager::GetPointer();
	m_pEffectManager	= CEffectObjManager::GetPointer();
	m_pDamageManager	= CDamageBillBoardManager::GetPointer();	//�_���[�W�\�L�}�l�[�W���[
	m_pEnemyGenerator	= CEnemyGenerator::GetPointer();	//�G�l�~�[�W�F�l���[�^�[
	m_pFade				= CFade::GetPointer();						//�t�F�[�h�A�E�g
	m_pHierarchieNum	= CHierarchieNum::GetPointer();				//�K�w���\��
	m_pUIManager		= CUIManager::GetPointer();
	m_pMap				= CMapData::GetPointer();				//�}�b�v�f�[�^


	//�����o�N���X�̃R���X�g���N�^���N��
	m_pFieldObjMaker	= new CFieldObjMaker(this);		//�t�B�[���h�I�u�W�F�N�g
	m_pTurn				= new CTurn();					//�^�[��
	m_pFieldGenerator	= new CItemGenerator(this);		//�t�B�[���h�A�C�e������
	m_pPlayer			= new CPlayer(this);			//�v���C���[

	//�e�N���X�̃����o�̃|�C���^���Z�b�g����
	m_pUIManager			->ManageUISetPointer();
	m_pEnemyGenerator		->SetPointer();
	m_pHierarchieNum		->SetPointer();
	m_pMap					->SetPointer();

	//�}�b�v�̐���
	m_pMap->MapGeneration();
	//�v���C���[�̈ʒu��ݒ肷��
	m_pPlayer->SetPos();
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CGameScene::~CGameScene()
{
	//�V���O���g���̍폜
	CCamera::Delete();
	CSky::Delete();
	CUnitManager::Delete();
	CItemManager::Delete();
	CMapObjManager::Delete();
	CParticleManager::Delete();
	CEffectObjManager::Delete();
	CDamageBillBoardManager::Delete();
	CFade::Delete();
	CHierarchieNum::Delete();
	CFade::Delete();
	CHierarchieNum::Delete();
	CMapData::Delete();
	CEnemyGenerator::Delete();
	CUIManager::Delete();
	//�V���O���g���̃|�C���^�̒��g�����ꂢ��
	m_pCamera	= NULL;			//�J����
	m_pSky		= NULL;			//�X�J�C�h�[��
	m_pDamageManager = NULL;	//�_���[�W�\�L

	//�����o�N���X�̃|�C���^������
	delete m_pFieldObjMaker;	//�t�B�[���h�I�u�W�F����
	delete m_pTurn;				//�^�[��
	delete m_pFieldGenerator;	//�t�B�[���h�A�C�e��

	m_nGameClaer = 0;

	//�v���C���[�̃|�C���^�����
	if (m_pPlayer)
	{
		m_pPlayer = NULL;
	}
}

//---------------------------------------------------------------------------------------
// �V�[������
//---------------------------------------------------------------------------------------
CGameScene* CGameScene::Create(CGraphics* pGraph)
{
	//�V�[���̃��������m�ۂ���
	CGameScene* pGameScene = new CGameScene();
	//�V�[���������m�ۂɐ���������A���������s��
	if (pGameScene) {
		if (!pGameScene->Initialize(pGraph)) {
			SAFE_DELETE(pGameScene);
		}
	}
	return pGameScene;
}

//---------------------------------------------------------------------------------------
// �f�o�C�X�A���\�[�X������
//---------------------------------------------------------------------------------------
bool CGameScene::Initialize(CGraphics* pGraph)
{
	m_pGraph = pGraph;

	//-------- �Q�[���p�I�u�W�F�N�g�̏�����

	//���f���f�[�^�̓ǂݍ���
	CModelManager::LoadMesh();

	//�e��I�u�W�F�N�g�̏�����
	InitObj();
	return true;
}

//---------------------------------------------------------------------------------------
// �f�o�C�X�A���\�[�X���
//---------------------------------------------------------------------------------------
void CGameScene::Finalize()
{
	//-------- �Q�[���p�I�u�W�F�N�g�̌�n��

	//���f���f�[�^�̊J��
	CModelManager::ReleaseMesh();

	//�I�u�W�F�N�g�̏I������
	FinObj();
}

//---------------------------------------------------------------------------------------
// �V�[�����
//---------------------------------------------------------------------------------------
void CGameScene::Release()
{
	//�g�p���Ă���N���X�̏I���������s��
	Finalize();
	//�V�[���N���X�̍폜���s��
	delete this;
}

//---------------------------------------------------------------------------------------
// �Q�[���`�揈���i���C�����[�v����R�[�������j
//---------------------------------------------------------------------------------------
void CGameScene::Render()
{
	if (m_pGraph->Begin())
	{
		// �`��J�n

		Draw();					// �`�揈��

		m_pGraph->End();		// �`��I��
	}
	m_pGraph->SwapBuffer();		// �o�b�N�o�b�t�@����
}

//---------------------------------------------------------------------------------------
// �Q�[�����C�������i���C�����[�v����R�[�������j
//---------------------------------------------------------------------------------------
void CGameScene::Update()
{
	// ���͍X�V
	CInput::Update();

	//----- �����ɃQ�[���{�̏���
	UpdateObj();
}

//---------------------------------------------------------------------------------------
// �`�揈���iCGraphics::Render() ����R�[�������j
//---------------------------------------------------------------------------------------
void CGameScene::Draw()
{
	//�f�o�b�O���[�h�̂ݕ`��
	if (DebugMode)
	{
		m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���

		// FPS ����ʂɕ`�悷�邽�߂̕�������쐬
		TCHAR	str[256];
		_stprintf(str, _T("FPS = %d\n"), m_FPS);
		lstrcat(m_szDebug, str);
	}
	//----- �����ɕ`�揈��
	DrawObj();

	// �f�o�b�O������`��
	m_pGraph->DrawText(0, 0, m_szDebug);
}
//---------------------------------------------------------------------------------------
//�S�I�u�W�F�N�g������
//---------------------------------------------------------------------------------------
void CGameScene::InitObj()
{
	//�}�b�v�̏�����
	m_pMap ->Init();

	//�S�ẴI�u�W�F�N�g�̏�����
	m_pFieldItemManager->Init();//�A�C�e���}�l�[�W���[�̊Ǘ��I�u�W�F�N�g�̏�����
	m_pUnitManager->Init();		//���j�b�g�}�l�[�W���[�̊Ǘ��I�u�W�F�N�g�̏�����
	m_pMapObjManager->Init();	//�t�B�[���h�I�u�W�F�}�l�[�W���[�̊Ǘ��I�u�W�F�N�g�̏�����
	m_pParticleManager->Init();	//�p�[�e�B�N���}�l�[�W���[�̏�����
	m_pEffectManager->Init();	//�G�t�F�N�g�}�l�[�W���[�̏�����

	//�J�����̏�����
	m_pCamera->Init();
	//�X�J�C�h�[���̏�����
	m_pSky->Init();

	//���̎��_�̃v���C���[�̃��x�����擾����
	m_nPlayerLevel = m_pPlayer->GetLevel();

	//�����z�u�G�l�~�[�̐ݒ�
	m_pEnemyGenerator ->MakeEnemy();

	//�����z�u�A�C�e���̐ݒ�
	m_pFieldGenerator->MakeItem();

	//�z���񂩂�A�I�u�W�F�N�g��u���ׂ��ʒu�ɃI�u�W�F�N�g��ݒu
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			switch (m_pMap->Get_TerrainMapSituation(i, j))
			{
			case WALL:
				m_pFieldObjMaker->PutObj(MODEL_TREE, i, j);
				break;
			case STAIRS:
				m_pFieldObjMaker->PutObj(MODEL_STAIRS, i, j);
				break;
			case HOME:
				m_pFieldObjMaker->PutObj(MODEL_HOME, i, j);
				break;

			}
		}
	}

	//�t�F�[�h�̏�Ԃ��t�F�[�h�C���ɐݒ�
	m_pFade->ChangeState(FADEMODE_IN);
	//���j�b�g���ꎞ�s���s�\��Ԃɐݒ�
	m_pUnitManager->ChangeMoveCanFlg(false);
}
//---------------------------------------------------------------------------------------
//�S�I�u�W�F�N�g�j��
//---------------------------------------------------------------------------------------
void CGameScene::FinObj()
{
	//�r���Ń��X�g���ς��\�����l�����A�ޔ�p�|�C���^������

	//�e�}�l�[�W���[�ŊǗ�����I�u�W�F�N�g�̏I���������s��
	m_pUnitManager->Fin();
	m_pFieldItemManager->Fin();
	m_pMapObjManager->Fin();
	m_pParticleManager->Fin();
	m_pEffectManager->Fin();

	m_pDamageManager->ManagerObjFin();

	//�}�b�v�f�[�^�̏I������
	m_pMap->Fin();
}
//---------------------------------------------------------------------------------------
//�S�I�u�W�F�N�g�X�V
//---------------------------------------------------------------------------------------
void CGameScene::UpdateObj()
{
	//�}�b�v�̍Đ����t���O�������Ă����珈��
	if(m_MapMake && m_OldMapMake)
	{
		//UI�̃f�[�^��������
		m_pUIManager->ManageUIInit();

		//�t�F�[�h�A�E�g�t���O�𗧂Ă�
		m_pFade->ChangeState(FADEMODE_OUT);

		//�}�b�v�f�[�^�̍Đ���
		m_pMap->MapGeneration();

		//�t�B�[���h�I�u�W�F�N�g�폜
		m_pMapObjManager->Fin();
		//�G�l�~�[�I�u�W�F�N�g�폜
		m_pUnitManager->EnemyDelete();
		//�A�C�e���I�u�W�F�N�g�̍폜
		m_pFieldItemManager->Fin();
		//�p�[�e�B�N���I�u�W�F�N�g�̍폜
		m_pParticleManager->Fin();
		//�G�t�F�N�g�I�u�W�F�N�g�̍폜
		m_pEffectManager->Fin();
		
		//�z���񂩂�A�I�u�W�F�N�g��u���ׂ��ʒu�ɃI�u�W�F�N�g��ݒu
		for(int i = 0;i < MAP_SIZE;i++)
		{
			for(int j = 0;j < MAP_SIZE;j++)
			{
				switch (m_pMap->Get_TerrainMapSituation(i, j))
				{
				case WALL:
					m_pFieldObjMaker->PutObj(MODEL_TREE, i, j);
					break;
				case STAIRS:
					m_pFieldObjMaker->PutObj(MODEL_STAIRS, i, j);
					break;
				case HOME:
					m_pFieldObjMaker->PutObj(MODEL_HOME, i, j);
					break;
				}
			}
		}

		//�^�[���X�e�[�g������
		CTurn::Init();

		//�G�l�~�[�����������Z�b�g
		m_pEnemyGenerator->ResetMakeEnemyNum();

		//�A�C�e�������������Z�b�g
		CItemGenerator::ResetMakeItemNum();

		//�v���C���[�ʒu�Đݒ�
		m_pPlayer -> SetPos();

		//�}�b�v�Đ����t���O��|��
		m_MapMake = false;

		//�����z�u�G�l�~�[�̐ݒ�
		m_pEnemyGenerator ->MakeEnemy();

		//�K�i���B��Ԃ��U�ɂ���
		m_MapMake = false;
	}
	//-----3D�I�u�W�F�N�g�̍X�V-----

	//�}�b�v�Đ����t���O�󋵂�ۑ����Ă���
	m_OldMapMake = m_MapMake;

	//�e�}�l�[�W���[�̎��I�u�W�F�N�g�̍X�V
	m_pUnitManager->Update();
	m_pFieldItemManager->Update();
	m_pMapObjManager->Update();
	m_pParticleManager->Update();
	m_pEffectManager->Update();
	m_pUIManager->ManageUIUpdate();

	//�_���[�W�\�L�̍X�V
	m_pDamageManager->ManagerObjUpdate();

	//�W�F�l���[�^�[�̍X�V
	m_pEnemyGenerator->Update();
	m_pFieldGenerator->Update();

	//�J�����̍X�V
	m_pCamera->Update();
	m_pCamera -> PostUpdate();
	m_pMap ->UpDate();				//�}�b�v�f�[�^�X�V

	//�t�F�[�h�C���J�n�t���O�������Ă����ꍇ�A�t�F�[�h�̏������s��
	//�t�F�[�h�C���̍X�V
	m_pFade ->Update();

	//�t�F�[�h�C��������������A�X�e�[�g��ύX����
	if(m_pFade ->GetFadeAlpha() >= 255)
	{
		//�t�F�[�h�̏�Ԃ��i�[
		int FadeMode = m_pFade->GetFadeState();

		//�t�F�[�h�̏�Ԃŏ����𕪊�
		switch(FadeMode)
		{
			//�t�F�[�h��Ԃ��t�F�[�h�C���̏�Ԃ������ꍇ
		case FADEMODE_IN:
			//���j�b�g���ꎞ�s���s�\��Ԃɐݒ�
			m_pUnitManager->ChangeMoveCanFlg(true);
			break;
			//�t�F�[�h��Ԃ��t�F�[�h�A�E�g�������ꍇ
		case FADEMODE_OUT:
			{
				//�Q�[���N���A�ł������ɂ���Ď��Ɉȍ~����V�[����ύX����
				if(m_nGameClaer == GAME_CLEAR)
				{
					CGameState::StateUpdate(STATE_GAMECLEAR);
				}
				else if(m_nGameClaer == GAME_OVER)
				{
					CGameState::StateUpdate(STATE_GAMEOVER);
				}
			}
			break;
		}
		m_pFade->ChangeState(FADEMODE_NON);
	}
}
//---------------------------------------------------------------------------------------
//�S�I�u�W�F�N�g�`��
//---------------------------------------------------------------------------------------
void CGameScene::DrawObj()
{
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();

	//Z�o�b�t�@�̓K�p
	pD->SetRenderState( D3DRS_ZENABLE , TRUE );

	m_pCamera -> PreDraw();	//�J�������f

	//�}�b�v�f�[�^�`��
	m_pMap -> Draw();

	//�s�����`��
	m_pMapObjManager->Draw(false);
	m_pFieldItemManager->Draw();
	m_pUnitManager->Draw();
	m_pEffectManager->Draw();

	m_pDamageManager->ManagerObjDraw();
	
	pD ->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);

	pD ->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);

	pD ->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//Z�o�b�t�@�����_�����O�v�Z������
	pD ->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	//�����`��
	//�t�B�[���h��̃I�u�W�F�N�g�̔������̃I�u�W�F�N�g�̂ݕ`�悷��
	m_pMapObjManager->Draw(true);
	m_pParticleManager->Draw();

	pD ->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

	
	//Z�o�b�t�@�����_�����O�v�Z�L����
	pD ->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	
	//Z�o�b�t�@�̖���
	pD->SetRenderState( D3DRS_ZENABLE , FALSE );

	//UI�̕`��
	m_pUIManager->ManageUIDraw();

	//�K�w���̕`��
	m_pMap->DrawHierarchyNum();
	//�v���C���[���x���̕\��
	m_pPlayer->DrawLevel();
	//�t�F�[�h�̕`��
	m_pFade ->Draw();
	//�t�F�[�h�̏�Ԃ��i�[
	int FadeMode = m_pFade->GetFadeState();
	//�t�F�[�h�̏�Ԃ��A�t�F�[�h�C���̏ꍇ�A�K�w����\��
	if(FadeMode == FADEMODE_IN)
		m_pHierarchieNum->Draw();
}
//�Q�[���̃N���A�󋵂�ύX����
void CGameScene::GameClearStateChange(int Change)
{
	m_nGameClaer = Change;
}

//=======================================================================================
//	End of File
//=======================================================================================