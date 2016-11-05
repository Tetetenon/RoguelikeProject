#pragma once

enum
{
	STATE_TITLE = 0,		//�^�C�g��
	STATE_GAME,				//�Q�[�����C��
	STATE_GAMECLEAR,		//�Q�[���N���A
	STATE_GAMEOVER,			//�Q�[���I�[�o�[
	STATE_MAX
};

class CGameState
{
private:
	static int m_nState;	//�X�e�[�g�ԍ�
	static int m_nOldState;
public:
	CGameState(void);
	~CGameState(void);

	//�X�e�[�g�̏󋵂��X�V����
	static void StateUpdate(int State);
	static void StateCheck()	{m_nOldState = m_nState;}
	static int GetState(){return m_nState;}	//�󋵎擾
	static int GetOldState(){return m_nOldState;}
};

