#include "ItemWindow.h"
#include "Graphics.h"
#include "Input.h"
#include <tchar.h>
#include "ItemCommandWindow.h"
#include "ItemWindowCursor.h"
#include "Turn.h"
#include "TextureManager.h"
//---------------------------------------------------------------------------------------
//マクロ定義
//---------------------------------------------------------------------------------------

//ウインドウサイズ
#define WINDOW_WIDHT 300
#define WINDOW_HEIGHT 30

//---------------------------------------------------------------------------------------
//静的メンバ定義
//---------------------------------------------------------------------------------------
bool					CInventory::m_bDrawFlg;				//描画フラグ
CCommandWindow			CInventory::m_CommandWindow;		//コマンドウインドウの描画フラグ変更用
CInventoryCursor		CInventory::m_InventoryCursor;		//選択しているアイテムウインドウの取得
CItemDescriptionFrame	CInventory::m_Description;			//アイテム説明文
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CInventory::CInventory(void)
{
	//メンバ初期化
	m_bDrawFlg = false;

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
CInventory::~CInventory(void)
{
}

//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void CInventory::Init()
{
	//説明文の初期化
	m_Description.Init();
}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CInventory::Fin()
{

}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CInventory::UpDate()
{
	//アイテム選択中のみ操作可能
	if(m_bDrawFlg && !CCommandWindow::GetDrawFlg())
	{
		//Lで決定
		//選択したアイテムウインドウにアイテムが存在しているか確認する
		if((CInput::GetKeyTrigger(DIK_L) || CInput::GetJoyTrigger(0, 3)) && m_Item[m_InventoryCursor.GetItemNum()].GetID())
		{
			//コマンドウインドウ描画フラグを立てる
			m_CommandWindow.DrawFlgChange();
		}

		//KとIキーで戻る
		if(CInput::GetKeyTrigger(DIK_K) || CInput::GetJoyTrigger(0, 2))
		{
			//自身のフラグを倒す
			DrawFlgChange();
		}
	}
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CInventory::Draw()
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
			ItemName = m_Item[i].GetName();
			ItemID	= m_Item[i].GetID();

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
		m_Description.Draw(m_Item[CInventoryCursor::GetItemNum()].GetID());

}
//---------------------------------------------------------------------------------------
//ポリゴン情報を埋める
//---------------------------------------------------------------------------------------
void CInventory::SetVertex()
{
	for(int i = 0;i < ITEM_NUM_MAX;i++)
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
void CInventory::SetFontPos()
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
//ストレージにアイテムをセット
//---------------------------------------------------------------------------------------
bool CInventory::SetItem(CItem Item)
{
	for(int i = 0;i < ITEM_NUM_MAX;i++)
	{
		//ストレージが空白の部分を探す
		if(m_Item[i].GetID() == 0)
		{
			//アイテムデータをコピー
			m_Item[i] = Item;


			//効能の設定がされていなければ、自動的に設定する
			if(Item.GetValue() == 0)
			{
				//効能を設定
				m_Item[i].SetValue(rand()%10 + 5);
			}
			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------------------
//描画フラグを外部からON/OFFする
//---------------------------------------------------------------------------------------
void CInventory::DrawFlgChange()
{
	m_bDrawFlg = !m_bDrawFlg;
}

//---------------------------------------------------------------------------------------
//指定されたアイテムを消去
//---------------------------------------------------------------------------------------
void CInventory::DelInventory(int Receipt)
{
	//中身を初期化し、消去
	//IDの初期化
	m_Item[Receipt].SetID(0);

	//名前の初期化
	m_Item[Receipt].SetName(_T("0"));

}
//---------------------------------------------------------------------------------------
//指定されたアイテムの効果ジャンルを返却する
//---------------------------------------------------------------------------------------
int CInventory::GetEffect(int Receipt)
{
	return m_Item[Receipt].GetType();
}
//---------------------------------------------------------------------------------------
//指定されたアイテムの効能?を返却する
//---------------------------------------------------------------------------------------
int CInventory::GetEffectValue(int Receipt)
{
	//アイテムのIDによって効果を変更する
	switch(m_Item[Receipt].GetID())
	{
		//林檎
	case ITEM_APPLE:
		//特に効果なし
		return EFFECT_NON;
		break;
		//薬草
	case ITEM_HERB:
		//体力の回復
		return m_Item[Receipt].GetValue();
		break;
		//剣
	case ITEM_SWORD:
		//攻撃力アップ
		return m_Item[Receipt].GetValue();
		break;
		//盾
	case ITEM_SHIELD:
		//防御力アップ
		return m_Item[Receipt].GetValue();
		break;

		//バグ検査用
	default:
		//効果なし
		return EFFECT_NON;
		break;
	}
}