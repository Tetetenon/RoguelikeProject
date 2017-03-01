#pragma once

//���j�b�g�̊Ǘ����s���B

//�C���N���[�h
#include<map>
#include<list>
#include<vector>


class CUnit;


typedef std::vector<CUnit*>			UNIT_LIST;	//���j�b�g�̃��X�g
typedef std::map<int, UNIT_LIST>	UNIT_MAP;	//���j�b�g�̃��X�g+ID
typedef std::pair<int, UNIT_LIST>	UNIT_PAIR;	//���j�b�g���X�g�y�A

class CUnitManager
{
private:
	//�ϐ��錾

	//�V���O���g��
	static CUnitManager* m_pManager;
	UNIT_MAP* m_pUnitManager;

	CUnit*	m_pPlayer;			//�v���C���[�|�C���^�[

	bool		m_bMoveCanFlg;		//�ړ��\�t���O
	int		m_nMakeNumber;		//���j�b�g�����̐����������B


	CUnitManager();		//�R���X�g���N�^
	~CUnitManager();	//�f�X�g���N�^
public:

	//�֐��錾
	void Init();		//������
	void Fin();			//�I������
	void Update();		//�X�V
	void Draw();		//�`��

	void EnemyDelete();	//�G�l�~�[�̍폜

	//���j�b�g�}�l�[�W���[�̍쐬
	static void Create();
	//���j�b�g�}�l�[�W���[�̍폜
	static void Delete();

	//�}�l�[�W���[�̃|�C���^��n��
	static CUnitManager* GetPointer();

	//�v���C���[�̃|�C���^���擾����
	void SetPlayerPointer();
	//�v���C���[�̃��x����n��
	int GetPlayerLevel();

	//���j�b�g�S�Ă̍s���\�t���O��ύX����
	void ChangeMoveCanFlg(bool ChangeFlg);

	//-----���j�b�g�֘A�̑���-----
	//���j�b�g��ǉ�����
	void Add(int UnitID,CUnit* pUnit);
	//���j�b�g���폜����
	void Del(int UnitID);
	//���j�b�g��T������
	CUnit*  Find(int UnitID);

	//-----�v���C���[�̏���n��-----
	CUnit* GetPlayerPointer();
	int GetPlayerPosX();
	int GetPlayerPosZ();

	bool GetMoveFlg()
	{
		return m_bMoveCanFlg;
	}

	int GetMakeNum()
	{
		return m_nMakeNumber;
	}

	void AddMakeNum(int nAddNum)
	{
		m_nMakeNumber += nAddNum;
	}
};

