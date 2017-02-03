#include "StatesWindow.h"
#include "TextureManager.h"
#include "Input.h"

#include "MenuWindow.h"

//ステータスウィンドウ描画フラグ
bool CStatesWindow::m_bDrawFlg = false;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CStatesWindow::CStatesWindow(void)
{
	//使用するテクスチャIDの設定
	m_nTextureID = TEXTURE_WINDOW;

	//描画フラグの初期化
	m_bDrawFlg = false;

	//位置情報の設定
	m_aVertex[0].pos = D3DXVECTOR3( 10.0f,				  50.0f,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(240.0f,				  50.0f,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3( 10.0f,SCREEN_HEIGHT - 250.0f,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(240.0f,SCREEN_HEIGHT - 250.0f,0.0f);
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CStatesWindow::~CStatesWindow(void)
{
	//描画フラグの初期化
	m_bDrawFlg = false;
}

//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CStatesWindow::Update(void)
{
	//描画処理を行っていない場合処理しない
	if (!m_bDrawFlg)
		return;
	//決定(L)又は戻る(K)でウィンドウを閉じる
	if(CInput::GetKeyTrigger(DIK_L)|| CInput::GetJoyTrigger(0,2) || !CMenuWindow::GetDrawFlg())
	{
		m_bDrawFlg = false;
	}
}

//---------------------------------------------------------------------------------------
//ウィンドウサイズの更新
//---------------------------------------------------------------------------------------
void CStatesWindow::WindowSizeUpdate(void)
{
	if(m_bDrawFlg)
	{
		//位置情報の設定
		m_aVertex[0].pos = D3DXVECTOR3( 10.0f,				  50.0f,0.0f);
		m_aVertex[1].pos = D3DXVECTOR3(240.0f,				  50.0f,0.0f);
		m_aVertex[2].pos = D3DXVECTOR3( 10.0f,SCREEN_HEIGHT - 250.0f,0.0f);
		m_aVertex[3].pos = D3DXVECTOR3(240.0f,SCREEN_HEIGHT - 250.0f,0.0f);
	}
	else
	{
		//位置情報の設定
		m_aVertex[0].pos = D3DXVECTOR3( 10.0f, 50.0f,0.0f);
		m_aVertex[1].pos = D3DXVECTOR3(240.0f, 50.0f,0.0f);
		m_aVertex[2].pos = D3DXVECTOR3( 10.0f,195.0f,0.0f);
		m_aVertex[3].pos = D3DXVECTOR3(240.0f,195.0f,0.0f);
	}
}