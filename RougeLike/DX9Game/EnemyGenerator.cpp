#include "EnemyGenerator.h"
#include "Enemy.h"
#include "Input.h"

#include"Unit.h"
#include"UnitManager.h"
#include "MapData.h"

#define MAKEPERCENTAGE 15

//静的メンバ実体定義
CEnemyGenerator* CEnemyGenerator::m_pEnemyGenerator = NULL;

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CEnemyGenerator::CEnemyGenerator(CGameScene *pScene):
CMeshObj(pScene)
{

	m_FieldEnemyCounter = 0;
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CEnemyGenerator::~CEnemyGenerator(void)
{
	m_FieldEnemyCounter = 0;
}
//---------------------------------------------------------------------------------------
//実体の作成
//---------------------------------------------------------------------------------------
void CEnemyGenerator::Create(CGameScene *pScene)
{
	//実体がまだなければ作成
	if (!m_pEnemyGenerator)
	{
		m_pEnemyGenerator = new CEnemyGenerator(pScene);
	}
}
//---------------------------------------------------------------------------------------
//実体の削除
//---------------------------------------------------------------------------------------
void CEnemyGenerator::Delete()
{
	//実体があれば削除
	if (m_pEnemyGenerator)
	{
		delete m_pEnemyGenerator;
		m_pEnemyGenerator = NULL;
	}
}
//---------------------------------------------------------------------------------------
//実体のポインタを渡す
//---------------------------------------------------------------------------------------
CEnemyGenerator* CEnemyGenerator::GetPointer()
{
	return m_pEnemyGenerator;
}
//---------------------------------------------------------------------------------------
//メンバ変数のポインタを設定
//---------------------------------------------------------------------------------------
void CEnemyGenerator::SetPointer()
{
	//ポインタの取得
	m_pMapData = CMapData::GetPointer();

	//プレイヤーのポインタを取得
	CUnitManager* pUnitManager = CUnitManager::GetPointer();
	m_pPlayer = pUnitManager->GetPlayerPointer();
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CEnemyGenerator::Update()
{
	//階層数を取得
	int Hierarchy = m_pMapData->GetHierarchieNum();

	//ターンステートが一定のステートの際、エネミーを確率で生成する
	if(m_pPlayer->GetUnitTurnState() == CTurn::GAME_STATE_STAND_BY)
	{
		if (Hierarchy != GameClearNum)
		{
			int nRand = rand() % 100;
			//フィールドに配置できる最大エネミー数に到達していない
			if (nRand < MAKEPERCENTAGE && m_FieldEnemyCounter < m_MaxFieldEnemy && !m_bMakeFlg)
			{
				//エネミーの生成
				CEnemy::Generation(this);
				//生成数加算
				m_FieldEnemyCounter++;
			}

			//このターンでの生成確認処理を完了した
			m_bMakeFlg = true;
		}
	}
	//ステートが違えば、生成フラグを下げておく
	else
	{
		m_bMakeFlg = false;
	}

	//デバッグコマンド(エネミー生成)
	if(CInput::GetKeyPress(DIK_Z) && m_FieldEnemyCounter < m_MaxFieldEnemy)
	{
		CEnemy::Generation(this);
		
		//生成数加算
		m_FieldEnemyCounter++;
	}
}

//---------------------------------------------------------------------------------------
//エネミー生成数を減算
//---------------------------------------------------------------------------------------
void CEnemyGenerator::SumMakeEnemyNum()
{
	m_FieldEnemyCounter --;
}
//---------------------------------------------------------------------------------------
//エネミー最大生成数を設定
//---------------------------------------------------------------------------------------
void CEnemyGenerator::SetMaxGenerator (int nMaxCount)
{
	m_MaxFieldEnemy = nMaxCount;

	//デバッグ用
	if (DebugMode)
		m_MaxFieldEnemy = 0;
}
//---------------------------------------------------------------------------------------
//エネミー生成数を再設定
//---------------------------------------------------------------------------------------
void CEnemyGenerator::ResetMakeEnemyNum ()
{
	m_FieldEnemyCounter = 0;
}
//---------------------------------------------------------------------------------------
//フィールド上にランダムにエネミーを生成する
//---------------------------------------------------------------------------------------
void CEnemyGenerator::MakeEnemy ()
{
	//生成数を設定
	int nMakeNum = rand()%8 + 2;

	//デバッグ用
	if (DebugMode)
		nMakeNum = 0;

	//階層数を取得
	int Hierarchy = m_pMapData->GetHierarchieNum();

	//階層数が最終階層ならば、生成数を一体に設定
	if (Hierarchy == GameClearNum)
	{
		nMakeNum = 1;
	}

	//生成
	for(int i = 0;i < nMakeNum;i++)
	{
		CEnemy::Generation(this);
		//生成数加算
		m_FieldEnemyCounter++;
	}
}