#pragma once

//ユニットの管理を行う。

//インクルード
#include<map>
#include<list>
#include<vector>


class CUnit;


typedef std::vector<CUnit*>			UNIT_LIST;	//ユニットのリスト
typedef std::map<int, UNIT_LIST>	UNIT_MAP;	//ユニットのリスト+ID
typedef std::pair<int, UNIT_LIST>	UNIT_PAIR;	//ユニットリストペア

class CUnitManager
{
private:
	//変数宣言

	//シングルトン
	static UNIT_MAP* m_pUnitManager;
	static int		m_NowProcUnitID;	//現在ターンステート処理中のユニット番号

	static CUnit*	m_pPlayer;			//プレイヤーポインター

	static bool				m_bMoveCanFlg;					//移動可能フラグ


	CUnitManager();		//コンストラクタ
	~CUnitManager();	//デストラクタ
public:

	//関数宣言
	static void Init();			//初期化
	static void Fin();			//終了処理
	static void Update();		//更新
	static void Draw();			//描画

	//エネミーの削除
	static void EnemyDelete();

	//ユニットマネージャーの作成
	static void Create();
	//ユニットマネージャーの削除
	static void Destroy();

	//マネージャーのポインタを渡す
	UNIT_MAP* GetPointer();

	//プレイヤーのポインタを取得する
	static void SetPlayerPointer();
	//プレイヤーのレベルを渡す
	static int GetPlayerLevel();

	//ユニット全ての行動可能フラグを変更する
	static void ChangeMoveCanFlg(bool ChangeFlg);

	//-----ユニット関連の操作-----
	//ユニットを追加する
	static void Add(int UnitID,CUnit* pUnit);
	//ユニットを削除する
	static void Del(int UnitID);
	//ユニットを探索する
	static CUnit*  Find(int UnitID);

	//-----プレイヤーの情報を渡す-----
	static int GetPlayerPosX();
	static int GetPlayerPosZ();

};

