#pragma once

//�X�e�[�^�X�E�B���h�E(�t���[��)

#include "C2DTexture.h"
class CStatesWindow :
	public C2DTexture
{
private:
	static bool m_bDrawFlg;		//�`��t���O
public:
	CStatesWindow(void);		//�R���X�g���N�^
	~CStatesWindow(void);		//�f�X�g���N�^

	void Update();				//�X�V
	void WindowSizeUpdate();	//�E�B���h�E�T�C�Y�̍X�V

	//���݂̃t���O��Ԃ��擾
	static bool GetDrawFlg()	{return m_bDrawFlg;}

	//�t���O�̔��]
	static void ChangeDrawFlg()	{m_bDrawFlg = !m_bDrawFlg;}
};

