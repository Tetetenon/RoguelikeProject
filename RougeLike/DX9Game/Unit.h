//���j�b�g�N���X�̒�`
#pragma once

#include "MeshObj.h"
#include "define.h"
#include "FieldItem.h"
#include "Circle.h"
#include "ItemWindow.h"
#include "EquipmentWindow.h"
#include "TrickWindow.h"
#include "LevelUp.h"
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>

//�s���ɂ����鎞��
#define ACTION_TIME	0.6f

//�����x�ő�l
#define MAX_SATIETY	100

//�o���l�ő�l
#define MAX_EXP		100

//�����ł���ő吔
#define EQUIPMENTMAX 5

//�X�e�[�^�X��
enum UNITSTATES
{
	STATES_MAX_HP = 0,
	STATES_HP,			//HP
	STATES_AT,			//�U����
	STATES_DF,			//�h���
	STATES_POS_X,		//�z���̈ʒuX
	STATES_POS_Z,		//�z���̈ʒuY
	STATES_EXP,			//�o���l
	STATES_XP,			//�|���ē�����o���l
	STATES_MAX
};

//���x���A�b�v�ŏ㏸����X�e�[�^�X�ꗗ
enum UNIT_UP_STATES
{
	UPSTATES_MAX_HP = 0,	//HP�ő�l
	UPSTATES_AT,			//�U����
	UPSTATES_DF,			//�h���
	UPSTATES_MAX
};

//��Ԉُ�p������
#define STATE_TURN_DEFINE 5	//��{�I�ɏ�Ԉُ�̌p�����Ԃ�5�^�[��
#define STATE_TURN_WINCE  1 //���݂̌p�����Ԃ�1�^�[��

class CGameScene;

