//�G�l�~�[�N���X�@��`
#pragma once

#include "Unit.h"
#include "define.h"

//�G�l�~�[�̃^�C�v���L�q
enum EnemyType
{
	TYPE_BEE = 0,
	TYPE_BEAR,
	TYPE_WOLF,
	TYPE_BOSS,
	TYPE_MAX,
};

//�G�̃v���C���[���F����
const float VisibilityDistance[TYPE_MAX] =
{
	2.0f,	//�N�}�̎��F����
	3.0f,	//�I�̎��F����
	5.0f,	//�T�̎��F����
	10.0f,	//�{�X�̎��F����
};


class CEnemy :
	public CUnit
{
private:
	static int			m_nEnemyData[STATES_MAX];		//�X�e�[�^�X���i�[
	static int			m_nLevelUpData[UPSTATES_MAX];	//���x���A�b�v���㏸�X�e�[�^�X���i�[

	static bool			m_bStatesLoad;					//�X�e�[�^�X���t�@�C���ǂݍ��݃t���O
	static bool			m_bLevelUpLoad;					//���x���A�b�v���̃X�e�[�^�X�㏸�l�t�@�C���ǂݍ��݊����t���O
	bool				m_bMakeSuccess;					//�G�l�~�[�̐��������t���O
	int					m_nEnemyType;					//�G�l�~�[�̃^�C�v(�͂��A�N�}�A�c)
	bool				m_bPlayerFindFlg;				//�v���C���[����������Ԃ�


	//�ړ��ڕW�n�_��ۑ�����
	int					m_TergetPositionX;
	int					m_TergetPositionZ;
public:
	CEnemy(CGameScene* pScene);							//�R���X�g���N�^
	~CEnemy(void);										//�f�X�g���N�^

	static void Generation(CMeshObj *pGenerator);		//����

	void Update();										//�X�V

	//�X�e�[�g�ʍX�V
	void InputUpdate();									//���͍X�V

	void MoveUpdate();									//�ړ��X�V

	void ActUpdate();									//�A�N�V�����X�V

	void ItemUpdate();									//�A�C�e���g�p�X�V

	void TurnEndUpdate();								//�^�[���I���X�V

	bool A_StarMove();									//A*�A���S���Y����p���Ĉړ����s��
	void TergetPositionSet();							//�^�[�Q�b�g�ƂȂ�n�_��ݒ肷��
};

