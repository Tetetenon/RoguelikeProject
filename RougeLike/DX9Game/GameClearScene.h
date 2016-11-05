#pragma once
//ゲームクリアシーンクラス
#include "Graphics.h"
#include "GameClear.h"
#include "PressSpace.h"

class CGameClearScene
{
private:
	CGraphics*	m_pGraphics;		//グラフィックデバイス
	CGameClear*	m_GameClear;		//ゲームクリアテクスチャ
	CPressSpace*	m_pPress;		//プレススタート
public:
	CGameClearScene(void);			//コンストラクタ
	~CGameClearScene(void);			//デストラクタ

	static CGameClearScene* Create(CGraphics* pGraph);	//ゲームクリアシーンの生成

	void Release();				//ゲームクリアクラスの開放
	void Render();				//ゲームクリアクラスレンダリング開始
	void UpDate();				//更新

private:
	bool Initialize(CGraphics* pGraph);	//初期化

	void Finalize();			//終了処理

	void Draw();				//描画処理

};

