#include "StatesWindow.h"
#include "TextureManager.h"
#include "Input.h"

#include "MenuWindow.h"

//シングルトンのポインタ
CStatesWindow* CStatesWindow::m_pStatesWindow = NULL;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CStatesWindow::CStatesWindow(void)
{
	//使用するテクスチャIDの設定
	m_nTextureID = TEXTURE_WINDOW;

	//入力経過時間初期化
	m_IntervalTime = 0;

	//描画フラグの初期化
	m_bDrawFlg = false;

	//位置情報の設定
	WindowSizeUpdate();
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CStatesWindow::~CStatesWindow(void)
{
	//描画フラグの初期化
	m_bDrawFlg = false;

	//入力経過時間初期化
	m_IntervalTime = 0;
}
//---------------------------------------------------------------------------------------
//実体の作成
//---------------------------------------------------------------------------------------
void CStatesWindow::Create()
{
	//中身が無ければ作成
	if (!m_pStatesWindow)
	{
		m_pStatesWindow = new CStatesWindow;
	}
}
//---------------------------------------------------------------------------------------
//実体の削除
//---------------------------------------------------------------------------------------
void CStatesWindow::Delete()
{
	//中身があれば削除
	if (m_pStatesWindow)
	{
		delete m_pStatesWindow;
		m_pStatesWindow = NULL;
	}
}
//---------------------------------------------------------------------------------------
//実体のポインタを渡す
//---------------------------------------------------------------------------------------
CStatesWindow* CStatesWindow::GetPointer()
{
	//念のため作成関数を呼ぶ
	Create();
	return m_pStatesWindow;
}

//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CStatesWindow::Update(void)
{
	//描画処理を行っていない場合処理しない
	if (!m_bDrawFlg)
		return;

	m_IntervalTime++;

	//入力経過時間が一定以下の場合処理しない
	if (m_IntervalTime < ButtonIntervalTime)
		return;

	//決定(L)又は戻る(K)でウィンドウを閉じる
	if(CInput::GetKeyTrigger(DIK_L)|| CInput::GetJoyTrigger(0,2) || !m_pMenuWindow->GetDrawFlg())
	{
		m_bDrawFlg = false;
		m_IntervalTime = 0;
	}
}

//---------------------------------------------------------------------------------------
//ウィンドウサイズの更新
//---------------------------------------------------------------------------------------
void CStatesWindow::WindowSizeUpdate(void)
{
	//位置情報の設定
	m_aVertex[0].pos = D3DXVECTOR3( 10.0f, 10.0f,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(600.0f, 10.0f,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3( 10.0f, 50.0f,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(600.0f, 50.0f,0.0f);
}

//---------------------------------------------------------------------------------------
//メンバ変数のポインタを設定する
//---------------------------------------------------------------------------------------
void CStatesWindow::SetPointer()
{
	//ポインタの取得
	m_pMenuWindow = CMenuWindow::GetPointer();
}
