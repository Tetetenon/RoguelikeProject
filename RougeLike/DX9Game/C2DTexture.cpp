#include "C2DTexture.h"

#include "Graphics.h"
#include "TextureManager.h"


//頂点フォーマット（頂点座標[2D]/頂点カラー）
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)//(位置情報 | カラー | テクスチャの情報0じゃだめ)

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
C2DTexture::C2DTexture(void)
{
	//ポリゴンの情報を設定する
	SetVertex();
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
C2DTexture::~C2DTexture(void)
{
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void C2DTexture::Draw()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//αブレンディングを行う
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 透過処理を行う
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//テクスチャのセット
	pDevice ->SetTexture(0,*CTextureManager::GetTexture(m_nTextureID));

	
	//ポリゴンの描画
	pDevice -> DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,          //プリミティブの種類List（三角形描く）Strip(つなげて作る)
		NUM_POLYGON,                 //ポリゴン数
		m_aVertex,            //配列の先頭アドレス
		sizeof(VERTEX_2D)            //データの大きさ
		);

}
//---------------------------------------------------------------------------------------
//ポリゴン情報の設定
//---------------------------------------------------------------------------------------
void C2DTexture::SetVertex()
{
	//位置情報設定
	m_aVertex[0].pos = D3DXVECTOR3(0.0f			,0.0f			,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH	,0.0f			,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(0.0f			,SCREEN_HEIGHT	,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH	,SCREEN_HEIGHT	,0.0f);

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
//位置情報の設定
//---------------------------------------------------------------------------------------
void C2DTexture::SetPos(float fPosX,float fPosY,float fHalfSizeX,float fHalfSizeY)
{
	//位置情報設定
	m_aVertex[0].pos = D3DXVECTOR3(fPosX - (fHalfSizeX / 2),fPosY - (fHalfSizeY / 2),0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(fPosX + (fHalfSizeX / 2),fPosY - (fHalfSizeY / 2),0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(fPosX - (fHalfSizeX / 2),fPosY + (fHalfSizeY / 2),0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(fPosX + (fHalfSizeX / 2),fPosY + (fHalfSizeY / 2),0.0f);
}

void C2DTexture::SetPosLeftUpOrigin(float fPosX, float fPosY, float fWidth, float fHeight)
{
	m_aVertex[0].pos = D3DXVECTOR3(fPosX,fPosY,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(fPosX + fWidth,fPosY,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(fPosX,fPosY + fHeight,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(fPosX + fWidth,fPosY + fHeight,0.0f);
}

//---------------------------------------------------------------------------------------
//ポリゴンのアルファ値を設定する
//---------------------------------------------------------------------------------------
void C2DTexture::SetAlpha(int nAlpha)
{
	//頂点カラーの設定
	m_aVertex[0].col = D3DCOLOR_RGBA(255,255,255,nAlpha);
	m_aVertex[1].col = D3DCOLOR_RGBA(255,255,255,nAlpha);
	m_aVertex[2].col = D3DCOLOR_RGBA(255,255,255,nAlpha);
	m_aVertex[3].col = D3DCOLOR_RGBA(255,255,255,nAlpha);
}