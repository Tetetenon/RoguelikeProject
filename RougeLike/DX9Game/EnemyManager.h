#pragma once

//�G�l�~�[�̊Ǘ����s��

//�C���N���[�h
#include<map>
#include<list>
#include<vector>
class CUnit;

typedef std::vector<CUnit*>			UNIT_LIST;	//���j�b�g�̃��X�g
typedef std::map<int, UNIT_LIST>	UNIT_MAP;	//���j�b�g�̃��X�g+ID
typedef std::pair<int, UNIT_LIST>	UNIT_PAIR;	//���j�b�g���X�g�y�A

class CEnemyManager
{
private:
	//�V���O���g��
	static UNIT_MAP* m_pEnemyManager;

	static int m_NowProcUnitID;			//���ݍU���������s���Ă���G�l�~�[��ID��ۑ�


	//�֐��錾
	CEnemyManager();						//�R���X�g���N�^
	~CEnemyManager();					//�f�X�g���N�^
public:

	//�֐��錾
	static void Init();					//������
	static void Fin();					//�I������
	static void WaitUpdate();			//�ҋ@�̍X�V
	static void TurnUpdate();			//�^�[���̍X�V	
	static void Draw();					//�`��

	//�}�l�[�W���[�̍쐬
	static void Create();

	//�}�l�[�W���[�̍폜
	static void Destroy();

	//���X�g�֘A����
	//���j�b�g�̒ǉ�
	static void Add(int UnitID, CUnit* pUnit);
	//���j�b�g�̍폜
	static void Del(int UnitID);
	//���j�b�g�̒T��
	static CUnit* Find(int UnitID);
};

