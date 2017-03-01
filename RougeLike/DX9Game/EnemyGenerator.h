#pragma once
#include "meshobj.h"

class CMapData;
class CUnit;

class CEnemyGenerator :
	public CMeshObj
{
private:
	//�V���O���g��
	static CEnemyGenerator* m_pEnemyGenerator;

	CMapData*	m_pMapData;
	CUnit*		m_pPlayer;

	int m_FieldEnemyCounter;			//�t�B�[���h��̃G�l�~�[�̐����J�E���g����
	int m_MaxFieldEnemy;				//�t�B�[���h��ɐ�������ő吔��ݒ�
	bool m_bMakeFlg;					//���̃^�[���ł̐����t���O

	CEnemyGenerator(CGameScene* pScene);	//�R���X�g���N�^
	~CEnemyGenerator(void);				//�f�X�g���N�^
public:

	static void Create(CGameScene *pScene);
	static void Delete();
	static CEnemyGenerator* GetPointer();

	//�����o�ϐ��̃|�C���^��ݒ肷��
	void SetPointer();

	void Update();						//�X�V

	//�t�B�[���h��ɐ����ł���ő吔��ݒ�
	void SetMaxGenerator (int nMaxCount);

	//�G�l�~�[�����������Z
	void SumMakeEnemyNum();

	//�t�B�[���h��Ƀ����_���ɓG��z�u����
	void MakeEnemy();

	//�G�l�~�[�̐����������Z�b�g
	void  ResetMakeEnemyNum();
};