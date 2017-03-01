#include "EquipmentWindow.h"
#include "Graphics.h"
#include "Input.h"
#include <tchar.h>
#include "EquipmentCommandWindow.h"
#include "EquipmentWindowCursor.h"
#include "Turn.h"
#include "TextureManager.h"
#include "MenuWindow.h"
#include"Unit.h"
#include "UnitManager.h"
#include "ItemWindow.h"
//---------------------------------------------------------------------------------------
//�}�N����`
//---------------------------------------------------------------------------------------
//�E�C���h�E�T�C�Y
#define WINDOW_WIDHT 300
#define WINDOW_HEIGHT 30

//---------------------------------------------------------------------------------------
//�ÓI�����o��`
//---------------------------------------------------------------------------------------
CEquipmentWindow* CEquipmentWindow::m_pEquipmentWindow = NULL;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CEquipmentWindow::CEquipmentWindow(void)
{
	//�����o������
	m_bDrawFlg = false;
	m_nInterval = 0;

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
CEquipmentWindow::~CEquipmentWindow(void)
{
	m_nInterval = 0;
}

//---------------------------------------------------------------------------------------
//���̂̐���
//---------------------------------------------------------------------------------------
void CEquipmentWindow::Create()
{
	//���̂��Ȃ���΍쐬
	if (!m_pEquipmentWindow)
	{
		m_pEquipmentWindow = new CEquipmentWindow;
	}
}
//---------------------------------------------------------------------------------------
//���̂̍폜
//---------------------------------------------------------------------------------------
void CEquipmentWindow::Delete()
{
	//���̂�����΍폜
	if (m_pEquipmentWindow)
	{
		delete m_pEquipmentWindow;
		m_pEquipmentWindow = NULL;
	}
}
//---------------------------------------------------------------------------------------
//���̂̃|�C���^��n��
//---------------------------------------------------------------------------------------
CEquipmentWindow* CEquipmentWindow::GetPointer()
{
	//�O�̂��ߍ쐬�֐����Ă�
	Create();
	return m_pEquipmentWindow;
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CEquipmentWindow::UpDate()
{

	m_nInterval++;

	if (m_nInterval < ButtonIntervalTime)
		return;

	//L�Ō���
	if((CInput::GetKeyTrigger(DIK_L) || CInput::GetJoyTrigger(0,3)))
	{
		CItem Equipment = m_pPlayerEquipment->GetItem(m_pInventoryCursor->GetItemNum());
		//�I�������A�C�e���E�C���h�E�ɃA�C�e�������݂��Ă��邩�m�F����
		//ID��0�ȊO�Ȃ�Α�����
		if (Equipment.GetID() == 0)
			return;
		//�R�}���h�E�C���h�E�`��t���O�𗧂Ă�
		m_pCommandWindow->DrawFlgChange();
		m_nInterval = 0;
	}

	//K��I�L�[�Ŗ߂�
	if(CInput::GetKeyTrigger(DIK_K) || CInput::GetJoyTrigger(0,2) || !m_pMenuWindow->GetDrawFlg())
	{
		//�A�C�e���E�B���h�E�̃t���O��|��
		m_pItemWindow->DrawFlgChange(false);
		m_nInterval = 0;
	}
}
//---------------------------------------------------------------------------------------
//�`��
//---------------------------------------------------------------------------------------
void CEquipmentWindow::Draw()
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
	for(int i = 0;i < EQUIPMENT_NUM_MAX;i++)
	{
		CItem Equipment = m_pPlayerEquipment->GetItem(i);
		ItemName = Equipment.GetName();
		ItemID	= Equipment.GetID();

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
void CEquipmentWindow::SetVertex()
{
	for(int i = 0;i < EQUIPMENT_NUM_MAX;i++)
	{
		//�ʒu���ݒ�
		m_aVertex[i][0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT	,(float)WINDOW_HEIGHT * (i + 1)					+ WINDOW_HEIGHT,0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT				,(float)WINDOW_HEIGHT * (i + 1)					+ WINDOW_HEIGHT,0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT	,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	+ WINDOW_HEIGHT,0.0f);
		m_aVertex[i][3].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT				,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	+ WINDOW_HEIGHT,0.0f);

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
void CEquipmentWindow::SetFontPos()
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
//�����o�ϐ��̃|�C���^��ݒ肷��
//---------------------------------------------------------------------------------------
void CEquipmentWindow::SetPointer()
{
	//�v���C���[�̑����A�C�e���|�C���^���擾����
	CUnitManager* pUnitManager = CUnitManager::GetPointer();
	CUnit* pPlayer = pUnitManager->GetPlayerPointer();
	m_pPlayerEquipment = pPlayer->GetEquipment();

	//�|�C���^�̎擾
	m_pCommandWindow = CEquipmentCommandWindow::GetPointer();
	m_pInventoryCursor = CEquipmentWindowCursor::GetPointer();
	m_pMenuWindow = CMenuWindow::GetPointer();
	m_pItemWindow = CItemWindow::GetPointer();
}

//---------------------------------------------------------------------------------------
//�`��t���O���O������ON/OFF����
//---------------------------------------------------------------------------------------
void CEquipmentWindow::DrawFlgChange()
{
	m_bDrawFlg = !m_bDrawFlg;
}