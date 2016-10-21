//=======================================================================================
//
//	  [ DX9Game ] : DirectX9 �Q�[���x�[�X
//
//=======================================================================================
#include "GameWnd.h"
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>

//���������[�N���o�p
#if _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>

	#define new ::new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

//-------- ���C�u�����̃����N�i�����L�q���Ă����Εʓr�����N�ݒ肪�s�v�ƂȂ�j
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

#define CAPTION_NAME	_T("�s�v�c�̐X�̐Ԃ�����")	// �L���v�V����

//---------------------------------------------------------------------------------------
//	���C��
//---------------------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int iCmdShow)
{
#if _DEBUG
	//���������[�N�̌��m
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	// �E�B���h�E���쐬
	int nResult = EXIT_FAILURE;	//���ۏ�Ԃ��Ƃ肠�������s��Ԃɂ��ď�����(�̂��̊m�F�̍ۂ̃G���[���)


	//�������ԍ��Ƀu���[�N�|�C���g��u��
	//_CrtSetBreakAlloc(425);
	//_CrtSetBreakAlloc(310);


	//�E�C���h�E�N���X�̎��ԍ쐬
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
#if _DEBUG
	//���������[�N�̌��m
	::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	_CrtDumpMemoryLeaks();	// ���̎��_�ŊJ������Ă��Ȃ��������̏��̕\��
#endif
	return nResult;
}

//=======================================================================================
//	End of File
//=======================================================================================