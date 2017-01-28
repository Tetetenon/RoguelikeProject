#pragma once

//エネミーの管理を行う

//インクルード
#include<map>
#include<list>
#include<vector>
class CUnit;

typedef std::vector<CUnit*>			UNIT_LIST;	//ユニットのリスト
typedef std::map<int, UNIT_LIST>	UNIT_MAP;	//ユニットのリスト+ID
typedef std::pair<int, UNIT_LIST>	UNIT_PAIR;	//ユニットリストペア

class CEnemyManager
{
private:
	//シングルトン
	static UNIT_MAP* m_pEnemyManager;

	static int m_NowProcUnitID;			//現在攻撃処理を行っているエネミーのIDを保存


	//関数宣言
	CEnemyManager();						//コンストラクタ
	~CEnemyManager();					//デストラクタ
public:

	//関数宣言
	static void Init();					//初期化
	static void Fin();					//終了処理
	static void WaitUpdate();			//待機の更新
	static void TurnUpdate();			//ターンの更新	
	static void Draw();					//描画

	//マネージャーの作成
	static void Create();

	//マネージャーの削除
	static void Destroy();

	//リスト関連操作
	//ユニットの追加
	static void Add(int UnitID, CUnit* pUnit);
	//ユニットの削除
	static void Del(int UnitID);
	//ユニットの探索
	static CUnit* Find(int UnitID);
};

