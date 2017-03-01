#include "UIManager.h"
//-----�A�C�e���E�C���h�E-----
#include "ItemWindow.h"
#include "ItemWindowCursor.h"		//�A�C�e���J�[�\��
#include "ItemCommandWindow.h"		//�R�}���h�E�C���h�E
#include "ItemCommandCursor.h"		//�R�}���h�I���J�[�\��
#include "ItemDescriptionFrame.h"	//�A�C�e������
//-----�X�e�[�^�X�`��-----
#include "HPDraw.h"
//-----���j���[�E�C���h�E-----
#include "MenuWindow.h"				//���j���[�E�C���h�E�e�N�X�`���`��
#include "MenuSelect.h"				//���j���[�E�B���h�E�̃Z���N�g�p�|���S��
#include "MenuWindow_Back.h"		//���j���[�E�B���h�E�̔w�i
#include "MenuStatesWindow.h"
//-----�X�e�[�^�X�E�B���h�E-----
#include "StatesWindow.h"			//�X�e�[�^�X�̃E�B���h�E�̂�
#include "StatesCharacter.h"		//�L�����N�^�[�E�B���h�E
#include "StatesFont.h"				//�L�����N�^�[�X�e�[�^�X�̕���
#include "StatesValue.h"			//�L�����N�^�[�̃X�e�[�^�X
//-----�����E�B���h�E-----
#include "EquipmentWindow.h"		//�����E�B���h�E
#include "EquipmentWindowCursor.h"	//�����I���J�[�\��
#include "EquipmentCommandWindow.h"	//�����R�}���h�E�B���h�E
#include "EquipmentCommandCursor.h"	//�����R�}���h�J�[�\��
//-----�Z�E�B���h�E-----
#include "TrickWindow.h"			//�Z�E�B���h�E
#include "TrickWindowCursor.h"		//�Z�J�[�\��
//-----���̑�-----
#include "Operation.h"				//�������
#include "MiniMap.h"				//�~�j�}�b�v����
#include "HierarchieNum.h"			//���݂̊K�w�����A�t�F�[�h�C�����ɕ\������
#include "MessageWindow.h"			//���b�Z�[�W�E�B���h�E
//---------------------------------------------------------------------------------------
//�ÓI�����o�ϐ��錾
//---------------------------------------------------------------------------------------
CUIManager* CUIManager::m_pUIManager = NULL;
//---------------------------------------------------------------------------------------
//�R���X�g���N�^
//---------------------------------------------------------------------------------------
CUIManager::CUIManager()
{
	//�V���O���g���̍쐬
	CItemWindow::Create();
	CItemWindowCursor::Create();
	CItemCommandWindow::Create();
	CItemCommandCursor::Create();
	CItemDescriptionFrame::Create();

	CHPDraw::Create();

	CMenuSelect::Create();
	CMenuWindow_Back::Create();

	CMenuStatesWindow::Create();

	CStatesWindow::Create();
	CStatesCharacter::Create();
	CStatesFont::Create();
	CStatesValue::Create();

	CEquipmentWindow::Create();
	CEquipmentWindowCursor::Create();
	CEquipmentCommandWindow::Create();
	CEquipmentCommandCursor::Create();

	CTrickWindowCursor::Create();
	CTrickWindow::Create();

	COperation::Create();
	CMiniMap::Create();
	CHierarchieNum::Create();
	CMessageWindow::Create();
	CMenuWindow::Create();

	//-----�e�|�C���^�̎擾-----
	m_pItemWindow				= CItemWindow::GetPointer();
	m_pItemWindowCursor			= CItemWindowCursor::GetPointer();
	m_pItemCommandWindow		= CItemCommandWindow::GetPointer();
	m_pItemCommandCursor		= CItemCommandCursor::GetPointer();

	m_pHPDraw					= CHPDraw::GetPointer();

	m_pMenuSelect				= CMenuSelect::GetPointer();
	m_pMenuBack					= CMenuWindow_Back::GetPointer();

	m_pMenuStatesWindow			= CMenuStatesWindow::GetPointer();

	m_pStatesWindow				= CStatesWindow::GetPointer();
	m_pStatesCharcter			= CStatesCharacter::GetPointer();
	m_pStatesFont				= CStatesFont::GetPointer();
	m_pStatesValue				= CStatesValue::GetPointer();

	m_pEquipmentWindow			= CEquipmentWindow::GetPointer();
	m_pEquipmentWindowCursor	= CEquipmentWindowCursor::GetPointer();
	m_pEquipmentCommandWindow	= CEquipmentCommandWindow::GetPointer();
	m_pEquipmentCommandCursor	= CEquipmentCommandCursor::GetPointer();

	m_pTrickWindow				= CTrickWindow::GetPointer();
	m_pTrickWindowCursor		= CTrickWindowCursor::GetPointer();

	m_pOperation				= COperation::GetPoiner();
	m_pMiniMap					= CMiniMap::GetPointer();
	m_pMessageWindow			= CMessageWindow::GetPointer();
	m_pMenuWindow				= CMenuWindow::GetPointer();
}

