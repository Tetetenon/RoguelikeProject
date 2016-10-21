#include "StatesFont.h"
#include "define.h"
#include "Graphics.h"
#include "TextureManager.h"

//---------------------------------------------------------------------------------------
//静的メンバ定義
//---------------------------------------------------------------------------------------
int			CStatesFont::m_nTextureNumber[STATES_FONT_MAX];		//使用するテクスチャ設定用
VERTEX_2D	CStatesFont::m_aVertex[STATES_FONT_MAX][NUM_VERTEX];	//ポリゴン情報格納用

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CStatesFont::CStatesFont(void)
{
	//使用するテクスチャの設定
	m_nTextureNumber[STATES_FONT_ATTACK] = STATES_FONT_ATTACK;
	m_nTextureNumber[STATES_FONT_DEFENCE] = STATES_FONT_DEFENCE;
	m_nTextureNumber[STATES_FONT_EXP] = STATES_FONT_EXP;

	//頂点情報の設定
	SetVertex();
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CStatesFont::~CStatesFont(void)
{
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CStatesFont::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	
	// アルファ・ブレンディングを行う
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 透過処理を行う
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//アイテムウインドウ分描画
	for(int i = 0;i < STATES_FONT_MAX;i++)
	{
		//テクスチャの番号によりセットするテクスチャを決める
		switch(m_nTextureNumber[i])
		{
			//こうげき
		case STATES_FONT_ATTACK:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_ATTACK));
			break;
			//ぼうぎょ
		case STATES_FONT_DEFENCE:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_DEFENCE));
			break;
			//けいけんち
		case STATES_FONT_EXP:
			//テクスチャセット
			pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_EXP));
			break;
		}
		//ポリゴンの描画
		//頂点情報を外部が持っている場合Up
		//そのほかはprimitive
		pDevice -> DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP,          //プリミティブの種類List（三角形描く）Strip(つなげて作る)
			NUM_POLYGON,                 //ポリゴン数
			m_aVertex[i],            //配列の先頭アドレス
			sizeof(VERTEX_2D)            //データの大きさ
			);
	}
}
//---------------------------------------------------------------------------------------
//ポリゴン情報の設定
//---------------------------------------------------------------------------------------
void CStatesFont::SetVertex()
{
	for(int i = 0;i < STATES_FONT_MAX;i++)
	{
		//位置情報設定
		m_aVertex[i][0].pos = D3DXVECTOR3((float) 20.0f,(float)185.0f + FontScale * i + (FontClearance),0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)130.0f,(float)185.0f + FontScale * i + (FontClearance),0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float) 20.0f,(float)185.0f + FontScale * i + (FontClearance) + FontScale,0.0f);
		m_aVertex[i][3].pos = D3DXVECTOR3((float)130.0f,(float)185.0f + FontScale * i + (FontClearance) + FontScale,0.0f);

		//パースペクティブ設定?
		m_aVertex[i][0].rhw = 1.0f;
		m_aVertex[i][1].rhw = 1.0f;
		m_aVertex[i][2].rhw = 1.0f;
		m_aVertex[i][3].rhw = 1.0f;

		//頂点カラーの設定
		m_aVertex[i][0].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][1].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][2].col = D3DCOLOR_RGBA(255,255,255,255);
		m_aVertex[i][3].col = D3DCOLOR_RGBA(255,255,255,255);

		//ポリゴンとテクスチャの頂点を対応させる
		m_aVertex[i][0].tex = D3DXVECTOR2(0.0f,0.0f);
		m_aVertex[i][1].tex = D3DXVECTOR2(1.0f,0.0f);
		m_aVertex[i][2].tex = D3DXVECTOR2(0.0f,1.0f);
		m_aVertex[i][3].tex = D3DXVECTOR2(1.0f,1.0f);
	}
}