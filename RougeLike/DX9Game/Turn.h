#pragma once

//�^�[���N���X��`

#include "define.h"
class CTurn
{
public:
	//1�X�e�[�g�̎���
	#define STATE_TIME	7.0f

	//�^�[���̉���
	enum UnitTurnState
	{
		UNIT_TURN_PLAYER = 0,	//�v���C���[�̃^�[��
		UNIT_TURN_PARTY,		//�p�[�e�B
		UNIT_TURN_ENEMY,		//�G�l�~�[�̃^�[��
		UNIT_TURN_MAX,
	};

	//�퓬�X�e�[�g
	enum BattleState
	{
		BATTLE_STATE_GO = 0,			//����̕����ɓˌ�����(�U���A�j���[�V����)
		BATTLE_STATE_RETURN,			//����̈ʒu������Ƃɖ߂�
		BATTLE_STATE_SEARCH,			//�퓬�����T��
		BATTLE_STATE_HIT,				//����ɍU������������(�G�t�F�N�g�}��)
		BATTLE_STATE_FLASHING,			//����̕`����������������c
		BATTLE_STATE_WINDOW,			//���b�Z�[�W�E�C���h�E�Ƀ��b�Z�[�W�𑗂�
		BATTLE_STATE_DAMAGE,			//�����HP���_���[�W�����炷
		BATTLE_STATE_END,				//�퓬�I��(�^�[���X�e�[�g�̍X�V)
		BATTLE_STATE_MAX,				//�X�e�[�g�ő吔
	};

	//�Q�[���X�e�[�g
	enum GameState
	{

		GAME_STATE_STAND_BY = 0,			//���͑҂�
		GAME_STATE_ITEM_USE,			//�A�C�e���g�p
		GAME_STATE_MOVE,				//�ړ���
		GAME_STATE_ACT,					//�s����
		GAME_STATE_ATTACK,				//�U��
		GAME_STATE_TURN_END,			//�����s�����Ȃ�
		GAME_STATE_MAX
	};

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

	//�X�e�[�g�̌o�ߎ��Ԃ����Z
	static void TimeStateAdd(){m_StateTime ++;}

	//�X�e�[�g�̌o�ߎ��Ԃ����Z�b�g
	static void TimeStateReset(){m_StateTime = 0;}

	//�X�e�[�g�̌��݂̌o�ߎ��Ԃ�ԋp
	static int GetStateTime()	{return m_StateTime;}

	//���݂̃^�[�����j�b�g��Ԃ�
	static UnitTurnState GetUnitTurn()
	{
		return m_UnitTurnState;
	}
	//�^�[���̏���ύX����
	static void ChangeUnitState(UnitTurnState ChangeData)
	{
		m_UnitTurnState = ChangeData;
	}

private:
	static int m_State;									//�^�[���̏�Ԃ��i�[

	static int m_BattleState;							//�퓬���̃X�e�[�g���

	static int m_nSelectState_Num[GAME_STATE_MAX];		//�X�e�[�g���Ƃ̃��j�b�g�̑I��

	static int m_StateTime;								//1�X�e�[�g�̎���

	static UnitTurnState m_UnitTurnState;				//���݂͒N�̃^�[����
};

