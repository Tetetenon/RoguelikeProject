#pragma once

#include "C2DTexture.h"

class CStatesCharacter :
	public C2DTexture
{
public:
	CStatesCharacter(void);		//�R���X�g���N�^
	~CStatesCharacter(void);		//�f�X�g���N�^

	void Update(int nPlayerState);				//�e�N�X�`���f�[�^�̍X�V
};

