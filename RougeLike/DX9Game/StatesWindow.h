#pragma once

//ステータスウィンドウ(フレーム)

#include "C2DTexture.h"

class CMenuWindow;

class CStatesWindow :
	public C2DTexture
{
private:
	//シングルトン
	static CStatesWindow* m_pStatesWindow;
	bool m_bDrawFlg;		//描画フラグ
	int		m_IntervalTime;	//ボタン入力してからの経過時間

	CMenuWindow* m_pMenuWindow;

	CStatesWindow(void);		//コンストラクタ
	~CStatesWindow(void);		//デストラクタ
public:
	//作成
	static void Create();
	//削除
	static void Delete();
	//取得
	static CStatesWindow* GetPointer();

	void Update();				//更新
	void WindowSizeUpdate();	//ウィンドウサイズの更新

	//現在のフラグ状態を取得
	bool GetDrawFlg()	
	{
		return m_bDrawFlg;
	}

	//フラグの反転
	void ChangeDrawFlg()	
	{
		m_bDrawFlg = !m_bDrawFlg;
	}

	//メンバ変数のポインタを設定する
	void SetPointer();
};

