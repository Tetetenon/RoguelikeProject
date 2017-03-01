#include "HPDraw.h"
#include "Graphics.h"
#include "define.h"
#include "TextureManager.h"

#include <stdlib.h>
#include <tchar.h>
#include "TextureManager.h"

#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //文字ストリーム



//HP最大描画サイズ
#define HP_MAX_WIDHT 250
//---------------------------------------------------------------------------------------
//静的メンバ実体定義
//---------------------------------------------------------------------------------------
CHPDraw* CHPDraw::m_pHPDraw = NULL;
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CHPDraw::CHPDraw(void)
{
	//各種メンバ変数の初期化
	m_pFont = NULL;
	m_nHP = 0;
	m_nMaxHP = 0;

	//グラフィックデバイスの取得
	LPDIRECT3DDEVICE9	pDevice = CGraphics::GetDevice();

	//フォントへのポインタを取得する
	D3DXCreateFont(pDevice,24,0,1,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,NULL,&m_pFont);

	//ポリゴン情報の設定
	SetVertex();

	//フォント表示位置の設定
	SetFontPos();
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CHPDraw::~CHPDraw(void)
{

}
//---------------------------------------------------------------------------------------
//実体の作成
//---------------------------------------------------------------------------------------
void CHPDraw::Create()
{
	//中身が存在していない場合作成
	if (!m_pHPDraw)
	{
		m_pHPDraw = new CHPDraw;
	}
}
//---------------------------------------------------------------------------------------
//実体の削除
//---------------------------------------------------------------------------------------
void CHPDraw::Delete()
{
	//中身の確認
	if (m_pHPDraw)
	{
		//中身があれば削除
		delete m_pHPDraw;
		m_pHPDraw = NULL;
	}
}
//---------------------------------------------------------------------------------------
//実体のポインタを渡す
//---------------------------------------------------------------------------------------
CHPDraw* CHPDraw::GetPointer()
{
	//念のため作成
	Create();
	return m_pHPDraw;
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CHPDraw::Update()
{

}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CHPDraw::Draw()
{
	//グラフィックデバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//アルファブレンディングを行う
	pDevice ->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	//透過処理を行う
	pDevice ->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//テクスチャのセット
	pDevice -> SetTexture(0,*CTextureManager::GetTexture(TEXTURE_HP_BAR));

	//ポリゴンの描画
	pDevice ->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,NUM_POLYGON,m_aVertex,sizeof(VERTEX_2D));

	//数値(文字)描画
	m_pFont ->DrawText(NULL,m_States,-1,&m_FontDrawPos,DT_LEFT,D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));

}
//---------------------------------------------------------------------------------------
//ポリゴン情報を設定
//---------------------------------------------------------------------------------------
void CHPDraw::SetVertex()
{
	//位置情報設定
	SetPosition();

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
//文字描画位置を設定
//---------------------------------------------------------------------------------------
void CHPDraw::SetFontPos()
{
	m_FontDrawPos.left		= (LONG)240.0f;
	m_FontDrawPos.top		= (LONG) 15.0f;
	m_FontDrawPos.right		= (LONG)300.0f;
	m_FontDrawPos.bottom	= (LONG) 45.0f;
}
//---------------------------------------------------------------------------------------
//描画するHP数値をセット
//---------------------------------------------------------------------------------------
void CHPDraw::SetHP (int nHP)
{
	sprintf_s(m_States, _T("HP:%d"), nHP);

	m_nHP = nHP;

	SetPosition();
}
//---------------------------------------------------------------------------------------
//描画する最大HP数値をセット
//---------------------------------------------------------------------------------------
void CHPDraw::SetMaxHP (int nMaxHP)
{
	m_nMaxHP = nMaxHP;
}

//---------------------------------------------------------------------------------------
//ポリゴンの位置情報を再設定
//---------------------------------------------------------------------------------------
void CHPDraw::SetPosition()
{
	float nPercentage = ((float)m_nHP / (float)m_nMaxHP);

	//位置情報設定
	m_aVertex[0].pos = D3DXVECTOR3((float)300.0f								,(float)15.0f,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)300.0f + nPercentage * HP_MAX_WIDHT	,(float)15.0f,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)300.0f								,(float)45.0f,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)300.0f + nPercentage * HP_MAX_WIDHT	,(float)45.0f,0.0f);
}