#include "MenuSelect.h"
#include "TextureManager.h"
#include "Input.h"
#include "ItemWindow.h"
#include "StatesWindow.h"
#include "EquipmentWindow.h"
#include "TrickWindow.h"

//---------------------------------------------------------------------------------------
//�ÓI�����o�ϐ�
//---------------------------------------------------------------------------------------
CMenuSelect* CMenuSelect::m_pMenuSelect = NULL;

//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CMenuSelect::CMenuSelect(void)
{
	//�g�p����e�N�X�`��ID�̐ݒ�
	m_nTextureID = TEXTURE_RED_TEXTURE;

	//�I�𒆃R�}���h�̐ݒ�
	m_nSelectNumber = 0;

	//�{�^�����͌o�ߎ��Ԃ�������
	m_nInterval = 0;

	//����t���O�̏�����
	m_bOperationFlg = false;

	//�ʒu���̐ݒ�
	m_aVertex[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f , 50.0f ,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f , 50.0f ,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f ,205.0f ,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f ,205.0f ,0.0f);
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CMenuSelect::~CMenuSelect(void)
{
	//����t���O�̏�����
	m_bOperationFlg = false;

	//�{�^�����͌o�ߎ��Ԃ�������
	m_nInterval = 0;
}
//---------------------------------------------------------------------------------------
//���̂̐���
//---------------------------------------------------------------------------------------
void CMenuSelect::Create()
{
	//���g���Ȃ���΍쐬
	if (!m_pMenuSelect)
	{
		m_pMenuSelect = new CMenuSelect;
	}
}
//---------------------------------------------------------------------------------------
//���̂̍폜
//---------------------------------------------------------------------------------------
void CMenuSelect::Delete()
{
	//���̂�����΍폜
	if (m_pMenuSelect)
	{
		delete m_pMenuSelect;
		m_pMenuSelect = NULL;
	}
}
//---------------------------------------------------------------------------------------
//���̂̃|�C���^��n��
//---------------------------------------------------------------------------------------
CMenuSelect* CMenuSelect::GetPointer()
{
	//�O�̂��ߍ쐬�֐����Ăяo��
	Create();
	return m_pMenuSelect;
}
//---------------------------------------------------------------------------------------
//�X�V
//---------------------------------------------------------------------------------------
void CMenuSelect::Update(void)
{
	m_nInterval ++;
	if(!m_pItemWindow->GetDrawFlg() && !m_pEquipmentWindow->GetDrawFlg() && !m_pTrickWindow->GetDrawFlg())
	{
		//��L�[�������Ă���
		if((CInput::GetKeyTrigger(DIK_W) || CInput::GetJoyAxis(0,JOY_Y) <= -JoyMoveCap) && m_nInterval >= ButtonIntervalTime)
		{
			//�I�𒆃R�}���h�����
			m_nSelectNumber --;

			//���[�v
			if (m_nSelectNumber < 0)
				m_nSelectNumber = MENU_MAX - 1;

			//�{�^�����̓C���^�[�o����0�ɂ���
			m_nInterval = 0;
		}
		//���L�[�������Ă���
		if((CInput::GetKeyTrigger(DIK_S) || CInput::GetJoyAxis(0, JOY_Y) >= JoyMoveCap) && m_nInterval >= ButtonIntervalTime)
		{
			//�I�𒆃R�}���h������
			m_nSelectNumber ++;

			//���[�v
			m_nSelectNumber %= MENU_MAX;

			//�{�^�����̓C���^�[�o����0�ɂ���
			m_nInterval = 0;
		}

		//L(����)�{�^����������
		if((CInput::GetKeyTrigger(DIK_L) || CInput::GetJoyTrigger(0,3)) && m_nInterval >= ButtonIntervalTime)
		{
			//���ݑI�����Ă��郁�j���[�ɉ����A�o�͂���E�B���h�E��ݒ肷��
			switch(m_nSelectNumber)
			{
				//�A�C�e��
			case MENU_ITEM:
				//�A�C�e���E�C���h�E��`�悷��t���O�𗧂Ă�
				m_pItemWindow->DrawFlgChange(true);
				break;
			case MENU_TRICK:
				//�Z�E�B���h�E�̕`��t���O�𗧂Ă�
				m_pTrickWindow->DrawFlgChange();
				break;
			}

			//�{�^�����̓C���^�[�o����0�ɂ���
			m_nInterval = 0;
		}
	}

	//�ʒu���̐ݒ�
	m_aVertex[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 235.0f , 50.0f + (m_nSelectNumber * 155.0f) ,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH -  20.0f , 50.0f + (m_nSelectNumber * 155.0f) ,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 235.0f ,205.0f + (m_nSelectNumber * 155.0f) ,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH -  20.0f ,205.0f + (m_nSelectNumber * 155.0f) ,0.0f);
}
//---------------------------------------------------------------------------------------
//�����o�ϐ��̃|�C���^��ݒ�
//---------------------------------------------------------------------------------------
void CMenuSelect::SetPointer()
{
	//�X�e�[�^�X�E�B���h�E�̃|�C���^���擾
	m_pStatesWindow = CStatesWindow::GetPointer();
	m_pItemWindow = CItemWindow::GetPointer();
	m_pTrickWindow = CTrickWindow::GetPointer();
	m_pEquipmentWindow = CEquipmentWindow::GetPointer();
}
