//---------------------------------------------------------------------------------------
//2Dウインドウ基底クラス
//---------------------------------------------------------------------------------------
#include "2DWindow.h"
#include "Graphics.h"

#include "TextureManager.h"

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
C2DWindow::C2DWindow(void)
{
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
C2DWindow::~C2DWindow(void)
{
}

//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void C2DWindow::Init()
{

}

//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void C2DWindow::Fin()
{

}

//---------------------------------------------------------------------------------------
//描画処理
//---------------------------------------------------------------------------------------
void C2DWindow::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
		
	// アルファ・ブレンディングを行う
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 透過処理を行う
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//テクスチャセット
	pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_SELECT_WINDOW));

	//ポリゴンの描画
	//頂点情報を外部が持っている場合Up
	//そのほかはprimitive
	pDevice -> DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,          //プリミティブの種類List（三角形描く）Strip(つなげて作る)
		NUM_POLYGON,                 //ポリゴン数
		m_aVertex,            //配列の先頭アドレス
		sizeof(VERTEX_2D)            //データの大きさ
		);
}

//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void C2DWindow::Update()
{
}

//---------------------------------------------------------------------------------------
//ポリゴン情報設定
//---------------------------------------------------------------------------------------
void C2DWindow::SetVertex ()
{	
	//位置情報設定
	m_aVertex[0].pos = D3DXVECTOR3((float)0				,(float)0				,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH	,(float)0				,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)0				,(float)SCREEN_HEIGHT	,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH	,(float)SCREEN_HEIGHT	,0.0f);

	//パースペクティブ設定?
	m_aVertex[0].rhw = 1.0f;
	m_aVertex[1].rhw = 1.0f;
	m_aVertex[2].rhw = 1.0f;
	m_aVertex[3].rhw = 1.0f;

	//頂点カラーの設定
	m_aVertex[0].col = D3DCOLOR_RGBA(255,255,255,255);
	m_aVertex[1].col = D3DCOLOR_RGBA(255,255,255,255);
	m_aVertex[2].col = D3DCOLOR_RGBA(255,255,255,255);
	m_aVertex[3].col = D3DCOLOR_RGBA(255,255,255,255);

	//ポリゴンとテクスチャの頂点を対応させる
	m_aVertex[0].tex = D3DXVECTOR2(0.0f,0.0f);
	m_aVertex[1].tex = D3DXVECTOR2(1.0f,0.0f);
	m_aVertex[2].tex = D3DXVECTOR2(0.0f,1.0f);
	m_aVertex[3].tex = D3DXVECTOR2(1.0f,1.0f);
}

//---------------------------------------------------------------------------------------
//ポリゴン位置設定
//---------------------------------------------------------------------------------------
void C2DWindow::SetPos()
{
	//位置情報設定
	m_aVertex[0].pos = D3DXVECTOR3((float)0				,(float)0				,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH	,(float)0				,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)0				,(float)SCREEN_HEIGHT	,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH	,(float)SCREEN_HEIGHT	,0.0f);
}