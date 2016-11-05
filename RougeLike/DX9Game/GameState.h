#pragma once

enum
{
	STATE_TITLE = 0,		//タイトル
	STATE_GAME,				//ゲームメイン
	STATE_GAMECLEAR,		//ゲームクリア
	STATE_GAMEOVER,			//ゲームオーバー
	STATE_MAX
};

class CGameState
{
private:
	static int m_nState;	//ステート番号
	static int m_nOldState;
public:
	CGameState(void);
	~CGameState(void);

	//ステートの状況を更新する
	static void StateUpdate(int State);
	static void StateCheck()	{m_nOldState = m_nState;}
	static int GetState(){return m_nState;}	//状況取得
	static int GetOldState(){return m_nOldState;}
};

