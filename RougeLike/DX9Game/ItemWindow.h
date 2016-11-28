#pragma once

#include "2DWindow.h"
#include "Item.h"
#include "ItemDescriptionFrame.h"

class CCommandWindow;
class CInventoryCursor;


//所持できる最大アイテム量
#define ITEM_NUM_MAX 10

class CInventory:
	public CItem,
	public C2DWindow
{
private:
	CItem				m_Item[ITEM_NUM_MAX];	//アイテムデータ(アイテムの持てる数)
	LPD3DXFONT			m_Font;					//描画用フォント
	RECT				m_Pos[ITEM_NUM_MAX];	//ウィンドウ表示位置
	static bool			m_bDrawFlg;				//描画フラグ

	VERTEX_2D	m_aVertex[ITEM_NUM_MAX][NUM_VERTEX];	//ポリゴン頂点情報格納用

	static CCommandWindow		m_CommandWindow;		//コマンドウインドウの描画フラグ変更用
	static CInventoryCursor	m_InventoryCursor;		//選択しているアイテムウインドウの取得

	static CItemDescriptionFrame m_Description;		//アイテム説明文
public:
	CInventory(void);							//コンストラクタ
	~CInventory(void);							//デストラクタ

	void Init();								//初期化
	void Fin();									//終了処理

	void UpDate();								//更新部
	void Draw();								//描画

	static void DrawFlgChange();				//描画フラグをON/OFFする

	void SetVertex();							//ポリゴン情報を埋める
	void SetFontPos();							//フォント描画位置設定

	//描画のフラグ状況を取得
	static bool GetDrawFlg()	{return m_bDrawFlg;}

	bool SetItem(CItem Item);		//ストレージにアイテムをセット

	//指定されたアイテムデータを渡す
	CItem GetItem (int Coefficient)	{return m_Item[Coefficient];}

	//指定されたアイテムの名前を返す
	_TCHAR* GetInventoryItemName(int Coefficient){return m_Item[Coefficient].GetName();}

	void DelInventory(int Receipt);				//指定した番号のアイテムを消去

	int GetEffect(int Receipt);					//指定されたアイテムの効果ジャンルを返却

	int GetEffectValue(int Receipt);			//指定されたアイテムの効能を返却する

	void FindName	(int nID,int Receipt);		//IDから名前を検索する
};

