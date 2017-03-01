#include "MessageWindow.h"
#include "Graphics.h"
#include "define.h"

#include "TextureManager.h"

#include<fstream>
#include<iostream>
#include<string>
#include<sstream>

#define DRAW_TIME_MAX	300							//何も操作しなかった場合のウィンドウ最大描画時間

//ウインドウサイズ
#define WINDOW_WIDHT 400
#define WINDOW_HEIGHT 30


//---------------------------------------------------------------------------------------
//静的メンバ実体定義
//---------------------------------------------------------------------------------------
CMessageWindow*	CMessageWindow::m_pMessageWindow;
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CMessageWindow::CMessageWindow(void)
{
	//メンバ初期化
	m_bDrawflg = false;
	m_fDrawTime = 0;

	//グラフィックデバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//情報格納用フォントを設定
	//フォントへのポインタを初期化
	m_pFont = NULL;

	D3DXCreateFont(pDevice, 18, 12, 10, 0, FALSE, SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL,&m_pFont);

	//文字列先頭初期化
	for(int i = 0;i < DRAW_NUM;i++)
	{
		for(int j = 0;j < FONT_NUM;j++)
			m_Message[i][j] = 0;
	}
	//ポリゴン情報の設定
	SetVertex();
	//フォント表示位置の設定
	SetFontPos();
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CMessageWindow::~CMessageWindow(void)
{
}

//---------------------------------------------------------------------------------------
//実体の作成
//---------------------------------------------------------------------------------------
void CMessageWindow::Create()
{
	//中身が無かったら作成
	if (!m_pMessageWindow)
	{
		m_pMessageWindow = new CMessageWindow;
	}
}
//---------------------------------------------------------------------------------------
//実体の削除
//---------------------------------------------------------------------------------------
void CMessageWindow::Delete()
{
	//中身があったら作成
	if (m_pMessageWindow)
	{
		delete m_pMessageWindow;
		m_pMessageWindow = NULL;
	}
}
//---------------------------------------------------------------------------------------
//実体のポインタを渡す
//---------------------------------------------------------------------------------------
CMessageWindow* CMessageWindow::GetPointer()
{
	//念のため作成関数を呼ぶ
	Create();
	return m_pMessageWindow;
}

//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CMessageWindow::Update()
{
	//描画フラグが立っている場合、描画時間を減少させる
	if(m_bDrawflg)
	{
		//描画時間減少
		m_fDrawTime--;

		//もし描画時間が0以下ならば、描画フラグを倒し、今後描画しないように設定する
		if(m_fDrawTime <= 0)
		{
			m_bDrawflg = false;
		}
	}

}


//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CMessageWindow::Draw()
{
	//描画フラグが立っている時のみ描画を行う
	if(m_bDrawflg)
	{
		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
		
		// アルファ・ブレンディングを行う
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		// 透過処理を行う
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//頂点フォーマットの設定
		pDevice ->SetFVF(FVF_VERTEX_2D);
		//描画フラグが立っている場合描画
		if(m_bDrawflg)
		{
			for(int i = 0;i < DRAW_NUM;i++)
			{
				//中身がなければ描画しない
				if(m_Message[i][0] == NULL)
					continue;
				//テクスチャセット
				pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_WINDOW_ALPHA));

				//ポリゴンの描画
				//頂点情報を外部が持っている場合Up
				//そのほかはprimitive
				pDevice -> DrawPrimitiveUP(
					D3DPT_TRIANGLESTRIP,          //プリミティブの種類List（三角形描く）Strip(つなげて作る)
					NUM_POLYGON,                 //ポリゴン数
					m_aVertex[i],				 //配列の先頭アドレス
					sizeof(VERTEX_2D)            //データの大きさ
					);
				// テキスト描画
				m_pFont->DrawText(NULL,m_Message[i],-1, &m_DrawFontPos[i], DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0xff));
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//ポリゴン頂点情報をセットする
//---------------------------------------------------------------------------------------
void CMessageWindow::SetVertex()
{
	for(int i = 0;i < DRAW_NUM;i++)
	{
		//位置情報設定
		m_aVertex[i][0].pos = D3DXVECTOR3((float)-10.0f					,(float)SCREEN_HEIGHT - WINDOW_HEIGHT * (i + 1)					,0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)-10.0f + WINDOW_WIDHT	,(float)SCREEN_HEIGHT - WINDOW_HEIGHT * (i + 1)					,0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float)-10.0f					,(float)SCREEN_HEIGHT - WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	,0.0f);
		m_aVertex[i][3].pos = D3DXVECTOR3((float)-10.0f + WINDOW_WIDHT	,(float)SCREEN_HEIGHT - WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	,0.0f);

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
//フォント描画位置を設定する
void CMessageWindow::SetFontPos ()
{
	for(int i = 0;i < DRAW_NUM;i++)
	{
		m_DrawFontPos[i].left	= (LONG)m_aVertex[i][0].pos.x + (LONG)50.0f;
		m_DrawFontPos[i].top	= (LONG)m_aVertex[i][1].pos.y + (LONG)10.0f;
		m_DrawFontPos[i].right	= (LONG)m_aVertex[i][3].pos.x;
		m_DrawFontPos[i].bottom	= (LONG)m_aVertex[i][2].pos.y;
	}
}

//---------------------------------------------------------------------------------------
//描画する文字列をセットする
//---------------------------------------------------------------------------------------
void CMessageWindow::SetMassege(_TCHAR String[], ...)
{
	const int MAX_SIZE = 512;

	va_list vList;
	va_start(vList,String);
	char str[MAX_SIZE];
	vsprintf_s(str,sizeof(str), String, vList);
	va_end(vList);

	for (int i = 4;i;--i)
	{
		lstrcpyn(m_Message[i],m_Message[i-1],sizeof(_TCHAR) * FONT_NUM);
	}

	lstrcpyn(m_Message[0],str,sizeof(_TCHAR)*FONT_NUM);
	m_bDrawflg = true;
	m_fDrawTime = DRAW_TIME_MAX;
}
//---------------------------------------------------------------------------------------
//フォントのデータを初期化する
//---------------------------------------------------------------------------------------
void CMessageWindow::InitFontData()
{
	//文字列先頭初期化
	for(int i = 0;i < DRAW_NUM;i++)
	{
		for(int j = 0;j < FONT_NUM;j++)
			m_Message[i][j] = 0;
	}
}