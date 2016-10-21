#pragma once
#include "C2DTexture.h"

//フェードイン、フェードアウト

//フェードイン、フェードアウトの処理時間を規定する
#define FADETIME 255

class CFade :
	public C2DTexture
{
private:
	int		m_nFadeTime;		//フェードイン、アウトの時間を格納する
	bool	m_bDrawFlg;			//描画する、しないを設定する。
public:
	CFade(void);			//コンストラクタ
	~CFade(void);			//デストラクタ

	void Update();			//更新

	void ChangeFlg();		//フラグを変更する

	int GetFadeAlpha()	{return m_nFadeTime;};	//現在のアルファ値を取得
};

