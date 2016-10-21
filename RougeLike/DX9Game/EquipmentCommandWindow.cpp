#include "EquipmentCommandWindow.h"
#include "Graphics.h"
#include "Input.h"
#include "Turn.h"
#include "EquipmentWindow.h"
#include "TextureManager.h"
#include "Player.h"
#include "ItemWindow.h"
#include "MenuWindow.h"

//---------------------------------------------------------------------------------------
//�}�N����`
//---------------------------------------------------------------------------------------

//�E�C���h�E�T�C�Y
#define WINDOW_WIDHT 200
#define WINDOW_HEIGHT 30


//---------------------------------------------------------------------------------------
//�ÓI�����o��`
//---------------------------------------------------------------------------------------
_TCHAR				CEquipmentCommandWindow::m_CommandName[EQUIPMENT_COMMAND_MAX][FONT_MAX];			//�R�}���h��
LPD3DXFONT			CEquipmentCommandWindow::m_Font;											//�`��p�t�H���g
RECT				CEquipmentCommandWindow::m_Pos[EQUIPMENT_COMMAND_MAX];								//�E�B���h�E�\���ʒu

bool				CEquipmentCommandWindow::m_bDrawFlg;										//�`��t���O

VERTEX_2D			CEquipmentCommandWindow::m_aVertex[EQUIPMENT_COMMAND_MAX][NUM_VERTEX];				//�|���S�����_���i�[�p
CTurn				CEquipmentCommandWindow::m_Turn;											//�X�e�[�g�ύX
CEquipmentInventory	CEquipmentCommandWindow::m_Inbentory;
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEquipmentCommandWindow::CEquipmentCommandWindow(void)
{
	//�����o������
	m_bDrawFlg = false;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//���i�[�p�t�H���g��ݒ�
	//�t�H���g�ւ̃|�C���^��������
	m_Font = NULL;

	//�t�H���g��ݒ�
	D3DXCreateFont(pDevice, 12, 12, 1, 0, FALSE, SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL,&m_Font);


	//�|���S�����̐ݒ�
	SetVertex();

	//�t�H���g�\���ʒu�̐ݒ�
	SetFontPos();

	//�R�}���h���̐ݒ�
	SetCommand();
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CEquipmentCommandWindow::~CEquipmentCommandWindow(void)
{
}

//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::Init()
{
	m_EnterInterval = 0;
}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::Fin()
{

}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::UpDate()
{
	//�g�p�@��I�����Ă���ꍇ�̂ݍX�V
	if(m_bDrawFlg)
	{
		m_EnterInterval ++;

		//L�Ō���
		if(CInput::GetKeyTrigger(DIK_L) && m_EnterInterval > 30)
		{
			//���g�̃t���O��|��
			DrawFlgChange();
			//�����E�B���h�E�̕`��t���O��|��
			CEquipmentInventory::DrawFlgChange();
			//���j���[�E�B���h�E�̕`��t���O��|��
			CMenuWindow::ChangDrawFlg();
			m_EnterInterval = 0;
		}

		//K�Ŗ߂�
		if(CInput::GetKeyTrigger(DIK_K) && m_EnterInterval > 30)
		{
			//���g�̃t���O��|��
			DrawFlgChange();
			m_EnterInterval = 0;
		}
	}
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::Draw()
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	
	// �A���t�@�E�u�����f�B���O���s��
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���ߏ������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//�A�C�e���E�C���h�E���`��
	for(int i = 0;i < EQUIPMENT_COMMAND_MAX;i++)
	{
		//�e�N�X�`���Z�b�g
		pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_WINDOW));
		//�|���S���̕`��
		//���_�����O���������Ă���ꍇUp
		//���̂ق���primitive
		pDevice -> DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP,          //�v���~�e�B�u�̎��List�i�O�p�`�`���jStrip(�Ȃ��č��)
			NUM_POLYGON,                 //�|���S����
			m_aVertex[i],            //�z��̐擪�A�h���X
			sizeof(VERTEX_2D)            //�f�[�^�̑傫��
			);
		// �e�L�X�g�`��
		m_Font->DrawText(NULL,m_CommandName[i],-1, &m_Pos[i], DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0xff));
	}

}
//---------------------------------------------------------------------------------------
//�|���S�����𖄂߂�
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::SetVertex()
{
	for(int i = 0;i < EQUIPMENT_COMMAND_MAX;i++)
	{
		//�ʒu���ݒ�
		m_aVertex[i][0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (i + 1)					,0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (i + 1)					,0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	,0.0f);
		m_aVertex[i][3].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	,0.0f);

		//�p�[�X�y�N�e�B�u�ݒ�?
		m_aVertex[i][0].rhw = 1.0f;
		m_aVertex[i][1].rhw = 1.0f;
		m_aVertex[i][2].rhw = 1.0f;
		m_aVertex[i][3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		m_aVertex[i][0].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][1].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][2].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][3].col = D3DCOLOR_RGBA(255,255,255,255);

		//�|���S���ƃe�N�X�`���̒��_��Ή�������
		m_aVertex[i][0].tex = D3DXVECTOR2(0.0f,0.0f);
		m_aVertex[i][1].tex = D3DXVECTOR2(1.0f,0.0f);
		m_aVertex[i][2].tex = D3DXVECTOR2(0.0f,1.0f);
		m_aVertex[i][3].tex = D3DXVECTOR2(1.0f,1.0f);
	}
}
//---------------------------------------------------------------------------------------
//�t�H���g���̐ݒ�
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::SetFontPos()
{
	for(int i = 0;i < EQUIPMENT_COMMAND_MAX;i++)
	{
		m_Pos[i].left	= (LONG)(m_aVertex[i][0].pos.x + 50.0f);
		m_Pos[i].top	= (LONG)(m_aVertex[i][1].pos.y + 10.0f);
		m_Pos[i].right	= (LONG)m_aVertex[i][3].pos.x;
		m_Pos[i].bottom	= (LONG)m_aVertex[i][2].pos.y;
	}
}
//---------------------------------------------------------------------------------------
//�`��t���O���O������ON/OFF����
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::DrawFlgChange()
{
	m_bDrawFlg = !m_bDrawFlg;
}
//---------------------------------------------------------------------------------------
//�R�}���h���̐ݒ�
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::SetCommand()
{
	lstrcpyn(m_CommandName[0],_T("�߂�")	,sizeof(LPCTSTR) * FONT_MAX / 2);
}