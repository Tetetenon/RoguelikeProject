#include "EquipmentWindow.h"
#include "Graphics.h"
#include "Input.h"
#include <tchar.h>
#include "EquipmentCommandWindow.h"
#include "EquipmentWindowCursor.h"
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
bool							CEquipmentInventory::m_bDrawFlg;								//�`��t���O
CEquipmentCommandWindow			CEquipmentInventory::m_CommandWindow;		//�R�}���h�E�C���h�E�̕`��t���O�ύX�p
CEquipmentInventoryCursor		CEquipmentInventory::m_InventoryCursor;		//�I�����Ă���A�C�e���E�C���h�E�̎擾
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEquipmentInventory::CEquipmentInventory(void)
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
CEquipmentInventory::~CEquipmentInventory(void)
{
}

//---------------------------------------------------------------------------------------
//������
//---------------------------------------------------------------------------------------
void CEquipmentInventory::Init()
{
}
//---------------------------------------------------------------------------------------
//�I������
//---------------------------------------------------------------------------------------
void CEquipmentInventory::Fin()
{

}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CEquipmentInventory::UpDate()
{
	//�A�C�e���I�𒆂̂ݑ���\
	if(m_bDrawFlg && !CEquipmentCommandWindow::GetDrawFlg())
	{
		//L�Ō���
		//�I�������A�C�e���E�C���h�E�ɃA�C�e�������݂��Ă��邩�m�F����
		if(CInput::GetKeyTrigger(DIK_L) && m_Item[m_InventoryCursor.GetItemNum()].GetID())
		{
			//�R�}���h�E�C���h�E�`��t���O�𗧂Ă�
			m_CommandWindow.DrawFlgChange();
		}

		//K��I�L�[�Ŗ߂�
		if(CInput::GetKeyTrigger(DIK_K))
		{
			//���g�̃t���O��|��
			DrawFlgChange();
		}
	}
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CEquipmentInventory::Draw()
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
		for(i = 0;i < EQUIPMENT_NUM_MAX;i++)
		{
			i = i;

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

}
//---------------------------------------------------------------------------------------
//�|���S�����𖄂߂�
//---------------------------------------------------------------------------------------
void CEquipmentInventory::SetVertex()
{
	for(int i = 0;i < EQUIPMENT_NUM_MAX;i++)
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
void CEquipmentInventory::SetFontPos()
{
	for(int i = 0;i < EQUIPMENT_NUM_MAX;i++)
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
bool CEquipmentInventory::SetItem(CItem Item)
{
	for(i = 0;i < EQUIPMENT_NUM_MAX;i++)
	{
		//�X�g���[�W���󔒂̕�����T��
		if(m_Item[i].GetID() == 0)
		{
			//�A�C�e���̊i�[
			m_Item[i] = Item;

			//���\�̐ݒ肪����Ă��Ȃ���΁A�����I�ɐݒ肷��
			if(m_Item[i].GetValue() == 0)
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
//ID���疼�O�������A���O���i�[
//---------------------------------------------------------------------------------------
void CEquipmentInventory::FindName	(int nID,int Receipt)
{
	switch(nID)
	{
	case ITEM_APPLE:
		m_Item[Receipt].SetName(_T("�ь�"));
		break;
	case ITEM_HERB:
		m_Item[Receipt].SetName(_T("��"));
		break;
	case ITEM_SWORD:
		m_Item[Receipt].SetName(_T("����"));
		break;
	case ITEM_SHIELD:
		m_Item[Receipt].SetName(_T("����"));
		break;
	default:
		break;
	}
}

//---------------------------------------------------------------------------------------
//�`��t���O���O������ON/OFF����
//---------------------------------------------------------------------------------------
void CEquipmentInventory::DrawFlgChange()
{
	m_bDrawFlg = !m_bDrawFlg;
}

//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�A�C�e��������
//---------------------------------------------------------------------------------------
void CEquipmentInventory::DelInventory(int Receipt)
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
int CEquipmentInventory::GetEffect(int Receipt)
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
		return EFFECT_RECOVERY;
		break;
		//��
	case ITEM_SWORD:
		//�U���̓A�b�v
		return EFFECT_EQUIPMENT_ATTACK;
		break;
		//��
	case ITEM_SHIELD:
		//�h��̓A�b�v
		return EFFECT_EQUIPMENT_DEFENCE;
		break;
		//�o�O�����p
	default:
		//���ʂȂ�
		return EFFECT_NON;
		break;
	}
}
//---------------------------------------------------------------------------------------
//�w�肳�ꂽ�A�C�e���̌��\?��ԋp����
//---------------------------------------------------------------------------------------
int CEquipmentInventory::GetEffectValue(int Receipt)
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
//---------------------------------------------------------------------------------------
//�C���x���g���ɑ��݂��邷�ׂĂ̍U�������A�C�e���̍��v�l���Z�o���A�n��
//---------------------------------------------------------------------------------------
int CEquipmentInventory::GetAttackTotalValue()
{
	//���v�l�i�[�p�ϐ�
	int nTotalNum = 0;

	//�S�ẴA�C�e�������m�F����
	for(int i = 0;i < EQUIPMENT_NUM_MAX;i++)
	{
		//���ʂ��U���⏕���m�F����
		if(m_Item[i].GetType() == EFFECT_EQUIPMENT_ATTACK)
		{
			//�U���⏕�^�Ȃ�A���̒l�����o���A���Z
			nTotalNum = m_Item[i].GetValue();
		}
	}
	return nTotalNum;
}
//---------------------------------------------------------------------------------------
//�C���x���g���ɑ��݂��邷�ׂĂ̖h�䋭���A�C�e���̍��v�l���Z�o���A�n��
//---------------------------------------------------------------------------------------
int CEquipmentInventory::GetDefenceTotalValue()
{
	//���v�l�i�[�p�ϐ�
	int nTotalNum = 0;
	//�S�ẴA�C�e�������m�F����
	for(int i = 0;i < EQUIPMENT_NUM_MAX;i++)
	{
		//���ʂ��h��⏕���m�F����
		if(m_Item[i].GetType() == EFFECT_EQUIPMENT_DEFENCE)
		{
			//�h��⏕�^�Ȃ�A���̒l�����o���A���Z
			nTotalNum = m_Item[i].GetValue();
		}
	}
	return nTotalNum;
}