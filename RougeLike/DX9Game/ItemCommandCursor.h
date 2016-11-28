#pragma once

#include "2DWindow.h"
#include "Turn.h"
#include "ItemCommandWindow.h"

//コマンド選択画面のカーソル

class CCommandCursor:
	public C2DWindow
{
private:
	static int					m_Command;				//何番目のコマンドを選択しているかを格納する

	CTurn						m_Turn;					//ターンステート変更用
public:
	CCommandCursor(void);								//コンストラクタ
	virtual ~CCommandCursor(void);						//デストラクタ

	void Init();										//初期化
	void Fin();											//終了処理

	void Draw();										//描画
	void Update();										//更新

	void SetVertex();									//ポリゴン情報を埋める
	void SetPos();										//ポリゴンの位置情報を設定する

	static int  GetCommand();									//選択したコマンドを返す 
};

