#pragma once

//���j���[�E�B���h�E�N���X(�`�悷�邾��)

#include "C2DTexture.h"

class CMenuWindow:
	public C2DTexture
{
private:
	static bool			m_bDrawFlg;			//���j���[�E�C���h�E�`��t���O		
public:
	CMenuWindow(void);	//�R���X�g���N�^
	~CMenuWindow(void);	//�f�X�g���N�^

	void Update();		//�X�V

	//���݂̕`��t���O��Ԃ��`�F�b�N
	static bool GetDrawFlg()		{return m_bDrawFlg;}
	//�`��t���O�𔽓]������
	static void ChangDrawFlg()		{m_bDrawFlg = !m_bDrawFlg;}
};