//---------------------------------------------------------------------------------------
//�f�X�g���N�^
//---------------------------------------------------------------------------------------
CUIManager::~CUIManager()
{
	//�V���O���g���̍폜
	CItemWindow::Delete();
	CItemWindowCursor::Delete();
	CItemCommandWindow::Delete();
	CItemCommandCursor::Delete();
	CItemDescriptionFrame::Delete();

	CHPDraw::Delete();

	CMenuWindow::Delete();
	CMenuSelect::Delete();
	CMenuWindow_Back::Delete();

	CMenuStatesWindow::Delete();

	CStatesWindow::Delete();
	CStatesCharacter::Delete();
	CStatesFont::Delete();
	CStatesValue::Delete();

	CEquipmentWindow::Delete();
	CEquipmentWindowCursor::Delete();
	CEquipmentCommandWindow::Delete();
	CEquipmentCommandCursor::Delete();

	CTrickWindow::Delete();
	CTrickWindowCursor::Delete();

	COperation::Delete();
	CMiniMap::Delete();
	CHierarchieNum::Delete();
	CMessageWindow::Delete();
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̎��̂̍쐬
//---------------------------------------------------------------------------------------
void CUIManager::Create()
{
	//���̂��Ȃ���΍쐬
	if (!m_pUIManager)
	{
		m_pUIManager = new CUIManager;
	}
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̎��̂��폜
//---------------------------------------------------------------------------------------
void CUIManager::Delete()
{
	//���̂�����΍폜
	if (m_pUIManager)
	{
		delete m_pUIManager;
		m_pUIManager = NULL;
	}
}
//---------------------------------------------------------------------------------------
//�}�l�[�W���[�̃|�C���^��n��
//---------------------------------------------------------------------------------------
CUIManager* CUIManager::GetPointer()
{
	//�O�̂��ߍ쐬�֐����Ă�
	Create();
	return m_pUIManager;
}
//---------------------------------------------------------------------------------------
//�eUI�̍X�V
//---------------------------------------------------------------------------------------
void CUIManager::ManageUIUpdate()
{
	m_pMessageWindow->Update();	//���b�Z�[�W�E�C���h�E�X�V
	m_pHPDraw->Update();			//HP�X�V

	//���j���[�E�B���h�E�̕`�悪�s���Ă��邩�H
	if(m_pMenuWindow->GetDrawFlg())
	{
		//�X�e�[�^�X�E�B���h�E�̕`�悪�s���Ă��邩�H
		if (!m_pStatesWindow->GetDrawFlg())
		{
			//���j���[�E�B���h�E�̃Z���N�g���X�V
			m_pMenuSelect->Update();
			//���j���[�E�B���h�E�̓��͍X�V
			m_pMenuWindow->Update();
			//���j���[�X�e�[�^�X�E�B���h�E�̍X�V
			m_pMenuStatesWindow->Update();
		}
	}
	//�X�e�[�^�X�E�B���h�E�̍X�V(�L�[���͂̍X�V)
	m_pStatesWindow->Update();

	//�A�C�e���E�B���h�E�̍X�V
	ItemWindowUpdate();

	//�v���C���[�̋Z�E�B���h�E�̕`��t���O���m�F
	if (m_pTrickWindow->GetDrawFlg())
	{
		//�Z�E�B���h�E�̍X�V
		m_pTrickWindow->UpDate();
		//�Z�E�B���h�E�̃J�[�\�����X�V
		m_pTrickWindowCursor->Update();
	}
	//�X�e�[�^�X�E�B���h�E�̃T�C�Y�̍X�V
	m_pStatesWindow->WindowSizeUpdate();

	// �~�j�}�b�v�̍X�V
	m_pMiniMap->Update();

}
//---------------------------------------------------------------------------------------
//�eUI�̕`��
//---------------------------------------------------------------------------------------
void CUIManager::ManageUIDraw()
{
	//���b�Z�[�W�E�C���h�E�`��
	m_pMessageWindow->Draw();
	//��������`��
	m_pOperation->Draw();
	//�X�e�[�^�X�̃E�B���h�E��`�悷��
	m_pStatesWindow->Draw();
	//HP�`��
	m_pHPDraw->Draw();
	//�L�����N�^�[�E�B���h�E�̕`��
	m_pStatesCharcter->Draw();

	//���j���[�E�B���h�E�̕`��t���O�������Ă��邩�m�F
	if (m_pMenuWindow->GetDrawFlg())
	{
		//���j���[�E�B���h�E�̔w�i�`��
		m_pMenuBack->Draw();
		//�Z���N�g���j���[�e�N�X�`���`��
		m_pMenuSelect->Draw();
		//���j���[�E�B���h�E�e�N�X�`���`��
		m_pMenuWindow->Draw();

		//���j���[�X�e�[�^�X�E�B���h�E�̕`��
		m_pMenuStatesWindow->Draw();
		//�X�e�[�^�X�̕�����`�悷��
		m_pStatesFont->Draw();
		//�X�e�[�^�X�̐��l��`�悷��
		m_pStatesValue->Draw();
	}

	//�A�C�e���E�B���h�E�̕`��
	ItemWindowDraw();

	//�v���C���[�̋Z�E�B���h�E�̕`��t���O���m�F
	if (m_pTrickWindow->GetDrawFlg())
	{
		//�Z�E�B���h�E��`��
		m_pTrickWindow->Draw();
		//�Z�E�B���h�E�̃J�[�\����`��
		m_pTrickWindowCursor->Draw();
	}

	//���j���[�E�B���h�E�̕`�悵�ĂȂ���Ε`��
	if (!m_pMenuWindow->GetDrawFlg())
	{
		//�~�j�}�b�v�̕`��
		m_pMiniMap->Draw();
	}
}
//---------------------------------------------------------------------------------------
//�A�C�e���E�B���h�E�̍X�V
//---------------------------------------------------------------------------------------
void CUIManager::ItemWindowUpdate()
{
	//�A�C�e���E�B���h�E�̕`�悪�s���Ă��Ȃ��ꍇ�A�������s��Ȃ�
	if (!m_pItemWindow->GetDrawFlg())
		return;

	//�A�C�e���E�B���h�E�̍X�V�t���O�������Ă���΃A�C�e���E�B���h�E���X�V����
	if (m_pItemWindow->GetUpdateFlg())
	{
		//�R�}���h�E�C���h�E���`�悳��Ă��邩���ʂ��s��
		if (m_pItemCommandWindow->GetDrawFlg())
		{
			//�R�}���h�E�C���h�E�̍X�V
			m_pItemCommandWindow->UpDate();
			//�R�}���h�J�[�\���̍X�V
			m_pItemCommandCursor->Update();
		}
		else
		{
			//�A�C�e���E�B���h�E�̍X�V
			m_pItemWindow->UpDate();
			//�E�C���h�E�J�[�\���̍X�V
			m_pItemWindowCursor->Update();
		}
	}
	else
	{
		//�����R�}���h�E�C���h�E���`�悳��Ă��邩���ʂ��s��
		if (m_pEquipmentCommandWindow->GetDrawFlg())
		{
			//�����E�C���h�E�̍X�V
			m_pEquipmentCommandWindow->UpDate();
			//�����J�[�\���̍X�V
			m_pEquipmentCommandCursor->Update();
		}
		else
		{
			//�����E�B���h�E�̍X�V
			m_pEquipmentWindow->UpDate();
			//�����E�C���h�E�J�[�\���̍X�V
			m_pEquipmentWindowCursor->Update();
		}
	}
}


//---------------------------------------------------------------------------------------
//�A�C�e���E�B���h�E�̕`��
//---------------------------------------------------------------------------------------
void CUIManager::ItemWindowDraw()
{
	//�A�C�e���E�B���h�E�̕`������Ă��Ȃ��ꍇ�������s��Ȃ�
	if (!m_pItemWindow->GetDrawFlg())
		return;
	//�A�C�e���E�C���h�E�̕`��
	m_pItemWindow->Draw();

	//�����E�C���h�E�̕`��
	m_pEquipmentWindow->Draw();

	//�R�}���h�J�[�\�����`�揈�����s�������ʂ��s��
	if (m_pItemCommandWindow->GetDrawFlg())
	{
		//�R�}���h�E�C���h�E�`��
		m_pItemCommandWindow->Draw();
		//�R�}���h�J�[�\���̕`��
		m_pItemCommandCursor->Draw();
	}

	//�A�C�e���E�B���h�E���̍X�V���s���ꍇ
	if (m_pItemWindow->GetUpdateFlg())
	{
		//�A�C�e���E�B���h�E�J�[�\����`��
		m_pItemWindowCursor->Draw();
	}
	else if (m_pItemWindow->GetDrawFlg())
	{
		//�����J�[�\���̕`��
		m_pEquipmentWindowCursor->Draw();
	}
	//�R�}���h�J�[�\�����`�揈�����s�������ʂ��s��
	if (m_pEquipmentCommandWindow->GetDrawFlg())
	{
		//�����R�}���h�E�C���h�E�`��
		m_pEquipmentCommandWindow->Draw();
		//�����R�}���h�J�[�\���̕`��
		m_pEquipmentCommandCursor->Draw();
	}
}
//---------------------------------------------------------------------------------------
//�eUI�̃����o�ϐ��̃|�C���^���Z�b�g����
//---------------------------------------------------------------------------------------
void CUIManager::ManageUISetPointer()
{
	m_pItemWindow				->SetPoiner();
	m_pItemWindowCursor			->SetPointer();
	m_pItemCommandWindow		->SetPointer();
	m_pItemCommandCursor		->SetPointer();
	m_pMenuSelect				->SetPointer();
	m_pStatesWindow				->SetPointer();
	m_pEquipmentWindow			->SetPointer();
	m_pEquipmentWindowCursor	->SetPointer();
	m_pEquipmentCommandWindow	->SetPointer();
	m_pEquipmentCommandCursor	->SetPointer();
	m_pTrickWindow				->SetPointer();
	m_pTrickWindowCursor		->SetPointer();
	m_pMiniMap					->SetPointer();
}
//---------------------------------------------------------------------------------------
//�eUI�̏�����
//---------------------------------------------------------------------------------------
void CUIManager::ManageUIInit()
{
	m_pMessageWindow->InitFontData();
}