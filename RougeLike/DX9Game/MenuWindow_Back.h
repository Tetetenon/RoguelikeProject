#pragma once

//���j���[�E�B���h�E�N���X(�`�悷�邾��)

#include "C2DTexture.h"
#include <tchar.h>

class CMenuWindow_Back:
	public C2DTexture
{
private:
	static bool			m_bDrawFlg;							//���j���[�E�C���h�E�`��t���O
public:
	CMenuWindow_Back(void);	//�R���X�g���N�^
	~CMenuWindow_Back(void);	//�f�X�g���N�^

	//���݂̕`��t���O��Ԃ��`�F�b�N
	static bool GetDrawFlg()		{return m_bDrawFlg;}
	//�`��t���O�𔽓]������
	static void ChangDrawFlg()		{m_bDrawFlg = !m_bDrawFlg;}
};

