#pragma once

#include "2DWindow.h"

class CTrickWindow;

class CTrickWindowCursor:
	public C2DWindow
{
private:
	//シングルトン
	static CTrickWindowCursor* m_pTrickWindowCursor;

	CTrickWindow*	m_pTrickWindow;

	int	m_nNumber;			//現在選択しているが何番目の物かを管理する
	int			m_nInterval;		//ボタン入力経過時間

	CTrickWindowCursor(void);		//コンストラクタ
	~CTrickWindowCursor(void);	//デストラクタ
public:
	static void Create();
	static void Delete();
	static CTrickWindowCursor* GetPointer();

	void Draw();				//描画
	void Update();				//更新

	void SetVertex ();			//ポリゴン情報を埋める

	void SetPos();				//ポリゴンの位置情報を設定する

	int GetTrickNum();			//選択している技の情報を返却する。

	//メンバ変数のポインタを設定する
	void SetPointer();
};

