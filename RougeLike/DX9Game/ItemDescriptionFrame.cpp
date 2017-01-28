#include "ItemDescriptionFrame.h"
#include "define.h"
#include "TextureManager.h"
#include "ItemWindow.h"
#include "ItemWindowCursor.h"
#include "Graphics.h"



//�E�C���h�E�T�C�Y
#define WINDOW_WIDHT  300
#define WINDOW_HEIGHT  30

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CItemDescriptionFrame::CItemDescriptionFrame(void)
{
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CItemDescriptionFrame::~CItemDescriptionFrame(void)
{
}
//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void CItemDescriptionFrame::Init(void)
{
	//�e�N�X�`���ԍ��̐ݒ�
	m_nTextureID = TEXTURE_WINDOW;
	//�|���S�����̐ݒ�
	SetVertex();
	//�t�H���g���̐ݒ�
	SetFontPos();
	//�����̊i�[
	FontDataSet();
}
//---------------------------------------------------------------------------------------
//�|���S�����̐ݒ���s��
//---------------------------------------------------------------------------------------
void CItemDescriptionFrame::SetVertex(void)
{	
	//�ʒu���ݒ�
	m_aVertex[0].pos = D3DXVECTOR3((float)WINDOW_WIDHT	,(float)WINDOW_HEIGHT * (ITEM_NUM_MAX + 1)					,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH	,(float)WINDOW_HEIGHT * (ITEM_NUM_MAX + 1)					,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)WINDOW_WIDHT	,(float)WINDOW_HEIGHT * (ITEM_NUM_MAX + 1) + WINDOW_HEIGHT	,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH	,(float)WINDOW_HEIGHT * (ITEM_NUM_MAX + 1) + WINDOW_HEIGHT	,0.0f);

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
//�t�H���g���̐ݒ�
//---------------------------------------------------------------------------------------
void CItemDescriptionFrame::SetFontPos()
{
	
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//���i�[�p�t�H���g��ݒ�
	//�t�H���g�ւ̃|�C���^��������
	m_Font = NULL;

	//�t�H���g�̐ݒ�
	D3DXCreateFont(pDevice, 18, 18, 1, 0, FALSE, SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL,&m_Font);
	
	m_FontPosition.top		= (LONG)(WINDOW_HEIGHT * (ITEM_NUM_MAX + 1) + 6.0f);
	m_FontPosition.bottom	= (LONG)(WINDOW_HEIGHT * (ITEM_NUM_MAX + 1) + WINDOW_HEIGHT);
	m_FontPosition.left		= (LONG)(WINDOW_WIDHT + 30.0f);
	m_FontPosition.right	= (LONG)SCREEN_WIDTH;
}

//---------------------------------------------------------------------------------------
//�t�H���g���̐ݒ�
//---------------------------------------------------------------------------------------
void CItemDescriptionFrame::Draw(int ItemNumber)
{

	//�`�悷��e�L�X�g��0�̏ꍇ�������΂�
	if(ItemNumber == 0)
		return;

	//�E�B���h�E�̕`��
	C2DTexture::Draw();

	//�e�L�X�g�̕`��
	m_Font->DrawText(NULL,m_Description[ItemNumber],-1,&m_FontPosition,DT_LEFT,D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0xff));
}

//---------------------------------------------------------------------------------------
//�t�H���g�f�[�^�̐ݒ�
//---------------------------------------------------------------------------------------
void CItemDescriptionFrame::FontDataSet(void)
{
	//���ꕨ�̏�����
	::SecureZeroMemory(m_Description, sizeof(_TCHAR) * DESCRIPTION_FONT_MAX * ITEM_MAX);

	//�S�ẴA�C�e���������t�H���g�̐ݒ�
	for (int i = ITEM_APPLE; i < ITEM_MAX;i++)
	{
		#if RIKU_TAKAHASHI
		#error �������ς����ꏊ
		#endif //  RIK_T

		switch(i)
		{
		case ITEM_APPLE:
				lstrcpyn(m_Description[i],_T("���������B"),sizeof(_TCHAR) * DESCRIPTION_FONT_MAX / 2);
			break;
		case ITEM_HERB:
				lstrcpyn(m_Description[i],_T("�̗͂��񕜂���"),sizeof(_TCHAR) * DESCRIPTION_FONT_MAX / 2);
			break;
		case ITEM_SWORD:
				lstrcpyn(m_Description[i],_T("��������ƍU�����オ��"),sizeof(_TCHAR) * DESCRIPTION_FONT_MAX / 2);
			break;
		case ITEM_SHIELD:
				lstrcpyn(m_Description[i],_T("��������Ɩh�䂪�オ��"),sizeof(_TCHAR) * DESCRIPTION_FONT_MAX / 2);
			break;
		}
	}
}