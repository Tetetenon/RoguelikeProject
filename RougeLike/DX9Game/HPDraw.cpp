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
#define HP_MAX_WIDHT 210
//---------------------------------------------------------------------------------------
//静的メンバ実体定義
//---------------------------------------------------------------------------------------
LPD3DXFONT			CHPDraw::m_pFont;						//描画フォントの設定
RECT				CHPDraw::m_FontDrawPos;					//フォントの描画位置を設定する

char				CHPDraw::m_States[256];	//ステータス(HP情報)を格納する

VERTEX_2D			CHPDraw::m_aVertex[NUM_VERTEX];			//テクスチャの描画位置

int				CHPDraw::m_nHP;								//描画するユニットの現在の体力
int				CHPDraw::m_nMaxHP;							//描画するユニットの最大HP


//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CHPDraw::CHPDraw(void)
{
	//各種メンバ変数の初期化
	m_pFont = NULL;

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
//初期化
//---------------------------------------------------------------------------------------
void CHPDraw::Init()
{

}

//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CHPDraw::Fin()
{

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
	m_aVertex[0].pos = D3DXVECTOR3((float)20.0f					,(float) 165.0f,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)20.0f + HP_MAX_WIDHT	,(float) 165.0f,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)20.0f					,(float) 185.0f,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)20.0f + HP_MAX_WIDHT	,(float) 185.0f,0.0f);

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
	m_FontDrawPos.left		= (LONG)125.0f;
	m_FontDrawPos.top		= (LONG)130.0f;
	m_FontDrawPos.right		= (LONG)230.0f;
	m_FontDrawPos.bottom	= (LONG)150.0f;
}
//---------------------------------------------------------------------------------------
//描画するHP数値をセット
//---------------------------------------------------------------------------------------
void CHPDraw::SetHP (int nHP)
{
	//値を文字列として格納
	//_itot_s(nHP,m_States,sizeof(_TCHAR) * mAX_STATES_DIGIT - 1,10);
	
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
	m_aVertex[0].pos = D3DXVECTOR3((float)20.0f								,(float)165.0f,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)20.0f + nPercentage * HP_MAX_WIDHT,(float)165.0f,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)20.0f								,(float)185.0f,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)20.0f + nPercentage * HP_MAX_WIDHT,(float)185.0f,0.0f);
}