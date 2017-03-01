#pragma once

//�U���q�b�g���̃r���{�[�h�̊Ǘ����s��

//�C���N���[�h
#include <map>
#include<list>
#include<vector>

//�_���[�W�\�����s���N���X
class CDamageNotation;

//�^�̒�`
typedef std::vector<CDamageNotation*>			DAMAGE_NOTATION_LIST;
typedef std::map <int, DAMAGE_NOTATION_LIST>	DAMAGE_NOTATION_MAP;
typedef std::pair<int, DAMAGE_NOTATION_LIST>		DAMAGE_NOTATION_PAIR;

class CDamageBillBoardManager
{
private:
	//�ϐ�
	//�V���O���g��
	static CDamageBillBoardManager* m_pManager;


	DAMAGE_NOTATION_MAP* m_pDamageBillBoardMap;
	//���̃r���{�[�h�̔ԍ�
	int m_nNextBillBoardNumber;

	//�֐�
	CDamageBillBoardManager();		//�R���X�g���N�^
	~CDamageBillBoardManager();		//�f�X�g���N�^
public:
	//�֐�
	void ManagerObjFin();			//�Ǘ��I�u�W�F�N�g�̏I������
	void ManagerObjUpdate();		//�Ǘ��I�u�W�F�N�g�̍X�V
	void ManagerObjDraw();			//�Ǘ��I�u�W�F�N�g�̍X�V

	//�}�l�[�W���[�̍쐬�A�폜
	static void Create();
	static void Delete();

	//�|�C���^��n��
	static CDamageBillBoardManager* GetPointer();

	//���Ɋ���U��ԍ��̎擾
	int GetNextNumber()
	{
		return m_nNextBillBoardNumber;
	}

	//���Ɋ���U��ԍ��̐ݒ�
	void SetNextNumber(int nNumber)
	{
		m_nNextBillBoardNumber = nNumber;
	}

	//-----���X�g�̑���-----
	void Add(int ID, CDamageNotation* pAddObj);	//�I�u�W�F�N�g�̒ǉ�
	void Del(int ID);							//�I�u�W�F�N�g�̍폜
	CDamageNotation* Find(int ID);				//�I�u�W�F�N�g�̌���

};

