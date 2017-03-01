#include "DamageBillBoardManager.h"
#include "DamageNotation.h"

//静的変数宣言
CDamageBillBoardManager* CDamageBillBoardManager::m_pManager = NULL;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CDamageBillBoardManager::CDamageBillBoardManager()
{
	//リストポインタの取得
	m_pDamageBillBoardMap = new DAMAGE_NOTATION_MAP;
	//リストの初期化
	m_pDamageBillBoardMap->clear();
	//使用変数の初期化
	m_nNextBillBoardNumber = 0;
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CDamageBillBoardManager::~CDamageBillBoardManager()
{
	//管理オブジェクトの終了処理
	ManagerObjFin();
	//削除
	delete m_pDamageBillBoardMap;
	//中身をきれいに
	m_pDamageBillBoardMap = NULL;
	//使用変数の初期化
	m_nNextBillBoardNumber = 0;
}
//---------------------------------------------------------------------------------------
//マネージャーの作成
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::Create()
{
	//マネージャーが作成されていなければ作成
	if (!m_pManager)
	{
		m_pManager = new CDamageBillBoardManager;
	}
}
//---------------------------------------------------------------------------------------
//マネージャーの削除
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::Delete()
{
	//中身が存在しているか、チェックを行う
	if (m_pManager)
	{
		//マネージャー削除
		delete m_pManager;
		m_pManager = NULL;
	}
}
//---------------------------------------------------------------------------------------
//マネージャーのポインタを渡す
//---------------------------------------------------------------------------------------
CDamageBillBoardManager* CDamageBillBoardManager::GetPointer()
{
	//マネージャーの作成
	Create();

	//ポインタを返す
	return m_pManager;
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの追加
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::Add(int ID, CDamageNotation* pAddObj)
{
	//IDが既に登録がされているか確認を行う
	auto BoardIterator = m_pDamageBillBoardMap->find(ID);

	//そのIDが既に登録されているか確認を行う
	if (BoardIterator != m_pDamageBillBoardMap->end())
	{
		//既にIDが登録されているため、オブジェデータのみをその場所に登録する
		BoardIterator->second.push_back(pAddObj);
	}
	else
	{
		//IDも登録がされていないため、両方のデータを登録する
		DAMAGE_NOTATION_LIST NewList;
		NewList.push_back(pAddObj);

		DAMAGE_NOTATION_PAIR NewEffectPair(ID, NewList);
		m_pDamageBillBoardMap->insert(NewEffectPair);
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの削除
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::Del(int ID)
{
	//IDでオブジェクトの検索
	auto BoardIterator = m_pDamageBillBoardMap->find(ID);

	//そのオブジェクトが存在している場合、削除
	if (BoardIterator != m_pDamageBillBoardMap->end())
	{
		auto ListIterator = BoardIterator->second.begin();
		delete (*ListIterator);
		BoardIterator->second.erase(ListIterator);
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの検索
//---------------------------------------------------------------------------------------
CDamageNotation* CDamageBillBoardManager::Find(int ID)
{
	//IDでオブジェクトの検索を行う
	auto BoardIterator = m_pDamageBillBoardMap->find(ID);

	//その指定されたIDのデータが存在する場合、データを返す
	if (BoardIterator != m_pDamageBillBoardMap->end())
	{
		return BoardIterator->second[0];
	}
	else
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの終了処理
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::ManagerObjFin()
{
	//リストの先頭を取得
	auto BoardIterator = m_pDamageBillBoardMap->begin();

	for (; BoardIterator != m_pDamageBillBoardMap->end(); ++BoardIterator)
	{
		for (auto ListIterator = BoardIterator->second.begin(); ListIterator != BoardIterator->second.end();)
		{
			delete (*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = BoardIterator->second.erase(ListIterator);
		}
	}
	//リストの掃除
	m_pDamageBillBoardMap->clear();
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの更新
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::ManagerObjUpdate()
{
	//リストの先頭を取得
	auto BoardIterator = m_pDamageBillBoardMap->begin();

	for (; BoardIterator != m_pDamageBillBoardMap->end(); ++BoardIterator)
	{
		for (auto ListIterator = BoardIterator->second.begin(); ListIterator != BoardIterator->second.end();)
		{
			//更新
			(*ListIterator)->Update();

			//残りの生存時間が無くなれば、削除
			if ((*ListIterator)->GetLifeTime() <= 0)
			{
				//削除処理
				delete (*ListIterator);
				ListIterator = BoardIterator->second.erase(ListIterator);

			}
			else
			{
				//生存時間が残っている場合はスル―
				ListIterator++;
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの描画
//---------------------------------------------------------------------------------------
void CDamageBillBoardManager::ManagerObjDraw()
{
	//リストの先頭を取得
	auto BoardIterator = m_pDamageBillBoardMap->begin();

	for (; BoardIterator != m_pDamageBillBoardMap->end(); ++BoardIterator)
	{
		for (auto ListIterator = BoardIterator->second.begin(); ListIterator != BoardIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Draw();
		}
	}
}
