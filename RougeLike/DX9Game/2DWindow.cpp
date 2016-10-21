//---------------------------------------------------------------------------------------
//2D�E�C���h�E���N���X
//---------------------------------------------------------------------------------------
#include "2DWindow.h"
#include "Graphics.h"

#include "TextureManager.h"

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
C2DWindow::C2DWindow(void)
{
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
C2DWindow::~C2DWindow(void)
{
}

//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void C2DWindow::Init()
{

}

//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void C2DWindow::Fin()
{

}

//---------------------------------------------------------------------------------------
//�`�揈��
//---------------------------------------------------------------------------------------
void C2DWindow::Draw()
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
void C2DWindow::Update()
{
}

//---------------------------------------------------------------------------------------
//�|���S�����ݒ�
//---------------------------------------------------------------------------------------
void C2DWindow::SetVertex ()
{	
	//�ʒu���ݒ�
	m_aVertex[0].pos = D3DXVECTOR3((float)0				,(float)0				,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH	,(float)0				,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)0				,(float)SCREEN_HEIGHT	,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH	,(float)SCREEN_HEIGHT	,0.0f);

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
void C2DWindow::SetPos()
{
	//�ʒu���ݒ�
	m_aVertex[0].pos = D3DXVECTOR3((float)0				,(float)0				,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH	,(float)0				,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)0				,(float)SCREEN_HEIGHT	,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH	,(float)SCREEN_HEIGHT	,0.0f);
}