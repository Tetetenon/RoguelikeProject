#pragma once

//���j���[�E�B���h�E�N���X(�`�悷�邾��)

#include "C2DTexture.h"

class CMenuWindow:
	public C2DTexture
{
private:
	//�V���O���g��
	static CMenuWindow* m_pMenuWindow;
	bool			m_bDrawFlg;			//���j���[�E�C���h�E�`��t���O

	CMenuWindow(void);	//�R���X�g���N�^
	~CMenuWindow(void);	//�f�X�g���N�^
public:
	static void Create();
	static void Delete();
	static CMenuWindow* GetPointer();

	void Update();		//�X�V

	//���݂̕`��t���O��Ԃ��`�F�b�N
	bool GetDrawFlg()		{return m_bDrawFlg;}
	//�`��t���O�𔽓]������
	void ChangDrawFlg()		{m_bDrawFlg = !m_bDrawFlg;}
};

