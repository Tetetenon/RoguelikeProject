//=======================================================================================
//
//	  �Q�[���p�E�B���h�E �N���X��`
//
//=======================================================================================
#include "GameWnd.h"
#include "define.h"
#include "Input.h"

#include "TextureManager.h"

#include "GameState.h"

#pragma comment(lib, "imm32")

//---------------------------------------------------------------------------------------
//	�E�B���h�E������
//---------------------------------------------------------------------------------------
bool CGameWindow::InitInstance()
{
	m_pGraph			= NULL;	//�`��N���X�̒��g��������
	m_pGameMainScene	= NULL;	//�Q�[�����C���V�[���N���X�̒��g��������
	m_pResultscene		= NULL;	//���U���g�V�[���N���X�̏�����
	m_pGameClearScene	= NULL;	//�Q�[���N���A�V�[���̃|�C���^��������

	//�E�C���h�E�Ɠ��̓n���h���̊֘A�t��(NULL�̏ꍇ�؂藣��)
	::ImmAssociateContext(GetHwnd(), NULL);

	//�E�C���h�E�̏�����?
	if (!CWindow::InitInstance()) return false;

	//�E�C���h�E�̃t���X�N���[������
	m_bWindow = false;

	::timeBeginPeriod(1);	// �^�C�}�̕���\���ŏ��ɃZ�b�g

	// �O���t�B�b�N�f�o�C�X������
	m_pGraph = CGraphics::Create(GetHwnd(), SCREEN_WIDTH, SCREEN_HEIGHT, m_bWindow);

	if (!m_pGraph)
		return false;

	//�^�C�g���V�[���쐬
	m_pTitleScene = CTitleScene::Create(m_pGraph);
	if (!m_pTitleScene) 
		return false;

	//�g�p�e�N�X�`���f�[�^�̓ǂݍ���
	CTextureManager::LoadTexture();


	//FPS�̌��ݎ��Ԃ��擾
	m_dwFPSLastTime = ::timeGetTime();

	m_dwExecLastTime = m_dwFPSLastTime - FRAME_RATE;// �K���ŏ��� m_pScene->Update() �����s

	m_dwFrameCount = 0;

	//DirectInput������
	CInput::Init(CWindow::GetHwnd());

	return true;
}

//---------------------------------------------------------------------------------------
//	�E�B���h�E���
//---------------------------------------------------------------------------------------
int CGameWindow::ExitInstance()
{
	//�Q�[�����C���V�[�����
	SAFE_RELEASE(m_pGameMainScene);

	//���U���g�V�[�����
	SAFE_RELEASE(m_pResultscene);

	//�^�C�g���V�[�����
	SAFE_RELEASE(m_pTitleScene);

	//�Q�[���N���A�V�[�����
	SAFE_RELEASE(m_pGameClearScene);

	//�g�p�e�N�X�`���J��
	CTextureManager::ReleaseTexture();

	// �O���t�B�b�N �f�o�C�X���
	SAFE_RELEASE(m_pGraph);

	::timeEndPeriod(1);				// �^�C�}�̕���\�����ɖ߂�

	//DirectInput�̊J��
	CInput::Fin();

	return CWindow::ExitInstance();	// ���s�t�@�C���̖߂�l
}

