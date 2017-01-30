#include "MenuWindow.h"
#include "TextureManager.h"
#include "Input.h"

bool CMenuWindow::m_bDrawFlg = false;							//メニューウインドウ描画フラグ

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CMenuWindow::CMenuWindow(void)
{
	//使用するテクスチャIDの設定
	m_nTextureID = TEXTURE_MENU_WINDOW;

	//描画フラグの初期化
	m_bDrawFlg = false;

	//位置情報の設定
	m_aVertex[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f , 50.0f ,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f , 50.0f ,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 240.0f ,360.0f ,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH -  10.0f ,360.0f ,0.0f);
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CMenuWindow::~CMenuWindow(void)
{
	//描画フラグの初期化
	m_bDrawFlg = false;
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CMenuWindow::Update(void)
{
	//K入力で戻る
	if(CInput::GetKeyTrigger(DIK_K) || CInput::GetJoyTrigger(0,2))
	{
		//描画フラグを倒す
		m_bDrawFlg = false;
	}
}