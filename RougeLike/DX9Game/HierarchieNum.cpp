#include "HierarchieNum.h"
#include "Graphics.h"
#include "MapData.h"
#include "TextureManager.h"

#include "Fade.h"

#define NUM_FONT_SIZE (180)

VERTEX_2D	CHierarchieNum::m_aVertex[HIERARCHIENUM][NUM_VERTEX];
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CHierarchieNum::CHierarchieNum(void)
{
	//�|���S�����ݒ�
	SetVertex();
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CHierarchieNum::~CHierarchieNum(void)
{

}

//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CHierarchieNum::Draw()
{
	//�K�w����ۑ�
	int HierarchieNum = CMapData::GetHierarchieNum();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	
	// �A���t�@�E�u�����f�B���O���s��
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// ���ߏ������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice ->SetFVF(FVF_VERTEX_2D);

	for(int i =0 ;i < HIERARCHIENUM;i++)
	{
		if(i == HIERARCHIENUM - 1)
		{
			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_F));
		}
		else
		{
			int nNumTexture = HierarchieNum / (9 * i + 1) % 10;

			//�\�����鐔�l�ɉ����ăe�N�X�`����ύX����
			switch(nNumTexture)
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
		}
		//�A���t�@�l��ݒ�
		int AlphaNum = 255 - CFade::GetFadeAlpha();
		for(int j = 0;j < HIERARCHIENUM;j++)
		{
			//���_�J���[�̐ݒ�
			m_aVertex[j][0].col = D3DCOLOR_RGBA(255,255,255,AlphaNum);
			m_aVertex[j][1].col = D3DCOLOR_RGBA(255,255,255,AlphaNum);
			m_aVertex[j][2].col = D3DCOLOR_RGBA(255,255,255,AlphaNum);
			m_aVertex[j][3].col = D3DCOLOR_RGBA(255,255,255,AlphaNum);
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
void CHierarchieNum::SetVertex()
{
	for(int i = 0;i < HIERARCHIENUM;i++)
	{
		//�ʒu���ݒ�
		m_aVertex[i][0].pos		= D3DXVECTOR3((float)(SCREEN_WIDTH / 2) + (NUM_FONT_SIZE - NUM_FONT_SIZE / 2) - (NUM_FONT_SIZE * i),(float)(SCREEN_HEIGHT / 2) - NUM_FONT_SIZE,0.0f);
		m_aVertex[i][1].pos		= D3DXVECTOR3((float)(SCREEN_WIDTH / 2)	+ (NUM_FONT_SIZE + NUM_FONT_SIZE / 2) - (NUM_FONT_SIZE * i),(float)(SCREEN_HEIGHT / 2) - NUM_FONT_SIZE,0.0f);
		m_aVertex[i][2].pos		= D3DXVECTOR3((float)(SCREEN_WIDTH / 2) + (NUM_FONT_SIZE - NUM_FONT_SIZE / 2) - (NUM_FONT_SIZE * i),(float)(SCREEN_HEIGHT / 2) + NUM_FONT_SIZE,0.0f);
		m_aVertex[i][3].pos		= D3DXVECTOR3((float)(SCREEN_WIDTH / 2)	+ (NUM_FONT_SIZE + NUM_FONT_SIZE / 2) - (NUM_FONT_SIZE * i),(float)(SCREEN_HEIGHT / 2) + NUM_FONT_SIZE,0.0f);
		
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