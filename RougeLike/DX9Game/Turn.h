#pragma once

//ターンクラス定義

#include "define.h"


//ゲームステート
enum GameState
{

	GAME_STATE_STAND_BY_PLAYER = 0,	//入力待ち(プレイヤー)
	GAME_STATE_STAND_BY_OTHER,		//入力待ち
	GAME_STATE_ITEM_USE,				//アイテム使用
	GAME_STATE_MOVE,					//移動中
	GAME_STATE_ACT,					//行動中
	GAME_STATE_ATTACK,				//攻撃
	GAME_STATE_TURN_END,				//何も行動しない
	GAME_STATE_MAX
};

//戦闘ステート
enum BattleState
{
	BATTLE_STATE_GO = 0,				//相手の方向に突撃する(攻撃アニメーション)
	BATTLE_STATE_RETURN,			//相手の位置からもとに戻る
	BATTLE_STATE_SEARCH,			//戦闘相手を探す
	BATTLE_STATE_HIT,				//相手に攻撃が当たった(エフェクト挿入)
	BATTLE_STATE_FLASHING,			//相手の描画をつけたり消したり…
	BATTLE_STATE_WINDOW,			//メッセージウインドウにメッセージを送る
	BATTLE_STATE_DAMAGE,			//相手のHPをダメージ分減らす
	BATTLE_STATE_END,				//戦闘終了(ターンステートの更新)
	BATTLE_STATE_MAX,				//ステート最大数
};

//1ステートの時間
#define STATE_TIME	7.0f


class CTurn
{
private:
	static int m_State;									//ターンの状態を格納

	static int m_BattleState;							//戦闘時のステート情報

	static int m_nSelectState_Num[GAME_STATE_MAX];		//ステートごとのユニットの選択数

	static int m_StateTime;								//1ステートの時間
public:
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

	//-----ターンステートカウント関連-----
	//指定ステートの選択しているユニット数を加算
	static void AddCount (int nState)	{m_nSelectState_Num[nState] ++;}

	//指定ステートの選択しているユニット数を減算
	static void SumCount (int nState)	{m_nSelectState_Num[nState] --;}

	//指定ステートの選択しているユニットの数を返す
	static int GetStateSelectNum (int nState) {return m_nSelectState_Num[nState];}

	//指定しているステートの選択しているユニット数を消去
	static void StateCountReset (int nState) {m_nSelectState_Num[nState] = 0;}

	//ステートの経過時間を加算
	static void TimeStateAdd(){m_StateTime ++;}

	//ステートの経過時間をリセット
	static void TimeStateReset(){m_StateTime = 0;}

	//ステートの現在の経過時間を返却
	static int GetStateTime()	{return m_StateTime;}
};

