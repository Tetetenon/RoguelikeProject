#include "EffectObjManager.h"
#include "EffectObj.h"


//静的変数の初期化
CEffectObjManager*	CEffectObjManager::m_pEffectManager = NULL;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CEffectObjManager::CEffectObjManager()
{
	//リストの作成
	m_pEffectMap = new EFFECTOBJ_MAP();

	//リストの初期化
	m_pEffectMap->clear();

	//変数の初期化
	m_nEffectNumber = 0;
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CEffectObjManager::~CEffectObjManager()
{
	//終了処理
	Fin();
	//削除
	delete m_pEffectMap;
	//中身をきれいに
	m_pEffectMap = NULL;
	//変数の初期化
	m_nEffectNumber = 0;
}
//---------------------------------------------------------------------------------------
//マネージャーの作成
//---------------------------------------------------------------------------------------
void CEffectObjManager::Create()
{
	//まだ作成がされていない場合、作成する
	if (!m_pEffectManager)
	{
		m_pEffectManager = new CEffectObjManager;
	}
}

//---------------------------------------------------------------------------------------
//マネージャーの削除
//---------------------------------------------------------------------------------------
void CEffectObjManager::Delete()
{
	//NULLチェック
	if (m_pEffectManager)
	{
		delete m_pEffectManager;
		m_pEffectManager = NULL;
	}
}

//---------------------------------------------------------------------------------------
//マネージャーのポインタを渡す
//---------------------------------------------------------------------------------------
CEffectObjManager* CEffectObjManager::GetPointer()
{
	//作成関数を呼ぶ
	Create();
	return m_pEffectManager;
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの追加
//---------------------------------------------------------------------------------------
void CEffectObjManager::Add(int ID, CEffectObj* pAdd)
{
	//IDが既に登録がされているか確認を行う
	auto EfectIterator = m_pEffectMap->find(ID);

	//そのIDが既に登録されているか確認を行う
	if (EfectIterator != m_pEffectMap->end())
	{
		//既にIDが登録されているため、オブジェデータのみをその場所に登録する
		EfectIterator->second.push_back(pAdd);
	}
	else
	{
		//IDも登録がされていないため、両方のデータを登録する
		EFFECTOBJ_LIST NewList;
		NewList.push_back(pAdd);

		EFFECTOBJ_PAIR NewEffectPair(ID, NewList);
		m_pEffectMap->insert(NewEffectPair);
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの削除
//---------------------------------------------------------------------------------------
void CEffectObjManager::Del(int ID)
{
	//IDでオブジェクトの検索
	auto EffectIterator = m_pEffectMap->find(ID);

	//そのオブジェクトが存在している場合、削除
	if (EffectIterator != m_pEffectMap->end())
	{
		auto ListIterator = EffectIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		EffectIterator->second.erase(ListIterator);
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクト中から、指定されたIDのオブジェクトを返す
//---------------------------------------------------------------------------------------
CEffectObj* CEffectObjManager::Find(int ID)
{
	//IDでオブジェクトの検索を行う
	auto EffectIterator = m_pEffectMap->find(ID);

	//その指定されたIDのデータが存在する場合、データを返す
	if (EffectIterator != m_pEffectMap->end())
	{
		return EffectIterator->second[0];
	}
	else
	{
		return NULL;
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの初期化
//---------------------------------------------------------------------------------------
void CEffectObjManager::Init()
{
	//リストの先頭を取得
	auto EffectIterator = m_pEffectMap->begin();

	for (; EffectIterator != m_pEffectMap->end(); ++EffectIterator)
	{
		for (auto ListIterator = EffectIterator->second.begin(); ListIterator != EffectIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Init();
		}
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの更新
//---------------------------------------------------------------------------------------
void CEffectObjManager::Update()
{
	//リストの先頭を取得
	auto EffectIterator = m_pEffectMap->begin();

	for (; EffectIterator != m_pEffectMap->end(); ++EffectIterator)
	{
		for (auto ListIterator = EffectIterator->second.begin(); ListIterator != EffectIterator->second.end();)
		{
			//更新
			(*ListIterator)->Update();

			//残りの生存時間が無くなれば、削除
			if ((*ListIterator)->GetLifeTime() <= 0)
			{
				//削除処理
				(*ListIterator)->Fin();
				delete (*ListIterator);
				ListIterator = EffectIterator->second.erase(ListIterator);

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
//管理するオブジェクトの描画
//---------------------------------------------------------------------------------------
void CEffectObjManager::Draw()
{
	//リストの先頭を取得
	auto EffectIterator = m_pEffectMap->begin();

	for (; EffectIterator != m_pEffectMap->end(); ++EffectIterator)
	{
		for (auto ListIterator = EffectIterator->second.begin(); ListIterator != EffectIterator->second.end(); ++ListIterator)
		{
			(*ListIterator)->Draw();
		}
	}
}
//---------------------------------------------------------------------------------------
//管理するオブジェクトの終了処理
//---------------------------------------------------------------------------------------
void CEffectObjManager::Fin()
{
	//リストの先頭を取得
	auto EffectIterator = m_pEffectMap->begin();

	for (; EffectIterator != m_pEffectMap->end(); ++EffectIterator)
	{
		for (auto ListIterator = EffectIterator->second.begin(); ListIterator != EffectIterator->second.end();)
		{
			(*ListIterator)->Fin();
			delete (*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = EffectIterator->second.erase(ListIterator);
		}
	}
	//リストの掃除
	m_pEffectMap->clear();
}