class CUnit :
	public CMeshObj
{
protected:

	//-----���j�b�g�X�e�[�^�X-----
	char					m_szName[5];					//���O
	int						m_nID;							//���j�b�g�̎�ގ���ID
	int						m_nUnitNumber;					//���j�b�g����ӂɒ�߂�ԍ�
	static int				m_nMakeNumber;					//���j�b�g�����̐����������B
	int						m_nLevel;						//���x��
	int						m_nHP;							//�̗�
	int						m_nMaxHP;						//�̗͍ő�l
	int						m_nAttack;						//�U����
	int						m_nDefence;						//�h���
	int						m_nExp;							//�o���l�~�ϒl
	int						m_nXp;							//�|���ē�����o���l
	int						m_nMoney;						//����
	int						m_nSatiety;						//�����x

	int						m_nTrickNumber;					//������g�p����Z�̔ԍ�

	static int				m_nAttackNumber;				//�U�����s���Ă��郆�j�b�g�̔ԍ�

	//���x���A�b�v���X�e�[�^�X�㏸�l
	int						m_nHPUpNum;						//���x���A�b�v��HP�㏸�l
	int						m_nAttackUpNum;					//���x���A�b�v���U���͏㏸�l
	int						m_nDefenceUpNum;				//���x���A�b�v���h��͏㏸�l


	bool					m_bSurvival;					//�����t���O
	D3DXVECTOR3				m_Pos;							//�ړ���̈ʒu
	bool					m_bDestination;					//�ڕW�n�_���B�t���O
	float					m_fTimer;						//�L�[���͂����Ă���̎��Ԃ𑪒肷��
	bool					m_bDirectionFlg[MaxDirection];	//�����ׂ��������t���O�ŊǗ�����
	D3DXVECTOR3				m_Angle;						//�����p�x
	float					m_fOldAngle;					//���̊p�x

	//-----���X�g�\���p�ϐ�-----
	CUnit*					m_pNextUnit;					//���̃|�C���^
	CUnit*					m_pBackUnit;					//�O�̃|�C���^

	CUnit*					m_pBattleUnit;					//�퓬���s���G�̃|�C���^
	CUnit*					m_pBattleNext;					//�퓬�������Ȃ����j�b�g�̑O�̃��j�b�g���w��
	CUnit*					m_pBattleBack;					//�퓬�������Ȃ����j�b�g�̌�̃��j�b�g���w��

	CFieldItem*				m_pFootItem;					//�����̃A�C�e���̏����i�[����

	int						m_nStateNumber;					//�X�e�[�g�ԍ�
	int						m_nOldStateNumber;				//1�t���[���O�̃X�e�[�g�ԍ�
	CCircle					m_Circle;						//���j�b�g�T�[�N��

	int						m_nState;						//���g�̌��N���
	int						m_nState_Turn;					//���g�̏�Ԉُ�̌p������

	bool					m_bDrawFlg;						//�`��t���O
	int						m_nDrawFlashTime;				//�`��_�Ŏ���
	int						m_nFlashNum;					//�_�ŉ�

	bool					m_bJump;						//�W�����v���[�V�������̏㏸�t���O
	float					m_fJumpPos;						//�W�����v���̈ʒu
	bool					m_bJumpFlg;						//�W�����v�̊J�n�t���O
	int						m_nJumpInterval;				//�W�����v�̊Ԋu
	

	//-----�C���x���g��-----
	CInventory*				m_pInventory;					//�A�C�e���C���x���g��
	CEquipmentInventory*	m_pEquipment;					//�����C���x���g��

	CTrickWindow*			m_pTrickWindow;					//�Z

	CLevelUp*				m_pLevelUp;						//���x���A�b�v�e�N�X�`��
public:
	CUnit(CGameScene* pScene);								//�R���X�g���N�^
	~CUnit(void);											//�f�X�g���N�^
	
	virtual void Init();									//������
	virtual void Fin();										//�I��
	virtual void Update();									//�X�V
	virtual void Draw();									//�`��
	
	//-----���I�u�W�F�N�g�̒T��-----
	CUnit* FindUnit(UINT u_UnitID,CUnit* p = NULL);				//���j�b�g�̒T��
	CFieldItem* ItemFind(UINT u_UnitID,CFieldItem* p = NULL);	//�A�C�e���̒T��

	//�X�e�[�g�ʍX�V
	virtual void InputUpdate();		//���͍X�V
	virtual void MoveUpdate();		//�ړ��X�V
	virtual void ActUpdate();		//�A�N�V�����X�V
	virtual void ItemUpdate();		//�A�C�e���g�p�X�V
	
	//�`��t���O�𔽓]������
	void ChangeDrawFlg()	{m_bDrawFlg = !m_bDrawFlg;}
	//�`��t���O�𗧂Ă�
	void UpDrawFlg()	{m_bDrawFlg = true;}

	//�_�Ŏ��Ԃ����Z������
	void FlashAddTimer()	{m_nDrawFlashTime++;}
	//���݂̓_�Ŏ��Ԃ��擾
	int GetFlashTime(){return m_nDrawFlashTime;}

	//�_�ŉ񐔂̉��Z
	void FlashAddNum()	{m_nFlashNum++;}
	//�_�ŉ񐔂̎擾
	int GetFlashNum()	{return m_nFlashNum;}

	//-----�퓬�X�V�֘A-----
	void AttackUpdate();			//�U���X�V����

	void BattleGo();				//����̕����֓ˌ�������
	void BattleReturn();			//�ˌ���������̈ʒu���玩�g�̖{���̈ʒu�֖߂�
	void AttackSwitch();			//�Z�͈̔͂���A�U�����鑊��𕪊򂳂���

	void BattleCalculation(CUnit* BattleUnit);		//�퓬�Ŕ�������_���[�W�ʂ̎Z�o���s��

	bool FrontFind();				//���ʂ̓G�ɍU��
	bool Side_Right();				//�E�̓G�ɍU��
	bool Side_Left();				//���̓G�ɍU��
	bool BackFind();				//���̓G�ɍU��
	bool SlightRight();				//�΂߉E�̓G�ɍU��
	bool SlightLeft();				//�΂ߍ��̓G�ɍU��
	bool SlightRightBack();			//�΂߉E���̓G�ɍU��
	bool SlightLeftBack();			//�΂ߍ����̓G�ɍU��

	bool FindEnemy(int,int);		//�w�肵���ʒu�ɓG�����邩

	void AttackFront();				//���ʂ̓G�݂̂ɍU�����s��
	void AttackWide();				//�O���O�}�X�̓G�ɍU�����s��
	void AttackAll();				//�����̓G�S�ĂɍU�����s��

	void BattleHit();				//�q�b�g�G�t�F�N�g�𔭐�������
	void BattleFlasing();			//����̕`���_�ł�����
	void BattleWindow();			//���b�Z�[�W�E�C���h�E�Ƀ��b�Z�[�W�𑗂�
	void BattleDamage();			//����ɎZ�o���ꂽ�_���[�W��^����
	void BattleDelete();			//HP�������Ȃ�����A���ŃG�t�F�N�g���o��
	void BattleEnd();				//�퓬�X�e�[�g���Ō�܂ōs�����̂ŁA�o�g���X�e�[�g�������A���g�̃^�[���X�e�[�g�X�V
	virtual void TurnEndUpdate();	//�^�[���I���X�V

	//-----HP�֘A-----
	virtual void DamegeHP (int Damage);		//HP�����炷
	void RecoveryHP (int Recovery);	//HP���񕜂�����
	//-----��Ԉُ�֘A-----
	//��Ԃ�ύX������
	void SetStateAbnormal(int nStateNum);
	//�^�[�����߂̏�Ԉُ�̏������s��
	void TurnStartStateProcessing();

	//���X�g�\���֘A
	CUnit*  GetNextUnit ()					{return m_pNextUnit;}				//���̃|�C���^�̎擾
	void	SetNextUnit (CUnit *pNext)		{m_pNextUnit = pNext;}				//���̃|�C���^�̐ݒ�
	CUnit*	GetBackUnit ()					{return m_pBackUnit;}				//�O�̃|�C���^�̎擾
	void	SetBackUnit (CUnit *pBack)		{m_pBackUnit = pBack;}				//�O�̃|�C���^�̐ݒ�

	int		GetNumber()						{return m_nUnitNumber;}				//���j�b�g�̔ԍ��̎擾
	void	Delete();															//HP���`�F�b�N���폜�𔻒�	
	static void DeleteMakeCount();												//���j�b�g���������N���A����

	//-----�X�e�[�^�X�Q�b�^�[-----
	//���x�����擾
	int		GetLevel()	{return m_nLevel;}
	//���O���擾
	char*	GetName	(char *pName);
	//HP���擾
	int		GetHP()			{return m_nHP;}
	//�U���͂��擾
	int		GetAT ()		{return m_nAttack;}
	//�h��͂��擾
	int		GetDF ()		{return m_nDefence;}
	//�o���l�̎擾
	int		GetExp()		{return m_nExp;}
	//��o���l�̎擾
	int		GetXP()			{return m_nXp;}
	//���݂̏�Ԃ��擾
	int		GetStatesMode()	{return m_nState;}

	//���g�̑������Ă���A�C�e���̍U���͍��v�l��n��
	int GetEquipmentAttackNum();
	//���g�̑������Ă���A�C�e���̖h��͍��v�l��n��
	int GetEquipmentDefenceNum();

	//�����̃A�C�e���̊m�F
	void ChackFeetItem();
};