#include "UnitManager.h"
#include "Turn.h"
#include "Unit.h"				//ユニット


//静的変数の初期化
int				CUnitManager::m_NowProcUnitID = 0;
UNIT_MAP*		CUnitManager::m_pUnitManager = NULL;

CUnit*	CUnitManager::m_pPlayer = NULL;			//プレイヤーポインター
bool	CUnitManager::m_bMoveCanFlg;					//移動可能フラグ


//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CUnitManager::CUnitManager()
{
	//現在処理中のユニットの番号の初期化
	m_NowProcUnitID = 0;

	//リストの初期化
	m_pUnitManager->clear();
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CUnitManager::~CUnitManager()
{
	//現在処理中のユニットの番号を初期化
	m_NowProcUnitID = 0;

	//リストの掃除
	m_pUnitManager->clear();

	m_pPlayer = NULL;
}

//---------------------------------------------------------------------------------------
//マネージャーの生成
//---------------------------------------------------------------------------------------
void CUnitManager::Create()
{
	//まだ作成をしていなかったらさくせいする
	if (!m_pUnitManager)
	{
		m_pUnitManager = new UNIT_MAP;
	}
}
//---------------------------------------------------------------------------------------
//マネージャーの削除
//---------------------------------------------------------------------------------------
void CUnitManager::Destroy()
{
	//NULLチェック
	if (m_pUnitManager)
	{
		//終了処理
		Fin();
		//削除
		delete m_pUnitManager;
		//中身をきれいに
		m_pUnitManager = NULL;
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの追加
//---------------------------------------------------------------------------------------
void CUnitManager::Add(int UnitID, CUnit* pAddUnit)
{
	//既にIDが登録されているか確認を行う
	auto UnitIterator = m_pUnitManager->find(UnitID);

	//そのIDが既に登録されているか確認する
	if (UnitIterator != m_pUnitManager->end())
	{
		//IDが既に登録されているため、オブジェクトデータのみ挿入
		UnitIterator->second.push_back(pAddUnit);
	}
	else
	{
		//IDも、オブジェデータも登録されていないため、両方登録する
		UNIT_LIST NewUnitList;
		NewUnitList.push_back(pAddUnit);

		UNIT_PAIR NewUnitPair(UnitID, NewUnitList);
		m_pUnitManager->insert(NewUnitPair);
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの削除
//---------------------------------------------------------------------------------------
void CUnitManager::Del(int UnitID)
{
	//IDでオブジェクトの検索
	auto UnitIterator = m_pUnitManager->find(UnitID);

	//そのオブジェクトが存在している場合、削除を行う
	if (UnitIterator != m_pUnitManager->end())
	{
		auto ListIterator = UnitIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		UnitIterator->second.erase(ListIterator);
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの中から、指定されたIDのユニットを返す
//---------------------------------------------------------------------------------------
CUnit* CUnitManager::Find(int UnitID)
{
	//IDでオブジェクトの検索を行う
	auto UnitIterator = m_pUnitManager->find(UnitID);

	//その指定されたIDのデータが存在する場合、データを返す
	if (UnitIterator != m_pUnitManager->end())
	{
		return UnitIterator->second[0];
	}
	else
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの初期化
//---------------------------------------------------------------------------------------
void CUnitManager::Init()
{
	//リストの先頭を取得
	auto UnitIterator = m_pUnitManager->begin();

	for (; UnitIterator != m_pUnitManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Init();
		}
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの更新
//---------------------------------------------------------------------------------------
void CUnitManager::Update()
{
	//リストの先頭を取得
	auto UnitIterator = m_pUnitManager->begin();

	for (; UnitIterator != m_pUnitManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			//待機状態の更新を行う
			(*ListIterator)->WaitUpdate();
			(*ListIterator)->Update();

			//現在のユニットの番号を取得し、そのユニットの番号ならば、ターンの処理を行う
			if (m_NowProcUnitID == (*ListIterator)->GetNumber() || m_NowProcUnitID == 0)
			{
				//ターンが終了しているか確認する
				if ((*ListIterator)->GetTurnEndFlg())
				{
					//ターン処理が完了している場合
			
					//現在の処理中ユニット番号を初期化
					//次のユニットの処理ができるようにする
					m_NowProcUnitID = 0;
			
					//ユニットのターンの処理状態を初期化
					(*ListIterator)->setTurnEndFlg(false);
				}
				else
				{
					//ターン処理が完了していない場合
			
					//現在の処理ユニットを自身に設定する
					m_NowProcUnitID = (*ListIterator)->GetNumber();
			
					//もし、行動可能フラグが立っていなければ、処理をスキップ
					if (!m_bMoveCanFlg)
						return;
			
					//ターン処理の更新
					(*ListIterator)->TurnUpdate();
				}
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの描画
//---------------------------------------------------------------------------------------
void CUnitManager::Draw()
{
	//リストの先頭を取得
	auto UnitIterator = m_pUnitManager->begin();

	for (; UnitIterator != m_pUnitManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Draw();
		}
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの終了処理
//---------------------------------------------------------------------------------------
void CUnitManager::Fin()
{
	//リストの先頭を取得
	auto UnitIterator = m_pUnitManager->begin();

	for (; UnitIterator != m_pUnitManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end();)
		{
			(*ListIterator)->Fin();
			delete (*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = UnitIterator->second.erase(ListIterator);
		}
	}
	//リストの掃除
	m_pUnitManager->clear();
}
//---------------------------------------------------------------------------------------
//エネミーの削除
//---------------------------------------------------------------------------------------
void CUnitManager::EnemyDelete()
{
	//リストの先頭を取得
	auto UnitIterator = m_pUnitManager->begin();

	for (; UnitIterator != m_pUnitManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end();)
		{
			//エネミーの場合削除
			if((*ListIterator)->GetNumber() >= OBJ_NUM_ENEMY)
			{
				(*ListIterator)->Fin();
				delete (*ListIterator);
				ListIterator = UnitIterator->second.erase(ListIterator);
			}
			else
			{
				ListIterator++;
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//マネージャーのデバイスを渡す
//---------------------------------------------------------------------------------------
UNIT_MAP* CUnitManager::GetPointer()
{
	return m_pUnitManager;
}
//---------------------------------------------------------------------------------------
//ユニット全ての行動可能フラグを変更する
//---------------------------------------------------------------------------------------
void CUnitManager::ChangeMoveCanFlg(bool ChangeFlg)
{
	m_bMoveCanFlg = ChangeFlg;
}
//---------------------------------------------------------------------------------------
//プレイヤーのポインタを設定する
//---------------------------------------------------------------------------------------
void CUnitManager::SetPlayerPointer()
{
	auto UnitIterator = m_pUnitManager->find(OBJ_NUM_PLAYER);

	m_pPlayer = *(UnitIterator->second.begin());
}
//---------------------------------------------------------------------------------------
//プレイヤーのレベルを返す
//---------------------------------------------------------------------------------------
int CUnitManager::GetPlayerLevel()
{
	//プレイヤーポインタの中身が入っているのか確認
	if (m_pPlayer)
	{
		//入っている場合、プレイヤーのレベルを返す
		return m_pPlayer->GetLevel();
	}
	else
		//入っていなければ、0を返す
		return 0;
}
//---------------------------------------------------------------------------------------
//プレイヤーの位置情報を渡す(横)
//---------------------------------------------------------------------------------------
int CUnitManager::GetPlayerPosX()
{
	//プレイヤーのポインタに中身が入っているか確認する
	if (m_pPlayer)
	{
		//入っている場合、プレイヤーの位置を返す
		return m_pPlayer->GetPosX();
	}
	else
	{
		//入っていない場合、0を返す
		return 0;
	}
}
//---------------------------------------------------------------------------------------
//プレイヤーの位置情報を返す(縦)
//---------------------------------------------------------------------------------------
int CUnitManager::GetPlayerPosZ()
{
	//プレイヤーのポインタが存在するか確認する
	if (m_pPlayer)
	{
		return m_pPlayer->GetPosZ();
	}
	else
	{
		//入っていない場合、0を返す
		return 0;
	}
}