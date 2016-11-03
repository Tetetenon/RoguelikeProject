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

bool	CGameScene::m_MapMake = false;
bool	CGameScene::m_OldMapMake = false;

bool	CGameScene::m_bFadeStart = false;
int		CGameScene::m_nPlayerLevel = 0;

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CGameScene::CGameScene():
	m_pGraph(NULL),
	m_pObj(NULL),
	m_FPS(),
	m_pUnit(NULL),
	m_pItemDevice(NULL)
{
	//�f�o�b�O�����̏�����
	m_szDebug[0] = _T('\0');

	//�t�F�[�h�t���O�̏�����
	m_bFadeStart = false;
	m_bFadeSuccess = false;

	srand((unsigned int)time(NULL));			//���Ԃŗ����̏��������s��

	
	//�����o�N���X�̃R���X�g���N�^���N��
	m_pCamera			= new CCamera(this);			//�J����
	m_pPlayer			= new CPlayer(this);			//�v���C���[
	m_pFieldObjMaker	= new CFieldObjMaker(this);		//�t�B�[���h�I�u�W�F�N�g

	m_pFade				= new CFade();					//�t�F�[�h�A�E�g
	
	m_pMessageWindow		= new MessageWindow();		//���b�Z�[�W�E�C���h�E
	m_pHPDraw			= new CHPDraw();				//�X�e�[�^�X�E�C���h�E

	//�A�C�e���E�B���h�E
	//m_pInventory		= new CInventory();			//�C���x���g��(�A�C�e���E�C���h�E)
	m_pInventoryCursor	= new CInventoryCursor();		//�A�C�e���J�[�\��
	m_pCommandWindow	= new CCommandWindow();			//�R�}���h�E�C���h�E
	m_pCommandCursor	= new CCommandCursor();		//�R�}���h�J�[�\��

	//�����E�B���h�E
	//m_pEquipmentInventory = new CEquipmentInventory();	//�����A�C�e���E�B���h�E
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
	
	m_pSky = new CSky(this);							//�X�J�C�h�[��

	m_pOperation = new COperation();					//�������

	m_pTrickWindowCursor = new CTrickWindowCursor();	//���U�E�B���h�E�J�[�\��

	m_pMiniMap = new CMiniMap();						//�~�j�}�b�v
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CGameScene::~CGameScene()
{
	//�����o�N���X�̃|�C���^������
	delete m_pPlayer;			//�v���C���[
	delete m_pEnemyGenerator;	//�G�l�~�[�W�F�l���[�^�[

	delete m_pFieldObjMaker;	//�t�B�[���h�I�u�W�F����

	delete m_pFade;				//�t�F�[�h�A�E�g

	delete m_pCamera;			//�J����

	delete m_pMessageWindow;	//���b�Z�[�W�E�C���h�E

	delete m_pHPDraw;			//�X�e�[�^�X�E�C���h�E

	//�A�C�e���E�B���h�E
	//delete m_pInventory;		//�C���x���g���j��
	delete m_pInventoryCursor;	//�A�C�e���J�[�\���j��
	delete m_pCommandWindow;	//�R�}���h�E�C���h�E�j��
	delete m_pCommandCursor;	//�R�}���h�J�[�\���j��

	//�����E�B���h�E
	//delete m_pEquipmentInventory;	//�����E�B���h�E
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
	
	delete m_pSky;				//�X�J�C�h�[��

	delete m_pOperation;		//�������

	delete m_pTrickWindowCursor;	//�Z�E�B���h�E�J�[�\��

	delete m_pMiniMap;				//�~�j�}�b�v
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
	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���

	// FPS ����ʂɕ`�悷�邽�߂̕�������쐬
	TCHAR	str[256];
	_stprintf(str, _T("FPS = %d\n"), m_FPS);
	lstrcat(m_szDebug, str);

	//----- �����ɕ`�揈��
	DrawObj();

	// �f�o�b�O������`��
	m_pGraph->DrawText(0, 0, m_szDebug);
}

//---------------------------------------------------------------------------------------
//�V�[���ɃI�u�W�F�N�g��ǉ�
//---------------------------------------------------------------------------------------
void	CGameScene::Add(C3DObj* pObj)
{
	//���łɃI�u�W�F�N�g���Z�b�g����Ă���΂��̃I�u�W�F�N�g�̎��̃|�C���^�ʒu��
	//�w�肳�ꂽ�I�u�W�F�N�g��ǉ�����
	if(m_pObj)
	{
		m_pObj ->SetBack(pObj);
		pObj ->SetNext(m_pObj);
	}
	else
	{
		pObj ->SetNext(NULL);
	}
	m_pObj = pObj;
	pObj ->SetBack(NULL);
}
//---------------------------------------------------------------------------------------
//�V�[������I�u�W�F�N�g���폜
//---------------------------------------------------------------------------------------
void	CGameScene::Del(C3DObj* pObj)
{
	//�f�[�^��ޔ�
	C3DObj * pBack = pObj ->GetBack();
	C3DObj *pNext = pObj ->GetNext();

	//���̃|�C���^�Ƀf�[�^������΂Ȃ��Ȃ���
	if(pBack)
	{
		pBack ->SetNext(pNext);
	}
	else
	{
		m_pObj = pNext;
	}

	//���̃f�[�^�̑O�|�C���^��ݒ肵�Ȃ���
	if(pNext)
	{
		pNext ->SetBack(pBack);
	}
}

//---------------------------------------------------------------------------------------
//�I�u�W�F�N�g�T��
//---------------------------------------------------------------------------------------
C3DObj* CGameScene::Find(UINT uID,C3DObj *p)
{
	//(�������)?�^:�U
	//�n���ꂽ�I�u�W�F�N�g���ɒ��g������΂��̃I�u�W�F�N�g�̎����瑖������
	//������΁A�I�u�W�F�N�g�̐擪���珇��������s��
	C3DObj* pObj = (p)? p->GetNext():m_pObj;

	//���X�g�������A�w�肳�ꂽID�ƈ�v����I�u�W�F�N�g�����X�g�\���̏I�[�܂ő��������ꍇ�A
	//�������I������
	while(pObj)
	{
		if(uID && pObj ->GetID() == uID)
		{
			break;
		}
		pObj = pObj ->GetNext();
	}

	//�����̌���(��v�����I�u�W�F�N�g�f�[�^�����݂��Ȃ�����NULL)��Ԃ�
	return pObj;
}

//---------------------------------------------------------------------------------------
//�V�[���Ƀ��j�b�g��ǉ�
//---------------------------------------------------------------------------------------
void	CGameScene::AddUnit(CUnit* pUnit)
{
	//���łɃI�u�W�F�N�g���Z�b�g����Ă���΂��̃I�u�W�F�N�g�̎��̃|�C���^�ʒu��
	//�w�肳�ꂽ�I�u�W�F�N�g��ǉ�����
	if(m_pUnit)
	{
		m_pUnit ->SetBackUnit(pUnit);
		pUnit ->SetNextUnit(m_pUnit);
	}
	else
	{
		pUnit ->SetNextUnit(NULL);
	}
	m_pUnit = pUnit;
	pUnit ->SetBackUnit(NULL);
}
//---------------------------------------------------------------------------------------
//�V�[�����烆�j�b�g���폜
//---------------------------------------------------------------------------------------
void	CGameScene::DelUnit(CUnit* pUnit)
{
	//�f�[�^��ޔ�
	CUnit *pBack = pUnit ->GetBackUnit();
	CUnit *pNext = pUnit ->GetNextUnit();

	//���̃|�C���^�Ƀf�[�^������΂Ȃ��Ȃ���
	if(pBack)
	{
		pBack ->SetNextUnit(pNext);
	}
	else
	{
		m_pUnit = pNext;
	}

	//���̃f�[�^�̑O�|�C���^��ݒ肵�Ȃ���
	if(pNext)
	{
		pNext ->SetBackUnit(pBack);
	}
}

//---------------------------------------------------------------------------------------
//���j�b�g�T��
//---------------------------------------------------------------------------------------
CUnit* CGameScene::FindUnit(UINT uNumber,CUnit *p)
{
	//(�������)?�^:�U
	//�n���ꂽ�I�u�W�F�N�g���ɒ��g������΂��̃I�u�W�F�N�g�̎����瑖������
	//������΁A�I�u�W�F�N�g�̐擪���珇��������s��
	CUnit* pObj = (p)? p->GetNextUnit():m_pUnit;

	//���X�g�������A�w�肳�ꂽID�ƈ�v����I�u�W�F�N�g�����X�g�\���̏I�[�܂ő��������ꍇ�A
	//�������I������
	while(pObj)
	{
		if(uNumber && pObj ->GetNumber() == uNumber)
		{
			break;
		}
		pObj = pObj ->GetNextUnit();
	}

	//�����̌���(��v�����I�u�W�F�N�g�f�[�^�����݂��Ȃ�����NULL)��Ԃ�
	return pObj;
}
//---------------------------------------------------------------------------------------
//�V�[���ɃA�C�e����ǉ�
//---------------------------------------------------------------------------------------
void	CGameScene::AddItem(CFieldItem* pItem)
{
	//���łɃI�u�W�F�N�g���Z�b�g����Ă���΂��̃I�u�W�F�N�g�̎��̃|�C���^�ʒu��
	//�w�肳�ꂽ�I�u�W�F�N�g��ǉ�����
	if(m_pItemDevice)
	{
		m_pItemDevice ->SetBackFieldItem(pItem);
		pItem ->SetNextFieldItem(m_pItemDevice);
	}

	else
	{
		pItem ->SetNextFieldItem(NULL);
	}
	m_pItemDevice = pItem;
	pItem ->SetBackFieldItem(NULL);
}
//---------------------------------------------------------------------------------------
//�V�[������A�C�e���폜
//---------------------------------------------------------------------------------------
void	CGameScene::DelItem(CFieldItem* pItem)
{
	//�f�[�^��ޔ�
	CFieldItem *pBack = pItem ->GetBackFieldItem();
	CFieldItem *pNext = pItem ->GetNextFieldItem();

	//���̃|�C���^�Ƀf�[�^������΂Ȃ��Ȃ���
	if(pBack)
	{
		pBack ->SetNextFieldItem(pNext);
	}

	else
	{
		m_pItemDevice = pNext;
	}

	//���̃f�[�^�̑O�|�C���^��ݒ肵�Ȃ���
	if(pNext)
	{
		pNext ->SetBackFieldItem(pBack);
	}
}

//---------------------------------------------------------------------------------------
//�A�C�e���T��
//---------------------------------------------------------------------------------------
CFieldItem* CGameScene::FindItem(UINT uNumber,CFieldItem *p)
{
	//(�������)?�^:�U
	//�n���ꂽ�I�u�W�F�N�g���ɒ��g������΂��̃I�u�W�F�N�g�̎����瑖������
	//������΁A�I�u�W�F�N�g�̐擪���珇��������s��
	CFieldItem* pObj = (p)? p->GetNextFieldItem():m_pItemDevice;

	int nNumber;

	//���X�g�������A�w�肳�ꂽID�ƈ�v����I�u�W�F�N�g�����X�g�\���̏I�[�܂ő��������ꍇ�A
	//�������I������
	while(pObj)
	{
		nNumber = pObj ->GetFieldID();
		if(uNumber && nNumber == uNumber)
		{
			break;
		}
		pObj = pObj ->GetNextFieldItem();
	}

	//�����̌���(��v�����I�u�W�F�N�g�f�[�^�����݂��Ȃ�����NULL)��Ԃ�
	return pObj;
}

//---------------------------------------------------------------------------------------
//�S�I�u�W�F�N�g������
//---------------------------------------------------------------------------------------
void CGameScene::InitObj()
{
	//�}�b�v�̏�����
	m_pMap ->Init();

	//�~�j�}�b�v�̏�����
	m_pMiniMap->Init();

	//���X�g�łȂ����Ă��邷�ׂẴI�u�W�F�N�g�f�[�^�̏�����
	C3DObj* pObj = m_pObj;
	for(;pObj;pObj = pObj ->GetNext())
	{
		pObj ->Init();
	}
	// �������㏈��
	for (pObj = m_pObj; pObj; pObj = pObj->GetNext()) {
		pObj->PostInit();
	}

	//���̎��_�̃v���C���[�̃��x�����擾����
	m_nPlayerLevel = m_pPlayer->GetLevel();

	//�G�l�~�[�̃v���C���[�|�C���^�̏�����
	CEnemy::PlayerPointInit();

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
	//m_pEnemyGenerator ->MakeEnemy();

	//�����z�u�A�C�e���̐ݒ�
	m_pFieldGenerator->MakeItem();

	//�z���񂩂�A�I�u�W�F�N�g��u���ׂ��ʒu�ɃI�u�W�F�N�g��ݒu
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			if(CMapData::Get_TerrainMapSituation(i,j) == 1)
				m_pFieldObjMaker->PutObj(MODEL_WALL,i,j);

			if(CMapData::Get_TerrainMapSituation(i,j) == -1)
				m_pFieldObjMaker->PutObj(MODEL_TREE,i,j);

			if(CMapData::Get_TerrainMapSituation(i,j) == STAIRS)
				m_pFieldObjMaker->PutObj(MODEL_STAIRS,i,j);
		}
	}
}
//---------------------------------------------------------------------------------------
//�S�I�u�W�F�N�g�j��
//---------------------------------------------------------------------------------------
void CGameScene::FinObj()
{
	//�r���Ń��X�g���ς��\�����l�����A�ޔ�p�|�C���^������
	C3DObj* pObj = m_pObj;
	C3DObj* pNext;
	for(;pObj;pObj = pNext)
	{
		pNext = pObj ->GetNext();
		pObj ->Fin();
	}
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

	//�~�j�}�b�v�̏I������
	m_pMiniMap ->Fin();
}
//---------------------------------------------------------------------------------------
//�S�I�u�W�F�N�g�X�V
//---------------------------------------------------------------------------------------
void CGameScene::UpdateObj()
{
	//�}�b�v�̍Đ����t���O�������Ă����珈��
	if(m_MapMake && m_OldMapMake)
	{
		//�}�b�v�f�[�^�̍Đ���
		CMapData::MapGeneration();

		//�t�B�[���h�I�u�W�F�N�g�폜�t���O��������
		CFieldObj::DeleteObjFlgDown();
		
		//�z���񂩂�A�I�u�W�F�N�g��u���ׂ��ʒu�ɃI�u�W�F�N�g��ݒu
		for(int i = 0;i < MAP_SIZE;i++)
		{
			for(int j = 0;j < MAP_SIZE;j++)
			{
				if(CMapData::Get_TerrainMapSituation(i,j) == 1)
					m_pFieldObjMaker->PutObj(MODEL_WALL,i,j);

				if(CMapData::Get_TerrainMapSituation(i,j) == -1)
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

		//�~�j�}�b�v�f�[�^��������
		m_pMiniMap->Init();

		//�v���C���[�ʒu�Đݒ�
		m_pPlayer -> SetPos();

		//���̎��_�̃v���C���[�̃��x�����擾����
		m_nPlayerLevel = m_pPlayer->GetLevel();

		//�}�b�v�Đ����t���O��|��
		m_MapMake = false;

		//�G�l�~�[�̍폜�t���O��|��
		CEnemy::CanGeneration();

		//�A�C�e���̍폜�t���O��|��
		CFieldItem::CleatePermit();

		//�����z�u�G�l�~�[�̐ݒ�
		//m_pEnemyGenerator ->MakeEnemy();

		//�K�i���B��Ԃ��U�ɂ���
		m_MapMake = false;
	}

	//-----3D�I�u�W�F�N�g�̍X�V-----

	//�}�b�v�Đ����t���O�󋵂�ۑ����Ă���
	m_OldMapMake = m_MapMake;

	//�r���Ń��X�g���ς��\�����l�����A�ޔ�p�|�C���^������
	C3DObj* pObj = m_pObj;
	C3DObj* pNext;
	for(;pObj;pObj = pNext)
	{
		pNext = pObj ->GetNext();
		pObj ->Update();
	}

	//�}�b�v�̍Đ����t���O�������Ă����珈������
	if(m_MapMake && !m_OldMapMake)
	{
		//�G�l�~�[�̍폜�t���O���Ă�
		CEnemy::DeleteEnemy();

		//�t�B�[���h�A�C�e���̍폜�t���O���Ă�
		CFieldItem::DeleteAllItem();

		//�t�B�[���h�I�u�W�F�N�g�폜�t���O�𗧂Ă�
		CFieldObj::DeleteObjFlgUp();
	}

	m_pCamera -> PostUpdate();		//�J�����X�V
	m_pMessageWindow ->Update();	//���b�Z�[�W�E�C���h�E�X�V
	m_pHPDraw ->Update();			//HP�X�V
	m_pMap ->UpDate();				//�}�b�v�f�[�^�X�V

	//���j���[�E�B���h�E�̕`�悪�s���Ă��邩�H
	if(CMenuWindow::GetDrawFlg())
	{
		//�X�e�[�^�X�E�B���h�E�̕`�悪�s���Ă��邩�H
		if(CStatesWindow::GetDrawFlg())
		{
			//�X�e�[�^�X�E�B���h�E�̍X�V(�L�[���͂̍X�V)
			m_pStatesWindow ->Update();
		}

		else
		{
			//���j���[�E�B���h�E�̃Z���N�g���X�V
			m_pMenuSelect ->Update();
			//���j���[�E�B���h�E�̓��͍X�V
			m_pMenuWindow ->Update();
		}
	}

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

	//�~�j�}�b�v�̍X�V
	m_pMiniMap ->Update();
	
	//�t�F�[�h�C���J�n�t���O�������Ă����ꍇ�A�t�F�[�h�̏������s��
	if(m_bFadeStart)
	{
		int UpdateTimeing = m_FPS / 60.0f;


		//�t�F�[�h�C���̍X�V
		m_pFade ->Update();
	}
	//�t�F�[�h�C��������������A�X�e�[�g��ύX����
	if(m_pFade ->GetFadeAlpha() >= 255)
	{
		//�t�F�[�h��ԏ�����
		m_bFadeStart = false;
		m_bFadeSuccess = false;
		CGameState::Update();
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
	C3DObj* pObj = m_pObj;

	for(;pObj;pObj = pObj->GetNext())
	{
		pObj ->Draw();
	}
	
	pD ->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);

	pD ->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);

	pD ->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//Z�o�b�t�@�����_�����O�v�Z������
	pD ->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	//�����`��
	pObj = m_pObj;
	for(;pObj;pObj = pObj->GetNext())
	{
		pObj -> DrawAlpha();
	}

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

		//��������`��
		m_pOperation ->Draw();
	}

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

	//�t�F�[�h���J�n����Ă���΁A�`����s��
	if(m_bFadeStart)
	{
		m_pFade ->Draw();
	}
}

//=======================================================================================
//	End of File
//=======================================================================================