#pragma once

//フィールド上のアイテムの管理を行う。

//インクルード
#include <map>
#include<list>
#include<vector>

class CFieldItem;

typedef std::vector<CFieldItem*>		ITEM_LIST;		//フィールド上のアイテムのリスト
typedef std::map<int, ITEM_LIST>		ITEM_MAP;		//フィールド上のアイテムのリスト+ID
typedef std::pair<int, ITEM_LIST>		ITEM_PAIR;		//フィールド上のアイテムリストペア

class CItemManager
{
private:
	//変数宣言

	//シングルトン
	static ITEM_MAP *m_pItemManager;


	static int		m_MakeItemNum;			//アイテムの次に割り振られるID
	static bool		m_Delete;				//全アイテムデリートフラグ

	//関数宣言
	CItemManager();							//コンストラクタ
	~CItemManager();						//デストラクタ
public:
	static void Init();						//初期化
	static void Fin();						//終了処理
	static void Update();					//更新
	static void Draw();						//描画

	static void Create();					//アイテムマネージャーの作成
	static void Delete();					//アイテムマネージャーの削除

	static ITEM_MAP* GetPointer();		//マネージャーデバイスのポインタを渡す

	static void	CleatePermit(bool ChangeFlg) { m_Delete = ChangeFlg; }		//全アイテム削除フラグを倒す
	static int	GetNextItemID() { return m_MakeItemNum;	}	//次に割り振られるIDを返す
	static void NextItemID(int NextID) { m_MakeItemNum = NextID; }

	//-----アイテム関連の操作-----
	//アイテムを追加する
	static void Add(int ItemID,CFieldItem* pItem);
	//アイテムを削除する
	static void Del(int ItemID);
	//アイテムを探索
	static CFieldItem* Find(int ItemID);
};

