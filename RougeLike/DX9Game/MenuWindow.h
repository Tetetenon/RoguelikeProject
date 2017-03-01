#pragma once

//メニューウィンドウクラス(描画するだけ)

#include "C2DTexture.h"

class CMenuWindow:
	public C2DTexture
{
private:
	//シングルトン
	static CMenuWindow* m_pMenuWindow;
	bool			m_bDrawFlg;			//メニューウインドウ描画フラグ

	CMenuWindow(void);	//コンストラクタ
	~CMenuWindow(void);	//デストラクタ
public:
	static void Create();
	static void Delete();
	static CMenuWindow* GetPointer();

	void Update();		//更新

	//現在の描画フラグ状態をチェック
	bool GetDrawFlg()		{return m_bDrawFlg;}
	//描画フラグを反転させる
	void ChangDrawFlg()		{m_bDrawFlg = !m_bDrawFlg;}
};

