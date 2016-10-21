#pragma once

//ステータスウィンドウ(フレーム)

#include "C2DTexture.h"
class CStatesWindow :
	public C2DTexture
{
private:
	static bool m_bDrawFlg;		//描画フラグ
public:
	CStatesWindow(void);		//コンストラクタ
	~CStatesWindow(void);		//デストラクタ

	void Update();				//更新
	void WindowSizeUpdate();	//ウィンドウサイズの更新

	//現在のフラグ状態を取得
	static bool GetDrawFlg()	{return m_bDrawFlg;}

	//フラグの反転
	static void ChangeDrawFlg()	{m_bDrawFlg = !m_bDrawFlg;}
};

