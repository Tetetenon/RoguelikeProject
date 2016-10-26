#include "MessageWindow.h"
#include "Graphics.h"
#include "define.h"

#include "TextureManager.h"

#include<fstream>
#include<iostream>
#include<string>
#include<sstream>

#define DRAW_TIME_MAX	300							//�������삵�Ȃ������ꍇ�̃E�B���h�E�ő�`�掞��

//�E�C���h�E�T�C�Y
#define WINDOW_WIDHT 500
#define WINDOW_HEIGHT 30


//---------------------------------------------------------------------------------------
//�ÓI�����o���̒�`
//---------------------------------------------------------------------------------------
_TCHAR	MessageWindow::m_Message[DRAW_NUM][FONT_NUM];	//�i�[���郁�b�Z�[�W(������30����,�s��5)
bool	MessageWindow::m_bDrawflg;						//�`��t���O		
float	MessageWindow::m_fDrawTime;						//�`�掞��
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
MessageWindow::MessageWindow(void)
{
	//�����o������
	m_bDrawflg = false;
	m_fDrawTime = 0;

	//�O���t�B�b�N�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//���i�[�p�t�H���g��ݒ�
	//�t�H���g�ւ̃|�C���^��������
	m_pFont = NULL;

	D3DXCreateFont(pDevice, 18, 12, 10, 0, FALSE, SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL,&m_pFont);

	//������擪������
	for(int i = 0;i < DRAW_NUM;i++)
	{
		for(int j = 0;j < FONT_NUM;j++)
			m_Message[i][j] = 0;
	}
	//�|���S�����̐ݒ�
	SetVertex();
	//�t�H���g�\���ʒu�̐ݒ�
	SetFontPos();
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
MessageWindow::~MessageWindow(void)
{
}

//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void MessageWindow::Init()
{
}

//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void MessageWindow::Update()
{
	//�`��t���O�������Ă���ꍇ�A�`�掞�Ԃ�����������
	if(m_bDrawflg)
	{
		//�`�掞�Ԍ���
		m_fDrawTime--;

		//�����`�掞�Ԃ�0�ȉ��Ȃ�΁A�`��t���O��|���A����`�悵�Ȃ��悤�ɐݒ肷��
		if(m_fDrawTime <= 0)
		{
			//m_bDrawflg = false;
		}
	}

}


//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void MessageWindow::Draw()
{
	//�`��t���O�������Ă��鎞�̂ݕ`����s��
	if(m_bDrawflg)
	{
		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
		
		// �A���t�@�E�u�����f�B���O���s��
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		// ���ߏ������s��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice ->SetFVF(FVF_VERTEX_2D);
		//�`��t���O�������Ă���ꍇ�`��
		if(m_bDrawflg)
		{
			for(int i = 0;i < DRAW_NUM;i++)
			{
				//���g���Ȃ���Ε`�悵�Ȃ�
				if(m_Message[i][0] == NULL)
					continue;
				//�e�N�X�`���Z�b�g
				pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_WINDOW_ALPHA));

				//�|���S���̕`��
				//���_�����O���������Ă���ꍇUp
				//���̂ق���primitive
				pDevice -> DrawPrimitiveUP(
					D3DPT_TRIANGLESTRIP,          //�v���~�e�B�u�̎��List�i�O�p�`�`���jStrip(�Ȃ��č��)
					NUM_POLYGON,                 //�|���S����
					m_aVertex[i],				 //�z��̐擪�A�h���X
					sizeof(VERTEX_2D)            //�f�[�^�̑傫��
					);
				// �e�L�X�g�`��
				m_pFont->DrawText(NULL,m_Message[i],-1, &m_DrawFontPos[i], DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0xff));
			}
		}
	}
}


//---------------------------------------------------------------------------------------
//�I��
//---------------------------------------------------------------------------------------
void MessageWindow::Fin()
{
}
//---------------------------------------------------------------------------------------
//�|���S�����_�����Z�b�g����
//---------------------------------------------------------------------------------------
void MessageWindow::SetVertex()
{
	for(int i = 0;i < DRAW_NUM;i++)
	{
		//�ʒu���ݒ�
		m_aVertex[i][0].pos = D3DXVECTOR3((float)-10.0f					,(float)SCREEN_HEIGHT - WINDOW_HEIGHT * (i + 1)					,0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)-10.0f + WINDOW_WIDHT	,(float)SCREEN_HEIGHT - WINDOW_HEIGHT * (i + 1)					,0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float)-10.0f					,(float)SCREEN_HEIGHT - WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	,0.0f);
		m_aVertex[i][3].pos = D3DXVECTOR3((float)-10.0f + WINDOW_WIDHT	,(float)SCREEN_HEIGHT - WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	,0.0f);

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
//�t�H���g�`��ʒu��ݒ肷��
void MessageWindow::SetFontPos ()
{
	for(int i = 0;i < DRAW_NUM;i++)
	{
		m_DrawFontPos[i].left	= (LONG)m_aVertex[i][0].pos.x + (LONG)50.0f;
		m_DrawFontPos[i].top	= (LONG)m_aVertex[i][1].pos.y + (LONG)10.0f;
		m_DrawFontPos[i].right	= (LONG)m_aVertex[i][3].pos.x;
		m_DrawFontPos[i].bottom	= (LONG)m_aVertex[i][2].pos.y;
	}
}

//---------------------------------------------------------------------------------------
//�`�悷�镶������Z�b�g����
//---------------------------------------------------------------------------------------
void MessageWindow::SetMassege(_TCHAR String[], ...)
{
	const int MAX_SIZE = 512;

	va_list vList;
	va_start(vList,String);
	char str[MAX_SIZE];
	vsprintf_s(str,sizeof(str), String, vList);
	va_end(vList);

	for (int i = 4;i;--i)
	{
		lstrcpyn(m_Message[i],m_Message[i-1],sizeof(_TCHAR) * FONT_NUM);
	}

	lstrcpyn(m_Message[0],str,sizeof(_TCHAR)*FONT_NUM);
	m_bDrawflg = true;
	m_fDrawTime = DRAW_TIME_MAX;
}