#include "Title.h"
#include "Graphics.h"
#include "TextureManager.h"
#include "EditTexture.h"

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CTitle::CTitle(void)
	//: m_pEditTexture(NULL)
{
	//�g�p����e�N�X�`����ID�̐ݒ�
	m_nTextureID = TEXTURE_TITLE;
	//m_pEditTexture = new CEditTexture(800,600,CGraphics::GetDevice());
	//
	//m_pEditTexture->FillColor(0xff000000);
	//for (int x = 50; x < 100; ++x)
	//{
	//	for ( int y = 50; y < 100; ++y)
	//	{
	//		m_pEditTexture->SetColor(x,y,D3DCOLOR_RGBA(255,255,255,255));
	//	}
	//}
	//
	//m_pEditTexture->FillColor(150,150,50,50,0xffff0000);
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CTitle::~CTitle(void)
{
	//delete m_pEditTexture;
}

//void CTitle::Draw()
//{
//	//�f�o�C�X�擾
//	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
//
//	//���u�����f�B���O���s��
//	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	// ���ߏ������s��
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice ->SetFVF(FVF_VERTEX_2D);
//
//	//�e�N�X�`���̃Z�b�g
//	pDevice ->SetTexture(0,*m_pEditTexture);
//	
//	//�|���S���̕`��
//	pDevice -> DrawPrimitiveUP(
//		D3DPT_TRIANGLESTRIP,          //�v���~�e�B�u�̎��List�i�O�p�`�`���jStrip(�Ȃ��č��)
//		NUM_POLYGON,                 //�|���S����
//		m_aVertex,            //�z��̐擪�A�h���X
//		sizeof(VERTEX_2D)            //�f�[�^�̑傫��
//		);
//
//}