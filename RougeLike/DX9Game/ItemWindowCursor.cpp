#include "ItemWindowCursor.h"
#include "Graphics.h"
#include "Input.h"

#include "TextureManager.h"
//---------------------------------------------------------------------------------------
//�}�N����`
//---------------------------------------------------------------------------------------


//�E�C���h�E�T�C�Y
#define WINDOW_WIDHT  300
#define WINDOW_HEIGHT  30

int					CInventoryCursor::m_Number = 0;				//���ݑI�����Ă���A�C�e�������Ԗڂ̕������Ǘ�����


//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CInventoryCursor::CInventoryCursor(void)
{
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
CInventoryCursor::~CInventoryCursor(void)
{
}

//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void CInventoryCursor::Init()
{

}
//---------------------------------------------------------------------------------------
//�I��
//---------------------------------------------------------------------------------------
void CInventoryCursor::Fin()
{

}

//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CInventoryCursor::Draw()
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
void CInventoryCursor::Update()
{
	//�A�C�e���I�𒆂̂ݑ���\
	if(CInventory::GetDrawFlg() && !CCommandWindow::GetDrawFlg())
	{
		if(CInput::GetKeyTrigger(DIK_W))
		{
			//�J�[�\������Ɉړ��ł��邩�m�F
			if(m_Number > 0)
			{
				//��Ɉړ�
				m_Number --;
				//�ʒu���Đݒ�
				SetPos();
			}
		}

		if(CInput::GetKeyTrigger(DIK_S))
		{
			//�J�[�\�������Ɉړ��ł��邩�m�F
			if(m_Number < ITEM_NUM_MAX - 1)
			{
				//���Ɉړ�
				m_Number ++;
				//�ʒu�����Đݒ�
				SetPos();
			}
		}
	}
}

//---------------------------------------------------------------------------------------
//�|���S�����ݒ�
//---------------------------------------------------------------------------------------
void CInventoryCursor::SetVertex ()
{	
	//�ʒu���ݒ�
	m_aVertex[0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_Number + 1)					,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (m_Number + 1)					,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_Number + 1) + WINDOW_HEIGHT	,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (m_Number + 1) + WINDOW_HEIGHT	,0.0f);

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
void CInventoryCursor::SetPos()
{
	//�ʒu���ݒ�
	m_aVertex[0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_Number + 1)					,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (m_Number + 1)					,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (m_Number + 1) + WINDOW_HEIGHT	,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (m_Number + 1) + WINDOW_HEIGHT	,0.0f);
}
//---------------------------------------------------------------------------------------
//�I�𒆂̃A�C�e���ԍ���Ԃ�
//---------------------------------------------------------------------------------------
int CInventoryCursor::GetItemNum()
{
	return m_Number;
}