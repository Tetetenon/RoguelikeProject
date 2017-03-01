#pragma once

#include "C2DTexture.h"

class CStatesCharacter :
	public C2DTexture
{
private:
	//�V���O���g��
	static CStatesCharacter* m_pStatesCharacter;

	CStatesCharacter(void);		//�R���X�g���N�^
	~CStatesCharacter(void);		//�f�X�g���N�^
public:
	static void Create();					//���̍쐬
	static void Delete();					//���̍폜
	static CStatesCharacter* GetPointer();	//���̂̃|�C���^��n��

	void ChangeTexture(int nPlayerState);		//�g�p����e�N�X�`���̌���
};

