#include "ParticleManager.h"

#include"Particle.h"

//静的変数宣言
CParticleManager*	CParticleManager::m_pParticleManager = NULL;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CParticleManager::CParticleManager()
{
	//リストの作成
	m_pParticleMap = new PARTICLE_MAP();
	//初期化
	m_nNextID = 0;

	//リスト初期化
	m_pParticleMap->clear();
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CParticleManager::~CParticleManager()
{
	//初期化
	m_nNextID = 0;

	//終了処理
	Fin();
	//削除
	delete m_pParticleMap;
	//中身の掃除
	m_pParticleMap = NULL;
}
//---------------------------------------------------------------------------------------
//マネージャーの作成
//---------------------------------------------------------------------------------------
void CParticleManager::Create()
{
	//マネージャーポインタの中身がまだなければ作成する
	if (!m_pParticleManager)
	{
		m_pParticleManager = new CParticleManager;
	}
}
//---------------------------------------------------------------------------------------
//マネージャーの削除
//---------------------------------------------------------------------------------------
void CParticleManager::Delete()
{
	//NULLチェック
	if (m_pParticleManager)
	{
		delete m_pParticleManager;
		m_pParticleManager = NULL;
	}
}
//---------------------------------------------------------------------------------------
//マネージャーの実体を渡す
//---------------------------------------------------------------------------------------
CParticleManager* CParticleManager::GetPointer()
{
	//念のため作成関数を呼ぶ
	Create();
	return m_pParticleManager;
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの追加
//---------------------------------------------------------------------------------------
void CParticleManager::Add(int ID, CParticle* pAdd)
{
	//IDが既に登録されているか確認を行う
	auto ParticleIterator = m_pParticleMap->find(ID);

	//そのIDが登録されているか確認を行う
	if (ParticleIterator != m_pParticleMap->end())
	{
		//IDが既に登録されているため、オブジェクトデータのみ登録
		ParticleIterator->second.push_back(pAdd);
	}
	else
	{
		//IDも登録が行われていないため、ID,オブジェクトデータともに登録を行う
		PARTICLE_LIST NewList;
		NewList.push_back(pAdd);

		PARTICLE_PAIR NewParticlePair(ID,NewList);
		m_pParticleMap->insert(NewParticlePair);
	}
}

//---------------------------------------------------------------------------------------
//管理オブジェクトの削除
//---------------------------------------------------------------------------------------
void CParticleManager::Del(int ID)
{
	//IDでオブジェクトの検索
	auto ParticleIterator = m_pParticleMap->find(ID);

	//検索したオブジェクトが存在していた場合、削除を行う
	if (ParticleIterator != m_pParticleMap->end())
	{
		auto ListIterator = ParticleIterator->second.begin();
		(*ListIterator)->Fin();
		delete (*ListIterator);
		ParticleIterator->second.erase(ListIterator);
	}
}

//---------------------------------------------------------------------------------------
//管理するオブジェクトから、指定されたIDのオブジェクトを返す
//---------------------------------------------------------------------------------------
CParticle* CParticleManager::Find(int ID)
{
	//IDでオブジェクトの探索
	auto ParticleIterator = m_pParticleMap->find(ID);

	//そのIDのオブジェクトが存在している場合、データを返す
	if (ParticleIterator != m_pParticleMap->end())
	{
		return ParticleIterator->second[0];
	}
	else
	{
		//データが存在していない場合NULLを返す
		return NULL;
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの初期化
//---------------------------------------------------------------------------------------
void CParticleManager::Init()
{
	//リストの先頭を取得
	auto ParticleIterator = m_pParticleMap->begin();

	for (; ParticleIterator != m_pParticleMap->end(); ++ParticleIterator)
	{
		for (auto ListIterator = ParticleIterator->second.begin(); ListIterator != ParticleIterator->second.end();)
		{
			//初期化
			(*ListIterator)->Init();
			ListIterator++;
		}
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの更新
//---------------------------------------------------------------------------------------
void CParticleManager::Update()
{
	//リストの先頭を取得
	auto ParticleIterator = m_pParticleMap->begin();

	for (; ParticleIterator != m_pParticleMap->end(); ++ParticleIterator)
	{
		for (auto ListIterator = ParticleIterator->second.begin(); ListIterator != ParticleIterator->second.end();)
		{
			//更新
			(*ListIterator)->Update();

			//削除フラグが立っているか確認
			if ((*ListIterator)->GetDeleteFlg())
			{
				//立っていたら、削除を行う
				//削除処理
				(*ListIterator)->Fin();
				delete (*ListIterator);
				ListIterator = ParticleIterator->second.erase(ListIterator);
			}
			else
			{
				//立っていなければ、次のオブジェクトの処理を行う
				ListIterator++;
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの描画
//---------------------------------------------------------------------------------------
void CParticleManager::Draw()
{
	//リストの先頭を取得
	auto ParticleIterator = m_pParticleMap->begin();

	for (; ParticleIterator != m_pParticleMap->end(); ++ParticleIterator)
	{
		for (auto ListIterator = ParticleIterator->second.begin(); ListIterator != ParticleIterator->second.end();)
		{
			//描画
			(*ListIterator)->DrawAlpha();
			ListIterator++;
		}
	}
}
//---------------------------------------------------------------------------------------
//管理オブジェクトの終了処理
//---------------------------------------------------------------------------------------
void CParticleManager::Fin()
{
	//リストの先頭を取得
	auto ParticleIterator = m_pParticleMap->begin();

	for (; ParticleIterator != m_pParticleMap->end(); ++ParticleIterator)
	{
		for (auto ListIterator = ParticleIterator->second.begin(); ListIterator != ParticleIterator->second.end();)
		{
			//終了処理
			(*ListIterator)->Fin();
			delete(*ListIterator);
			(*ListIterator) = NULL;
			ListIterator = ParticleIterator->second.erase(ListIterator);
		}
	}

	//リストの掃除
	m_pParticleMap->clear();
}