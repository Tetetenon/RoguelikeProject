#include "ItemCommandWindow.h"
#include "Graphics.h"
#include "Input.h"
#include "Turn.h"
#include "ItemWindow.h"
#include "TextureManager.h"
#include "Player.h"
#include "MenuWindow.h"

//---------------------------------------------------------------------------------------
//マクロ定義
//---------------------------------------------------------------------------------------

//ウインドウサイズ
#define WINDOW_WIDHT 200
#define WINDOW_HEIGHT 30


//---------------------------------------------------------------------------------------
//静的メンバ定義
//---------------------------------------------------------------------------------------
_TCHAR				CCommandWindow::m_CommandName[COMMAND_MAX][FONT_MAX];			//コマンド名
LPD3DXFONT			CCommandWindow::m_Font;											//描画用フォント
RECT				CCommandWindow::m_Pos[COMMAND_MAX];								//ウィンドウ表示位置

bool				CCommandWindow::m_bDrawFlg;										//描画フラグ

VERTEX_2D			CCommandWindow::m_aVertex[COMMAND_MAX][NUM_VERTEX];				//ポリゴン頂点情報格納用
CTurn				CCommandWindow::m_Turn;											//ステート変更
CInventory			CCommandWindow::m_Inbentory;
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CCommandWindow::CCommandWindow(void)
{
	//メンバ初期化
	m_bDrawFlg = false;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//情報格納用フォントを設定
	//フォントへのポインタを初期化
	m_Font = NULL;

	//フォントを設定
	D3DXCreateFont(pDevice, 12, 12, 1, 0, FALSE, SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL,&m_Font);


	//ポリゴン情報の設定
	SetVertex();

	//フォント表示位置の設定
	SetFontPos();

	//コマンド名の設定
	SetCommand();
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CCommandWindow::~CCommandWindow(void)
{
}

//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void CCommandWindow::Init()
{
	m_EnterInterval = 0;
}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CCommandWindow::Fin()
{

}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CCommandWindow::UpDate()
{
	//使用法を選択している場合のみ更新
	if(m_bDrawFlg)
	{
		m_EnterInterval ++;

		//Lで決定
		if(CInput::GetKeyTrigger(DIK_L) && m_EnterInterval > 30)
		{
			//入力待ちステートのユニット数-1
			CTurn::SumCount(CPlayer::GetState());

			//アイテムを使用
			CPlayer::SetState(GAME_STATE_ITEM_USE);

			//アイテム使用ステートに存在するユニットの数+1
			CTurn::AddCount(CPlayer::GetState());
			
			//自身のフラグを倒す
			DrawFlgChange();

			//アイテムウインドウの描画フラグを倒す
			CInventory::DrawFlgChange();
			//メニューウィンドウの描画フラグを倒す
			CMenuWindow::ChangDrawFlg();
			m_EnterInterval = 0;
		}

		//Kで戻る
		if(CInput::GetKeyTrigger(DIK_K) && m_EnterInterval > 30)
		{
			//自身のフラグを倒す
			DrawFlgChange();
			m_EnterInterval = 0;
		}
	}
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CCommandWindow::Draw()
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
	for(int i = 0;i < COMMAND_MAX;i++)
	{
		//テクスチャセット
		pDevice ->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_WINDOW));
		//ポリゴンの描画
		//頂点情報を外部が持っている場合Up
		//そのほかはprimitive
		pDevice -> DrawPrimitiveUP(
			D3DPT_TRIANGLESTRIP,          //プリミティブの種類List（三角形描く）Strip(つなげて作る)
			NUM_POLYGON,                 //ポリゴン数
			m_aVertex[i],            //配列の先頭アドレス
			sizeof(VERTEX_2D)            //データの大きさ
			);
		// テキスト描画
		m_Font->DrawText(NULL,m_CommandName[i],-1, &m_Pos[i], DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0xff));
	}

}
//---------------------------------------------------------------------------------------
//ポリゴン情報を埋める
//---------------------------------------------------------------------------------------
void CCommandWindow::SetVertex()
{
	for(int i = 0;i < COMMAND_MAX;i++)
	{
		//位置情報設定
		m_aVertex[i][0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (i + 1)					,0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (i + 1)					,0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	,0.0f);
		m_aVertex[i][3].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	,0.0f);

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
//---------------------------------------------------------------------------------------
//フォント情報の設定
//---------------------------------------------------------------------------------------
void CCommandWindow::SetFontPos()
{
	for(int i = 0;i < COMMAND_MAX;i++)
	{
		m_Pos[i].left	= (LONG)(m_aVertex[i][0].pos.x + 50.0f);
		m_Pos[i].top	= (LONG)(m_aVertex[i][1].pos.y + 10.0f);
		m_Pos[i].right	= (LONG)m_aVertex[i][3].pos.x;
		m_Pos[i].bottom	= (LONG)m_aVertex[i][2].pos.y;
	}
}
//---------------------------------------------------------------------------------------
//描画フラグを外部からON/OFFする
//---------------------------------------------------------------------------------------
void CCommandWindow::DrawFlgChange()
{
	m_bDrawFlg = !m_bDrawFlg;
}
//---------------------------------------------------------------------------------------
//コマンド名の設定
//---------------------------------------------------------------------------------------
void CCommandWindow::SetCommand()
{
	lstrcpyn(m_CommandName[0],_T("使う")	,sizeof(LPCTSTR) * FONT_MAX / 2);
	lstrcpyn(m_CommandName[1],_T("装備")	,sizeof(LPCTSTR) * FONT_MAX / 2);
	lstrcpyn(m_CommandName[2],_T("捨てる")	,sizeof(LPCTSTR) * FONT_MAX / 2);
}