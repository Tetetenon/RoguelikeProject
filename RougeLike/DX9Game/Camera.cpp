#include "Camera.h"
#include "Input.h"
#include "define.h"
#include "GameState.h"
//�e�N���X��C3DObj

#include "Sky.h"

#include "Turn.h"

#define CAMERA_POS_X 0.0f
#define CAMERA_POS_Y 15.0f
#define CAMERA_POS_Z -15.0f

//�f�o�b�O�p�J�����ʒu(���ɖ߂�����)
#define DEBUG_CAMERA_POS_Y 120.0f
#define DEBUG_CAMERA_POS_Z -1.0f

#define LOOK_POS_X	0.0f
#define LOOK_POS_Y	1.0f
#define LOOK_POS_Z	0.0f

#define UP_DIR_X	0.0f
#define UP_DIR_Y	1.0f
#define UP_DIR_Z	0.0f


D3DXMATRIX CCamera::m_view;	//�r���[�}�g���b�N�X

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
//������
//---------------------------------------------------------------------------------------
void CCamera::Init ()
{
	D3DXMATRIX world;
	//�s��̍쐬
	D3DXMatrixTranslation(&world,CAMERA_POS_X,CAMERA_POS_Y,CAMERA_POS_Z);
	SetWorld(world);

	//�X�J�C�h�[������
	m_pSky = (CSky*)Find(ID_SKY);

	//�v���C���[�I�u�W�F�N�g�̒T���A�ݒ�
	m_pPlayer = (CPlayer*)Find(ID_PLAYER);
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
	//�퓬���ȊO�J�����ʒu���X�V
	if(CTurn::GetState() != GAME_STATE_ATTACK)
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
				m_pos = D3DXVECTOR3(Pos.x + CAMERA_POS_X,CAMERA_POS_Y,Pos.z  + CAMERA_POS_Z);

				D3DXMATRIX PlayerWorld = m_pPlayer ->GetWorld();

				D3DXVec3TransformCoord(&m_at,&D3DXVECTOR3(LOOK_POS_X,LOOK_POS_Y,LOOK_POS_Z),&PlayerWorld);
				
				m_at.x = PlayerWorld._41;
				m_at.y = 1.0f;
				m_at.z = PlayerWorld._43;
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

}
