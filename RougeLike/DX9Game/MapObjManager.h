#pragma once

//�t�B�[���h��̃I�u�W�F�N�g�̊Ǘ����s���B


//�C���N���[�h
#include<map>
#include<list>
#include<vector>

class CFieldObj;


typedef std::vector<CFieldObj*>					FIELDOBJ_LIST;	//�t�B�[���h�I�u�W�F�N�g�̃��X�g
typedef std::map<int, FIELDOBJ_LIST>			FIELDOBJ_MAP;	//���X�g��ID
typedef std::pair<int, FIELDOBJ_LIST>			FIELDOBJ_PAIR;

class CMapObjManager
{
private:

	//�ϐ�

	//�}�l�[�W���[�N���X
	static CMapObjManager* m_pMapObjManager;
	FIELDOBJ_MAP*	m_pMapObjMap;
	bool				m_bDeleteFlg;		//�S�I�u�W�F�N�g�폜�t���O
	int				m_nNextObjNumber;	//���ɐ������ꂽ�I�u�W�F�N�g�ɂ���ԍ�

	//�֐�
	CMapObjManager();							//�R���X�g���N�^
	~CMapObjManager();							//�f�X�g���N�^
public:

	void Init();							//������
	void Fin();							//�I������
	void Update();						//�X�V
	void Draw(bool Alpha);				//�`��

	static void Create();						//�t�B�[���h�I�u�W�F�}�l�[�W���[�̍쐬
	static void Delete();						//�t�B�[���h�I�u�W�F�}�l�[�W���[�̍폜
	static CMapObjManager* GetPointer();		//�}�l�[�W���[�̃|�C���^��n��

	void ChangeDeleteFlg(bool ChangeFlg);//�t�B�[���h�I�u�W�F�N�g�̍폜�t���O��ύX����

	//���̃I�u�W�F�N�g�̔ԍ���n��
	int	GetNextNumber() { return m_nNextObjNumber; }
	//���̃I�u�W�F�N�g�ԍ���ݒ�
	void SetNextNumber(int Number) { m_nNextObjNumber = Number; }
	//-----�t�B�[���h�I�u�W�F�̑���-----
	//�t�B�[���h�I�u�W�F�N�g�̃��X�g�ւ̒ǉ�
	void Add(int ObjID,CFieldObj* pObj);
	//�t�B�[���h�I�u�W�F�N�g�̃��X����̍폜
	void Del(int ObjID);
	//���X�g�ォ�����̃I�u�W�F�N�g��T������
	CFieldObj* Find(int ObjID);
};

