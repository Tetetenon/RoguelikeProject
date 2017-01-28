#include "ItemDescriptionFrame.h"
#include "define.h"
#include "TextureManager.h"
#include "ItemWindow.h"
#include "ItemWindowCursor.h"
#include "Graphics.h"



//ウインドウサイズ
#define WINDOW_WIDHT  300
#define WINDOW_HEIGHT  30

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CItemDescriptionFrame::CItemDescriptionFrame(void)
{
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CItemDescriptionFrame::~CItemDescriptionFrame(void)
{
}
//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void CItemDescriptionFrame::Init(void)
{
	//テクスチャ番号の設定
	m_nTextureID = TEXTURE_WINDOW;
	//ポリゴン情報の設定
	SetVertex();
	//フォント情報の設定
	SetFontPos();
	//文字の格納
	FontDataSet();
}
//---------------------------------------------------------------------------------------
//ポリゴン情報の設定を行う
//---------------------------------------------------------------------------------------
void CItemDescriptionFrame::SetVertex(void)
{	
	//位置情報設定
	m_aVertex[0].pos = D3DXVECTOR3((float)WINDOW_WIDHT	,(float)WINDOW_HEIGHT * (ITEM_NUM_MAX + 1)					,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3((float)SCREEN_WIDTH	,(float)WINDOW_HEIGHT * (ITEM_NUM_MAX + 1)					,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3((float)WINDOW_WIDHT	,(float)WINDOW_HEIGHT * (ITEM_NUM_MAX + 1) + WINDOW_HEIGHT	,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3((float)SCREEN_WIDTH	,(float)WINDOW_HEIGHT * (ITEM_NUM_MAX + 1) + WINDOW_HEIGHT	,0.0f);

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
//フォント情報の設定
//---------------------------------------------------------------------------------------
void CItemDescriptionFrame::SetFontPos()
{
	
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//情報格納用フォントを設定
	//フォントへのポインタを初期化
	m_Font = NULL;

	//フォントの設定
	D3DXCreateFont(pDevice, 18, 18, 1, 0, FALSE, SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL,&m_Font);
	
	m_FontPosition.top		= (LONG)(WINDOW_HEIGHT * (ITEM_NUM_MAX + 1) + 6.0f);
	m_FontPosition.bottom	= (LONG)(WINDOW_HEIGHT * (ITEM_NUM_MAX + 1) + WINDOW_HEIGHT);
	m_FontPosition.left		= (LONG)(WINDOW_WIDHT + 30.0f);
	m_FontPosition.right	= (LONG)SCREEN_WIDTH;
}

//---------------------------------------------------------------------------------------
//フォント情報の設定
//---------------------------------------------------------------------------------------
void CItemDescriptionFrame::Draw(int ItemNumber)
{

	//描画するテキストが0の場合処理を飛ばす
	if(ItemNumber == 0)
		return;

	//ウィンドウの描画
	C2DTexture::Draw();

	//テキストの描画
	m_Font->DrawText(NULL,m_Description[ItemNumber],-1,&m_FontPosition,DT_LEFT,D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0xff));
}

//---------------------------------------------------------------------------------------
//フォントデータの設定
//---------------------------------------------------------------------------------------
void CItemDescriptionFrame::FontDataSet(void)
{
	//入れ物の初期化
	::SecureZeroMemory(m_Description, sizeof(_TCHAR) * DESCRIPTION_FONT_MAX * ITEM_MAX);

	//全てのアイテム説明文フォントの設定
	for (int i = ITEM_APPLE; i < ITEM_MAX;i++)
	{
		#if RIKU_TAKAHASHI
		#error 高橋が変えた場所
		#endif //  RIK_T

		switch(i)
		{
		case ITEM_APPLE:
				lstrcpyn(m_Description[i],_T("おいしい。"),sizeof(_TCHAR) * DESCRIPTION_FONT_MAX / 2);
			break;
		case ITEM_HERB:
				lstrcpyn(m_Description[i],_T("体力を回復する"),sizeof(_TCHAR) * DESCRIPTION_FONT_MAX / 2);
			break;
		case ITEM_SWORD:
				lstrcpyn(m_Description[i],_T("装備すると攻撃が上がる"),sizeof(_TCHAR) * DESCRIPTION_FONT_MAX / 2);
			break;
		case ITEM_SHIELD:
				lstrcpyn(m_Description[i],_T("装備すると防御が上がる"),sizeof(_TCHAR) * DESCRIPTION_FONT_MAX / 2);
			break;
		}
	}
}