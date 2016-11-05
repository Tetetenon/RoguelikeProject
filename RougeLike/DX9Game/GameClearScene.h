#pragma once
//�Q�[���N���A�V�[���N���X
#include "Graphics.h"
#include "GameClear.h"
#include "PressSpace.h"

class CGameClearScene
{
private:
	CGraphics*	m_pGraphics;		//�O���t�B�b�N�f�o�C�X
	CGameClear*	m_GameClear;		//�Q�[���N���A�e�N�X�`��
	CPressSpace*	m_pPress;		//�v���X�X�^�[�g
public:
	CGameClearScene(void);			//�R���X�g���N�^
	~CGameClearScene(void);			//�f�X�g���N�^

	static CGameClearScene* Create(CGraphics* pGraph);	//�Q�[���N���A�V�[���̐���

	void Release();				//�Q�[���N���A�N���X�̊J��
	void Render();				//�Q�[���N���A�N���X�����_�����O�J�n
	void UpDate();				//�X�V

private:
	bool Initialize(CGraphics* pGraph);	//������

	void Finalize();			//�I������

	void Draw();				//�`�揈��

};

