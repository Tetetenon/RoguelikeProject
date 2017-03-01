#pragma once

//�U���q�b�g���̃G�t�F�N�g�I�u�W�F�N�g�̊Ǘ����s��

//�C���N���[�h
#include <map>
#include<list>
#include<vector>

class CEffectObj;

typedef std::vector<CEffectObj*>	EFFECTOBJ_LIST;
typedef std::map<int, EFFECTOBJ_LIST>	EFFECTOBJ_MAP;
typedef std::pair<int, EFFECTOBJ_LIST>	EFFECTOBJ_PAIR;

class CEffectObjManager
{
private:
	//�ϐ�

	//�V���O���g��
	static CEffectObjManager* m_pEffectManager;
	EFFECTOBJ_MAP*	m_pEffectMap;

	//���̃G�t�F�N�g�̔ԍ�
	int				m_nEffectNumber;

	//�֐�

	CEffectObjManager();					//�R���X�g���N�^
	~CEffectObjManager();					//�f�X�g���N�^
public:
	//�֐�
	void Init();						//������
	void Fin();						//�I������
	void Update();					//�X�V
	void Draw();						//�`��

	static void Create();					//�}�l�[�W���[�̍쐬
	static void Delete();					//�}�l�[�W���[�̍폜
	static CEffectObjManager* GetPointer();				//�|�C���^��n��

	//�G�t�F�N�g�̔ԍ��̎擾
	int GetEffectNumber() { return m_nEffectNumber; }
	//�G�t�F�N�g�ԍ��̐ݒ�
	void SetEffectNumber(int nNumber) { m_nEffectNumber = nNumber; }

	//-----���X�g�̑���-----
	//�I�u�W�F�N�g�̒ǉ�
	void Add(int ID, CEffectObj* pAdd);
	//�I�u�W�F�N�g�̍폜
	void Del(int ID);
	//�I�u�W�F�N�g�̒T��
	CEffectObj* Find(int ID);
};

