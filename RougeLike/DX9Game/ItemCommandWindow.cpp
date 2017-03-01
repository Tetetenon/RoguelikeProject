#include "ItemCommandWindow.h"
#include "Graphics.h"
#include "Input.h"
#include "Turn.h"
#include "ItemWindow.h"
#include "TextureManager.h"
#include "Unit.h"
#include "MenuWindow.h"
#include "UnitManager.h"

//---------------------------------------------------------------------------------------
//�}�N����`
//---------------------------------------------------------------------------------------

//�E�C���h�E�T�C�Y
#define WINDOW_WIDHT 200
#define WINDOW_HEIGHT 30


//---------------------------------------------------------------------------------------
//�ÓI�����o��`
//---------------------------------------------------------------------------------------
CItemCommandWindow* CItemCommandWindow::m_pItemCommandWindow = NULL;
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CItemCommandWindow::CItemCommandWindow(void)
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

	//�L�[���͂��s���Ă���̌o�ߎ��Ԃ�������
	m_EnterInterval = 0;
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CItemCommandWindow::~CItemCommandWindow(void)
{
}
//---------------------------------------------------------------------------------------
//���̂̐���
//---------------------------------------------------------------------------------------
void CItemCommandWindow::Create()
{
	//���̂����݂��Ă��Ȃ��ꍇ�A�쐬
	if (!m_pItemCommandWindow)
	{
		m_pItemCommandWindow = new CItemCommandWindow;
	}
}
//---------------------------------------------------------------------------------------
//���̂̍폜
//---------------------------------------------------------------------------------------
void CItemCommandWindow::Delete()
{
	//���̗̂L���̊m�F
	if (m_pItemCommandWindow)
	{
		//���g������΍폜
		delete m_pItemCommandWindow;
		m_pItemCommandWindow = NULL;
	}
}
//---------------------------------------------------------------------------------------
//���g�̃|�C���^��n��
//---------------------------------------------------------------------------------------
CItemCommandWindow* CItemCommandWindow::GetPointer()
{
	//�O�̂��߁A�쐬
	Create();
	return m_pItemCommandWindow;
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CItemCommandWindow::UpDate()
{
	m_EnterInterval ++;

	//L�Ō���
	if((CInput::GetKeyTrigger(DIK_L) || CInput::GetJoyTrigger(0,3)) && m_EnterInterval > 30)
	{

		//�A�C�e�����g�p
		m_pPlayer->SetState(CTurn::GAME_STATE_ITEM_USE);
		
		//���g�̃t���O��|��
		DrawFlgChange();

		//�A�C�e���E�C���h�E�̕`��t���O��|��
		m_pItemWindow->DrawFlgChange(false);
		//���j���[�E�B���h�E�̕`��t���O��|��
		m_pMenuWindow->ChangDrawFlg();
		m_EnterInterval = 0;
	}

	//K�Ŗ߂�
	if((CInput::GetKeyTrigger(DIK_K) || CInput::GetJoyTrigger(0,2)) && m_EnterInterval > 30)
	{
		//���g�̃t���O��|��
		DrawFlgChange();

		//�A�C�e���E�C���h�E�̕`��t���O��|��
		m_pItemWindow->DrawFlgChange(false);
		m_EnterInterval = 0;
	}
	
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CItemCommandWindow::Draw()
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
	for(int i = 0;i < COMMAND_MAX;i++)
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
void CItemCommandWindow::SetVertex()
{
	for(int i = 0;i < COMMAND_MAX;i++)
	{
		//�ʒu���ݒ�
		m_aVertex[i][0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (i + 1)					+ WINDOW_HEIGHT,0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (i + 1)					+ WINDOW_HEIGHT,0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	+ WINDOW_HEIGHT,0.0f);
		m_aVertex[i][3].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	+ WINDOW_HEIGHT,0.0f);

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
void CItemCommandWindow::SetFontPos()
{
	for(int i = 0;i < COMMAND_MAX;i++)
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
void CItemCommandWindow::DrawFlgChange()
{
	m_bDrawFlg = !m_bDrawFlg;
}
//---------------------------------------------------------------------------------------
//�R�}���h���̐ݒ�
//---------------------------------------------------------------------------------------
void CItemCommandWindow::SetCommand()
{
	lstrcpyn(m_CommandName[0],_T("�g��")	,sizeof(LPCTSTR) * FONT_MAX / 2);
	lstrcpyn(m_CommandName[1],_T("����")	,sizeof(LPCTSTR) * FONT_MAX / 2);
	lstrcpyn(m_CommandName[2],_T("�̂Ă�")	,sizeof(LPCTSTR) * FONT_MAX / 2);
}

//---------------------------------------------------------------------------------------
//�����o�ϐ��̃|�C���^��ݒ肷��
//---------------------------------------------------------------------------------------
void CItemCommandWindow::SetPointer()
{

	//���j�b�g�}�l�[�W���[�̃|�C���^���擾
	CUnitManager* pUnitManager = CUnitManager::GetPointer();
	//�v���C���[�̃|�C���^���擾
	m_pPlayer = pUnitManager->GetPlayerPointer();
	//���j���[�E�B���h�E�ւ̃|�C���^���擾
	m_pMenuWindow = CMenuWindow::GetPointer();
	//�A�C�e���E�B���h�E�̃|�C���^���擾
	m_pItemWindow = CItemWindow::GetPointer();
}
