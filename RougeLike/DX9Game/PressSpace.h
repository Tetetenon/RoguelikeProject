#pragma once
//�v���X�X�y�[�X

#include "C2DTexture.h"

class CPressSpace :
	public C2DTexture
{
private:
	bool	m_bAlphaSwitch;	//���߉��Z�X�C�b�`
	int		m_nFlashTimer;	//�_�Ŏ���
public:
	CPressSpace(void);		//�R���X�g���N�^
	~CPressSpace(void);		//�f�X�g���N�^
	void Update();			//�X�V
};

