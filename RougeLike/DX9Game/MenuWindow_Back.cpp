#include "MenuWindow_Back.h"

#include "TextureManager.h"


bool CMenuWindow_Back::m_bDrawFlg = false;							//メニューウインドウ描画フラグ

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CMenuWindow_Back::CMenuWindow_Back(void)
{
	//使用するテクスチャIDの設定
	m_nTextureID = TEXTURE_WHITE_TEXTURE;

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
CMenuWindow_Back::~CMenuWindow_Back(void)
{
	//描画フラグの初期化
	m_bDrawFlg = false;
}