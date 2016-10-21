#pragma once

//メニューウィンドウクラス(描画するだけ)

#include "C2DTexture.h"

class CMenuWindow:
	public C2DTexture
{
private:
	static bool			m_bDrawFlg;			//メニューウインドウ描画フラグ		
public:
	CMenuWindow(void);	//コンストラクタ
	~CMenuWindow(void);	//デストラクタ

	void Update();		//更新

	//現在の描画フラグ状態をチェック
	static bool GetDrawFlg()		{return m_bDrawFlg;}
	//描画フラグを反転させる
	static void ChangDrawFlg()		{m_bDrawFlg = !m_bDrawFlg;}
};

