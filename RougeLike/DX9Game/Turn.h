#pragma once

//ターンクラス定義

#include "define.h"
class CTurn
{
public:
	//1ステートの時間
	#define STATE_TIME	7.0f

	//ターンの回り方
	enum UnitTurnState
	{
		UNIT_TURN_PLAYER = 0,	//プレイヤーのターン
		UNIT_TURN_PARTY,		//パーティ
		UNIT_TURN_ENEMY,		//エネミーのターン
		UNIT_TURN_MAX,
	};

	//戦闘ステート
	enum BattleState
	{
		BATTLE_STATE_GO = 0,			//相手の方向に突撃する(攻撃アニメーション)
		BATTLE_STATE_RETURN,			//相手の位置からもとに戻る
		BATTLE_STATE_SEARCH,			//戦闘相手を探す
		BATTLE_STATE_HIT,				//相手に攻撃が当たった(エフェクト挿入)
		BATTLE_STATE_FLASHING,			//相手の描画をつけたり消したり…
		BATTLE_STATE_WINDOW,			//メッセージウインドウにメッセージを送る
		BATTLE_STATE_DAMAGE,			//相手のHPをダメージ分減らす
		BATTLE_STATE_END,				//戦闘終了(ターンステートの更新)
		BATTLE_STATE_MAX,				//ステート最大数
	};

	//ゲームステート
	enum GameState
	{

		GAME_STATE_STAND_BY = 0,			//入力待ち
		GAME_STATE_ITEM_USE,			//アイテム使用
		GAME_STATE_MOVE,				//移動中
		GAME_STATE_ACT,					//行動中
		GAME_STATE_ATTACK,				//攻撃
		GAME_STATE_TURN_END,			//何も行動しない
		GAME_STATE_MAX
	};

	CTurn(void);										//コンストラクタ
	~CTurn(void);										//デストラクタ

	static void Init ();										//初期化
	void Fin  ();												//終了

	//-----ターンステート関連-----
	static void State_Advance(int nStateNumber);				//ステートを進める

	static int GetState ()	{return m_State;}					//ステートの状態を返却する。


	//-----戦闘ステート関連-----
	static void BattleState_Advance(int nBattleStateNumber);	//戦闘ステートを進める

	static int  GetBattleState(){return m_BattleState;}			//現在の戦闘ステート状態を取得

	//戦闘ステートの初期化
	static void BattleState_Init(){m_BattleState = BATTLE_STATE_GO;}

	//ステートの経過時間を加算
	static void TimeStateAdd(){m_StateTime ++;}

	//ステートの経過時間をリセット
	static void TimeStateReset(){m_StateTime = 0;}

	//ステートの現在の経過時間を返却
	static int GetStateTime()	{return m_StateTime;}

	//現在のターンユニットを返す
	static UnitTurnState GetUnitTurn()
	{
		return m_UnitTurnState;
	}
	//ターンの情報を変更する
	static void ChangeUnitState(UnitTurnState ChangeData)
	{
		m_UnitTurnState = ChangeData;
	}

private:
	static int m_State;									//ターンの状態を格納

	static int m_BattleState;							//戦闘時のステート情報

	static int m_nSelectState_Num[GAME_STATE_MAX];		//ステートごとのユニットの選択数

	static int m_StateTime;								//1ステートの時間

	static UnitTurnState m_UnitTurnState;				//現在は誰のターンか
};

