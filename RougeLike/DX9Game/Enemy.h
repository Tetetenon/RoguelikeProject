//�G�l�~�[�N���X�@��`
#pragma once

#include "Unit.h"
#include "define.h"


class CEnemy :
	public CUnit
{
private:
	static int			m_nEnemyData[STATES_MAX];		//�X�e�[�^�X���i�[
	static int			m_nLevelUpData[UPSTATES_MAX];	//���x���A�b�v���㏸�X�e�[�^�X���i�[

	static bool			m_bStatesLoad;					//�X�e�[�^�X���t�@�C���ǂݍ��݃t���O
	static bool			m_bLevelUpLoad;					//���x���A�b�v���̃X�e�[�^�X�㏸�l�t�@�C���ǂݍ��݊����t���O
	bool				m_bMakeSuccess;					//�G�l�~�[�̐��������t���O
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
};

