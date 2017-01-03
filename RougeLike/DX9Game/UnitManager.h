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
	static UNIT_MAP* m_pUnitManager;
	static int		m_NowProcUnitID;	//���݃^�[���X�e�[�g�������̃��j�b�g�ԍ�

	static CUnit*	m_pPlayer;			//�v���C���[�|�C���^�[

	static bool				m_bMoveCanFlg;					//�ړ��\�t���O


	CUnitManager();		//�R���X�g���N�^
	~CUnitManager();	//�f�X�g���N�^
public:

	//�֐��錾
	static void Init();			//������
	static void Fin();			//�I������
	static void Update();		//�X�V
	static void Draw();			//�`��

	//�G�l�~�[�̍폜
	static void EnemyDelete();

	//���j�b�g�}�l�[�W���[�̍쐬
	static void Create();
	//���j�b�g�}�l�[�W���[�̍폜
	static void Destroy();

	//�}�l�[�W���[�̃|�C���^��n��
	UNIT_MAP* GetPointer();

	//�v���C���[�̃|�C���^���擾����
	static void SetPlayerPointer();
	//�v���C���[�̃��x����n��
	static int GetPlayerLevel();

	//���j�b�g�S�Ă̍s���\�t���O��ύX����
	static void ChangeMoveCanFlg(bool ChangeFlg);

	//-----���j�b�g�֘A�̑���-----
	//���j�b�g��ǉ�����
	static void Add(int UnitID,CUnit* pUnit);
	//���j�b�g���폜����
	static void Del(int UnitID);
	//���j�b�g��T������
	static CUnit*  Find(int UnitID);

	//-----�v���C���[�̏���n��-----
	static int GetPlayerPosX();
	static int GetPlayerPosZ();

};

