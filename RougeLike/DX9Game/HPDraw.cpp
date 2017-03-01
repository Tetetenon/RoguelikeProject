#include "HPDraw.h"
#include "Graphics.h"
#include "define.h"
#include "TextureManager.h"

#include <stdlib.h>
#include <tchar.h>
#include "TextureManager.h"

#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //�����X�g���[��



//HP�ő�`��T�C�Y
#define HP_MAX_WIDHT 250
//---------------------------------------------------------------------------------------
//�ÓI�����o���̒�`
//---------------------------------------------------------------------------------------
CHPDraw* CHPDraw::m_pHPDraw = NULL;
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CHPDraw::CHPDraw(void)
{
	//�e�탁���o�ϐ��̏�����
	m_pFont = NULL;
	m_nHP = 0;
	m_nMaxHP = 0;

	//�O���t�B�b�N�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = CGraphics::GetDevice();

	//�t�H���g�ւ̃|�C���^���擾����
	D3DXCreateFont(pDevice,24,0,1,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,NULL,&m_pFont);

	//�|���S�����̐ݒ�
	SetVertex();

	//�t�H���g�\���ʒu�̐ݒ�
	SetFontPos();
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CHPDraw::~CHPDraw(void)
{

}
//---------------------------------------------------------------------------------------
//���̂̍쐬
//---------------------------------------------------------------------------------------
void CHPDraw::Create()
{
	//���g�����݂��Ă��Ȃ��ꍇ�쐬
	if (!m_pHPDraw)
	{
		m_pHPDraw = new CHPDraw;
	}
}
//---------------------------------------------------------------------------------------
//���̂̍폜
//---------------------------------------------------------------------------------------
void CHPDraw::Delete()
{
	//���g�̊m�F
	if (m_pHPDraw)
	{
		//���g������΍폜
		delete m_pHPDraw;
		m_pHPDraw = NULL;
	}
}
//---------------------------------------------------------------------------------------
//���̂̃|�C���^��n��
//---------------------------------------------------------------------------------------
CHPDraw* CHPDraw::GetPointer()
{
	//�O�̂��ߍ쐬
	Create();
	return m_pHPDraw;
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CHPDraw::Update()
{

}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CHPDraw::Draw()
{
	//�O���t�B�b�N�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//�A���t�@�u�����f�B���O���s��
	pDevice ->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	//���ߏ������s��
	pDevice ->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture(0,*CTextureManager::GetTexture(TEXTURE_HP_BAR));

	//�|���S���̕`��
	pDevice ->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,NUM_POLYGON,m_aVertex,sizeof(VERTEX_2D));

	//���l(����)�`��
	m_pFont ->DrawText(NULL,m_States,-1,&m_FontDrawPos,DT_LEFT,D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));

}
//---------------------------------------------------------------------------------------
//�|���S������ݒ�
//---------------------------------------------------------------------------------------
void CHPDraw::SetVertex()
{
	//�ʒu���ݒ�
	SetPosition();

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
//�����`��ʒu��ݒ�
//---------------------------------------------------------------------------------------
void CHPDraw::SetFontPos()
{
	m_FontDrawPos.left		= (LONG)240.0f;
	m_FontDrawPos.top		= (LONG) 15.0f;
	m_FontDrawPos.right		= (LONG)300.0f;
	m_FontDrawPos.bottom	= (LONG) 45.0f;
}
//---------------------------------------------------------------------------------------
//�`�悷��HP���l���Z�b�g
//---------------------------------------------------------------------------------------
void CHPDraw::SetHP (int nHP)
{
	sprintf_s(m_States, _T("HP:%d"), nHP);

	m_nHP = nHP;

	SetPosition();
}
//---------------------------------------------------------------------------------------
//�`�悷��ő�HP���l���Z�b�g
//---------------------------------------------------------------------------------------
void CHPDraw::SetMaxHP (int nMaxHP)
{
	m_nMaxHP = nMaxHP;
}

//---------------------------------------------------------------------------------------
//�|���S���̈ʒu�����Đݒ�
//---------------------------------------------------------------------------------------
void CHPDraw::SetPosition()
{
	float nPercentage = ((float)m_nHP / (float)m_nMaxHP);

	//�ʒu���ݒ�
	m_aVertex[0].pos = D3DXVECTOR3((float)300.0f								,(float)15.0f,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)300.0f + nPercentage * HP_MAX_WIDHT	,(float)15.0f,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)300.0f								,(float)45.0f,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)300.0f + nPercentage * HP_MAX_WIDHT	,(float)45.0f,0.0f);
}