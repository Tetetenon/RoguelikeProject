#pragma once
//��������e�N�X�`��
#include "C2DTexture.h"

class COperation :
	public C2DTexture
{
private:
	//�V���O���g��
	static COperation* m_pOperation;

	COperation(void);		//�R���X�g���N�^
	~COperation(void);		//�f�X�g���N�^

public:
	static void Create();			//���̂̐���
	static void Delete();			//���̂̍폜
	static COperation* GetPoiner();	//���̂̃|�C���^��n��
};

