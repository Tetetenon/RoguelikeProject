//エネミークラス　定義
#pragma once

#include "Unit.h"
#include "define.h"


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

	bool A_StarMove();									//A*アルゴリズムを用いて移動を行う

	//全エネミーの削除フラグを立てる
	static void DeleteEnemy()	{m_bDelete = true;}

	//エネミーを生成可能にする(削除フラグを元に戻す)
	static void CanGeneration()	{m_bDelete = false;}
};

