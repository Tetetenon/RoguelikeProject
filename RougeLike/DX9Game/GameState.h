#pragma once

enum
{
	STATE_TITLE = 0,
	STATE_GAME,
	STATE_RESUALT,
	STATE_MAX
};

class CGameState
{
private:
	static int State;	//ステート番号
	static int OldState;
public:
	CGameState(void);
	~CGameState(void);

	static void Update();		//更新
	static void StateCheck()	{OldState = State;}
	static int GetState(){return State;}	//状況取得
	static int GetOldState(){return OldState;}
};

