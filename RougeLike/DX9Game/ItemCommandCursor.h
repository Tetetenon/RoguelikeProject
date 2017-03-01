#pragma once

#include "2DWindow.h"
#include "Turn.h"
class CItemCommandWindow;

//コマンド選択画面のカーソル

class CItemCommandCursor:
	public C2DWindow
{
private:
	//シングルトン
	static CItemCommandCursor* m_pItemCommandCursor;

	int					m_Command;				//何番目のコマンドを選択しているかを格納する

	CItemCommandWindow*	m_pItemCommandWindow;
	int							m_nInterval;			//ボタン入力経過時間を保存

	CItemCommandCursor(void);								//コンストラクタ
	virtual ~CItemCommandCursor(void);						//デストラクタ
public:
	static void Create();
	static void Delete();
	static CItemCommandCursor* GetPointer();

	void Draw();										//描画
	void Update();										//更新

	void SetVertex();									//ポリゴン情報を埋める
	void SetPos();										//ポリゴンの位置情報を設定する

	int  GetCommand();									//選択したコマンドを返す 

	//メンバ変数のポインタを設定する
	void SetPointer();
};

