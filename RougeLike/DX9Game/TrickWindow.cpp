#include "TrickWindow.h"
#include "Graphics.h"
#include "Input.h"
#include <tchar.h>
#include "Turn.h"
#include "TextureManager.h"
#include "TrickWindowCursor.h"
#include "Player.h"
#include "MenuWindow.h"
//---------------------------------------------------------------------------------------
//�}�N����`
//---------------------------------------------------------------------------------------

//�E�C���h�E�T�C�Y
#define WINDOW_WIDHT 300
#define WINDOW_HEIGHT 30

//---------------------------------------------------------------------------------------
//�ÓI�����o��`
//---------------------------------------------------------------------------------------
bool				CTrickWindow::m_bDrawFlg;				//�`��t���O
CTrickWindowCursor	CTrickWindow::m_TrickCursor;			//�I�����Ă���A�C�e���E�C���h�E�̎擾
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CTrickWindow::CTrickWindow(void)
{
	//�����o������
	m_bDrawFlg = false;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//���i�[�p�t�H���g��ݒ�
	//�t�H���g�ւ̃|�C���^��������
	m_Font = NULL;

	//�t�H���g�̐ݒ�
	D3DXCreateFont(pDevice, 12, 12, 1, 0, FALSE, SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL,&m_Font);

	//�|���S�����̐ݒ�
	SetVertex();

	//�t�H���g�\���ʒu�̐ݒ�
	SetFontPos();

	//ID�̐ݒ�m_Trick
	for(int i = 0;i < TRICK_NAME_MAX;i++)
	{
		//ID�̐ݒ�
		m_Trick[i].SetID(i);
		//���O�̐ݒ�
		m_Trick[i].FindName(i);
		//���ʂ̎�ނ̐ݒ�
		m_Trick[i].EffectSetting(i);
		//�Z�͈͂̐ݒ�
		m_Trick[i].SetRange(i);
	}
	//�Z�̌��ʂ̐ݒ�
	m_Trick[TRICK_NAME_1].SetValue(5);
	m_Trick[TRICK_NAME_2].SetValue(5);
	m_Trick[TRICK_NAME_3].SetValue(5);
	m_Trick[TRICK_NAME_4].SetValue(5);
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CTrickWindow::~CTrickWindow(void)
{
}

//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void CTrickWindow::Init()
{
}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CTrickWindow::Fin()
{

}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CTrickWindow::UpDate()
{
	//�Z�I�𒆂̂ݑ���\
	if(m_bDrawFlg)
	{
		//L�Ō���
		if(CInput::GetKeyTrigger(DIK_L))
		{
			//�����Ő퓬�X�e�[�g�ֈړ�

			//�Z���g�p
			CPlayer::SetState(CTurn::GAME_STATE_ATTACK);
			
			//���g�̃t���O��|��
			m_bDrawFlg = false;

			//���j���[�̕`��t���O��|��
			CMenuWindow::ChangDrawFlg();
		}

		//K��I�L�[�Ŗ߂�
		if(CInput::GetKeyTrigger(DIK_K))
		{
			//���g�̃t���O��|��
			m_bDrawFlg = false;
		}
	}
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CTrickWindow::Draw()
{
		_TCHAR* TrickName;		//�`��p�ɕ������i�[����
		int		TrickID;			//�`��̉ۂ�ID�Ŕ��ʂ���

		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
		
		// �A���t�@�E�u�����f�B���O���s��
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		// ���ߏ������s��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice ->SetFVF(FVF_VERTEX_2D);

		//�Z�E�C���h�E���`��
		for(int i = 0;i < ITEM_NUM_MAX;i++)
		{
			TrickName = m_Trick[i].GetName();
			TrickID	= m_Trick[i].GetID();

			//�e�N�X�`���Z�b�g
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_WINDOW));

			//�|���S���̕`��
			//���_�����O���������Ă���ꍇUp
			//���̂ق���primitive
			pDevice -> DrawPrimitiveUP(
				D3DPT_TRIANGLESTRIP,          //�v���~�e�B�u�̎��List�i�O�p�`�`���jStrip(�Ȃ��č��)
				NUM_POLYGON,                 //�|���S����
				m_aVertex[i],            //�z��̐擪�A�h���X
				sizeof(VERTEX_2D)            //�f�[�^�̑傫��
				);

			// �e�L�X�g�`��
			m_Font->DrawText(NULL,TrickName,-1, &m_Pos[i], DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0xff));
		}

}
//---------------------------------------------------------------------------------------
//�|���S�����𖄂߂�
//---------------------------------------------------------------------------------------
void CTrickWindow::SetVertex()
{
	for(int i = 0;i < TRICK_NUM_MAX;i++)
	{
		//�ʒu���ݒ�
		m_aVertex[i][0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (i + 1)					,0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (i + 1)					,0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	,0.0f);
		m_aVertex[i][3].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	,0.0f);

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
//---------------------------------------------------------------------------------------
//�t�H���g���̐ݒ�
//---------------------------------------------------------------------------------------
void CTrickWindow::SetFontPos()
{
	for(int i = 0;i < TRICK_NUM_MAX;i++)
	{
		m_Pos[i].left	= (LONG)(m_aVertex[i][0].pos.x + 50.0f);
		m_Pos[i].top	= (LONG)(m_aVertex[i][1].pos.y + 10.0f);
		m_Pos[i].right	= (LONG)m_aVertex[i][3].pos.x;
		m_Pos[i].bottom	= (LONG)m_aVertex[i][2].pos.y;
	}
}
//---------------------------------------------------------------------------------------
//�`��t���O���O������ON/OFF����
//---------------------------------------------------------------------------------------
void CTrickWindow::DrawFlgChange()
{
	m_bDrawFlg = !m_bDrawFlg;
}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�Z�̌��ʃW��������ԋp����
//---------------------------------------------------------------------------------------
int CTrickWindow::GetEffect(int Receipt)
{
	return m_Trick[Receipt].GetType();
}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�Z�̌��\��ԋp����
//---------------------------------------------------------------------------------------
int CTrickWindow::GetEffectValue(int Receipt)
{
	//�Z��ID�ɂ���Č��ʂ�ύX����
	switch(m_Trick[Receipt].GetID())
	{
		//1
	case TRICK_NAME_1:
		return EFFECT_NON;
		break;
		//2
	case TRICK_NAME_2:
		return m_Trick[Receipt].GetValue();
		break;
		//3
	case TRICK_NAME_3:
		return m_Trick[Receipt].GetValue();
		break;
		//4
	case TRICK_NAME_4:
		return m_Trick[Receipt].GetValue();
		break;

		//�o�O�����p
	default:
		//���ʂȂ�
		return -99;
		break;
	}
}

//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�Z�͈̔͂�Ԃ�
//---------------------------------------------------------------------------------------
int CTrickWindow::GetRange(int Receipt)
{
	//�w�肳�ꂽ�W�����A�z������m�F����
	if(Receipt < TRICK_NAME_MAX)
		//�z����ł���΁A���K�̒l���擾���A�n��
		return m_Trick[Receipt].GetRange();
	else
		//�z����łȂ���΁A���ʂ̒l��n���B
		return TRICK_RANGE_FRONT;
}