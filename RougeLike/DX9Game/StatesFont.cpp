#include "StatesFont.h"
#include "StatesDefine.h"
#include "Graphics.h"
#include "TextureManager.h"

//---------------------------------------------------------------------------------------
//�ÓI�����o��`
//---------------------------------------------------------------------------------------
CStatesFont* CStatesFont::m_pStatesFont;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CStatesFont::CStatesFont(void)
{
	//�g�p����e�N�X�`���̐ݒ�
	m_nTextureNumber[STATES_FONT_ATTACK] = STATES_FONT_ATTACK;
	m_nTextureNumber[STATES_FONT_DEFENCE] = STATES_FONT_DEFENCE;
	m_nTextureNumber[STATES_FONT_EXP] = STATES_FONT_EXP;

	//���_���̐ݒ�
	SetVertex();
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CStatesFont::~CStatesFont(void)
{
}
//---------------------------------------------------------------------------------------
//���̂̍쐬
//---------------------------------------------------------------------------------------
void CStatesFont::Create()
{
	//���g�̊m�F
	if (!m_pStatesFont)
	{
		//���g�����݂��Ȃ���΍쐬
		m_pStatesFont = new CStatesFont;
	}
}
//---------------------------------------------------------------------------------------
//���̂̍폜
//---------------------------------------------------------------------------------------
void CStatesFont::Delete()
{
	//���g�̊m�F
	if (m_pStatesFont)
	{
		//���g������΍폜
		delete m_pStatesFont;
		m_pStatesFont = NULL;
	}
}
//---------------------------------------------------------------------------------------
//���̂̃|�C���^��n��
//---------------------------------------------------------------------------------------
CStatesFont* CStatesFont::GetPointer()
{
	//�O�̂��ߍ쐬
	Create();
	return m_pStatesFont;
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CStatesFont::Draw(void)
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
	for(int i = 0;i < STATES_FONT_MAX;i++)
	{
		//�e�N�X�`���̔ԍ��ɂ��Z�b�g����e�N�X�`�������߂�
		switch(m_nTextureNumber[i])
		{
			//��������
		case STATES_FONT_ATTACK:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_ATTACK));
			break;
			//�ڂ�����
		case STATES_FONT_DEFENCE:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_DEFENCE));
			break;
			//��������
		case STATES_FONT_EXP:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_EXP));
			break;
		}
		//�|���S���̕`��
		//���_�����O���������Ă���ꍇUp
		//���̂ق���primitive
		pDevice -> DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP,          //�v���~�e�B�u�̎��List�i�O�p�`�`���jStrip(�Ȃ��č��)
			NUM_POLYGON,                 //�|���S����
			m_aVertex[i],            //�z��̐擪�A�h���X
			sizeof(VERTEX_2D)            //�f�[�^�̑傫��
			);
	}
}
//---------------------------------------------------------------------------------------
//�|���S�����̐ݒ�
//---------------------------------------------------------------------------------------
void CStatesFont::SetVertex()
{
	for(int i = 0;i < STATES_FONT_MAX;i++)
	{
		//�ʒu���ݒ�
		m_aVertex[i][0].pos = D3DXVECTOR3((float) 20.0f,(float) 90.0f + FontScale * i + (FontClearance),0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)150.0f,(float) 90.0f + FontScale * i + (FontClearance),0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float) 20.0f,(float) 90.0f + FontScale * i + (FontClearance) + FontScale,0.0f);
		m_aVertex[i][3].pos = D3DXVECTOR3((float)150.0f,(float) 90.0f + FontScale * i + (FontClearance) + FontScale,0.0f);

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