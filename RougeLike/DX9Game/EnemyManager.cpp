#include "EnemyManager.h"
#include "Unit.h"

//静的変数宣言
UNIT_MAP*	CEnemyManager::m_pEnemyManager = NULL;
int			CEnemyManager::m_NowProcUnitID = 0;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CEnemyManager::CEnemyManager()
{
	//リストの初期化
	m_pEnemyManager->clear();

	//攻撃ちゅうのエネミーの番号の初期化
	m_NowProcUnitID = 0;
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CEnemyManager::~CEnemyManager()
{
	//リストの初期化
	m_pEnemyManager->clear();

	//攻撃ちゅうのエネミーの番号の初期化
	m_NowProcUnitID = 0;
}

//---------------------------------------------------------------------------------------
//マネージャーの作成
//---------------------------------------------------------------------------------------
void CEnemyManager::Create()
{
	//まだ作成が行われていなかった場合、生成する
	if (!m_pEnemyManager)
	{
		m_pEnemyManager = new UNIT_MAP();
	}
}
//---------------------------------------------------------------------------------------
//マネージャーの削除
//---------------------------------------------------------------------------------------
void CEnemyManager::Destroy()
{
	//NULLのチェック
	if (m_pEnemyManager)
	{
		//中身が存在すれば削除

		//終了処理
		Fin();
		//削除
		delete m_pEnemyManager;
		//中身をきれいに
		m_pEnemyManager = NULL;
	}
}

//---------------------------------------------------------------------------------------
//管理オブジェクトの追加
//---------------------------------------------------------------------------------------
void CEnemyManager::Add(int UnitID,CUnit* pAddUnit)
{
	//IDが既に登録されているかどうか確認する
	auto UnitIterator = m_pEnemyManager->find(UnitID);

	//そのIDが登録されているかどうかで処理を変更する
	if (UnitIterator != m_pEnemyManager->end())
	{
		//IDが既に登録されている状態のため、その位置にオブジェクトデータを格納する
		UnitIterator->second.push_back(pAddUnit);
	}
	else
	{
		//IDも登録されていないため、両方のデータを登録する
		UNIT_LIST NewUnitList;
		NewUnitList.push_back(pAddUnit);

		UNIT_PAIR NewUnitPair(UnitID, NewUnitList);
		m_pEnemyManager->insert(NewUnitPair);
	}
}

//---------------------------------------------------------------------------------------
//管理オブジェクトの削除
//---------------------------------------------------------------------------------------
void CEnemyManager::Del(int UnitID)
{
	//IDでオブジェクトの詮索を行う
	auto UnitIterator = m_pEnemyManager->find(UnitID);

	//指定されたオブジェクトIDのデータが存在している場合、そのデータを削除する
	if (UnitIterator != m_pEnemyManager->end())
	{
		auto ListIterator = UnitIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		UnitIterator->second.erase(ListIterator);
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトのデータを返す
//---------------------------------------------------------------------------------------
CUnit* CEnemyManager::Find(int UnitID)
{
	//IDでオブジェクトの検索を行う
	auto UnitIterator = m_pEnemyManager->find(UnitID);

	//その指定されたIDのデータが存在する場合、データを返す
	if (UnitIterator != m_pEnemyManager->end())
	{
		return UnitIterator->second[0];
	}
	else
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの初期化
//---------------------------------------------------------------------------------------
void CEnemyManager::Init()
{
	//リストの先頭を取得
	auto UnitIterator = m_pEnemyManager->begin();

	for (; UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Init();
		}
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの待機更新
//---------------------------------------------------------------------------------------
void CEnemyManager::WaitUpdate()
{
	for (auto UnitIterator = m_pEnemyManager->begin(); UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			//待機状態の更新を行う
			(*ListIterator)->WaitUpdate();
			(*ListIterator)->Update();
		}
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトのターン更新
//---------------------------------------------------------------------------------------
void CEnemyManager::TurnUpdate()
{
	//全ユニットのターン処理が終了したか
	bool bAllUnitUpdateEndFlg = true;

	for (auto UnitIterator = m_pEnemyManager->begin(); UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			//ターン処理が終了していなければ処理を行う
			if (!(*ListIterator)->GetTurnEndFlg())
			{
				//全てのユニットの更新がまだ終了していない
				bAllUnitUpdateEndFlg = false;

				//ターンステートによって更新内容を変更する
				switch ((*ListIterator)->GetUnitTurnState())
				{
					//入力待ち
				case CTurn::GAME_STATE_STAND_BY:
					(*ListIterator)->InputUpdate();
					break;
					//アイテムの使用
				case CTurn::GAME_STATE_ITEM_USE:
					(*ListIterator)->ItemUpdate();
					break;
					//移動
				case CTurn::GAME_STATE_MOVE:
					(*ListIterator)->MoveUpdate();
					break;
					//行動
				case CTurn::GAME_STATE_ACT:
					(*ListIterator)->ActUpdate();
					break;
					//攻撃
				case CTurn::GAME_STATE_ATTACK:
					//現在の攻撃更新ユニットの番号が自身である、又は誰も処理を行っていなければ更新
					if (m_NowProcUnitID == (*ListIterator)->GetNumber() || m_NowProcUnitID == 0)
					{
						//自身が処理を行っていると、登録する
						m_NowProcUnitID = (*ListIterator)->GetNumber();
						//攻撃の更新が終了した場合、正が返る
						if ((*ListIterator)->AttackUpdate())
							m_NowProcUnitID = 0;
					}
					break;
					//ターン終了処理
				case CTurn::GAME_STATE_TURN_END:
					(*ListIterator)->TurnEndUpdate();
					break;
				default:
					break;
				}
			}
		}
	}
	//全てのユニットの更新が終了していた場合、ステートを変更する
	if (bAllUnitUpdateEndFlg)
	{
		for (auto UnitIterator = m_pEnemyManager->begin(); UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
		{
			for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
			{
				//ユニットのターンの処理状態を初期化
				(*ListIterator)->setTurnEndFlg(false);
			}
		}

		//ステートの変更
		CTurn::ChangeUnitState(CTurn::UNIT_TURN_PLAYER);
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの描画
//---------------------------------------------------------------------------------------
void CEnemyManager::Draw()
{
	//リストの先頭を取得
	auto UnitIterator = m_pEnemyManager->begin();

	for (; UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Draw();
		}
	}

	//ビルボードの描画
	UnitIterator = m_pEnemyManager->begin();
	
	for (; UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->BillBordDraw();
		}
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの終了処理
//---------------------------------------------------------------------------------------
void CEnemyManager::Fin()
{
	//リストの先頭を取得;
	for (auto UnitIterator = m_pEnemyManager->begin();UnitIterator != m_pEnemyManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end();)
		{
			(*ListIterator)->Fin();
			delete (*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = UnitIterator->second.erase(ListIterator);
		}
	}
	m_NowProcUnitID = 0;
	//リストの掃除
	m_pEnemyManager->clear();
}