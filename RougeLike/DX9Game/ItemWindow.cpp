#include "ItemWindow.h"
#include "Graphics.h"
#include "Input.h"
#include"Unit.h"
#include "UnitManager.h"
#include <tchar.h>
#include "ItemCommandWindow.h"
#include "ItemWindowCursor.h"
#include "Turn.h"
#include "TextureManager.h"
#include "ItemDescriptionFrame.h"
//---------------------------------------------------------------------------------------
//マクロ定義
//---------------------------------------------------------------------------------------

//ウインドウサイズ
#define WINDOW_WIDHT 300
#define WINDOW_HEIGHT 30

//---------------------------------------------------------------------------------------
//静的メンバ定義
//---------------------------------------------------------------------------------------
CItemWindow* CItemWindow::m_pItemWindow = NULL;
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CItemWindow::CItemWindow(void)
{
	//メンバ初期化
	m_bDrawFlg = false;
	m_bUpdateFlg = true;
	m_nInterval = 0;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//情報格納用フォントを設定
	//フォントへのポインタを初期化
	m_Font = NULL;

	//フォントの設定
	D3DXCreateFont(pDevice, 12, 12, 1, 0, FALSE, SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL,&m_Font);

	//ポリゴン情報の設定
	SetVertex();

	//フォント表示位置の設定
	SetFontPos();
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CItemWindow::~CItemWindow(void)
{
	//入力経過時間を初期化
	m_nInterval = 0;
}

//---------------------------------------------------------------------------------------
//実体の作成
//---------------------------------------------------------------------------------------
void CItemWindow::Create()
{
	//実体がなければ作成
	if (!m_pItemWindow)
	{
		m_pItemWindow = new CItemWindow;
	}
}
//---------------------------------------------------------------------------------------
//実体の削除
//---------------------------------------------------------------------------------------
void CItemWindow::Delete()
{
	//実体があれば削除
	if (m_pItemWindow)
	{
		delete m_pItemWindow;
		m_pItemWindow = NULL;
	}
}
//---------------------------------------------------------------------------------------
//実体のポインタを渡す
//---------------------------------------------------------------------------------------
CItemWindow* CItemWindow::GetPointer()
{
	//念のため作成関数を呼ぶ
	Create();
	return m_pItemWindow;
}

//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CItemWindow::UpDate()
{
	m_nInterval++;

	if (m_nInterval < ButtonIntervalTime)
		return;

	//Lで決定
	//選択したアイテムウインドウにアイテムが存在しているか確認する
	if((CInput::GetKeyTrigger(DIK_L) || CInput::GetJoyTrigger(0, 3)))
	{
		CItem pItemData = m_pPlayerInventory->GetItem(m_pIItemWindowCursor->GetItemNum());
		if (pItemData.GetID() == 0)
			return;
		//コマンドウインドウ描画フラグを立てる
		m_pCommandWindow->DrawFlgChange();

		m_nInterval = 0;
	}

	//KとIキーで戻る
	if(CInput::GetKeyTrigger(DIK_K) || CInput::GetJoyTrigger(0, 2))
	{
		//自身のフラグを倒す
		DrawFlgChange(false);

		m_nInterval = 0;
	}
	
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CItemWindow::Draw()
{
	_TCHAR* ItemName;		//描画用に文字を格納する
	int		ItemID;			//描画の可否をIDで判別する

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	
	// アルファ・ブレンディングを行う
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 透過処理を行う
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//頂点フォーマットの設定
	pDevice ->SetFVF(FVF_VERTEX_2D);

	//アイテムウインドウ分描画
	for(int i = 0;i < ITEM_NUM_MAX;i++)
	{
		CItem ItemData = m_pPlayerInventory->GetItem(i);
		ItemName = ItemData.GetName();
		ItemID	= ItemData.GetID();

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

		//中身がなければ描画しない
		if(ItemName == NULL || ItemID == 0)
			continue;

		// テキスト描画
		m_Font->DrawText(NULL,ItemName,-1, &m_Pos[i], DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0xff));
	}

	//アイテム説明文の描画
	CItem ItemData = m_pPlayerInventory->GetItem(m_pIItemWindowCursor->GetItemNum());
	m_pDescription->Draw(ItemData.GetID());

}
//---------------------------------------------------------------------------------------
//ポリゴン情報を埋める
//---------------------------------------------------------------------------------------
void CItemWindow::SetVertex()
{
	for(int i = 0;i < ITEM_NUM_MAX;i++)
	{
		//位置情報設定
		m_aVertex[i][0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (i + 1)					 + WINDOW_HEIGHT,0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (i + 1)					 + WINDOW_HEIGHT,0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	 + WINDOW_HEIGHT,0.0f);
		m_aVertex[i][3].pos = D3DXVECTOR3((float)SCREEN_WIDTH				,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	 + WINDOW_HEIGHT,0.0f);

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
void CItemWindow::SetFontPos()
{
	for(int i = 0;i < ITEM_NUM_MAX;i++)
	{
		m_Pos[i].left	= (LONG)(m_aVertex[i][0].pos.x + 50.0f);
		m_Pos[i].top	= (LONG)(m_aVertex[i][1].pos.y + 10.0f);
		m_Pos[i].right	= (LONG)m_aVertex[i][3].pos.x;
		m_Pos[i].bottom	= (LONG)m_aVertex[i][2].pos.y;
	}
}

//---------------------------------------------------------------------------------------
//メンバ変数のポインタを設定する
//---------------------------------------------------------------------------------------
void CItemWindow::SetPoiner()
{
	//プレイヤーへの持ち物へのポインタを取得する
	CUnitManager*	pUnitManager = CUnitManager::GetPointer();
	CUnit*			pPlayer = pUnitManager->GetPlayerPointer();
	m_pPlayerInventory = pPlayer->GetInventory();
	//ポインタの取得
	m_pCommandWindow = CItemCommandWindow::GetPointer();
	m_pDescription = CItemDescriptionFrame::GetPointer();
	m_pIItemWindowCursor = CItemWindowCursor::GetPointer();
}

//---------------------------------------------------------------------------------------
//描画フラグを外部からON/OFFする
//---------------------------------------------------------------------------------------
void CItemWindow::DrawFlgChange(bool ChangeFlg)
{
	m_bDrawFlg = ChangeFlg;
}

//---------------------------------------------------------------------------------------
//更新フラグを外部からON/OFFする
//---------------------------------------------------------------------------------------
void CItemWindow::UpdateFlgChange(bool ChangeFlg)
{
	m_bUpdateFlg = ChangeFlg;
}
