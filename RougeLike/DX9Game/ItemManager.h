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
	static CItemManager* m_pItemManager;
	ITEM_MAP *m_pItemMap;


	int		m_MakeItemNum;			//アイテムの次に割り振られるID
	bool		m_Delete;				//全アイテムデリートフラグ

	//関数宣言
	CItemManager();							//コンストラクタ
	~CItemManager();						//デストラクタ
public:
	void Init();						//初期化
	void Fin();						//終了処理
	void Update();					//更新
	void Draw();						//描画

	static void Create();					//アイテムマネージャーの作成
	static void Delete();					//アイテムマネージャーの削除

	static CItemManager* GetPointer();		//マネージャーデバイスのポインタを渡す

	void	CleatePermit(bool ChangeFlg) { m_Delete = ChangeFlg; }		//全アイテム削除フラグを倒す
	int	GetNextItemID() { return m_MakeItemNum;	}	//次に割り振られるIDを返す
	void NextItemID(int NextID) { m_MakeItemNum = NextID; }

	//-----アイテム関連の操作-----
	//アイテムを追加する
	void Add(int ItemID,CFieldItem* pItem);
	//アイテムを削除する
	void Del(int ItemID);
	//アイテムを探索
	CFieldItem* Find(int ItemID);
};

