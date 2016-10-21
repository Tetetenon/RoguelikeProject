#include "EquipmentWindow.h"
#include "Graphics.h"
#include "Input.h"
#include <tchar.h>
#include "EquipmentCommandWindow.h"
#include "EquipmentWindowCursor.h"
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
bool							CEquipmentInventory::m_bDrawFlg;								//描画フラグ
CEquipmentCommandWindow			CEquipmentInventory::m_CommandWindow;		//コマンドウインドウの描画フラグ変更用
CEquipmentInventoryCursor		CEquipmentInventory::m_InventoryCursor;		//選択しているアイテムウインドウの取得
//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CEquipmentInventory::CEquipmentInventory(void)
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
CEquipmentInventory::~CEquipmentInventory(void)
{
}

//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void CEquipmentInventory::Init()
{
}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CEquipmentInventory::Fin()
{

}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CEquipmentInventory::UpDate()
{
	//アイテム選択中のみ操作可能
	if(m_bDrawFlg && !CEquipmentCommandWindow::GetDrawFlg())
	{
		//Lで決定
		//選択したアイテムウインドウにアイテムが存在しているか確認する
		if(CInput::GetKeyTrigger(DIK_L) && m_Item[m_InventoryCursor.GetItemNum()].GetID())
		{
			//コマンドウインドウ描画フラグを立てる
			m_CommandWindow.DrawFlgChange();
		}

		//KとIキーで戻る
		if(CInput::GetKeyTrigger(DIK_K))
		{
			//自身のフラグを倒す
			DrawFlgChange();
		}
	}
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CEquipmentInventory::Draw()
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
		for(i = 0;i < EQUIPMENT_NUM_MAX;i++)
		{
			i = i;

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

}
//---------------------------------------------------------------------------------------
//ポリゴン情報を埋める
//---------------------------------------------------------------------------------------
void CEquipmentInventory::SetVertex()
{
	for(int i = 0;i < EQUIPMENT_NUM_MAX;i++)
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
void CEquipmentInventory::SetFontPos()
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
//ストレージにアイテムをセット
//---------------------------------------------------------------------------------------
bool CEquipmentInventory::SetItem(CItem Item)
{
	for(i = 0;i < EQUIPMENT_NUM_MAX;i++)
	{
		//ストレージが空白の部分を探す
		if(m_Item[i].GetID() == 0)
		{
			//アイテムの格納
			m_Item[i] = Item;

			//効能の設定がされていなければ、自動的に設定する
			if(m_Item[i].GetValue() == 0)
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
//IDから名前を検索、名前を格納
//---------------------------------------------------------------------------------------
void CEquipmentInventory::FindName	(int nID,int Receipt)
{
	switch(nID)
	{
	case ITEM_APPLE:
		m_Item[Receipt].SetName(_T("林檎"));
		break;
	case ITEM_HERB:
		m_Item[Receipt].SetName(_T("薬草"));
		break;
	case ITEM_SWORD:
		m_Item[Receipt].SetName(_T("けん"));
		break;
	case ITEM_SHIELD:
		m_Item[Receipt].SetName(_T("たて"));
		break;
	default:
		break;
	}
}

//---------------------------------------------------------------------------------------
//描画フラグを外部からON/OFFする
//---------------------------------------------------------------------------------------
void CEquipmentInventory::DrawFlgChange()
{
	m_bDrawFlg = !m_bDrawFlg;
}

//---------------------------------------------------------------------------------------
//指定されたアイテムを消去
//---------------------------------------------------------------------------------------
void CEquipmentInventory::DelInventory(int Receipt)
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
int CEquipmentInventory::GetEffect(int Receipt)
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
		return EFFECT_RECOVERY;
		break;
		//剣
	case ITEM_SWORD:
		//攻撃力アップ
		return EFFECT_EQUIPMENT_ATTACK;
		break;
		//盾
	case ITEM_SHIELD:
		//防御力アップ
		return EFFECT_EQUIPMENT_DEFENCE;
		break;
		//バグ検査用
	default:
		//効果なし
		return EFFECT_NON;
		break;
	}
}
//---------------------------------------------------------------------------------------
//指定されたアイテムの効能?を返却する
//---------------------------------------------------------------------------------------
int CEquipmentInventory::GetEffectValue(int Receipt)
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
//---------------------------------------------------------------------------------------
//インベントリに存在するすべての攻撃強化アイテムの合計値を算出し、渡す
//---------------------------------------------------------------------------------------
int CEquipmentInventory::GetAttackTotalValue()
{
	//合計値格納用変数
	int nTotalNum = 0;

	//全てのアイテム欄を確認する
	for(int i = 0;i < EQUIPMENT_NUM_MAX;i++)
	{
		//効果が攻撃補助か確認する
		if(m_Item[i].GetType() == EFFECT_EQUIPMENT_ATTACK)
		{
			//攻撃補助型なら、その値を取り出し、加算
			nTotalNum = m_Item[i].GetValue();
		}
	}
	return nTotalNum;
}
//---------------------------------------------------------------------------------------
//インベントリに存在するすべての防御強化アイテムの合計値を算出し、渡す
//---------------------------------------------------------------------------------------
int CEquipmentInventory::GetDefenceTotalValue()
{
	//合計値格納用変数
	int nTotalNum = 0;
	//全てのアイテム欄を確認する
	for(int i = 0;i < EQUIPMENT_NUM_MAX;i++)
	{
		//効果が防御補助か確認する
		if(m_Item[i].GetType() == EFFECT_EQUIPMENT_DEFENCE)
		{
			//防御補助型なら、その値を取り出し、加算
			nTotalNum = m_Item[i].GetValue();
		}
	}
	return nTotalNum;
}