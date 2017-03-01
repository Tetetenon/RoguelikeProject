//エネミークラス　定義
#pragma once

#include "Unit.h"
#include "define.h"

//エネミーのタイプを記述
enum EnemyType
{
	TYPE_BEE = 0,
	TYPE_BEAR,
	TYPE_WOLF,
	TYPE_BOSS,
	TYPE_MAX,
};

//敵のプレイヤー視認距離
const float VisibilityDistance[TYPE_MAX] =
{
	2.0f,	//クマの視認距離
	3.0f,	//蜂の視認距離
	5.0f,	//狼の視認距離
	10.0f,	//ボスの視認距離
};


class CEnemy :
	public CUnit
{
private:
	static int			m_nEnemyData[STATES_MAX];		//ステータス情報格納
	static int			m_nLevelUpData[UPSTATES_MAX];	//レベルアップ時上昇ステータス情報格納

	static bool			m_bStatesLoad;					//ステータス情報ファイル読み込みフラグ
	static bool			m_bLevelUpLoad;					//レベルアップ時のステータス上昇値ファイル読み込み完了フラグ
	bool				m_bMakeSuccess;					//エネミーの生成成功フラグ
	int					m_nEnemyType;					//エネミーのタイプ(はち、クマ、…)
	bool				m_bPlayerFindFlg;				//プレイヤーを見つけた状態か


	//移動目標地点を保存する
	int					m_TergetPositionX;
	int					m_TergetPositionZ;
public:
	CEnemy(CGameScene* pScene);							//コンストラクタ
	~CEnemy(void);										//デストラクタ

	static void Generation(CMeshObj *pGenerator);		//生成

	void Update();										//更新

	//ステート別更新
	void InputUpdate();									//入力更新

	void MoveUpdate();									//移動更新

	void ActUpdate();									//アクション更新

	void ItemUpdate();									//アイテム使用更新

	void TurnEndUpdate();								//ターン終了更新

	bool A_StarMove();									//A*アルゴリズムを用いて移動を行う
	void TergetPositionSet();							//ターゲットとなる地点を設定する
};

