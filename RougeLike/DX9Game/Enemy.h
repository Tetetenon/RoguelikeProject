//�G�l�~�[�N���X�@��`
#pragma once

#include "Unit.h"
#include "define.h"

//A*�A���S���Y���Ŏg�p����ۂɗp����\����
struct AStar
{
	bool		m_bMapStatus;		//�}�b�v�̏�Ԃ�ۑ�
	int			m_nCost;			//�X�^�[�g�ʒu���玩�g�̈ʒu�܂ł̈ړ��R�X�g
	int			m_nHeuristic;		//���g�̈ʒu����ڕW�n�_�܂ł̃R�X�g
	int			m_nScore;			//�R�X�g�ƃq���[���X�e�B�b�N�l�̍��v�l

	int			m_nChildNum;		//�ǂꂾ���̎q���������Ă��邩

	D3DXVECTOR2	m_ChildPos[MOVEVEC];//���g�̎q���̈ʒu(8�������m��)
	D3DXVECTOR2	m_ParentPos;		//���g�̐e�̃|�C���^(1�̂�)
};

class CEnemy :
	public CUnit
{
private:
	static CMeshObj*	m_Player;						//�v���C���[�ʒu���擾�p

	static int			m_nEnemyData[STATES_MAX];		//�X�e�[�^�X���i�[
	static int			m_nLevelUpData[UPSTATES_MAX];	//���x���A�b�v���㏸�X�e�[�^�X���i�[

	static bool			m_bStatesLoad;					//�X�e�[�^�X���t�@�C���ǂݍ��݃t���O
	static bool			m_bLevelUpLoad;					//���x���A�b�v���̃X�e�[�^�X�㏸�l�t�@�C���ǂݍ��݊����t���O

	static bool			m_bDelete;						//�S�G�l�~�[�̍폜�t���O

	bool				m_bMakeSuccess;					//�G�l�~�[�̐��������t���O
	
	static AStar		m_AStarData[MAP_SIZE][MAP_SIZE];//A*�A���S���Y���Ɏg�p����\����
public:
	CEnemy(CGameScene* pScene);							//�R���X�g���N�^
	~CEnemy(void);										//�f�X�g���N�^

	static void Generation(CMeshObj *pGenerator);		//����

	void Update();										//�X�V

	static void PlayerPointInit();						//�v���C���[�|�C���^�̏�����

	//�X�e�[�g�ʍX�V
	void InputUpdate();									//���͍X�V

	void MoveUpdate();									//�ړ��X�V

	void ActUpdate();									//�A�N�V�����X�V

	void ItemUpdate();									//�A�C�e���g�p�X�V

	void TurnEndUpdate();								//�^�[���I���X�V

	void A_StarMove();									//A*�A���S���Y����p���Ĉړ����s��

	//�S�G�l�~�[�̍폜�t���O�𗧂Ă�
	static void DeleteEnemy()	{m_bDelete = true;}

	//�G�l�~�[�𐶐��\�ɂ���(�폜�t���O�����ɖ߂�)
	static void CanGeneration()	{m_bDelete = false;}

	//A*�A���S���Y���p�\���̂̏��������s��
	void InitAStarData();

	//�w�肳�ꂽ�ʒu���͂̈ړ��\�ȏꏊ���������A���g�̎q���Ƃ��Đݒ肷��
	void SearchPosition(int PosX,int PosZ);

	//A*�A���S���Y���ɂ�����A�l���v�Z����
	int AStarCalculator(int NowPosX,int NowPosZ,int GoalPosX,int GoalPosZ);

	//A*�A���S���Y���̍\���̂̃f�[�^��ݒ肷��
	void ASarSetData(int NowPosX,int NowPosZ,int );
};

