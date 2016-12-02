//=======================================================================================
//
//	  [ DX9Game ] : DirectX9 ゲームベース
//
//=======================================================================================
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>

//メモリリーク検出用
#if _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>

	#define new ::new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

//-------- ライブラリのリンク（こう記述しておけば別途リンク設定が不要となる）
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

extern int WINAPI appWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int iCmdShow);

//---------------------------------------------------------------------------------------
//	メイン
//---------------------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int iCmdShow)
{
#if _DEBUG
	//メモリリークの検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	return appWinMain(hInstance,hPrevInst,lpCmdLine,iCmdShow);
}

//=======================================================================================
//	End of File
//=======================================================================================