#pragma once
//���U���g�V�[���N���X
#include "Graphics.h"
#include "Result.h"
#include "PressSpace.h"

class CResultScene
{
private:
	CGraphics*	m_pGraphics;	//�O���t�B�b�N�f�o�C�X
	CResult*	m_Result;		//���U���g�e�N�X�`��
	CPressSpace*	m_pPress;		//�v���X�X�^�[�g
public:
	CResultScene(void);			//�R���X�g���N�^
	~CResultScene(void);		//�f�X�g���N�^

	static CResultScene* Create(CGraphics* pGraph);	//���U���g�V�[���̐���

	void Release();				//���U���g�N���X�̊J��
	void Render();				//���U���g�N���X�����_�����O�J�n
	void UpDate();				//�X�V

private:
	bool Initialize(CGraphics* pGraph);	//������

	void Finalize();			//�I������

	void Draw();				//�`�揈��

};

