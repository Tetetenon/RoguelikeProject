#pragma once

#include "2DWindow.h"
#include "Item.h"

class CEquipmentCommandWindow;
class CEquipmentInventoryCursor;
class CPlayer;


//所持できる最大アイテム量
#define EQUIPMENT_NUM_MAX 5

class CEquipmentInventory:
	public CItem,
	public C2DWindow
{
private:
	CItem				m_Item[EQUIPMENT_NUM_MAX];	//アイテムデータ(アイテムの持てる数)
	LPD3DXFONT			m_Font;					//描画用フォント
	RECT				m_Pos[EQUIPMENT_NUM_MAX];	//ウィンドウ表示位置
	static bool			m_bDrawFlg;				//描画フラグ
	VERTEX_2D			m_aVertex[EQUIPMENT_NUM_MAX][NUM_VERTEX];	//ポリゴン頂点情報格納用

	static CEquipmentCommandWindow			m_CommandWindow;		//コマンドウインドウの描画フラグ変更用
	static CEquipmentInventoryCursor		m_InventoryCursor;		//選択しているアイテムウインドウの取得

	int i;
public:
	CEquipmentInventory(void);							//コンストラクタ
	~CEquipmentInventory(void);							//デストラクタ

	void Init();								//初期化
	void Fin();									//終了処理

	void UpDate();								//更新部
	void Draw();								//描画

	static void DrawFlgChange();				//描画フラグをON/OFFする

	void SetVertex();							//ポリゴン情報を埋める
	void SetFontPos();							//フォント描画位置設定

	//描画のフラグ状況を取得
	static bool GetDrawFlg()	{return m_bDrawFlg;}

	bool SetItem(CItem Item);	//ストレージにアイテムをセット

	//指定されたアイテムの名前を返す
	_TCHAR* GetInventoryItemName(int Coefficient){return m_Item[Coefficient].GetName();}

	//指定されたアイテムを渡す
	CItem GetItem(int Coefficient){return m_Item[Coefficient];}

	void DelInventory(int Receipt);				//指定した番号のアイテムを消去

	int GetEffect(int Receipt);					//指定されたアイテムの効果ジャンルを返却

	int GetEffectValue(int Receipt);			//指定されたアイテムの効能を返却する

	void FindName	(int nID,int Receipt);		//IDから名前を検索する

	int GetAttackTotalValue();					//インベントリに存在するすべての攻撃強化アイテムの合計値を算出し、渡す
	int GetDefenceTotalValue();					//インベントリに存在するすべての防御強化アイテムの合計値を算出し、渡す	
};

