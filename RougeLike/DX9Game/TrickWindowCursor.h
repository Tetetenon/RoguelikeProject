#pragma once

#include "2DWindow.h"
#include "TrickWindow.h"

class CTrickWindowCursor:
	public C2DWindow
{
private:
	static int	m_Number;			//現在選択しているが何番目の物かを管理する
	int			m_nInterval;		//ボタン入力経過時間
public:
	CTrickWindowCursor(void);		//コンストラクタ
	~CTrickWindowCursor(void);	//デストラクタ

	void Init();				//初期化
	void Fin();					//終了処理

	void Draw();				//描画
	void Update();				//更新

	void SetVertex ();			//ポリゴン情報を埋める

	void SetPos();				//ポリゴンの位置情報を設定する

	static int GetTrickNum();			//選択している技の情報を返却する。
};

