//エネミークラス　定義
#pragma once

#include "Unit.h"
#include "define.h"

//A*アルゴリズムで使用する際に用いる構造体
struct AStar
{
	bool		m_bMapStatus;		//マップの状態を保存
	int			m_nCost;			//スタート位置から自身の位置までの移動コスト
	int			m_nHeuristic;		//自身の位置から目標地点までのコスト
	int			m_nScore;			//コストとヒューリスティック値の合計値

	int			m_nChildNum;		//どれだけの子供を持っているか

	D3DXVECTOR2	m_ChildPos[MOVEVEC];//自身の子供の位置(8方向分確保)
	D3DXVECTOR2	m_ParentPos;		//自身の親のポインタ(1つのみ)
};

class CEnemy :
	public CUnit
{
private:
	static CMeshObj*	m_Player;						//プレイヤー位置情報取得用

	static int			m_nEnemyData[STATES_MAX];		//ステータス情報格納
	static int			m_nLevelUpData[UPSTATES_MAX];	//レベルアップ時上昇ステータス情報格納

	static bool			m_bStatesLoad;					//ステータス情報ファイル読み込みフラグ
	static bool			m_bLevelUpLoad;					//レベルアップ時のステータス上昇値ファイル読み込み完了フラグ

	static bool			m_bDelete;						//全エネミーの削除フラグ

	bool				m_bMakeSuccess;					//エネミーの生成成功フラグ
	
	static AStar		m_AStarData[MAP_SIZE][MAP_SIZE];//A*アルゴリズムに使用する構造体
public:
	CEnemy(CGameScene* pScene);							//コンストラクタ
	~CEnemy(void);										//デストラクタ

	static void Generation(CMeshObj *pGenerator);		//生成

	void Update();										//更新

	static void PlayerPointInit();						//プレイヤーポインタの初期化

	//ステート別更新
	void InputUpdate();									//入力更新

	void MoveUpdate();									//移動更新

	void ActUpdate();									//アクション更新

	void ItemUpdate();									//アイテム使用更新

	void TurnEndUpdate();								//ターン終了更新

	void A_StarMove();									//A*アルゴリズムを用いて移動を行う

	//全エネミーの削除フラグを立てる
	static void DeleteEnemy()	{m_bDelete = true;}

	//エネミーを生成可能にする(削除フラグを元に戻す)
	static void CanGeneration()	{m_bDelete = false;}

	//A*アルゴリズム用構造体の初期化を行う
	void InitAStarData();

	//指定された位置周囲の移動可能な場所を検索し、自身の子供として設定する
	void SearchPosition(int PosX,int PosZ);

	//A*アルゴリズムにおける、値を計算する
	int AStarCalculator(int NowPosX,int NowPosZ,int GoalPosX,int GoalPosZ);

	//A*アルゴリズムの構造体のデータを設定する
	void ASarSetData(int NowPosX,int NowPosZ,int );
};

