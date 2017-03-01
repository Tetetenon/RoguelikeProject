#include "ItemManager.h"
#include "FieldItem.h"

//静的変数の初期化
CItemManager*	CItemManager::m_pItemManager = NULL;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CItemManager::CItemManager()
{
	//リストを作成
	m_pItemMap = new ITEM_MAP();
	//リストの初期化
	m_pItemMap->clear();

	//変数の初期化
	m_Delete = false;
	m_MakeItemNum = 1;
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CItemManager::~CItemManager()
{
	//終了処理
	Fin();
	//削除
	delete m_pItemMap;
	//中身をきれいにする
	m_pItemMap = NULL;

	m_Delete = false;

	m_MakeItemNum = 1;
}

//---------------------------------------------------------------------------------------
//アイテムマネージャーの作成
//---------------------------------------------------------------------------------------
void CItemManager::Create()
{
	//アイテムマネージャが作成されていなければ、作成を行う
	if (!m_pItemManager)
	{
		m_pItemManager = new CItemManager;
	}
}

//---------------------------------------------------------------------------------------
//アイテムマネージャーの削除
//---------------------------------------------------------------------------------------
void CItemManager::Delete()
{
	//NULLチェック
	if (m_pItemManager)
	{
		delete m_pItemManager;
		m_pItemManager = NULL;
	}
}

//---------------------------------------------------------------------------------------
//アイテムを追加
//---------------------------------------------------------------------------------------
void CItemManager::Add(int ItemID,CFieldItem* pAddItem)
{
	//IDでオブジェクトが登録されているか確認を行う
	auto ItemItewrator = m_pItemMap->find(ItemID);

	//IDが既にリスト上に登録されているか確認を行う
	if (ItemItewrator != m_pItemMap->end())
	{
		//既に登録が行われているため、オブジェデータのみを書き込む
		ItemItewrator->second.push_back(pAddItem);
	}
	else
	{
		//IDも登録がされていないため、両方ともに登録を行う
		ITEM_LIST NewItemList;
		NewItemList.push_back(pAddItem);

		ITEM_PAIR NewItemPair(ItemID, NewItemList);
		m_pItemMap->insert(NewItemPair);
	}
}
//---------------------------------------------------------------------------------------
//アイテム削除
//---------------------------------------------------------------------------------------
void CItemManager::Del(int ItemID)
{
	//IDにてデータの検索
	auto ItemIterator = m_pItemMap->find(ItemID);

	//そのIDのオブジェクトが存在していた場合、削除を行う
	if (ItemIterator != m_pItemMap->end())
	{
		auto ListIterator = ItemIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		ItemIterator->second.erase(ListIterator);
	}
}

//---------------------------------------------------------------------------------------
//アイテム探索
//---------------------------------------------------------------------------------------
CFieldItem* CItemManager::Find(int ItemID)
{
	//IDでオブジェクトを検索
	auto ItemIterator = m_pItemMap->find(ItemID);

	//そのオブジェクトデータが存在する場合、そのデータを返す
	if (ItemIterator != m_pItemMap->end())
		return ItemIterator->second[0];
	//無ければ、NULLを返す
	else
		return NULL;
}
//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void CItemManager::Init()
{
	//リストの先頭を取得
	auto ItemIterator = m_pItemMap->begin();

	for (; ItemIterator != m_pItemMap->end(); ++ItemIterator)
	{
		for (auto ListIterator = ItemIterator->second.begin(); ListIterator != ItemIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Init();
		}
	}
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CItemManager::Update()
{
	//リストの先頭を取得
	auto ItemIterator = m_pItemMap->begin();

	for (; ItemIterator != m_pItemMap->end(); ++ItemIterator)
	{
		for (auto ListIterator = ItemIterator->second.begin(); ListIterator != ItemIterator->second.end();)
		{
			//全オブジェクト削除フラグが立っていた場合、削除
			if (m_Delete)
			{
				(*ListIterator)->Fin();
				delete (*ListIterator);
				ListIterator = ItemIterator->second.erase(ListIterator);
			}
			else
			{
				(*ListIterator)->Update();
				ListIterator++;
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CItemManager::Draw()
{
	//リスト構造の先頭を取得する
	auto ItemIterator = m_pItemMap->begin();

	for (; ItemIterator != m_pItemMap->end(); ++ItemIterator)
	{
		for (auto ListIterator = ItemIterator->second.begin(); ListIterator != ItemIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Draw();
		}
	}
}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CItemManager::Fin()
{
	//リストの先頭を取得
	auto ItemIterator = m_pItemMap->begin();

	for (; ItemIterator != m_pItemMap->end();++ItemIterator)
	{
		for (auto ListIterator = ItemIterator->second.begin(); ListIterator != ItemIterator->second.end();)
		{
			(*ListIterator)->Fin();
			delete (*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = ItemIterator->second.erase(ListIterator);
		}
	}

	//生成数を初期化する
	m_MakeItemNum = 1;

	//リストを掃除
	m_pItemMap->clear();
}
//---------------------------------------------------------------------------------------
//マネージャーデバイスのポインタを渡す
//---------------------------------------------------------------------------------------
CItemManager* CItemManager::GetPointer()
{
	return m_pItemManager;
}