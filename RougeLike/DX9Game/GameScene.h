//=======================================================================================
//
//	  �Q�[���V�[�� �N���X��`
//
//=======================================================================================
#pragma once

#include "Graphics.h"
#include "C3DObj.h"
#include "Mesh.h"				// CMesh�N���X��`

//-----�v���C���[�A�G�l�~�[(���j�b�g)-----
#include "Unit.h"				//���j�b�g
#include "Player.h"				//�v���C���[
#include "EnemyGenerator.h"		//�G�l�~�[�����N���X
#include "ItemGenerator.h"		//�A�C�e�������N���X

//-----�I�u�W�F�N�g-----
#include "FieldObjMaker.h"		//�t�B�[���h�I�u�W�F�N���X
#include "Camera.h"				//�J�����N���X
#include "Turn.h"				//�^�[���Ǘ��N���X
#include "MessageWindow.h"		//���b�Z�[�W�E�C���h�E����
#include "MapData.h"			//�}�b�v����
#include "DeleteObj.h"			//���ŃG�t�F�N�g�N���X
#include "HitObj.h"				//�q�b�g�G�t�F�N�g�N���X
#include "Sky.h"				//�X�J�C�h�[��

//-----�A�C�e���E�C���h�E-----
//#include "ItemWindow.h"			//�C���x���g��(�A�C�e���E�C���h�E)
#include "ItemWindowCursor.h"		//�A�C�e���J�[�\��
#include "ItemCommandWindow.h"		//�R�}���h�E�C���h�E
#include "ItemCommandCursor.h"		//�R�}���h�I���J�[�\��

//-----�X�e�[�^�X�`��-----
#include "HPDraw.h"

//-----���j���[�E�C���h�E-----
#include "MenuWindow.h"				//���j���[�E�C���h�E�e�N�X�`���`��
#include "MenuSelect.h"				//���j���[�E�B���h�E�̃Z���N�g�p�|���S��
#include "MenuWindow_Back.h"		//���j���[�E�B���h�E�̔w�i

//-----�X�e�[�^�X�E�B���h�E-----
#include "StatesWindow.h"			//�X�e�[�^�X�̃E�B���h�E�̂�
#include "StatesCharacter.h"		//�L�����N�^�[�E�B���h�E
#include "StatesFont.h"				//�L�����N�^�[�X�e�[�^�X�̕���
#include "StatesValue.h"			//�L�����N�^�[�̃X�e�[�^�X

//-----�����E�B���h�E-----
//#include "EquipmentWindow.h"		//�����̃E�B���h�E
#include "EquipmentWindowCursor.h"	//�����I���J�[�\��
#include "EquipmentCommandWindow.h"	//�����R�}���h�E�B���h�E
#include "EquipmentCommandCursor.h"	//�����R�}���h�J�[�\��

//-----�Z�E�B���h�E-----
#include "TrickWindowCursor.h"		//�Z�J�[�\��

#include "Fade.h"					//�t�F�[�h�A�E�g
#include "Operation.h"				//�������

#include "MiniMap.h"				//�~�j�}�b�v����

#include "HierarchieNum.h"			//���݂̊K�w�����A�t�F�[�h�C�����ɕ\������

#define GAME_CLEAR	(1)
#define GAME_OVER	(2)

class CGameScene
{
private:
	CGraphics*					m_pGraph;					//�O���t�B�b�N�f�o�C�X
	C3DObj *					m_pObj;						//�I�u�W�F�N�g�f�o�C�X
	CUnit*						m_pUnit;					//���j�b�g�f�o�C�X
	CFieldItem*					m_pItemDevice;				//�A�C�e���f�o�C�X

	CFade*						m_pFade;					//�t�F�[�h�A�E�g
		
	TCHAR						m_szDebug[1024];			// �f�o�b�O�p������
	int							m_FPS;						// �t���[�����J�E���g�p

	//-------- �Q�[���p�I�u�W�F�N�g -----
	CPlayer*					m_pPlayer;					//�v���C���[
	CEnemyGenerator*			m_pEnemyGenerator;			//�G�l�~�[����
	CItemGenerator*				m_pFieldGenerator;			//�A�C�e������
	CFieldObjMaker*				m_pFieldObjMaker;			//�t�B�[���h�I�u�W�F����
	CCamera*					m_pCamera;					//�J����
	MessageWindow*				m_pMessageWindow;			//�E�C���h�E
	CHPDraw*					m_pHPDraw;					//�X�e�[�^�X�`��
	CMapData*					m_pMap;						//�}�b�v
	CTurn*						m_pTurn;					//�^�[���N���X
	COperation*					m_pOperation;				//�������

