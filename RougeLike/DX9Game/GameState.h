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
	static int State;	//�X�e�[�g�ԍ�
	static int OldState;
public:
	CGameState(void);
	~CGameState(void);

	static void Update();		//�X�V
	static void StateCheck()	{OldState = State;}
	static int GetState(){return State;}	//�󋵎擾
	static int GetOldState(){return OldState;}
};

