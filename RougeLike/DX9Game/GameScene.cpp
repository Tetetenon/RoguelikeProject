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
#include"ItemManager.h"
#include"MapObjManager.h"
#include"ParticleManager.h"
#include"EffectObjManager.h"
#include"EnemyManager.h"

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

	//�V���O���g���̃|�C���^�̎擾
	m_pCamera	= CCamera::GetPointer();			//�J����
	m_pSky		= CSky::GetPointer();				//�X�J�C�h�[��

	
	//�����o�N���X�̃R���X�g���N�^���N��
	m_pFieldObjMaker	= new CFieldObjMaker(this);		//�t�B�[���h�I�u�W�F�N�g

	m_pFade				= new CFade();					//�t�F�[�h�A�E�g
	
	m_pMessageWindow		= new MessageWindow();		//���b�Z�[�W�E�C���h�E
	m_pHPDraw			= new CHPDraw();				//�X�e�[�^�X�E�C���h�E

	//�A�C�e���E�B���h�E
	m_pInventoryCursor	= new CInventoryCursor();		//�A�C�e���J�[�\��
	m_pCommandWindow	= new CCommandWindow();			//�R�}���h�E�C���h�E
	m_pCommandCursor	= new CCommandCursor();			//�R�}���h�J�[�\��
	//�����E�B���h�E
	m_pEquipmentInventoryCursor = new CEquipmentInventoryCursor();	//�����E�B���h�E�J�[�\��
	m_pEquipmentCommandWindow = new CEquipmentCommandWindow();	//�����R�}���h�E�B���h�E
	m_pEquipmentCommandCursor = new CEquipmentCommandCursor();	//�����R�}���h�J�[�\��

	m_pMap				= new CMapData();				//�}�b�v�f�[�^
	m_pTurn				= new CTurn();					//�^�[��

	m_pFieldGenerator	= new CItemGenerator(this);		//�t�B�[���h�A�C�e������
	m_pEnemyGenerator	= new CEnemyGenerator(this);	//�G�l�~�[�W�F�l���[�^�[

	//���j���[�E�B���h�E
	m_pMenuWindow		= new CMenuWindow();			//���j���[�E�C���h�E
	m_pMenuSelect		= new CMenuSelect();			//���j���[�Z���N�g
	m_pMenuWindowBack	= new CMenuWindow_Back();		//���j���[�̔w�i

	//�X�e�[�^�X�E�B���h�E
	m_pStatesWindow		= new CStatesWindow();			//�X�e�[�^�X�E�B���h�E
	m_pStatesCharacter	= new CStatesCharacter();		//�L�����N�^�[�E�B���h�E
	m_pStatesFont		= new CStatesFont();			//�X�e�[�^�X�t�H���g
	m_pStatesValue		= new CStatesValue();			//�X�e�[�^�X���l

	m_pOperation = new COperation();					//�������

	m_pTrickWindowCursor = new CTrickWindowCursor();	//���U�E�B���h�E�J�[�\��

	m_pMiniMap = new CMiniMap();						//�~�j�}�b�v
	m_pHierarchiNum = new CHierarchieNum();				//���݂̊K�w�����t�F�[�h�C�����ɕ\������

	m_pPlayer			= new CPlayer(this);			//�v���C���[
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CGameScene::~CGameScene()
{
	//�V���O���g���̍폜
	CCamera::Delete();
	CSky::Delete();
	//�V���O���g���̃|�C���^�̒��g�����ꂢ��
	m_pCamera	= NULL;			//�J����
	m_pSky		= NULL;			//�X�J�C�h�[��

	//�����o�N���X�̃|�C���^������
	delete m_pEnemyGenerator;	//�G�l�~�[�W�F�l���[�^�[

	delete m_pFieldObjMaker;	//�t�B�[���h�I�u�W�F����

	delete m_pFade;				//�t�F�[�h�A�E�g

	delete m_pMessageWindow;	//���b�Z�[�W�E�C���h�E

	delete m_pHPDraw;			//�X�e�[�^�X�E�C���h�E

	//�A�C�e���E�B���h�E
	//delete m_pInventory;		//�C���x���g���j��
	delete m_pInventoryCursor;	//�A�C�e���J�[�\���j��
	delete m_pCommandWindow;	//�R�}���h�E�C���h�E�j��
	delete m_pCommandCursor;	//�R�}���h�J�[�\���j��

	//�����E�B���h�E
	delete m_pEquipmentInventoryCursor;	//�����E�B���h�E�J�[�\��
	delete m_pEquipmentCommandWindow;	//�����R�}���h�E�B���h�E
	delete m_pEquipmentCommandCursor;	//�����R�}���h�J�[�\��

	delete m_pMap;				//�}�b�v�f�[�^
	delete m_pTurn;				//�^�[��

	delete m_pFieldGenerator;	//�t�B�[���h�A�C�e��

	//���j���[�E�B���h�E
	delete m_pMenuWindow;		//���j���[�E�C���h�E
	delete m_pMenuSelect;		//���j���[�Z���N�g
	delete m_pMenuWindowBack;	//���j���[�E�B���h�E�̔w�i

	//�X�e�[�^�X�E�B���h�E
	delete m_pStatesWindow;		//�X�e�[�^�X�E�B���h�E
	delete m_pStatesCharacter;	//�L�����N�^�[�E�B���h�E
	delete m_pStatesFont;		//�X�e�[�^�X����
	delete m_pStatesValue;		//�X�e�[�^�X���l

	delete m_pOperation;		//�������

	delete m_pTrickWindowCursor;	//�Z�E�B���h�E�J�[�\��

	delete m_pMiniMap;				//�~�j�}�b�v
	delete m_pHierarchiNum;			//�t�F�[�h�C�����ɕ\������K�w��

	m_nGameClaer = 0;

	//�}�l�[�W���[�̍폜
	CUnitManager::Destroy();
	CItemManager::Delete();
	CMapObjManager::Delete();
	CParticleManager::Delete();
	CEffectObjManager::Delete();

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
	CItemManager::Init();		//�A�C�e���}�l�[�W���[�̊Ǘ��I�u�W�F�N�g�̏�����
	CUnitManager::Init();		//���j�b�g�}�l�[�W���[�̊Ǘ��I�u�W�F�N�g�̏�����
	CMapObjManager::Init();		//�t�B�[���h�I�u�W�F�}�l�[�W���[�̊Ǘ��I�u�W�F�N�g�̏�����
	CParticleManager::Init();	//�p�[�e�B�N���}�l�[�W���[�̏�����
	CEffectObjManager::Init();	//�G�t�F�N�g�}�l�[�W���[�̏�����
	//�v���C���[�̃|�C���^���擾����
	CMapObjManager::PlayerSet();

	//�J�����̏�����
	m_pCamera->Init();
	//�X�J�C�h�[���̏�����
	m_pSky->Init();

	//���̎��_�̃v���C���[�̃��x�����擾����
	m_nPlayerLevel = m_pPlayer->GetLevel();

	//���b�Z�[�W�E�C���h�E�̏�����
	m_pMessageWindow ->Init();


	//-----�A�C�e���E�B���h�E-----
	//�A�C�e���J�[�\���̏�����
	m_pInventoryCursor->Init();
	//�R�}���h�E�C���h�E�̏�����
	m_pCommandWindow ->Init();
	//�R�}���h�J�[�\���̏�����
	m_pCommandCursor ->Init();

	//-----�����E�B���h�E-----
	//�����J�[�\��
	m_pEquipmentInventoryCursor ->Init();
	//�����R�}���h�E�B���h�E
	m_pEquipmentCommandWindow ->Init();
	//�����R�}���h�J�[�\��
	m_pEquipmentCommandCursor ->Init();

	//���U�E�B���h�E�J�[�\��������
	m_pTrickWindowCursor ->Init();

	//�����z�u�G�l�~�[�̐ݒ�
	m_pEnemyGenerator ->MakeEnemy();

	//�����z�u�A�C�e���̐ݒ�
	m_pFieldGenerator->MakeItem();

	//�z���񂩂�A�I�u�W�F�N�g��u���ׂ��ʒu�ɃI�u�W�F�N�g��ݒu
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{

			if(CMapData::Get_TerrainMapSituation(i,j) == IN_THE_WALL)
				m_pFieldObjMaker->PutObj(MODEL_TREE,i,j);

			if(CMapData::Get_TerrainMapSituation(i,j) == STAIRS)
				m_pFieldObjMaker->PutObj(MODEL_STAIRS,i,j);
		}
	}

	//�t�F�[�h�̏�Ԃ��t�F�[�h�C���ɐݒ�
	CFade::ChangeState(FADEMODE_IN);
	//���j�b�g���ꎞ�s���s�\��Ԃɐݒ�
	CUnitManager::ChangeMoveCanFlg(false);
}
//---------------------------------------------------------------------------------------
//�S�I�u�W�F�N�g�j��
//---------------------------------------------------------------------------------------
void CGameScene::FinObj()
{
	//�r���Ń��X�g���ς��\�����l�����A�ޔ�p�|�C���^������

	//�e�}�l�[�W���[�ŊǗ�����I�u�W�F�N�g�̏I���������s��
	CUnitManager::Fin();
	CItemManager::Fin();
	CMapObjManager::Fin();
	CParticleManager::Fin();
	CEffectObjManager::Fin();

	//���b�Z�[�W�E�C���h�E�̏I������
	m_pMessageWindow ->Fin();

	//�}�b�v�f�[�^�̏I������
	m_pMap ->Fin();


	//-----�A�C�e���E�B���h�E-----
	//�C���x���g���I��
	//m_pInventory ->Fin();
	//�A�C�e���J�[�\���̏I��
	m_pInventoryCursor ->Fin();
	//�R�}���h�E�C���h�E�̏I������
	m_pCommandWindow ->Fin();
	//�R�}���h�J�[�\���̏I������
	m_pCommandCursor ->Fin();

	//-----�����E�B���h�E-----
	//�����E�B���h�E�I������
	//m_pEquipmentInventory ->Fin();
	//�����J�[�\���I������
	m_pEquipmentInventoryCursor->Fin();
	//�����R�}���h�E�B���h�E�I������
	m_pEquipmentCommandWindow ->Fin();
	//�����R�}���h�J�[�\���I������
	m_pEquipmentCommandCursor ->Fin();

	//-----�Z�E�B���h�E�J�[�\��-----
	m_pTrickWindowCursor ->Fin();
}
//---------------------------------------------------------------------------------------
//�S�I�u�W�F�N�g�X�V
//---------------------------------------------------------------------------------------
void CGameScene::UpdateObj()
{
	//�}�b�v�̍Đ����t���O�������Ă����珈��
	if(m_MapMake && m_OldMapMake)
	{
		//�t�F�[�h�A�E�g�t���O�𗧂Ă�
		m_pFade->ChangeState(FADEMODE_OUT);

		//�}�b�v�f�[�^�̍Đ���
		CMapData::MapGeneration();

		//�t�B�[���h�I�u�W�F�N�g�폜
		CMapObjManager::Fin();
		//�G�l�~�[�I�u�W�F�N�g�폜
		CEnemyManager::Fin();
		//�A�C�e���I�u�W�F�N�g�̍폜
		CItemManager::Fin();
		//�p�[�e�B�N���I�u�W�F�N�g�̍폜
		CParticleManager::Fin();
		//�G�t�F�N�g�I�u�W�F�N�g�̍폜
		CEffectObjManager::Fin();
		
		//�z���񂩂�A�I�u�W�F�N�g��u���ׂ��ʒu�ɃI�u�W�F�N�g��ݒu
		for(int i = 0;i < MAP_SIZE;i++)
		{
			for(int j = 0;j < MAP_SIZE;j++)
			{

				if(CMapData::Get_TerrainMapSituation(i,j) == IN_THE_WALL)
					m_pFieldObjMaker->PutObj(MODEL_TREE,i,j);

				if(CMapData::Get_TerrainMapSituation(i,j) == STAIRS)
					m_pFieldObjMaker->PutObj(MODEL_STAIRS,i,j);
			}
		}

		//�^�[���X�e�[�g������
		CTurn::Init();

		//�G�l�~�[�����������Z�b�g
		CEnemyGenerator::ResetMakeEnemyNum();

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
	CUnitManager::Update();
	CItemManager::Update();
	CMapObjManager::Update();
	CParticleManager::Update();
	CEffectObjManager::Update();

	//�W�F�l���[�^�[�̍X�V
	m_pEnemyGenerator->Update();
	m_pFieldGenerator->Update();

	m_pCamera->Update();
	m_pCamera -> PostUpdate();		//�J�����X�V
	m_pMessageWindow ->Update();	//���b�Z�[�W�E�C���h�E�X�V
	m_pHPDraw ->Update();			//HP�X�V
	m_pMap ->UpDate();				//�}�b�v�f�[�^�X�V

	//���j���[�E�B���h�E�̕`�悪�s���Ă��邩�H
	if(CMenuWindow::GetDrawFlg())
	{
		//�X�e�[�^�X�E�B���h�E�̕`�悪�s���Ă��邩�H
		if(!CStatesWindow::GetDrawFlg())
		{
			//���j���[�E�B���h�E�̃Z���N�g���X�V
			m_pMenuSelect ->Update();
			//���j���[�E�B���h�E�̓��͍X�V
			m_pMenuWindow ->Update();
		}
	}
	//�X�e�[�^�X�E�B���h�E�̍X�V(�L�[���͂̍X�V)
	m_pStatesWindow ->Update();

	//-----�A�C�e���E�B���h�E-----
	//�A�C�e���E�C���h�E�̕`�揈��������Ă��邩���ʂ��s��
	if(CInventory::GetDrawFlg())
	{
		//�E�C���h�E�J�[�\���̍X�V
		m_pInventoryCursor->Update();
	}

	//�R�}���h�E�C���h�E���`�悳��Ă��邩���ʂ��s��
	if(m_pCommandWindow ->GetDrawFlg())
	{
		//�R�}���h�E�C���h�E�̍X�V
		m_pCommandWindow->UpDate();
		//�R�}���h�J�[�\���̍X�V
		m_pCommandCursor->Update();
	}

	//-----�����E�B���h�E-----
	
	//�����E�C���h�E�̕`�揈��������Ă��邩���ʂ��s��
	if(CEquipmentInventory::GetDrawFlg())
	{
		//�����E�C���h�E�J�[�\���̍X�V
		m_pEquipmentInventoryCursor->Update();
	}

	//�����R�}���h�E�C���h�E���`�悳��Ă��邩���ʂ��s��
	if(m_pEquipmentCommandWindow ->GetDrawFlg())
	{
		//�����E�C���h�E�̍X�V
		m_pEquipmentCommandWindow->UpDate();
		//�����J�[�\���̍X�V
		m_pEquipmentCommandCursor->Update();
	}

	//�v���C���[�̋Z�E�B���h�E�̕`��t���O���m�F
	if(m_pPlayer ->GetPlayerTrickWindowFlg())
	{
		//�Z�E�B���h�E�̃J�[�\�����X�V
		m_pTrickWindowCursor->Update();
	}

	//�X�e�[�^�X�摜�̍X�V
	m_pStatesCharacter->Update(m_pPlayer ->GetStatesMode());

	//�X�e�[�^�X�E�B���h�E�̃T�C�Y�̍X�V
	m_pStatesWindow->WindowSizeUpdate();

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
			CUnitManager::ChangeMoveCanFlg(true);
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
		CFade::ChangeState(FADEMODE_NON);
	}

	// �~�j�}�b�v�̍X�V
	m_pMiniMap->Update();
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
	CMapObjManager::Draw(false);
	CItemManager::Draw();
	CUnitManager::Draw();
	CEffectObjManager::Draw();
	
	pD ->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);

	pD ->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);

	pD ->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//Z�o�b�t�@�����_�����O�v�Z������
	pD ->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	//�����`��
	//�t�B�[���h��̃I�u�W�F�N�g�̔������̃I�u�W�F�N�g�̂ݕ`�悷��
	CMapObjManager::Draw(true);
	CParticleManager::Draw();

	pD ->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

	
	//Z�o�b�t�@�����_�����O�v�Z�L����
	pD ->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	
	//Z�o�b�t�@�̖���
	pD->SetRenderState( D3DRS_ZENABLE , FALSE );

	//���b�Z�[�W�E�C���h�E�`��
	m_pMessageWindow -> Draw();

	//�~�j�}�b�v�̕`��
	m_pMiniMap->Draw();

	//���j���[�E�B���h�E�̕`��t���O�������Ă��邩�m�F
	if(CMenuWindow::GetDrawFlg())
	{
		//���j���[�E�B���h�E�̔w�i�`��
		m_pMenuWindowBack -> Draw();
		//�Z���N�g���j���[�e�N�X�`���`��
		m_pMenuSelect ->Draw();
		//���j���[�E�B���h�E�e�N�X�`���`��
		m_pMenuWindow ->Draw();
	}

	//��������`��
	m_pOperation ->Draw();

	//-----�A�C�e���E�B���h�E-----

	//�A�C�e���E�C���h�E���`�揈�����s�������ʂ���
	if(CInventory::GetDrawFlg())
	{
		//�C���x���g��(�A�C�e���E�C���h�E)�̕`��
		m_pPlayer ->DrawInventory();
		//�A�C�e���J�[�\���̕`��
		m_pInventoryCursor->Draw();
	}
	//�R�}���h�J�[�\�����`�揈�����s�������ʂ��s��
	if(m_pCommandWindow ->GetDrawFlg())
	{
		//�R�}���h�E�C���h�E�`��
		m_pCommandWindow ->Draw();
		//�R�}���h�J�[�\���̕`��
		m_pCommandCursor ->Draw();
	}

	//-----�����E�B���h�E-----

	//�����E�C���h�E���`�揈�����s�������ʂ���
	if(CEquipmentInventory::GetDrawFlg())
	{
		//�����E�C���h�E�̕`��
		m_pPlayer ->DrawEquipment();
		//�����J�[�\���̕`��
		m_pEquipmentInventoryCursor->Draw();
	}
	//�R�}���h�J�[�\�����`�揈�����s�������ʂ��s��
	if(m_pEquipmentCommandWindow ->GetDrawFlg())
	{
		//�����R�}���h�E�C���h�E�`��
		m_pEquipmentCommandWindow ->Draw();
		//�����R�}���h�J�[�\���̕`��
		m_pEquipmentCommandCursor ->Draw();
	}
	//�X�e�[�^�X�̃E�B���h�E��`�悷��
	m_pStatesWindow -> Draw();
	//HP�`��
	m_pHPDraw ->Draw();
	//�L�����N�^�[�E�B���h�E�̕`��
	m_pStatesCharacter ->Draw();

	//�K�w���̕`��
	CMapData::DrawHierarchyNum();
	//�v���C���[���x���̕\��
	m_pPlayer->DrawLevel();

	//�X�e�[�^�X�E�B���h�E�̕`��t���O�������Ă�����`��
	if(m_pStatesWindow->GetDrawFlg())
	{
		//�X�e�[�^�X�̕�����`�悷��
		m_pStatesFont ->Draw();
		//�X�e�[�^�X�̐��l��`�悷��
		m_pStatesValue ->Draw();
	}

	//�v���C���[�̋Z�E�B���h�E�̕`��t���O���m�F
	if(m_pPlayer ->GetPlayerTrickWindowFlg())
	{
		//�Z�E�B���h�E��`��
		m_pPlayer ->DrawTrick();
		//�Z�E�B���h�E�̃J�[�\����`��
		m_pTrickWindowCursor->Draw();
	}
	//�t�F�[�h�̕`��
	m_pFade ->Draw();
	//�t�F�[�h�̏�Ԃ��i�[
	int FadeMode = m_pFade->GetFadeState();
	//�t�F�[�h�̏�Ԃ��A�t�F�[�h�C���̏ꍇ�A�K�w����\��
	if(FadeMode == FADEMODE_IN)
		m_pHierarchiNum->Draw();
}
//�Q�[���̃N���A�󋵂�ύX����
void CGameScene::GameClearStateChange(int Change)
{
	m_nGameClaer = Change;
}

//=======================================================================================
//	End of File
//=======================================================================================