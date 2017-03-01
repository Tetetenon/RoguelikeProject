#pragma once

//フィールド上に存在するアイテムクラス

#include "meshobj.h"
#include "Item.h"
#include "MapData.h"
#include "Circle.h"

class CGameScene;				//シーンクラスを仮定義
class CMapData;
class CItemManager;

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
	CMapData*		m_pMapData;
	CItemManager*	m_pItemManager;
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
};