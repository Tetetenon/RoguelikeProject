#pragma once
#include "C2DTexture.h"

//�t�F�[�h�C���A�t�F�[�h�A�E�g

//�t�F�[�h�C���A�t�F�[�h�A�E�g�̏������Ԃ��K�肷��
#define FADETIME 255

class CFade :
	public C2DTexture
{
private:
	int		m_nFadeTime;		//�t�F�[�h�C���A�A�E�g�̎��Ԃ��i�[����
	bool	m_bDrawFlg;			//�`�悷��A���Ȃ���ݒ肷��B
public:
	CFade(void);			//�R���X�g���N�^
	~CFade(void);			//�f�X�g���N�^

	void Update();			//�X�V

	void ChangeFlg();		//�t���O��ύX����

	int GetFadeAlpha()	{return m_nFadeTime;};	//���݂̃A���t�@�l���擾
};

