#pragma once
#include "Graphics.h"
#include "Fade.h"
#include "Title.h"
#include "PressSpace.h"


class CTitleScene
{
private:
	CGraphics*		m_pGraphics;	//グラフィックデバイス
	CTitle*			m_pTitle;		//タイトル画面
	CFade*			m_pFade;		//フェードイン、フェードアウト
	CPressSpace*	m_pPress;		//プレススタート
	static bool		m_bCreate;		//生成成功フラグ
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

