#include "MenuSelect.h"
#include "TextureManager.h"
#include "Input.h"
#include "ItemWindow.h"
#include "StatesWindow.h"
#include "EquipmentWindow.h"
#include "TrickWindow.h"

int	 CMenuSelect::m_nSelectNumber = 0;		//���ݑI�����Ă��郁�j���[�ԍ��i�[�p�ϐ�
bool CMenuSelect::m_bOperationFlg = false;	//���j���[�E�B���h�E����t���O
int	 CMenuSelect::m_nInterval = 0;			//�{�^�����͂̃C���^�[�o��	


//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CMenuSelect::CMenuSelect(void)
{
	//�g�p����e�N�X�`��ID�̐ݒ�
	m_nTextureID = TEXTURE_RED_TEXTURE;

	//�I�𒆃R�}���h�̐ݒ�
	m_nSelectNumber = 0;

	//����t���O�̏�����
	m_bOperationFlg = false;

	//�ʒu���̐ݒ�
	m_aVertex[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f , 50.0f ,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f , 50.0f ,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f ,127.5f ,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f ,127.5f ,0.0f);
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CMenuSelect::~CMenuSelect(void)
{
	//����t���O�̏�����
	m_bOperationFlg = false;
}


//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CMenuSelect::Update(void)
{
	m_nInterval ++;
	//�A�C�e���E�B���h�E���A�����E�B���h�E���A�Z�E�B���h�E���`�悵�Ă��Ȃ�
	if(!CInventory::GetDrawFlg() && !CEquipmentInventory::GetDrawFlg()&&!CTrickWindow::GetDrawFlg())
	{
		//��L�[�������Ă���
		if(CInput::GetKeyTrigger(DIK_W))
		{
			//�I�𒆃R�}���h�����
			m_nSelectNumber --;
		}
		//���L�[�������Ă���
		if(CInput::GetKeyTrigger(DIK_S))
		{
			//�I�𒆃R�}���h������
			m_nSelectNumber ++;
		}

		//L(����)�{�^����������
		if(CInput::GetKeyTrigger(DIK_L) && m_nInterval >= 10)
		{
			//���ݑI�����Ă��郁�j���[�ɉ����A�o�͂���E�B���h�E��ݒ肷��
			switch(m_nSelectNumber)
			{
				//�A�C�e��
			case MENU_ITEM:
				//�A�C�e���E�C���h�E��`�悷��t���O�𗧂Ă�
				CInventory::DrawFlgChange();
				break;
				//����
			case MENU_EQUIPMENT:
				//�����E�B���h�E��`�悷��t���O�𗧂Ă�
				CEquipmentInventory::DrawFlgChange();
				break;
				//�X�e�[�^�X
			case MENU_STATES:
				//�X�e�[�^�X�E�B���h�E�̕`��t���O�𗧂Ă�
				CStatesWindow::ChangeDrawFlg();
				break;
			case MENU_TRICK:
				//�Z�E�B���h�E�̕`��t���O�𗧂Ă�
				CTrickWindow::DrawFlgChange();
				break;
			}
		}
	}
	//-----���e�̈�͈͓��ɋ��邩�m�F-----
	if(m_nSelectNumber < 0)
	{
		m_nSelectNumber = 0;
	}
	if(m_nSelectNumber >= MENU_MAX)
	{
		m_nSelectNumber = MENU_MAX - 1;
	}

	//�ʒu���̐ݒ�
	m_aVertex[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 235.0f , 50.0f + (m_nSelectNumber * 77.5f) ,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH -  20.0f , 50.0f + (m_nSelectNumber * 77.5f) ,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 235.0f ,127.5f + (m_nSelectNumber * 77.5f) ,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH -  20.0f ,127.5f + (m_nSelectNumber * 77.5f) ,0.0f);
}
