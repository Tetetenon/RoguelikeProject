#include "EnemyGenerator.h"
#include "Enemy.h"
#include "Input.h"

#include "Turn.h"
#include "MapData.h"

#define MAKEPERCENTAGE 15

//静的メンバ実体定義
int CEnemyGenerator::m_FieldEnemyCounter = 0;			//フィールド上のエネミーの数をカウントする
int CEnemyGenerator::m_MaxFieldEnemy;				//フィールドのエネミーの最大生成数を設定
bool CEnemyGenerator::m_bMakeFlg = false;			//エネミー生成完了フラグ

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
//初期化
//---------------------------------------------------------------------------------------
void CEnemyGenerator::Init()
{
	//親クラスの初期化呼び出し
	CMeshObj::Init();

}
//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CEnemyGenerator::Fin()
{
	//親クラスの終了処理呼び出し
	CMeshObj::Fin();
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CEnemyGenerator::Update()
{
	//階層数を取得
	int Hierarchy = CMapData::GetHierarchieNum();

	//ターンステートが一定のステートの際、エネミーを確率で生成する
	if(CTurn::GetState() == CTurn::GAME_STATE_STAND_BY && Hierarchy != GameClearNum)
	{
		int nRand = rand()%100;
		//生成確立5%かつフィールドに配置できる最大エネミー数に到達していない
		if(nRand < MAKEPERCENTAGE && m_FieldEnemyCounter < m_MaxFieldEnemy && !m_bMakeFlg)
		{
			//エネミーの生成
			CEnemy::Generation(this);
			//生成数加算
			m_FieldEnemyCounter++;
		}

		//このターンでの生成確認処理を完了した
		m_bMakeFlg = true;
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
	int nMakeNum = rand()%8;

	//階層数を取得
	int Hierarchy = CMapData::GetHierarchieNum();

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