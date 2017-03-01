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
	//シングルトン
	static CFade*	m_pFade;
	int		m_nFadeTime;		//フェードイン、アウトの時間を格納する
	int		m_nFadeState;		//フェードアウト、フェードイン、しないを設定する。

	CFade(void);			//コンストラクタ
	~CFade(void);			//デストラクタ
public:
	static void Create();		//実体の作成
	static void Delete();		//実体の削除
	static CFade* GetPointer();	//実体のポインタを渡す

	void Update();			//更新
	void Draw();			//描画

	void ChangeState(int State);		//フラグを変更する

	int GetFadeAlpha()	{return m_nFadeTime;}	//現在のアルファ値を取得
	int GetFadeState()	{return m_nFadeState;}	//現在のフェード状態を取得
};

