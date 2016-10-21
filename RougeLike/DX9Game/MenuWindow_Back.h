#pragma once

//メニューウィンドウクラス(描画するだけ)

#include "C2DTexture.h"
#include <tchar.h>

class CMenuWindow_Back:
	public C2DTexture
{
private:
	static bool			m_bDrawFlg;							//メニューウインドウ描画フラグ
public:
	CMenuWindow_Back(void);	//コンストラクタ
	~CMenuWindow_Back(void);	//デストラクタ

	//現在の描画フラグ状態をチェック
	static bool GetDrawFlg()		{return m_bDrawFlg;}
	//描画フラグを反転させる
	static void ChangDrawFlg()		{m_bDrawFlg = !m_bDrawFlg;}
};

