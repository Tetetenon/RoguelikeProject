#pragma once

//フィールド上に存在するアイテムクラス

#include "meshobj.h"
#include "Item.h"
#include "MapData.h"
#include "Circle.h"

class CGameScene;				//シーンクラスを仮定義

class CFieldItem :
	public CMeshObj,
	public CItem
{
private:
	static int n_Debug;
	CItem			m_Item;
	D3DXVECTOR2		m_Pos;					//配列上の位置情報
	int				m_FieldID;				//フィールド上のアイテムのID

	bool			m_ItemDelete;			//自身のデリートフラグ

	CCircle			m_Circle;				//アイテムサークル


	//-----リスト構造用-----
	CFieldItem*		m_pNextFieldItem;		//次のポインタ
	CFieldItem*		m_pBackFieldItem;		//前のポインタ

public:
	CFieldItem(CGameScene* pScene);				//コンストラクタ
	~CFieldItem(void);						//デストラクタ

	void Draw();							//描画処理
	void Update();							//更新
	void Fin();								//終了処理

	static void Generation(CMeshObj *pGeneration);			//生成
	int		GetFieldID ()	{return m_FieldID;}			//アイテムのIDの取得
	int		GetID ()		{return m_Item.GetID();}	//IDを取得
	CItem	GetItemData()	{return m_Item;}

	void	Delete();			//自身の削除

	//-----リスト構造関連-----
	CFieldItem* GetNextFieldItem ()							{return m_pNextFieldItem;}	//次のポインタを取得

	void		SetNextFieldItem (CFieldItem *pNext)		{m_pNextFieldItem = pNext;}	//次のポインタを設定する

	CFieldItem* GetBackFieldItem ()							{return m_pBackFieldItem;}	//前のポインタを取得

	void		SetBackFieldItem (CFieldItem *pBack)		{m_pBackFieldItem = pBack;}	//前のポインタを設定
};