#pragma once

//���j���[�E�B���h�E�N���X(�`�悷�邾��)

#include "C2DTexture.h"
#include <tchar.h>

class CMenuWindow_Back:
	public C2DTexture
{
private:
	//�V���O���g��
	static CMenuWindow_Back* m_pMenuWindow_Back;
	bool			m_bDrawFlg;							//���j���[�E�C���h�E�`��t���O

	CMenuWindow_Back(void);	//�R���X�g���N�^
	~CMenuWindow_Back(void);	//�f�X�g���N�^
public:
	static void Create();					//���̂��쐬
	static void Delete();					//���̂��폜
	static CMenuWindow_Back* GetPointer();	//���̂̃|�C���^��n��

	//���݂̕`��t���O��Ԃ��`�F�b�N
	bool GetDrawFlg()		{return m_bDrawFlg;}
	//�`��t���O�𔽓]������
	void ChangDrawFlg()		{m_bDrawFlg = !m_bDrawFlg;}
};

