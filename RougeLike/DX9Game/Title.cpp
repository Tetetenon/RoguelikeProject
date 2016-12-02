#include "Title.h"
#include "Graphics.h"
#include "TextureManager.h"
#include "EditTexture.h"

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CTitle::CTitle(void)
	//: m_pEditTexture(NULL)
{
	//使用するテクスチャのIDの設定
	m_nTextureID = TEXTURE_TITLE;
	//m_pEditTexture = new CEditTexture(800,600,CGraphics::GetDevice());
	//
	//m_pEditTexture->FillColor(0xff000000);
	//for (int x = 50; x < 100; ++x)
	//{
	//	for ( int y = 50; y < 100; ++y)
	//	{
	//		m_pEditTexture->SetColor(x,y,D3DCOLOR_RGBA(255,255,255,255));
	//	}
	//}
	//
	//m_pEditTexture->FillColor(150,150,50,50,0xffff0000);
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CTitle::~CTitle(void)
{
	//delete m_pEditTexture;
}

//void CTitle::Draw()
//{
//	//デバイス取得
//	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
//
//	//αブレンディングを行う
//	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
//	// 透過処理を行う
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	//頂点フォーマットの設定
//	pDevice ->SetFVF(FVF_VERTEX_2D);
//
//	//テクスチャのセット
//	pDevice ->SetTexture(0,*m_pEditTexture);
//	
//	//ポリゴンの描画
//	pDevice -> DrawPrimitiveUP(
//		D3DPT_TRIANGLESTRIP,          //プリミティブの種類List（三角形描く）Strip(つなげて作る)
//		NUM_POLYGON,                 //ポリゴン数
//		m_aVertex,            //配列の先頭アドレス
//		sizeof(VERTEX_2D)            //データの大きさ
//		);
//
//}