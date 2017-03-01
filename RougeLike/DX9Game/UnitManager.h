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
	static CUnitManager* m_pManager;
	UNIT_MAP* m_pUnitManager;

	CUnit*	m_pPlayer;			//プレイヤーポインター

	bool		m_bMoveCanFlg;		//移動可能フラグ
	int		m_nMakeNumber;		//ユニットを何体生成したか。


	CUnitManager();		//コンストラクタ
	~CUnitManager();	//デストラクタ
public:

	//関数宣言
	void Init();		//初期化
	void Fin();			//終了処理
	void Update();		//更新
	void Draw();		//描画

	void EnemyDelete();	//エネミーの削除

	//ユニットマネージャーの作成
	static void Create();
	//ユニットマネージャーの削除
	static void Delete();

	//マネージャーのポインタを渡す
	static CUnitManager* GetPointer();

	//プレイヤーのポインタを取得する
	void SetPlayerPointer();
	//プレイヤーのレベルを渡す
	int GetPlayerLevel();

	//ユニット全ての行動可能フラグを変更する
	void ChangeMoveCanFlg(bool ChangeFlg);

	//-----ユニット関連の操作-----
	//ユニットを追加する
	void Add(int UnitID,CUnit* pUnit);
	//ユニットを削除する
	void Del(int UnitID);
	//ユニットを探索する
	CUnit*  Find(int UnitID);

	//-----プレイヤーの情報を渡す-----
	CUnit* GetPlayerPointer();
	int GetPlayerPosX();
	int GetPlayerPosZ();

	bool GetMoveFlg()
	{
		return m_bMoveCanFlg;
	}

	int GetMakeNum()
	{
		return m_nMakeNumber;
	}

	void AddMakeNum(int nAddNum)
	{
		m_nMakeNumber += nAddNum;
	}
};

