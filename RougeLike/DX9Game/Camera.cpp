#include "Camera.h"
#include "Input.h"
#include "define.h"
#include "GameState.h"
//�e�N���X��C3DObj
#include"Unit.h"

#include "Sky.h"
#include"UnitManager.h"
#include "Turn.h"

#define CAMERA_POS_X 0.0f
#define CAMERA_POS_Y 15.0f
#define CAMERA_POS_Z -10.0f

//�f�o�b�O�p�J�����ʒu(���ɖ߂�����)
#define DEBUG_CAMERA_POS_Y 160.0f
#define DEBUG_CAMERA_POS_Z -1.0f

#define LOOK_POS_X	0.0f
#define LOOK_POS_Y	1.0f
#define LOOK_POS_Z	0.0f

#define UP_DIR_X	0.0f
#define UP_DIR_Y	1.0f
#define UP_DIR_Z	0.0f


D3DXMATRIX CCamera::m_view;	//�r���[�}�g���b�N�X
CCamera* CCamera::m_pCamera = NULL;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CCamera::CCamera(CGameScene* pScene):
	C3DObj(pScene),
	m_pSky(NULL),
	m_pPlayer(NULL),
	m_fFovy(FOVY),
	m_fAspect((float)SCREEN_WIDTH / SCREEN_HEIGHT),
	m_fZNear(NEAR_CLIP),
	m_fZFar(FAR_CLIP)
{
	//�J����ID��ݒ�
	m_uID = ID_CAMERA;

	//�r���[�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_view);

	m_pos = D3DXVECTOR3(CAMERA_POS_X,CAMERA_POS_Y,CAMERA_POS_Z);
	m_pos2 = D3DXVECTOR3(CAMERA_POS_X,DEBUG_CAMERA_POS_Y,DEBUG_CAMERA_POS_Z);
	
	m_at = D3DXVECTOR3(LOOK_POS_X,LOOK_POS_Y,LOOK_POS_Z);
	m_at2 = m_at;

	m_Up = D3DXVECTOR3(UP_DIR_X,UP_DIR_Y,UP_DIR_Z);
	m_Up2 = m_Up;

	
	m_cp = CP_TPVIEW;

	//�^�C�}�[�̏�����
	m_nTimer = 0.0f;

	//�J�������[�h�ؑփt���O
	m_bSwitch = false;
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CCamera::~CCamera(void)
{
}
//---------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̍쐬
//---------------------------------------------------------------------------------------
void CCamera::Create(CGameScene* pScene)
{
	//�|�C���^�̒��g���Ȃ���΍쐬
	if (!m_pCamera)
	{
		m_pCamera = new CCamera(pScene);
	}
}
//---------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̍폜
//---------------------------------------------------------------------------------------
void CCamera::Delete()
{
	//NULL�`�F�b�N
	if (m_pCamera)
	{
		//�폜
		delete m_pCamera;
		//���g�����ꂢ�ɂ���
		m_pCamera = NULL;
	}
}
//---------------------------------------------------------------------------------------
//�I�u�W�F�N�g�̃|�C���^��n��
//---------------------------------------------------------------------------------------
CCamera* CCamera::GetPointer()
{
	return m_pCamera;
}
//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void CCamera::Init ()
{
	D3DXMATRIX world;
	//�s��̍쐬
	D3DXMatrixTranslation(&world,CAMERA_POS_X,CAMERA_POS_Y,CAMERA_POS_Z);
	SetWorld(world);

	//�X�J�C�h�[���擾
	m_pSky = CSky::GetPointer();

	//�v���C���[�I�u�W�F�N�g�̒T���A�ݒ�
	CUnitManager* pUnitManager = CUnitManager::GetPointer();


	m_pPlayer = pUnitManager->Find(OBJ_NUM_PLAYER);
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CCamera::Update()
{
	//�J�����ʒu���f�o�b�O�ƒʏ��؂�ւ���
	if(CInput::GetKeyTrigger(DIK_C))
	{
		m_bSwitch = !m_bSwitch;
	}
}
//---------------------------------------------------------------------------------------
//�X�V�㏈��
//---------------------------------------------------------------------------------------
void CCamera::PostUpdate()
{
	//����Ɋ�Â���������W�n�p�[�X�y�N�e�B�u�ˉe�s��̍쐬
	D3DXMatrixPerspectiveFovLH(&m_proj,m_fFovy,m_fAspect,m_fZNear,m_fZFar);

	if(m_pPlayer)
	{
		D3DXVECTOR3 Pos = m_pPlayer ->GetPos();
		if(m_bSwitch)
		{
			m_pos = D3DXVECTOR3(CAMERA_POS_X,DEBUG_CAMERA_POS_Y,DEBUG_CAMERA_POS_Z);

			D3DXVec3TransformCoord(&m_at,&D3DXVECTOR3(LOOK_POS_X,LOOK_POS_Y,LOOK_POS_Z),&m_pPlayer ->GetWorld());
			
			m_at.x = 0.0f;
			m_at.y = 1.0f;
			m_at.z = 0.0f;
		}
		else
		{
			//�퓬���ȊO�J�����ʒu���X�V
			if (m_pPlayer->GetUnitTurnState() != CTurn::GAME_STATE_ATTACK)
			{
					m_pos = D3DXVECTOR3(Pos.x + CAMERA_POS_X,CAMERA_POS_Y,Pos.z  + CAMERA_POS_Z);

					D3DXMATRIX PlayerWorld = m_pPlayer ->GetWorld();

					D3DXVec3TransformCoord(&m_at,&D3DXVECTOR3(LOOK_POS_X,LOOK_POS_Y,LOOK_POS_Z),&PlayerWorld);
					
					m_at.x = PlayerWorld._41;
					m_at.y = 1.0f;
					m_at.z = PlayerWorld._43;
			}
		}

		D3DXVec3TransformNormal(&m_Up,&D3DXVECTOR3(UP_DIR_X,UP_DIR_Y,UP_DIR_Z),&m_pPlayer ->GetWorld());
		
		m_Up.x = 0.0f;
		m_Up.y = 1.0f;
		m_Up.z = 0.0f;

		D3DXMatrixLookAtLH(&m_view,&m_pos,&m_at,&m_Up);

		SetPos(m_pos);
	}
	else
	{
		//������W�n�r���[�s��̍쐬
		D3DXMatrixLookAtLH(&m_view,&GetPos(),&(GetPos() + GetForward()),&GetUp());
	}
	
	//�X�J�C�h�[���|�C���^NULL�`�F�b�N
	if (m_pSky) 
	{
		//�X�V
		m_pSky->PostUpdate();
	}
}
//---------------------------------------------------------------------------------------
//�`��O����
//---------------------------------------------------------------------------------------
void CCamera::PreDraw()
{
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();

	//�������̐ݒ���g�p���A�������̃g�����X�t�H�[�����s��
	pD -> SetTransform(D3DTS_PROJECTION,&m_proj);

	pD -> SetTransform(D3DTS_VIEW,&m_view);
	
	//�X�J�C�h�[���|�C���^NULL�`�F�b�N
	if (m_pSky) 
	{
		//�`��
		m_pSky->PreDraw();
	}
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CCamera::Draw()
{
}
//---------------------------------------------------------------------------------------
//�������`��
//---------------------------------------------------------------------------------------
void CCamera::DrawAlpha()
{

}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CCamera::Fin()
{
	m_pSky = NULL;
}
