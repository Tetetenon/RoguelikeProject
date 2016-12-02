//=======================================================================================
//
//	  [ DX9Game ] : DirectX9 �Q�[���x�[�X
//
//=======================================================================================
#include "GameWnd.h"
#include <windows.h>
#include <tchar.h>

#define CAPTION_NAME	_T("�s�v�c�̐X�̐Ԃ�����")	// �L���v�V����


int WINAPI appWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int iCmdShow)
{
	int nResult = EXIT_FAILURE;
	//�E�C���h�E�N���X�̎��̍쐬
	CGameWindow* pWnd = new CGameWindow();
	
	//�E�C���h�E�̍쐬
	if (pWnd->CreateFrame(
		CAPTION_NAME,								// �E�B���h�E �L���v�V����
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION,	// �E�B���h�E �X�^�C��
		0,											// �g���X�^�C��
		CW_USEDEFAULT, CW_USEDEFAULT,				// �E�B���h�E�ʒu(CW_USEDEFAULT���g�p�����0�ɂȂ�)
		SCREEN_WIDTH, SCREEN_HEIGHT)) {				// �N���C�A���g�̈�T�C�Y
		pWnd->Show(iCmdShow);						// �E�B���h�E��\��
		pWnd->Update();								// �E�B���h�E�\�����X�V
		nResult = pWnd->Run();						// ���b�Z�[�W ���[�v
	}
	delete pWnd;
	return nResult;
}
