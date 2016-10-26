//=======================================================================================
//
//	  �Q�[���p�E�B���h�E �N���X��`
//
//=======================================================================================
#pragma once

#include "Window.h"
#include "Graphics.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "TitleScene.h"

#define SCREEN_WIDTH	800			// �X�N���[���̕�
#define SCREEN_HEIGHT	600			// �X�N���[���̍���
#define FRAME_RATE		(1000/60)	// �t���[�����[�g

class CGameWindow : public CWindow
{
private:
	CGraphics*	m_pGraph;			// �`��f�o�C�X �N���X
	CGameScene*		m_pScene;			// �V�[��

	CResultScene*	m_pResultscene;	//���U���g�V�[���N���X
	CTitleScene*	m_pTitleScene;	//�^�C�g���V�[���N���X

	bool		m_bWindow;			// �E�B���h�E / �t���X�N���[��

	DWORD		m_dwExecLastTime;	// FPS�v���p
	DWORD		m_dwFPSLastTime;
	DWORD		m_dwFrameCount;

public:
	bool InitInstance();
	int ExitInstance();
	bool OnIdle(long lCount);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	bool OnEraseBkgnd(HDC hdc);
	bool OnSetCursor(HWND hwnd, UINT nHitTest, UINT uMouseMsg);
};

//=======================================================================================
//	End of File
//=======================================================================================