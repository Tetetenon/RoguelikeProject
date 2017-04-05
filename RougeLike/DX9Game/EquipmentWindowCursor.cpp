#include "EquipmentWindowCursor.h"
#include "EquipmentWindow.h"
#include "EquipmentCommandWindow.h"
#include "ItemWindow.h"
#include "Graphics.h"
#include "Input.h"

#include "TextureManager.h"
//---------------------------------------------------------------------------------------
//�}�N����`
//---------------------------------------------------------------------------------------


//�E�C���h�E�T�C�Y
#define WINDOW_WIDHT  300
#define WINDOW_HEIGHT  30

//---------------------------------------------------------------------------------------
//�ÓI�����o�ϐ���`
//---------------------------------------------------------------------------------------
CEquipmentWindowCursor* CEquipmentWindowCursor::m_pEquiomentInventoryCursor = NULL;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEquipmentWindowCursor::CEquipmentWindowCursor(void)
{
	//�I�𒆂̑����ԍ��̏�����
	m_Number = 0;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//�|���S�����̐ݒ�
	SetVertex();

	//�|���S���ʒu���̐ݒ�
	SetPos();

	//�{�^�����͎��Ԃ�������
	m_nInterval = 0;
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CEquipmentWindowCursor::~CEquipmentWindowCursor(void)
{
	//�I�𒆂̑����ԍ��̏�����
	m_Number = 0;
	//�{�^�����͂̎��Ԃ�������
	m_nInterval = 0;
}

//---------------------------------------------------------------------------------------
//���̂̍쐬
//---------------------------------------------------------------------------------------
void CEquipmentWindowCursor::Create()
{
	//���g��������΍쐬
	if (!m_pEquiomentInventoryCursor)
	{
		m_pEquiomentInventoryCursor = new CEquipmentWindowCursor;
	}
}
//---------------------------------------------------------------------------------------
//���̂̍폜
//---------------------------------------------------------------------------------------
void CEquipmentWindowCursor::Delete()
{
	//���̂�����΍폜
	if (m_pEquiomentInventoryCursor)
	{
		delete m_pEquiomentInventoryCursor;
		m_pEquiomentInventoryCursor = NULL;
	}
}
//---------------------------------------------------------------------------------------
//���̂̃|�C���^��n��
//---------------------------------------------------------------------------------------
CEquipmentWindowCursor* CEquipmentWindowCursor::GetPointer()
{
	//�O�̂��ߍ쐬�֐����Ă�
	Create();
	return m_pEquiomentInventoryCursor;
}

//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CEquipmentWindowCursor::Draw()
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
		D3DPT_TRIANGLESTRIP,          //�v���~�e�B�u�̎��List�i�O�p�`�`���jStrip(�Ȃ��č��)
		NUM_POLYGON,                 //�|���S����
		m_aVertex,            //�z��̐擪�A�h���X
		sizeof(VERTEX_2D)            //�f�[�^�̑傫��
		);
}

//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CEquipmentWindowCursor::Update()
{
	//�{�^�����͂���̌o�ߎ��Ԃ����Z����
	m_nInterval++;

	//�A�C�e���I�𒆂̂ݑ���\
	//W�������͏����͂����A���A�A�����͂�h�~����
	if((CInput::GetKeyTrigger(DIK_W) || (CInput::GetJoyAxis(0,JOY_Y) <= -JoyMoveCap)) && m_nInterval >= ButtonIntervalTime)
	{
		//��Ɉړ�
		m_Number --;

		//���[�v
		if (m_Number < 0)
			m_Number = EQUIPMENT_NUM_MAX - 1;

		//�ʒu���Đݒ�
		SetPos();
		//�{�^�����͂���̃C���^�[�o���^�C����0�ɂ���
		m_nInterval = 0;
	}

	if((CInput::GetKeyTrigger(DIK_S) || (CInput::GetJoyAxis(0,JOY_Y) >= JoyMoveCap)) && m_nInterval >= ButtonIntervalTime)
	{
		//���Ɉړ�
		m_Number ++;

		//���[�v
		m_Number %= EQUIPMENT_NUM_MAX;

		//�ʒu�����Đݒ�
		SetPos();
		//�{�^�����͂���̃C���^�[�o���^�C����0�ɂ���
		m_nInterval = 0;
	}
	//����I�������ꍇ�A�A�C�e���E�B���h�E�̂ق��փJ�[�\���X�V���ڂ�
	if (((CInput::GetKeyTrigger(DIK_D) || CInput::GetKeyTrigger(DIK_A) || abs((long)CInput::GetJoyAxis(0, JOY_X)) >= JoyMoveCap)) && m_nInterval >= ButtonIntervalTime)
	{
		//�A�C�e���E�B���h�E�̍X�V
		m_pItemWindow->UpdateFlgChange(true);
		//�{�^�����͌o�ߎ��Ԃ�0��
		m_nInterval = 0;
	}
	
}

//---------------------------------------------------------------------------------------
//�|���S�����ݒ�
//---------------------------------------------------------------------------------------
void CEquipmentWindowCursor::SetVertex ()
{	
	//�ʒu���ݒ�
	m_aVertex[0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_Number + 1)					+ WINDOW_HEIGHT,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT				,(float)WINDOW_HEIGHT * (m_Number + 1)					+ WINDOW_HEIGHT,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_Number + 1) + WINDOW_HEIGHT	+ WINDOW_HEIGHT,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT				,(float)WINDOW_HEIGHT * (m_Number + 1) + WINDOW_HEIGHT	+ WINDOW_HEIGHT,0.0f);

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
void CEquipmentWindowCursor::SetPos()
{
	//�ʒu���ݒ�
	m_aVertex[0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT, (float)WINDOW_HEIGHT * (m_Number + 1)					+ WINDOW_HEIGHT, 0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT				, (float)WINDOW_HEIGHT * (m_Number + 1)					+ WINDOW_HEIGHT, 0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT, (float)WINDOW_HEIGHT * (m_Number + 1) + WINDOW_HEIGHT	+ WINDOW_HEIGHT, 0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT				, (float)WINDOW_HEIGHT * (m_Number + 1) + WINDOW_HEIGHT	+ WINDOW_HEIGHT, 0.0f);
}
//---------------------------------------------------------------------------------------
//�I�𒆂̃A�C�e���ԍ���Ԃ�
//---------------------------------------------------------------------------------------
int CEquipmentWindowCursor::GetItemNum()
{
	return m_Number;
}

//---------------------------------------------------------------------------------------
//�����o�ϐ��̃|�C���^��ݒ肷��
//---------------------------------------------------------------------------------------
void CEquipmentWindowCursor::SetPointer()
{
	//�|�C���^�̎擾
	m_pEquipmentWindow = CEquipmentWindow::GetPointer();
	m_pEquipmentCommandWindow = CEquipmentCommandWindow::GetPointer();
	m_pItemWindow = CItemWindow::GetPointer();
}
