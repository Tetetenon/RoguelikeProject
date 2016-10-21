#pragma once
//リザルトシーンクラス
#include "Graphics.h"
#include "Result.h"
#include "PressSpace.h"

class CResultScene
{
private:
	CGraphics*	m_pGraphics;	//グラフィックデバイス
	CResult*	m_Result;		//リザルトテクスチャ
	CPressSpace*	m_pPress;		//プレススタート
public:
	CResultScene(void);			//コンストラクタ
	~CResultScene(void);		//デストラクタ

	static CResultScene* Create(CGraphics* pGraph);	//リザルトシーンの生成

	void Release();				//リザルトクラスの開放
	void Render();				//リザルトクラスレンダリング開始
	void UpDate();				//更新

private:
	bool Initialize(CGraphics* pGraph);	//初期化

	void Finalize();			//終了処理

	void Draw();				//描画処理

};

