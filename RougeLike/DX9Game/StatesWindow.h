#pragma once

//�X�e�[�^�X�E�B���h�E(�t���[��)

#include "C2DTexture.h"

class CMenuWindow;

class CStatesWindow :
	public C2DTexture
{
private:
	//�V���O���g��
	static CStatesWindow* m_pStatesWindow;
	bool m_bDrawFlg;		//�`��t���O
	int		m_IntervalTime;	//�{�^�����͂��Ă���̌o�ߎ���

	CMenuWindow* m_pMenuWindow;

	CStatesWindow(void);		//�R���X�g���N�^
	~CStatesWindow(void);		//�f�X�g���N�^
public:
	//�쐬
	static void Create();
	//�폜
	static void Delete();
	//�擾
	static CStatesWindow* GetPointer();

	void Update();				//�X�V
	void WindowSizeUpdate();	//�E�B���h�E�T�C�Y�̍X�V

	//���݂̃t���O��Ԃ��擾
	bool GetDrawFlg()	
	{
		return m_bDrawFlg;
	}

	//�t���O�̔��]
	void ChangeDrawFlg()	
	{
		m_bDrawFlg = !m_bDrawFlg;
	}

	//�����o�ϐ��̃|�C���^��ݒ肷��
	void SetPointer();
};

