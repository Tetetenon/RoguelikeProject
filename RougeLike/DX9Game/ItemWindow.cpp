#include "ItemWindow.h"
#include "Graphics.h"
#include "Input.h"
#include <tchar.h>
#include "ItemCommandWindow.h"
#include "ItemWindowCursor.h"
#include "Turn.h"
#include "TextureManager.h"
//---------------------------------------------------------------------------------------
//�}�N����`
//---------------------------------------------------------------------------------------

//�E�C���h�E�T�C�Y
#define WINDOW_WIDHT 300
#define WINDOW_HEIGHT 30

//---------------------------------------------------------------------------------------
//�ÓI�����o��`
//---------------------------------------------------------------------------------------
bool					CInventory::m_bDrawFlg;				//�`��t���O
CCommandWindow			CInventory::m_CommandWindow;		//�R�}���h�E�C���h�E�̕`��t���O�ύX�p
CInventoryCursor		CInventory::m_InventoryCursor;		//�I�����Ă���A�C�e���E�C���h�E�̎擾
CItemDescriptionFrame	CInventory::m_Description;			//�A�C�e��������
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CInventory::CInventory(void)
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
}


//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CInventory::~CInventory(void)
{
}

//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void CInventory::Init()
{
	//�������̏�����
	m_Description.Init();
}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CInventory::Fin()
{

}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CInventory::UpDate()
{
	//�A�C�e���I�𒆂̂ݑ���\
	if(m_bDrawFlg && !CCommandWindow::GetDrawFlg())
	{
		//L�Ō���
		//�I�������A�C�e���E�C���h�E�ɃA�C�e�������݂��Ă��邩�m�F����
		if((CInput::GetKeyTrigger(DIK_L) || CInput::GetJoyTrigger(0, 3)) && m_Item[m_InventoryCursor.GetItemNum()].GetID())
		{
			//�R�}���h�E�C���h�E�`��t���O�𗧂Ă�
			m_CommandWindow.DrawFlgChange();
		}

		//K��I�L�[�Ŗ߂�
		if(CInput::GetKeyTrigger(DIK_K) || CInput::GetJoyTrigger(0, 2))
		{
			//���g�̃t���O��|��
			DrawFlgChange();
		}
	}
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CInventory::Draw()
{
		_TCHAR* ItemName;		//�`��p�ɕ������i�[����
		int		ItemID;			//�`��̉ۂ�ID�Ŕ��ʂ���

		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
		
		// �A���t�@�E�u�����f�B���O���s��
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		// ���ߏ������s��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice ->SetFVF(FVF_VERTEX_2D);

		//�A�C�e���E�C���h�E���`��
		for(int i = 0;i < ITEM_NUM_MAX;i++)
		{
			ItemName = m_Item[i].GetName();
			ItemID	= m_Item[i].GetID();

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

			//���g���Ȃ���Ε`�悵�Ȃ�
			if(ItemName == NULL || ItemID == 0)
				continue;

			// �e�L�X�g�`��
			m_Font->DrawText(NULL,ItemName,-1, &m_Pos[i], DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0xff));
		}

		//�A�C�e���������̕`��
		m_Description.Draw(m_Item[CInventoryCursor::GetItemNum()].GetID());

}
//---------------------------------------------------------------------------------------
//�|���S�����𖄂߂�
//---------------------------------------------------------------------------------------
void CInventory::SetVertex()
{
	for(int i = 0;i < ITEM_NUM_MAX;i++)
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
void CInventory::SetFontPos()
{
	for(int i = 0;i < ITEM_NUM_MAX;i++)
	{
		m_Pos[i].left	= (LONG)(m_aVertex[i][0].pos.x + 50.0f);
		m_Pos[i].top	= (LONG)(m_aVertex[i][1].pos.y + 10.0f);
		m_Pos[i].right	= (LONG)m_aVertex[i][3].pos.x;
		m_Pos[i].bottom	= (LONG)m_aVertex[i][2].pos.y;
	}
}
//---------------------------------------------------------------------------------------
//�X�g���[�W�ɃA�C�e�����Z�b�g
//---------------------------------------------------------------------------------------
bool CInventory::SetItem(CItem Item)
{
	for(int i = 0;i < ITEM_NUM_MAX;i++)
	{
		//�X�g���[�W���󔒂̕�����T��
		if(m_Item[i].GetID() == 0)
		{
			//�A�C�e���f�[�^���R�s�[
			m_Item[i] = Item;


			//���\�̐ݒ肪����Ă��Ȃ���΁A�����I�ɐݒ肷��
			if(Item.GetValue() == 0)
			{
				//���\��ݒ�
				m_Item[i].SetValue(rand()%10 + 5);
			}
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------------------
//�`��t���O���O������ON/OFF����
//---------------------------------------------------------------------------------------
void CInventory::DrawFlgChange()
{
	m_bDrawFlg = !m_bDrawFlg;
}

//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�A�C�e��������
//---------------------------------------------------------------------------------------
void CInventory::DelInventory(int Receipt)
{
	//���g�����������A����
	//ID�̏�����
	m_Item[Receipt].SetID(0);

	//���O�̏�����
	m_Item[Receipt].SetName(_T("0"));

}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�A�C�e���̌��ʃW��������ԋp����
//---------------------------------------------------------------------------------------
int CInventory::GetEffect(int Receipt)
{
	return m_Item[Receipt].GetType();
}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�A�C�e���̌��\?��ԋp����
//---------------------------------------------------------------------------------------
int CInventory::GetEffectValue(int Receipt)
{
	//�A�C�e����ID�ɂ���Č��ʂ�ύX����
	switch(m_Item[Receipt].GetID())
	{
		//�ь�
	case ITEM_APPLE:
		//���Ɍ��ʂȂ�
		return EFFECT_NON;
		break;
		//��
	case ITEM_HERB:
		//�̗͂̉�
		return m_Item[Receipt].GetValue();
		break;
		//��
	case ITEM_SWORD:
		//�U���̓A�b�v
		return m_Item[Receipt].GetValue();
		break;
		//��
	case ITEM_SHIELD:
		//�h��̓A�b�v
		return m_Item[Receipt].GetValue();
		break;

		//�o�O�����p
	default:
		//���ʂȂ�
		return EFFECT_NON;
		break;
	}
}