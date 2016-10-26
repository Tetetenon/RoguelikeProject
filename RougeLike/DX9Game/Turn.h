#pragma once

//�^�[���N���X��`

#include "define.h"


//�Q�[���X�e�[�g
enum GameState
{

	GAME_STATE_STAND_BY_PLAYER = 0,	//���͑҂�(�v���C���[)
	GAME_STATE_STAND_BY_OTHER,		//���͑҂�
	GAME_STATE_ITEM_USE,				//�A�C�e���g�p
	GAME_STATE_MOVE,					//�ړ���
	GAME_STATE_ACT,					//�s����
	GAME_STATE_ATTACK,				//�U��
	GAME_STATE_TURN_END,				//�����s�����Ȃ�
	GAME_STATE_MAX
};

//�퓬�X�e�[�g
enum BattleState
{
	BATTLE_STATE_GO = 0,				//����̕����ɓˌ�����(�U���A�j���[�V����)
	BATTLE_STATE_RETURN,			//����̈ʒu������Ƃɖ߂�
	BATTLE_STATE_SEARCH,			//�퓬�����T��
	BATTLE_STATE_HIT,				//����ɍU������������(�G�t�F�N�g�}��)
	BATTLE_STATE_FLASHING,			//����̕`����������������c
	BATTLE_STATE_WINDOW,			//���b�Z�[�W�E�C���h�E�Ƀ��b�Z�[�W�𑗂�
	BATTLE_STATE_DAMAGE,			//�����HP���_���[�W�����炷
	BATTLE_STATE_END,				//�퓬�I��(�^�[���X�e�[�g�̍X�V)
	BATTLE_STATE_MAX,				//�X�e�[�g�ő吔
};

//1�X�e�[�g�̎���
#define STATE_TIME	7.0f


class CTurn
{
private:
	static int m_State;									//�^�[���̏�Ԃ��i�[

	static int m_BattleState;							//�퓬���̃X�e�[�g���

	static int m_nSelectState_Num[GAME_STATE_MAX];		//�X�e�[�g���Ƃ̃��j�b�g�̑I��

	static int m_StateTime;								//1�X�e�[�g�̎���
public:
	CTurn(void);										//�R���X�g���N�^
	~CTurn(void);										//�f�X�g���N�^

	static void Init ();										//������
	void Fin  ();												//�I��

	//-----�^�[���X�e�[�g�֘A-----
	static void State_Advance(int nStateNumber);				//�X�e�[�g��i�߂�

	static int GetState ()	{return m_State;}					//�X�e�[�g�̏�Ԃ�ԋp����B


	//-----�퓬�X�e�[�g�֘A-----
	static void BattleState_Advance(int nBattleStateNumber);	//�퓬�X�e�[�g��i�߂�

	static int  GetBattleState(){return m_BattleState;}			//���݂̐퓬�X�e�[�g��Ԃ��擾

	//�퓬�X�e�[�g�̏�����
	static void BattleState_Init(){m_BattleState = BATTLE_STATE_GO;}

	//-----�^�[���X�e�[�g�J�E���g�֘A-----
	//�w��X�e�[�g�̑I�����Ă��郆�j�b�g�������Z
	static void AddCount (int nState)	{m_nSelectState_Num[nState] ++;}

	//�w��X�e�[�g�̑I�����Ă��郆�j�b�g�������Z
	static void SumCount (int nState)	{m_nSelectState_Num[nState] --;}

	//�w��X�e�[�g�̑I�����Ă��郆�j�b�g�̐���Ԃ�
	static int GetStateSelectNum (int nState) {return m_nSelectState_Num[nState];}

	//�w�肵�Ă���X�e�[�g�̑I�����Ă��郆�j�b�g��������
	static void StateCountReset (int nState) {m_nSelectState_Num[nState] = 0;}

	//�X�e�[�g�̌o�ߎ��Ԃ����Z
	static void TimeStateAdd(){m_StateTime ++;}

	//�X�e�[�g�̌o�ߎ��Ԃ����Z�b�g
	static void TimeStateReset(){m_StateTime = 0;}

	//�X�e�[�g�̌��݂̌o�ߎ��Ԃ�ԋp
	static int GetStateTime()	{return m_StateTime;}
};

