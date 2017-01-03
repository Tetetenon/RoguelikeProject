//エネミークラス　定義
#pragma once

#include "Unit.h"
#include "define.h"


class CEnemy :
	public CUnit
{
private:
	static int			m_nEnemyData[STATES_MAX];		//ステータス情報格納
	static int			m_nLevelUpData[UPSTATES_MAX];	//レベルアップ時上昇ステータス情報格納

	static bool			m_bStatesLoad;					//ステータス情報ファイル読み込みフラグ
	static bool			m_bLevelUpLoad;					//レベルアップ時のステータス上昇値ファイル読み込み完了フラグ
	bool				m_bMakeSuccess;					//エネミーの生成成功フラグ
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
};

