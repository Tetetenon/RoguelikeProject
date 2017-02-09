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
	static EFFECTOBJ_MAP*	m_pEffectManager;

	//���̃G�t�F�N�g�̔ԍ�
	static int				m_nEffectNumber;

	//�֐�

	CEffectObjManager();					//�R���X�g���N�^
	~CEffectObjManager();					//�f�X�g���N�^
public:
	//�֐�
	static void Init();						//������
	static void Fin();						//�I������
	static void Update();					//�X�V
	static void Draw();						//�`��

	static void Create();					//�}�l�[�W���[�̍쐬
	static void Delete();					//�}�l�[�W���[�̍폜

	//�G�t�F�N�g�̔ԍ��̎擾
	static int GetEffectNumber() { return m_nEffectNumber; }
	//�G�t�F�N�g�ԍ��̐ݒ�
	static void SetEffectNumber(int nNumber) { m_nEffectNumber = nNumber; }

	//-----���X�g�̑���-----
	//�I�u�W�F�N�g�̒ǉ�
	static void Add(int ID, CEffectObj* pAdd);
	//�I�u�W�F�N�g�̍폜
	static void Del(int ID);
	//�I�u�W�F�N�g�̒T��
	static CEffectObj* Find(int ID);
};

