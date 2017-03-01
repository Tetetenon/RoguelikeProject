//=======================================================================================
//
//	  �Q�[���V�[�� �N���X��`
//
//=======================================================================================
#pragma once

#include "Graphics.h"
#include "C3DObj.h"
#include "Mesh.h"

//-----�v���C���[�A�G�l�~�[(���j�b�g)-----
#include "ItemGenerator.h"		//�A�C�e�������N���X

//-----�I�u�W�F�N�g-----
#include "FieldObjMaker.h"		//�t�B�[���h�I�u�W�F�N���X
#include "Camera.h"				//�J�����N���X
#include "Turn.h"				//�^�[���Ǘ��N���X
#include "MapData.h"			//�}�b�v����
#include "DeleteObj.h"			//���ŃG�t�F�N�g�N���X
#include "HitObj.h"				//�q�b�g�G�t�F�N�g�N���X
#include "Sky.h"				//�X�J�C�h�[��

#define GAME_CLEAR	(1)
#define GAME_OVER	(2)

class CFade;					//�t�F�[�h
class CHierarchieNum;			//�K�w���\��
class CUnitManager;				//���j�b�g�}�l�[�W���[
class CEffectObjManager;		//�G�t�F�N�g�I�u�W�F
class CDamageBillBoardManager;	//�_���[�W�r���{�[�h
class CItemManager;				//�t�B�[���h�A�C�e��
class CMapObjManager;			//�}�b�v�I�u�W�F
class CParticleManager;			//�p�[�e�B�N��
class CUIManager;				//UI�}�l�[�W��
class CPlayer;					//�v���C���[
class CEnemyGenerator;

class CGameScene
{
private:
	CGraphics*					m_pGraph;					//�O���t�B�b�N�f�o�C�X	
	TCHAR						m_szDebug[1024];			// �f�o�b�O�p������
	int							m_FPS;						// �t���[�����J�E���g�p

	//-------- �Q�[���p�I�u�W�F�N�g -----
	CPlayer*					m_pPlayer;					//�v���C���[
	CEnemyGenerator*			m_pEnemyGenerator;			//�G�l�~�[����
	CItemGenerator*				m_pFieldGenerator;			//�A�C�e������
	CFieldObjMaker*				m_pFieldObjMaker;			//�t�B�[���h�I�u�W�F����
	CCamera*					m_pCamera;					//�J����

	CFade*						m_pFade;					//�t�F�[�h
	CHierarchieNum*				m_pHierarchieNum;			//�K�w���\��

	//�}�l�[�W���[�|�C���^
	CDamageBillBoardManager*	m_pDamageManager;			//�_���[�W�\�L�}�l�[�W���[
	CUnitManager*				m_pUnitManager;				//���j�b�g�}�l�[�W���[			
	CEffectObjManager*			m_pEffectManager;			//�G�t�F�N�g�I�u�W�F�}�l�[�W���[
	CItemManager*				m_pFieldItemManager;		//�t�B�[���h�A�C�e��
	CMapObjManager*				m_pMapObjManager;			//�}�b�v�I�u�W�F
	CParticleManager*			m_pParticleManager;			//�p�[�e�B�N��
	CUIManager*					m_pUIManager;				//UI�}�l�[�W���[

	CMapData*					m_pMap;						//�}�b�v
	CTurn*						m_pTurn;					//�^�[���N���X
	CSky*						m_pSky;						//�X�J�C�h�[��
	static bool					m_MapMake;					//�}�b�v�f�[�^���Đ�������
	static bool					m_OldMapMake;				//�O�t���[���̃}�b�v�Đ����t���O��ێ�

	static int					m_nPlayerLevel;				//�K�w�����肽���_�̃v���C���[�̃��x��

	static int					m_nGameClaer;				//�Q�[�����N���A�������A�Q�[���I�[�o�[�ɂȂ�����
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
	//�}�b�v�̍Đ����t���O�𗧂Ă�
	static void MapReMake ()	{m_MapMake = true;}	

	//�v���C���[�̃��x�����擾
	//static int GetPlayerLevel()	{return m_nPlayerLevel;}

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