//=======================================================================================
//
//	  [ DX9Game ] : DirectX9 ゲームベース
//
//=======================================================================================
#include "GameWnd.h"
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

#define CAPTION_NAME	_T("不思議の森の赤ずきん")	// キャプション

//---------------------------------------------------------------------------------------
//	メイン
//---------------------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int iCmdShow)
{
#if _DEBUG
	//メモリリークの検知
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	// ウィンドウを作成
	int nResult = EXIT_FAILURE;	//成否状態をとりあえず失敗状態にして初期化(のちの確認の際のエラー回避)


	//メモリ番号にブレークポイントを置く
	//_CrtSetBreakAlloc(425);
	//_CrtSetBreakAlloc(310);


	//ウインドウクラスの実態作成
	CGameWindow* pWnd = new CGameWindow();
	
	//ウインドウの作成
	if (pWnd->CreateFrame(
		CAPTION_NAME,								// ウィンドウ キャプション
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION,	// ウィンドウ スタイル
		0,											// 拡張スタイル
		CW_USEDEFAULT, CW_USEDEFAULT,				// ウィンドウ位置(CW_USEDEFAULTを使用すると0になる)
		SCREEN_WIDTH, SCREEN_HEIGHT)) {				// クライアント領域サイズ
		pWnd->Show(iCmdShow);						// ウィンドウを表示
		pWnd->Update();								// ウィンドウ表示を更新
		nResult = pWnd->Run();						// メッセージ ループ
	}
	delete pWnd;
#if _DEBUG
	//メモリリークの検知
	::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	_CrtDumpMemoryLeaks();	// この時点で開放されていないメモリの情報の表示
#endif
	return nResult;
}

//=======================================================================================
//	End of File
//=======================================================================================