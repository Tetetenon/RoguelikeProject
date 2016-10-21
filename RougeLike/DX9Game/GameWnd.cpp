//=======================================================================================
//
//	  ゲーム用ウィンドウ クラス定義
//
//=======================================================================================
#include "GameWnd.h"
#include "define.h"
#include "Input.h"

#include "TextureManager.h"

#include "GameState.h"

#pragma comment(lib, "imm32")

//---------------------------------------------------------------------------------------
//	ウィンドウ初期化
//---------------------------------------------------------------------------------------
bool CGameWindow::InitInstance()
{
	m_pGraph = NULL;	//描画クラスの中身を初期化
	m_pScene = NULL;	//シーンクラスの中身を初期化
	m_pResultscene = NULL;	//リザルトシーンクラスの初期化

	//ウインドウと入力ハンドルの関連付け(NULLの場合切り離し)
	::ImmAssociateContext(GetHwnd(), NULL);

	//ウインドウの初期化?
	if (!CWindow::InitInstance()) return false;

	//ウインドウのフルスクリーン成否
	m_bWindow = false;

	//
	int nID = MessageBox(_T("ウィンドウモードで実行しますか？"), _T("画面モード"), MB_YESNOCANCEL);
	if (nID == IDCANCEL) 
		return false;
	if (nID == IDYES) 
		m_bWindow = true;

	::timeBeginPeriod(1);	// タイマの分解能を最小にセット

	// グラフィックデバイス初期化
	m_pGraph = CGraphics::Create(GetHwnd(), SCREEN_WIDTH, SCREEN_HEIGHT, m_bWindow);

	if (!m_pGraph) return false;

	//タイトルシーン作成
	m_pTitleScene = CTitleScene::Create(m_pGraph);
	if (!m_pTitleScene) 
		return false;

	//使用テクスチャデータの読み込み
	CTextureManager::LoadTexture();


	//FPSの現在時間を取得
	m_dwFPSLastTime = ::timeGetTime();

	m_dwExecLastTime = m_dwFPSLastTime - FRAME_RATE;// 必ず最初に m_pScene->Update() を実行

	m_dwFrameCount = 0;

	//DirectInput初期化
	CInput::Init(CWindow::GetHwnd());

	return true;
}

//---------------------------------------------------------------------------------------
//	ウィンドウ解放
//---------------------------------------------------------------------------------------
int CGameWindow::ExitInstance()
{
	// シーン解放
	SAFE_RELEASE(m_pScene);

	//リザルトシーン解放
	SAFE_RELEASE(m_pResultscene);

	//タイトルシーン解放
	SAFE_RELEASE(m_pTitleScene);

	//使用テクスチャ開放
	CTextureManager::ReleaseTexture();

	// グラフィック デバイス解放
	SAFE_RELEASE(m_pGraph);

	::timeEndPeriod(1);				// タイマの分解能を元に戻す

	//DirectInputの開放
	CInput::Fin();

	return CWindow::ExitInstance();	// 実行ファイルの戻り値
}

//---------------------------------------------------------------------------------------
//	アイドル時処理
//---------------------------------------------------------------------------------------
bool CGameWindow::OnIdle(long lCount)
{
	// この辺でフレーム数カウント
	DWORD dwCurrentTime = timeGetTime();			// 現在のタイマ値を取得
	if ((dwCurrentTime - m_dwFPSLastTime) >= 500) 
	{	// 0.5 秒ごとに計測
		// フレーム数を計算
		if (m_pScene) 
		{
			m_pScene->SetFPS(m_dwFrameCount * 1000 / (dwCurrentTime - m_dwFPSLastTime));
		}
		m_dwFPSLastTime = dwCurrentTime;	// タイマ値を更新
		m_dwFrameCount = 0;					// フレームカウンタをリセット
	}
	// この辺で時間管理
	if ((dwCurrentTime - m_dwExecLastTime) >= FRAME_RATE)
	{	
		// 一定時間が経過したら…
		m_dwExecLastTime = dwCurrentTime;							// タイマ値を更新
		m_dwFrameCount++;
		//現在のシーンと前フレームのシーンが異なれば、前のフレームのシーンの実態を削除する
		if(CGameState::GetState() != CGameState::GetOldState())
		{
			switch(CGameState::GetOldState())
			{
			case STATE_GAME:
				SAFE_RELEASE(m_pScene);
				break;
			case STATE_TITLE:
				SAFE_RELEASE(m_pTitleScene);
				break;
			case STATE_RESUALT:
				SAFE_RELEASE(m_pResultscene);
				break;
			}
			
			CGameState::StateCheck();
		}

		//現在のステートから、更新するステートを決定
		switch(CGameState::GetState())
		{
		case STATE_GAME:
			//ゲームシーンが存在しなかった場合、作成する
			if (!m_pScene) 
			{
				m_pScene = CGameScene::Create(m_pGraph);
			}
			m_pScene -> Update();
			break;
		case STATE_TITLE:
			//タイトルシーンが存在しなければ作成する
			if(!m_pTitleScene)
			{
				m_pTitleScene = CTitleScene::Create(m_pGraph);
			}
			m_pTitleScene -> Update();
			break;
		case STATE_RESUALT:
			//リザルトシーンが存在しなければ作成する
			if(!m_pResultscene)
			{
				m_pResultscene = CResultScene::Create(m_pGraph);
			}
			m_pResultscene -> UpDate();
			break;
		}
	}

	//現在のステートのシーンのみレンダリングする
	switch(CGameState::GetState())
	{
	case STATE_GAME:
		if (m_pScene) 
		{
			m_pScene-> Render();				// レンダリング処理
			m_dwFrameCount++;					// フレームカウント＋１
		}
		break;
	case STATE_TITLE:
		if(m_pTitleScene)
		{
			m_pTitleScene -> Render();
			m_dwFrameCount++;					// フレームカウント＋１
		}
		break;
	case STATE_RESUALT:
		if(m_pResultscene)
		{
			m_pResultscene -> Render();
			m_dwFrameCount++;					// フレームカウント＋１
		}
		break;
	}
	return true;
}

//---------------------------------------------------------------------------------------
//	WM_KEYDOWN ハンドラ
//---------------------------------------------------------------------------------------
void CGameWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// [Esc] が押されていたら
	if (nChar == VK_ESCAPE) 
	{
		// ウィンドウを閉じる
		OnClose();
	}
}

//---------------------------------------------------------------------------------------
//	WM_ERASEBKGND ハンドラ
//---------------------------------------------------------------------------------------
bool CGameWindow::OnEraseBkgnd(HDC hdc)
{
	// 背景消去しないで消去済みとして返す
	return true;
}

//---------------------------------------------------------------------------------------
//	WM_SETCURSOR ハンドラ
//---------------------------------------------------------------------------------------
bool CGameWindow::OnSetCursor(HWND hwnd, UINT nHitTest, UINT uMouseMsg)
{
	// 全画面モードか、マウスカーソル座標がクライアント領域内なら
	if (!m_bWindow || nHitTest == HTCLIENT) {
		// マウスカーソル消去
		//::SetCursor(NULL);
		return true;
	}
	return false;
}

//=======================================================================================
//	End of File
//=======================================================================================