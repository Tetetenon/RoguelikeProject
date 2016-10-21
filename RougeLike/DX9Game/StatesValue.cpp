#include "StatesValue.h"
#include "Graphics.h"
#include "TextureManager.h"


//�e�X�e�[�^�X�f�[�^�̊i�[
int CStatesValue::m_nStatesValue[STATES_FONT_MAX];
//�|���S�����
VERTEX_2D	CStatesValue::m_aVertex[STATES_FONT_MAX * 2][NUM_VERTEX];

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CStatesValue::CStatesValue(void)
{
	//�|���S�����ݒ�
	SetVertex();
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CStatesValue::~CStatesValue(void)
{
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CStatesValue::Draw ()
{
	int nParNum;	//�X�e�[�^�X���l�i�[

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	
	// �A���t�@�E�u�����f�B���O���s��
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���ߏ������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//�A�C�e���E�C���h�E���`��
	for(int i = 0;i < STATES_FONT_MAX * 2;i++)
	{
		//�z��W���ɂ���ăX�e�[�^�X���l��ύX����
		nParNum = m_nStatesValue[(int)i / (int)2];
		int j = (1 + (9 * ((1 - (i % 2)) % 2)));
		//�\�����錅���l������
		nParNum = nParNum / j;

		nParNum %= 10;

		//�\�����鐔�l�ɉ����ăe�N�X�`����ύX����
		switch(nParNum)
		{
		case 0:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_0));
			break;
		case 1:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_1));
			break;
		case 2:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_2));
			break;
		case 3:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_3));
			break;
		case 4:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_4));
			break;
		case 5:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_5));
			break;
		case 6:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_6));
			break;
		case 7:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_7));
			break;
		case 8:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_8));
			break;
		case 9:
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_9));
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
void CStatesValue::SetVertex()
{
	for(int i = 0;i < STATES_FONT_MAX * 2;i += 2)
	{
		//�ʒu���ݒ�
		m_aVertex[i][0].pos		= D3DXVECTOR3((float)130.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance),0.0f);
		m_aVertex[i][1].pos		= D3DXVECTOR3((float)180.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance),0.0f);
		m_aVertex[i][2].pos		= D3DXVECTOR3((float)130.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance) + FontScale,0.0f);
		m_aVertex[i][3].pos		= D3DXVECTOR3((float)180.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance) + FontScale,0.0f);
		//�ʒu���ݒ�
		m_aVertex[i + 1][0].pos = D3DXVECTOR3((float)180.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance),0.0f);
		m_aVertex[i + 1][1].pos = D3DXVECTOR3((float)230.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance),0.0f);
		m_aVertex[i + 1][2].pos = D3DXVECTOR3((float)180.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance) + FontScale,0.0f);
		m_aVertex[i + 1][3].pos = D3DXVECTOR3((float)230.0f,(float)185.0f + FontScale * (i / 2) + (FontClearance) + FontScale,0.0f);
		
		//�p�[�X�y�N�e�B�u�ݒ�?
		m_aVertex[i][0].rhw = 1.0f;
		m_aVertex[i][1].rhw = 1.0f;
		m_aVertex[i][2].rhw = 1.0f;
		m_aVertex[i][3].rhw = 1.0f;

		//�p�[�X�y�N�e�B�u�ݒ�?
		m_aVertex[i + 1][0].rhw = 1.0f;
		m_aVertex[i + 1][1].rhw = 1.0f;
		m_aVertex[i + 1][2].rhw = 1.0f;
		m_aVertex[i + 1][3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		m_aVertex[i][0].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][1].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][2].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][3].col = D3DCOLOR_RGBA(255,255,255,255);

		//���_�J���[�̐ݒ�
		m_aVertex[i + 1][0].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i + 1][1].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i + 1][2].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i + 1][3].col = D3DCOLOR_RGBA(255,255,255,255);

		//�|���S���ƃe�N�X�`���̒��_��Ή�������
		m_aVertex[i][0].tex = D3DXVECTOR2(0.0f,0.0f);
		m_aVertex[i][1].tex = D3DXVECTOR2(1.0f,0.0f);
		m_aVertex[i][2].tex = D3DXVECTOR2(0.0f,1.0f);
		m_aVertex[i][3].tex = D3DXVECTOR2(1.0f,1.0f);

		//�|���S���ƃe�N�X�`���̒��_��Ή�������
		m_aVertex[i + 1][0].tex = D3DXVECTOR2(0.0f,0.0f);
		m_aVertex[i + 1][1].tex = D3DXVECTOR2(1.0f,0.0f);
		m_aVertex[i + 1][2].tex = D3DXVECTOR2(0.0f,1.0f);
		m_aVertex[i + 1][3].tex = D3DXVECTOR2(1.0f,1.0f);
	}

}