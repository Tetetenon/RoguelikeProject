#pragma once
#include "Graphics.h"
#include "Fade.h"
#include "Title.h"
#include "PressSpace.h"


class CTitleScene
{
private:
	CGraphics*		m_pGraphics;	//�O���t�B�b�N�f�o�C�X
	CTitle*			m_pTitle;		//�^�C�g�����
	CFade*			m_pFade;		//�t�F�[�h�C���A�t�F�[�h�A�E�g
	CPressSpace*	m_pPress;		//�v���X�X�^�[�g
	static bool		m_bCreate;		//���������t���O
public:
	CTitleScene(void);
	~CTitleScene(void);

	static CTitleScene* Create(CGraphics* pGraph);

	void Release();
	void Render();
	void Update();
	

private:
	bool Initialize(CGraphics* pGraph);
	void Finalize();
	void Draw();
};

