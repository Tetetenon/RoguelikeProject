#pragma once
#include "meshobj.h"

class CEnemyGenerator :
	public CMeshObj
{
private:
	static int m_FieldEnemyCounter;			//�t�B�[���h��̃G�l�~�[�̐����J�E���g����

	static int m_MaxFieldEnemy;				//�t�B�[���h��ɐ�������ő吔��ݒ�

	static bool m_bMakeFlg;					//���̃^�[���ł̐����t���O
public:
	CEnemyGenerator(CGameScene* pScene);	//�R���X�g���N�^
	~CEnemyGenerator(void);				//�f�X�g���N�^

	void Init();						//������
	void Fin();							//�I������

	void Update();						//�X�V

	//�t�B�[���h��ɐ����ł���ő吔��ݒ�
	static void SetMaxGenerator (int nMaxCount);

	//�G�l�~�[�����������Z
	static void SumMakeEnemyNum();

	//�t�B�[���h��Ƀ����_���ɓG��z�u����
	void MakeEnemy();

	//�G�l�~�[�̐����������Z�b�g
	static void  ResetMakeEnemyNum();
};