#include "EquipmentWindow.h"
#include "Graphics.h"
#include "Input.h"
#include <tchar.h>
#include "EquipmentCommandWindow.h"
#include "EquipmentWindowCursor.h"
#include "Turn.h"
#include "TextureManager.h"
#include "MenuWindow.h"
#include"Unit.h"
#include "UnitManager.h"
#include "ItemWindow.h"
//---------------------------------------------------------------------------------------
//マクロ定義
//---------------------------------------------------------------------------------------
//ウインドウサイズ
#define WINDOW_WIDHT 300
#define WINDOW_HEIGHT 30

//---------------------------------------------------------------------------------------
//静的メンバ定義
//---------------------------------------------------------------------------------------
CEquipmentWindow* CEquipmentWindow::m_pEquipmentWindow = NULL;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CEquipmentWindow::CEquipmentWindow(void)
{
	//メンバ初期化
	m_bDrawFlg = false;
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
CEquipmentWindow::~CEquipmentWindow(void)
{
	m_nInterval = 0;
}

//---------------------------------------------------------------------------------------
//実体の生成
//---------------------------------------------------------------------------------------
void CEquipmentWindow::Create()
{
	//実体がなければ作成
	if (!m_pEquipmentWindow)
	{
		m_pEquipmentWindow = new CEquipmentWindow;
	}
}
//---------------------------------------------------------------------------------------
//実体の削除
//---------------------------------------------------------------------------------------
void CEquipmentWindow::Delete()
{
	//実体があれば削除
	if (m_pEquipmentWindow)
	{
		delete m_pEquipmentWindow;
		m_pEquipmentWindow = NULL;
	}
}
//---------------------------------------------------------------------------------------
//実体のポインタを渡す
//---------------------------------------------------------------------------------------
CEquipmentWindow* CEquipmentWindow::GetPointer()
{
	//念のため作成関数を呼ぶ
	Create();
	return m_pEquipmentWindow;
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CEquipmentWindow::UpDate()
{

	m_nInterval++;

	if (m_nInterval < ButtonIntervalTime)
		return;

	//Lで決定
	if((CInput::GetKeyTrigger(DIK_L) || CInput::GetJoyTrigger(0,3)))
	{
		CItem Equipment = m_pPlayerEquipment->GetItem(m_pInventoryCursor->GetItemNum());
		//選択したアイテムウインドウにアイテムが存在しているか確認する
		//IDが0以外ならば続ける
		if (Equipment.GetID() == 0)
			return;
		//コマンドウインドウ描画フラグを立てる
		m_pCommandWindow->DrawFlgChange();
		m_nInterval = 0;
	}

	//KとIキーで戻る
	if(CInput::GetKeyTrigger(DIK_K) || CInput::GetJoyTrigger(0,2) || !m_pMenuWindow->GetDrawFlg())
	{
		//アイテムウィンドウのフラグを倒す
		m_pItemWindow->DrawFlgChange(false);
		m_nInterval = 0;
	}
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CEquipmentWindow::Draw()
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
	for(int i = 0;i < EQUIPMENT_NUM_MAX;i++)
	{
		CItem Equipment = m_pPlayerEquipment->GetItem(i);
		ItemName = Equipment.GetName();
		ItemID	= Equipment.GetID();

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

}
//---------------------------------------------------------------------------------------
//ポリゴン情報を埋める
//---------------------------------------------------------------------------------------
void CEquipmentWindow::SetVertex()
{
	for(int i = 0;i < EQUIPMENT_NUM_MAX;i++)
	{
		//位置情報設定
		m_aVertex[i][0].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT	,(float)WINDOW_HEIGHT * (i + 1)					+ WINDOW_HEIGHT,0.0f);
		m_aVertex[i][1].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT				,(float)WINDOW_HEIGHT * (i + 1)					+ WINDOW_HEIGHT,0.0f);
		m_aVertex[i][2].pos = D3DXVECTOR3((float)SCREEN_WIDTH - WINDOW_WIDHT - WINDOW_WIDHT	,(float)WINDOW_HEIGHT * (i + 1) + WINDOW_HEIGHT	+ WINDOW_HEIGHT,0.0f);
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
void CEquipmentWindow::SetFontPos()
{
	for(int i = 0;i < EQUIPMENT_NUM_MAX;i++)
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
void CEquipmentWindow::SetPointer()
{
	//プレイヤーの装備アイテムポインタを取得する
	CUnitManager* pUnitManager = CUnitManager::GetPointer();
	CUnit* pPlayer = pUnitManager->GetPlayerPointer();
	m_pPlayerEquipment = pPlayer->GetEquipment();

	//ポインタの取得
	m_pCommandWindow = CEquipmentCommandWindow::GetPointer();
	m_pInventoryCursor = CEquipmentWindowCursor::GetPointer();
	m_pMenuWindow = CMenuWindow::GetPointer();
	m_pItemWindow = CItemWindow::GetPointer();
}

//---------------------------------------------------------------------------------------
//描画フラグを外部からON/OFFする
//---------------------------------------------------------------------------------------
void CEquipmentWindow::DrawFlgChange()
{
	m_bDrawFlg = !m_bDrawFlg;
}