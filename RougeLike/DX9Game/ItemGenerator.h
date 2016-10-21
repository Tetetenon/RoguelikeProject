#pragma once
#include "MeshObj.h"

class CItemGenerator:
	public CMeshObj
{
private:
	static int m_FieldItemCounter;		//�t�B�[���h��̃A�C�e���̐����J�E���g����

	static int m_MaxFieldItem;			//�t�B�[���h��ɐ�������ő吔��ݒ肷��
public:
	CItemGenerator(CGameScene* pScene);				//�R���X�g���N�^
	~CItemGenerator(void);				//�f�X�g���N�^

	void Init();						//������
	void Fin();							//�I������

	void Update();						//�X�V

	//�t�B�[���h��ɐ�������A�C�e���̍ő吔��ݒ肷��
	static void SetMaxItem(int MaxItemNum);

	//�t�B�[���h��ɃA�C�e���𐶐�����
	 void MakeItem();

	 //�A�C�e���Đ��������Z�b�g
	 static void ResetMakeItemNum();
};

