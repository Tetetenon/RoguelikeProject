//=======================================================================================
//
//	  [ DX9Game ] : DirectX9 ゲームベース
//
//=======================================================================================
#include "GameWnd.h"
#include <windows.h>
#include <tchar.h>

#define CAPTION_NAME	_T("不思議の森の赤ずきん")	// キャプション


int WINAPI appWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int iCmdShow)
{
	int nResult = EXIT_FAILURE;
	//ウインドウクラスの実体作成
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
	return nResult;
}