//---------------------------------------------------------------------------------------
//	�A�C�h��������
//---------------------------------------------------------------------------------------
bool CGameWindow::OnIdle(long lCount)
{
	// ���̕ӂŃt���[�����J�E���g
	DWORD dwCurrentTime = timeGetTime();			// ���݂̃^�C�}�l���擾
	if ((dwCurrentTime - m_dwFPSLastTime) >= 1000) 
	{	// 0.5 �b���ƂɌv��
		// �t���[�������v�Z
		if (m_pGameMainScene) 
		{
			m_pGameMainScene->SetFPS(m_dwFrameCount);
		}
		m_dwFPSLastTime = dwCurrentTime;	// �^�C�}�l���X�V
		m_dwFrameCount = 0;					// �t���[���J�E���^�����Z�b�g
	}
	// ���̕ӂŎ��ԊǗ�
	if ((dwCurrentTime - m_dwExecLastTime) >= FRAME_RATE)
	{	
		// ��莞�Ԃ��o�߂�����c
		m_dwExecLastTime = dwCurrentTime;							// �^�C�}�l���X�V
		m_dwFrameCount++;
		//���݂̃V�[���ƑO�t���[���̃V�[�����قȂ�΁A�O�̃t���[���̃V�[���̎��Ԃ��폜����
		if(CGameState::GetState() != CGameState::GetOldState())
		{
			switch(CGameState::GetOldState())
			{
			case STATE_GAME:
				SAFE_RELEASE(m_pGameMainScene);
				break;
			case STATE_TITLE:
				SAFE_RELEASE(m_pTitleScene);
				break;
			case STATE_GAMEOVER:
				SAFE_RELEASE(m_pResultscene);
				break;
			case STATE_GAMECLEAR:
				SAFE_RELEASE(m_pGameClearScene);
				break;
			}
			
			CGameState::StateCheck();
		}

		//���݂̃X�e�[�g����A�X�V����X�e�[�g������
		switch(CGameState::GetState())
		{
		case STATE_GAME:
			//�Q�[���V�[�������݂��Ȃ������ꍇ�A�쐬����
			if (!m_pGameMainScene) 
			{
				m_pGameMainScene = CGameScene::Create(m_pGraph);
			}
			m_pGameMainScene -> Update();
			break;
		case STATE_TITLE:
			//�^�C�g���V�[�������݂��Ȃ���΍쐬����
			if(!m_pTitleScene)
			{
				m_pTitleScene = CTitleScene::Create(m_pGraph);
			}
			m_pTitleScene -> Update();
			break;
		case STATE_GAMEOVER:
			//���U���g�V�[�������݂��Ȃ���΍쐬����
			if(!m_pResultscene)
			{
				m_pResultscene = CResultScene::Create(m_pGraph);
			}
			m_pResultscene -> UpDate();
			break;
		case STATE_GAMECLEAR:
			//�Q�[���N���A�V�[�������݂��Ȃ���΍쐬����
			if(!m_pGameClearScene)
			{
				m_pGameClearScene = CGameClearScene::Create(m_pGraph);
			}
			m_pGameClearScene ->UpDate();
			break;
		}
	}

	//���݂̃X�e�[�g�̃V�[���̂݃����_�����O����
	switch(CGameState::GetState())
	{
	case STATE_GAME:

		//�Q�[���V�[���̃|�C���^�����݂��邩�m�F�����
		if (m_pGameMainScene) 
		{
			m_pGameMainScene-> Render();		// �����_�����O����
		}
		break;
	case STATE_TITLE:

		//�^�C�g���V�[���̃|�C���^�����݂��邩�m�F�����
		if(m_pTitleScene)
		{
			m_pTitleScene -> Render();			//�����_�����O
		}
		break;
	case STATE_GAMEOVER:

		//�Q�[���I�[�o�[�V�[���̃|�C���^�����݂��邩�m�F�����
		if(m_pResultscene)
		{
			m_pResultscene -> Render();			//�����_�����O
		}
		break;
	case STATE_GAMECLEAR:

		//�Q�[���N���A�V�[���̃|�C���^�����݂��邩�m�F�����
		if(m_pGameClearScene)
		{
			m_pGameClearScene ->Render();		//�����_�����O
		}
	}
	return true;
}

//---------------------------------------------------------------------------------------
//	WM_KEYDOWN �n���h��
//---------------------------------------------------------------------------------------
void CGameWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// [Esc] ��������Ă�����
	if (nChar == VK_ESCAPE) 
	{
		// �E�B���h�E�����
		OnClose();
	}
}

//---------------------------------------------------------------------------------------
//	WM_ERASEBKGND �n���h��
//---------------------------------------------------------------------------------------
bool CGameWindow::OnEraseBkgnd(HDC hdc)
{
	// �w�i�������Ȃ��ŏ����ς݂Ƃ��ĕԂ�
	return true;
}

//---------------------------------------------------------------------------------------
//	WM_SETCURSOR �n���h��
//---------------------------------------------------------------------------------------
bool CGameWindow::OnSetCursor(HWND hwnd, UINT nHitTest, UINT uMouseMsg)
{
	// �S��ʃ��[�h���A�}�E�X�J�[�\�����W���N���C�A���g�̈���Ȃ�
	if (!m_bWindow || nHitTest == HTCLIENT) {
		// �}�E�X�J�[�\������
		::SetCursor(NULL);
		return true;
	}
	return false;
}

//=======================================================================================
//	End of File
//=======================================================================================