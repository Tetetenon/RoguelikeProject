#include "UnitManager.h"
#include "Unit.h"				//ユニット

#include "EnemyManager.h"


//静的変数の初期化
UNIT_MAP*		CUnitManager::m_pUnitManager = NULL;

CUnit*	CUnitManager::m_pPlayer = NULL;			//プレイヤーポインター
int		CUnitManager::m_nMakeNumber = OBJ_NUM_PLAYER;	//生成したユニットの数
bool	CUnitManager::m_bMoveCanFlg;			//移動可能フラグ


//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CUnitManager::CUnitManager()
{
	//リストの初期化
	m_pUnitManager->clear();

	//生成したユニットの数初期化
	m_nMakeNumber = OBJ_NUM_PLAYER;
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CUnitManager::~CUnitManager()
{
	//生成したユニットの数初期化
	m_nMakeNumber = OBJ_NUM_PLAYER;

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
		m_pUnitManager = new UNIT_MAP();

		//エネミーマネージャーの作成
		CEnemyManager::Create();
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
		//エネミーマネージャーの削除
		CEnemyManager::Destroy();
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
	//IDによって登録する先を決定する
	if (UnitID >= OBJ_NUM_ENEMY)
	{
		//エネミーの場合、エネミーマネージャー側に登録させる
		CEnemyManager::Add(UnitID,pAddUnit);
	}

	else if (UnitID >= OBJ_NUM_PARTY)
	{
		//パーティーメンバーの場合、パーティーマネージャーへ
	}
	
	if (UnitID == OBJ_NUM_PLAYER)
	{
		//プレイヤーの場合、自身のリストへ登録する

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
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの削除
//---------------------------------------------------------------------------------------
void CUnitManager::Del(int UnitID)
{
	//IDによって削除するデータの先を変更する
	if (UnitID >= OBJ_NUM_ENEMY)
	{
		//エネミーの場合、エネミーマネージャー側のデータを削除
		CEnemyManager::Del(UnitID);
	}

	else if (UnitID >= OBJ_NUM_PARTY)
	{
		//パーティーメンバーの場合、パーティーマネージャーへ
	}

	if (UnitID == OBJ_NUM_PLAYER)
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
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの中から、指定されたIDのユニットを返す
//---------------------------------------------------------------------------------------
CUnit* CUnitManager::Find(int UnitID)
{
	//IDによって探索する先を決定する
	if (UnitID >= OBJ_NUM_ENEMY)
	{
		//エネミーの場合、エネミーマネージャーから探索させる
		return CEnemyManager::Find(UnitID);
	}

	else if (UnitID >= OBJ_NUM_PARTY)
	{
		//パーティーメンバーの場合、パーティーマネージャーへ
	}

	if (UnitID == OBJ_NUM_PLAYER)
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
	return NULL;
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

	//エネミーの初期化
	CEnemyManager::Init();
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの更新
//---------------------------------------------------------------------------------------
void CUnitManager::Update()
{
	//現在のターンユニットを取得
	CTurn::UnitTurnState NowTurnUnit = CTurn::GetUnitTurn();

	//全ユニットの待機更新を行う
	for (auto UnitIterator = m_pUnitManager->begin(); UnitIterator != m_pUnitManager->end(); ++UnitIterator)
	{
		for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
		{
			//待機状態の更新を行う
			(*ListIterator)->WaitUpdate();
			(*ListIterator)->Update();
		}
	}

	//エネミーの待機更新を行う
	CEnemyManager::WaitUpdate();

	//現在のターンユニットのオブジェクトのみターンの更新を行う
	switch (NowTurnUnit)
	{
		//プレイヤーのターン更新
	case CTurn::UNIT_TURN_PLAYER:
		for (auto UnitIterator = m_pUnitManager->begin(); UnitIterator != m_pUnitManager->end(); ++UnitIterator)
		{
			for (auto ListIterator = UnitIterator->second.begin(); ListIterator != UnitIterator->second.end(); ++ListIterator)
			{
				//ターンの更新を行う
				(*ListIterator)->TurnUpdate();
			}
		}
		break;
		//パーティーメンバーのターン
	case CTurn::UNIT_TURN_PARTY:
		break;
		//エネミーのターン更新
	case CTurn::UNIT_TURN_ENEMY:
		CEnemyManager::TurnUpdate();
		break;
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

	//エネミーの描画
	CEnemyManager::Draw();
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

	//エネミーマネージャーの終了処理
	CEnemyManager::Fin();
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