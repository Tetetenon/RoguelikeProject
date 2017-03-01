#include "EquipmentCommandCursor.h"
#include "Graphics.h"
#include "Input.h"

#include "TextureManager.h"

//---------------------------------------------------------------------------------------
//�}�N����`
//---------------------------------------------------------------------------------------


//�E�C���h�E�T�C�Y
#define WINDOW_WIDHT  200
#define WINDOW_HEIGHT  30

//---------------------------------------------------------------------------------------
//�ÓI�����o��`
//---------------------------------------------------------------------------------------
CEquipmentCommandCursor* CEquipmentCommandCursor::m_pEquipmentCommandCursor = NULL;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEquipmentCommandCursor::CEquipmentCommandCursor(void)
{
	//�{�^�����̓C���^�[�o���^�C���̏�����
	m_nInterval = 0;
	//���Ԗڂ̃A�C�e����I�����Ă��邩
	m_Command = 0;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//�|���S�����̐ݒ�
	SetVertex();

	//�|���S���ʒu���̐ݒ�
	SetPos();
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CEquipmentCommandCursor::~CEquipmentCommandCursor(void)
{
	//���Ԗڂ̃A�C�e����I�����Ă��邩
	m_Command = 0;
	//�{�^�����̓C���^�[�o���^�C���̏�����
	m_nInterval = 0;
}
//---------------------------------------------------------------------------------------
//���̂̍쐬
//---------------------------------------------------------------------------------------
void CEquipmentCommandCursor::Create()
{
	//���g���Ȃ���΍쐬
	if (!m_pEquipmentCommandCursor)
	{
		m_pEquipmentCommandCursor = new CEquipmentCommandCursor;
	}
}
//---------------------------------------------------------------------------------------
//���̂̍폜
//---------------------------------------------------------------------------------------
void CEquipmentCommandCursor::Delete()
{
	//���̂�����΍폜
	if (m_pEquipmentCommandCursor)
	{
		delete m_pEquipmentCommandCursor;
		m_pEquipmentCommandCursor = NULL;
	}
}
//---------------------------------------------------------------------------------------
//���̂̃|�C���^��n��
//---------------------------------------------------------------------------------------
CEquipmentCommandCursor* CEquipmentCommandCursor::GetPointer()
{
	//�O�̂��ߍ쐬�֐����Ăяo��
	Create();
	return m_pEquipmentCommandCursor;
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CEquipmentCommandCursor::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
		
	// �A���t�@�E�u�����f�B���O���s��
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���ߏ������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���Z�b�g
	pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_SELECT_WINDOW));
	//�|���S���̕`��
	//���_�����O���������Ă���ꍇUp
	//���̂ق���primitive
	pDevice -> DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��List�i�O�p�`�`���jStrip(�Ȃ��č��)
		NUM_POLYGON,				//�|���S����
		m_aVertex,					//�z��̐擪�A�h���X
		sizeof(VERTEX_2D)			//�f�[�^�̑傫��
		);
}

//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CEquipmentCommandCursor::Update()
{
	//�{�^�����͂̃C���^�[�o���^�C�������Z
	m_nInterval++;

	//�g�p�@��I�����Ă���ꍇ�̂ݍX�V
	if(m_pEquipmentCommandWindow->GetDrawFlg())
	{
		//if ((CInput::GetKeyTrigger(DIK_W) || CInput::GetJoyAxis(0, JOY_Y) <= -JoyMoveCap) && m_nInterval >= ButtonIntervalTime)
		//{
		//		//��Ɉړ�
		//		m_Command --;
		//
		//		//���[�v
		//		if (m_Command < 0)
		//			m_Command = COMMAND_MAX - 1;
		//
		//		//�ʒu���Đݒ�
		//		SetPos();
		//
		//		//���͂������Ȃ����Ƃ��ăC���^�[�o���^�C����0�ɖ߂�
		//		m_nInterval = 0;
		//}
		//
		//if ((CInput::GetKeyTrigger(DIK_S) || CInput::GetJoyAxis(0, JOY_Y) >= JoyMoveCap) && m_nInterval >= ButtonIntervalTime)
		//{
		//		//���Ɉړ�
		//		m_Command ++;
		//
		//		//���[�v
		//		m_Command %= COMMAND_MAX;
		//		//�ʒu�����Đݒ�
		//		SetPos();
		//
		//		//���͂������Ȃ����Ƃ��ăC���^�[�o���^�C����0�ɖ߂�
		//		m_nInterval = 0;
		//}
	}
}

//---------------------------------------------------------------------------------------
//�|���S�����ݒ�
//---------------------------------------------------------------------------------------
void CEquipmentCommandCursor::SetVertex ()
{	
	//�ʒu���ݒ�
	m_aVertex[0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT, (float)WINDOW_HEIGHT * (m_Command + 1)				+ WINDOW_HEIGHT, 0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT				, (float)WINDOW_HEIGHT * (m_Command + 1)				+ WINDOW_HEIGHT, 0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT, (float)WINDOW_HEIGHT * (m_Command + 1) + WINDOW_HEIGHT+ WINDOW_HEIGHT, 0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT				,(float)WINDOW_HEIGHT * (m_Command + 1) + WINDOW_HEIGHT	+ WINDOW_HEIGHT,0.0f);

	//�p�[�X�y�N�e�B�u�ݒ�?
	m_aVertex[0].rhw = 1.0f;
	m_aVertex[1].rhw = 1.0f;
	m_aVertex[2].rhw = 1.0f;
	m_aVertex[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	m_aVertex[0].col = D3DCOLOR_RGBA(255,255,255,255);
	m_aVertex[1].col = D3DCOLOR_RGBA(255,255,255,255);
	m_aVertex[2].col = D3DCOLOR_RGBA(255,255,255,255);
	m_aVertex[3].col = D3DCOLOR_RGBA(255,255,255,255);

	//�|���S���ƃe�N�X�`���̒��_��Ή�������
	m_aVertex[0].tex = D3DXVECTOR2(0.0f,0.0f);
	m_aVertex[1].tex = D3DXVECTOR2(1.0f,0.0f);
	m_aVertex[2].tex = D3DXVECTOR2(0.0f,1.0f);
	m_aVertex[3].tex = D3DXVECTOR2(1.0f,1.0f);
}

//---------------------------------------------------------------------------------------
//�|���S���ʒu�ݒ�
//---------------------------------------------------------------------------------------
void CEquipmentCommandCursor::SetPos()
{
	//�ʒu���ݒ�
	m_aVertex[0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT, (float)WINDOW_HEIGHT * (m_Command + 1) + WINDOW_HEIGHT, 0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT, (float)WINDOW_HEIGHT * (m_Command + 1) + WINDOW_HEIGHT, 0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT, (float)WINDOW_HEIGHT * (m_Command + 1) + WINDOW_HEIGHT + WINDOW_HEIGHT, 0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT, (float)WINDOW_HEIGHT * (m_Command + 1) + WINDOW_HEIGHT + WINDOW_HEIGHT, 0.0f);
}
//---------------------------------------------------------------------------------------
//�I�𒆂̃R�}���h�ԍ���Ԃ�
//---------------------------------------------------------------------------------------
int CEquipmentCommandCursor::GetCommand()
{
	return m_Command;
}

//---------------------------------------------------------------------------------------
//�����o�ϐ��̃|�C���^�̐ݒ�
//---------------------------------------------------------------------------------------
void CEquipmentCommandCursor::SetPointer()
{
	//�|�C���^�̎擾
	m_pEquipmentCommandWindow = CEquipmentCommandWindow::GetPointer();
}