	//�A�C�e���E�B���h�E
	CInventoryCursor*			m_pInventoryCursor;			//�A�C�e���J�[�\��
	CCommandWindow*				m_pCommandWindow;			//�R�}���h�E�C���h�E
	CCommandCursor*				m_pCommandCursor;			//�R�}���h�J�[�\��

	//�����E�B���h�E
	CEquipmentInventoryCursor*	m_pEquipmentInventoryCursor;//�����J�[�\��
	CEquipmentCommandWindow*	m_pEquipmentCommandWindow;	//�����E�B���h�E�R�}���h�E�B���h�E
	CEquipmentCommandCursor*	m_pEquipmentCommandCursor;	//�����E�B���h�E�R�}���h�I��
	//-----���j���[�E�B���h�E-----
	CMenuWindow*				m_pMenuWindow;				//���j���[�E�C���h�E
	CMenuSelect*				m_pMenuSelect;				//���j���[�Z���N�g
	CMenuWindow_Back*			m_pMenuWindowBack;			//���j���[�E�B���h�E�̔w�i

	//-----�X�e�[�^�X�E�B���h�E-----
	CStatesWindow*				m_pStatesWindow;			//�E�B���h�E
	CStatesCharacter*			m_pStatesCharacter;			//�L�����N�^�[�E�B���h�E
	CStatesFont*				m_pStatesFont;				//�X�e�[�^�X���ڕ���
	CStatesValue*				m_pStatesValue;				//�X�e�[�^�X���l


	//-----�Z�E�B���h�E-----
	CTrickWindowCursor*			m_pTrickWindowCursor;		//�Z�E�B���h�E�J�[�\��

	CSky*						m_pSky;						//�X�J�C�h�[��

	CMiniMap*					m_pMiniMap;					//�~�j�}�b�v

	static bool					m_MapMake;					//�}�b�v�f�[�^���Đ�������
	static bool					m_OldMapMake;				//�O�t���[���̃}�b�v�Đ����t���O��ێ�

	static int					m_nPlayerLevel;				//�K�w�����肽���_�̃v���C���[�̃��x��

	static int					m_nGameClaer;				//�Q�[�����N���A�������A�Q�[���I�[�o�[�ɂȂ�����

	CHierarchieNum*				m_pHierarchiNum;			//�t�F�[�h�C�����ɊK�w����\������
public:
	CGameScene();
	virtual ~CGameScene();
	//�V�[���̍쐬
	static CGameScene* Create(CGraphics* pGraph);
	//�V�[���̍폜
	void Release();
	//�`��
	void Render();
	//�X�V
	void Update();
	//FPS�����擾
	void SetFPS(int nFPS){m_FPS = nFPS;}
	//
	void AddDebugStr(LPCTSTR psz)
	{
		lstrcat(m_szDebug, psz);
	}

	//-----�I�u�W�F�N�g�֘A�̑���-----
	//�V�[����ɃI�u�W�F�N�g��ǉ�
	void Add(C3DObj* pObj);
	//�V�[����̃I�u�W�F�N�g���폜
	void Del(C3DObj* pObj);
	//�V�[����̃I�u�W�F�N�g��T������
	C3DObj* Find(UINT uID,C3DObj *p);

	
	//-----���j�b�g�֘A�̑���-----
	//�V�[����Ƀ��j�b�g��ǉ�����
	void AddUnit(CUnit* pUnit);
	//�V�[����̃��j�b�g���폜����
	void DelUnit(CUnit* pUnit);
	//�V�[����̃��j�b�g��T������
	CUnit*  FindUnit(UINT uID,CUnit *p);


	//-----�A�C�e���֘A�̑���-----
	//�V�[����ɃA�C�e����ǉ�����
	void AddItem(CFieldItem* pItem);
	//�V�[����̃A�C�e�����폜����
	void DelItem(CFieldItem* pItem);
	//�V�[����̃A�C�e����T��
	CFieldItem* FindItem(UINT uID,CFieldItem *p);

	//�}�b�v�̍Đ����t���O�𗧂Ă�
	static void MapReMake ()	{m_MapMake = true;}	

	//�v���C���[�̃��x�����擾
	static int GetPlayerLevel()	{return m_nPlayerLevel;}

	//�Q�[���̃N���A�󋵂�ύX����
	static void GameClearStateChange(int Change);
private:
	//������
	bool Initialize(CGraphics* pGraph);
	//�I������
	void Finalize();
	//�`��
	void Draw();

	//-----�I�u�W�F�N�g�̏���-----
	//������
	void InitObj();
	//�I������
	void FinObj();
	//�X�V
	void UpdateObj();
	//�`��
	void DrawObj();
};

//=======================================================================================
//	End of File
//=======================================================================================