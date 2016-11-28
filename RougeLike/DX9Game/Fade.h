#pragma once
#include "C2DTexture.h"
#include "HierarchieNum.h"
//�t�F�[�h�C���A�t�F�[�h�A�E�g

//�t�F�[�h�C���A�t�F�[�h�A�E�g�̏������Ԃ��K�肷��
#define FADETIME 255

enum FADEMODE
{
	FADEMODE_NON = 0,	//�������Ȃ�
	FADEMODE_IN,		//�t�F�[�h�C��
	FADEMODE_OUT,		//�t�F�[�h�A�E�g
	FADEMODE_MAX
};

class CFade :
	public C2DTexture
{
private:
	static int		m_nFadeTime;		//�t�F�[�h�C���A�A�E�g�̎��Ԃ��i�[����
	static int		m_nFadeState;		//�t�F�[�h�A�E�g�A�t�F�[�h�C���A���Ȃ���ݒ肷��B
public:
	CFade(void);			//�R���X�g���N�^
	~CFade(void);			//�f�X�g���N�^

	void Update();			//�X�V
	void Draw();			//�`��

	static void ChangeState(int State);		//�t���O��ύX����

	static int GetFadeAlpha()	{return m_nFadeTime;}	//���݂̃A���t�@�l���擾
	static int GetFadeState()	{return m_nFadeState;}	//���݂̃t�F�[�h��Ԃ��擾
};

