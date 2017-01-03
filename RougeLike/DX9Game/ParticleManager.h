#pragma once

//�p�[�e�B�N���̊Ǘ����s��

//�C���N���[�h
#include<map>
#include<list>
#include<vector>

class CParticle;

typedef std::vector<CParticle*>			PARTICLE_LIST;
typedef std::map<int, PARTICLE_LIST>	PARTICLE_MAP;
typedef std::pair<int, PARTICLE_LIST>	PARTICLE_PAIR;

class CParticleManager
{
private:
	//�ϐ�
	//�}�l�[�W���[�|�C���^
	static PARTICLE_MAP*	m_pParticleManager;
	static int				m_nNextID;

	//�֐�
	CParticleManager();			//�R���X�g���N�^
	~CParticleManager();		//�f�X�g���N�^

public:
	static void Init();				//������
	static void Fin();				//�I������
	static void Update();			//�X�V����
	static void Draw();				//�`��

	static void Create();			//�}�l�[�W���[�̍쐬
	static void Delete();			//�}�l�[�W���[�̍폜

	//���ɍ쐬����p�[�e�B�N���̔ԍ���n��
	static int GetNextID() { return m_nNextID; }
	//���ɍ쐬����I�u�W�F�N�g�ԍ���ݒ�
	static void SetNextID(int SetID) { m_nNextID = SetID; }

	//-----�p�[�e�B�N���̊Ǘ�-----
	//���X�g�֒ǉ�
	static void Add(int ID, CParticle* pObj);
	//���X�g����폜
	static void Del(int ID);
	//���X�g���猟��
	static CParticle* Find(int ID);
};