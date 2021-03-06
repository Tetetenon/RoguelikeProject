#include "EquipmentCommandWindow.h"
#include "Graphics.h"
#include "Input.h"
#include "Turn.h"
#include "EquipmentWindow.h"
#include "TextureManager.h"
#include "Player.h"
#include "ItemWindow.h"
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
CEquipmentCommandWindow* CEquipmentCommandWindow::m_pEquipmentCommandWindow = NULL;
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CEquipmentCommandWindow::CEquipmentCommandWindow(void)
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

	//ボタン入力経過時間を初期化
	m_EnterInterval = 0;
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CEquipmentCommandWindow::~CEquipmentCommandWindow(void)
{
}

//---------------------------------------------------------------------------------------
//実体の作成
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::Create()
{
	//中身がなければ作成
	if (!m_pEquipmentCommandWindow)
	{
		m_pEquipmentCommandWindow = new CEquipmentCommandWindow;
	}
}
//---------------------------------------------------------------------------------------
//実体の削除
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::Delete()
{
	//中身があれば削除
	if (m_pEquipmentCommandWindow)
	{
		delete m_pEquipmentCommandWindow;
		m_pEquipmentCommandWindow = NULL;
	}
}
//---------------------------------------------------------------------------------------
//実体のポインタを渡す
//---------------------------------------------------------------------------------------
CEquipmentCommandWindow* CEquipmentCommandWindow::GetPointer()
{
	//念のため作成関数を呼ぶ
	Create();
	return m_pEquipmentCommandWindow;
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::UpDate()
{
	m_EnterInterval ++;

	//Lで決定
	if((CInput::GetKeyTrigger(DIK_L) || CInput::GetJoyTrigger(0,3)) && m_EnterInterval > 30)
	{
		//自身のフラグを倒す
		DrawFlgChange();
		//アイテムウィンドウのフラグを倒す
		m_pItemWindow->DrawFlgChange(false);
		//メニューウィンドウの描画フラグを倒す
		m_pMenuWindow->ChangDrawFlg();
		m_EnterInterval = 0;
	}

	//Kで戻る
	if((CInput::GetKeyTrigger(DIK_K) || CInput::GetJoyTrigger(0,2)) && m_EnterInterval > 30)
	{
		//自身のフラグを倒す
		DrawFlgChange();
		//アイテムウィンドウのフラグを倒す
		m_pItemWindow->DrawFlgChange(false);
		m_EnterInterval = 0;
	}
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::Draw()
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
	for(int i = 0;i < EQUIPMENT_COMMAND_MAX;i++)
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
void CEquipmentCommandWindow::SetVertex()
{
	for(int i = 0;i < EQUIPMENT_COMMAND_MAX;i++)
	{
		//位置情報設定
		m_aVertex[i][0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT	, (float)WINDOW_HEIGHT * (i + 1)				+ WINDOW_HEIGHT, 0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT				, (float)WINDOW_HEIGHT * (i + 1)				+ WINDOW_HEIGHT, 0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT	, (float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT+ WINDOW_HEIGHT, 0.0f);
		m_aVertex[i][3].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT				,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	+ WINDOW_HEIGHT,0.0f);

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
void CEquipmentCommandWindow::SetFontPos()
{
	for(int i = 0;i < EQUIPMENT_COMMAND_MAX;i++)
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
void CEquipmentCommandWindow::DrawFlgChange()
{
	m_bDrawFlg = !m_bDrawFlg;
}
//---------------------------------------------------------------------------------------
//コマンド名の設定
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::SetCommand()
{
	lstrcpyn(m_CommandName[0],_T("戻す")	,sizeof(LPCTSTR) * FONT_MAX / 2);
}

//---------------------------------------------------------------------------------------
//コマンド名の設定
//---------------------------------------------------------------------------------------
void CEquipmentCommandWindow::SetPointer()
{
	//ポインタの取得
	m_pEquipmentWindow = CEquipmentWindow::GetPointer();
	m_pMenuWindow = CMenuWindow::GetPointer();
	m_pItemWindow = CItemWindow::GetPointer();
}
