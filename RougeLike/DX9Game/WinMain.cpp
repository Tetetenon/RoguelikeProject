//=======================================================================================
//
//	  [ DX9Game ] : DirectX9 �Q�[���x�[�X
//
//=======================================================================================
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

extern int WINAPI appWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int iCmdShow);

//---------------------------------------------------------------------------------------
//	���C��
//---------------------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int iCmdShow)
{
#if _DEBUG
	//���������[�N�̌��m
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	return appWinMain(hInstance,hPrevInst,lpCmdLine,iCmdShow);
}

//=======================================================================================
//	End of File
//=======================================================================================