#include "C2DTexture.h"

#include "Graphics.h"
#include "TextureManager.h"


//���_�t�H�[�}�b�g�i���_���W[2D]/���_�J���[�j
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)//(�ʒu��� | �J���[ | �e�N�X�`���̏��0���Ⴞ��)

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
C2DTexture::C2DTexture(void)
{
	//�|���S���̏���ݒ肷��
	SetVertex();
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
C2DTexture::~C2DTexture(void)
{
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void C2DTexture::Draw()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//���u�����f�B���O���s��
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���ߏ������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̃Z�b�g
	pDevice ->SetTexture(0,*CTextureManager::GetTexture(m_nTextureID));

	
	//�|���S���̕`��
	pDevice -> DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,          //�v���~�e�B�u�̎��List�i�O�p�`�`���jStrip(�Ȃ��č��)
		NUM_POLYGON,                 //�|���S����
		m_aVertex,            //�z��̐擪�A�h���X
		sizeof(VERTEX_2D)            //�f�[�^�̑傫��
		);

}
//---------------------------------------------------------------------------------------
//�|���S�����̐ݒ�
//---------------------------------------------------------------------------------------
void C2DTexture::SetVertex()
{
	//�ʒu���ݒ�
	m_aVertex[0].pos = D3DXVECTOR3(0.0f			,0.0f			,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH	,0.0f			,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(0.0f			,SCREEN_HEIGHT	,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH	,SCREEN_HEIGHT	,0.0f);

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
//�ʒu���̐ݒ�
//---------------------------------------------------------------------------------------
void C2DTexture::SetPos(float fPosX,float fPosY,float fHalfSizeX,float fHalfSizeY)
{
	//�ʒu���ݒ�
	m_aVertex[0].pos = D3DXVECTOR3(fPosX - (fHalfSizeX / 2),fPosY - (fHalfSizeY / 2),0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(fPosX + (fHalfSizeX / 2),fPosY - (fHalfSizeY / 2),0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(fPosX - (fHalfSizeX / 2),fPosY + (fHalfSizeY / 2),0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(fPosX + (fHalfSizeX / 2),fPosY + (fHalfSizeY / 2),0.0f);
}

void C2DTexture::SetPosLeftUpOrigin(float fPosX, float fPosY, float fWidth, float fHeight)
{
	m_aVertex[0].pos = D3DXVECTOR3(fPosX,fPosY,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(fPosX + fWidth,fPosY,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(fPosX,fPosY + fHeight,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(fPosX + fWidth,fPosY + fHeight,0.0f);
}

//---------------------------------------------------------------------------------------
//�|���S���̃A���t�@�l��ݒ肷��
//---------------------------------------------------------------------------------------
void C2DTexture::SetAlpha(int nAlpha)
{
	//���_�J���[�̐ݒ�
	m_aVertex[0].col = D3DCOLOR_RGBA(255,255,255,nAlpha);
	m_aVertex[1].col = D3DCOLOR_RGBA(255,255,255,nAlpha);
	m_aVertex[2].col = D3DCOLOR_RGBA(255,255,255,nAlpha);
	m_aVertex[3].col = D3DCOLOR_RGBA(255,255,255,nAlpha);
}