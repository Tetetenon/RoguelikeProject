#pragma once

//メニューウィンドウクラス(描画するだけ)

#include "C2DTexture.h"
#include <tchar.h>

class CMenuWindow_Back:
	public C2DTexture
{
private:
	//シングルトン
	static CMenuWindow_Back* m_pMenuWindow_Back;
	bool			m_bDrawFlg;							//メニューウインドウ描画フラグ

	CMenuWindow_Back(void);	//コンストラクタ
	~CMenuWindow_Back(void);	//デストラクタ
public:
	static void Create();					//実体を作成
	static void Delete();					//実体を削除
	static CMenuWindow_Back* GetPointer();	//実体のポインタを渡す

	//現在の描画フラグ状態をチェック
	bool GetDrawFlg()		{return m_bDrawFlg;}
	//描画フラグを反転させる
	void ChangDrawFlg()		{m_bDrawFlg = !m_bDrawFlg;}
};

