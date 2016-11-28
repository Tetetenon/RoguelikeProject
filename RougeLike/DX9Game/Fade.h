#pragma once
#include "C2DTexture.h"
#include "HierarchieNum.h"
//フェードイン、フェードアウト

//フェードイン、フェードアウトの処理時間を規定する
#define FADETIME 255

enum FADEMODE
{
	FADEMODE_NON = 0,	//何もしない
	FADEMODE_IN,		//フェードイン
	FADEMODE_OUT,		//フェードアウト
	FADEMODE_MAX
};

class CFade :
	public C2DTexture
{
private:
	static int		m_nFadeTime;		//フェードイン、アウトの時間を格納する
	static int		m_nFadeState;		//フェードアウト、フェードイン、しないを設定する。
public:
	CFade(void);			//コンストラクタ
	~CFade(void);			//デストラクタ

	void Update();			//更新
	void Draw();			//描画

	static void ChangeState(int State);		//フラグを変更する

	static int GetFadeAlpha()	{return m_nFadeTime;}	//現在のアルファ値を取得
	static int GetFadeState()	{return m_nFadeState;}	//現在のフェード状態を取得
};

