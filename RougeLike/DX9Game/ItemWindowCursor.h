#pragma once

#include "2DWindow.h"

class CItemCommandWindow;
class CItemWindow;

class CItemWindowCursor:
	public C2DWindow
{
private:
	//シングルトンにすることで、一意性を確保
	static CItemWindowCursor* m_pItemWindowCursor;

	int			m_nNumber;				//現在選択しているアイテムが何番目の物かを管理する
	int			m_nInterval;			//ボタン入力してからの経過時間を保存する

	CItemCommandWindow* m_pItemCommandWindow;
	CItemWindow*		m_pItemWindow;

	CItemWindowCursor(void);		//コンストラクタ
	~CItemWindowCursor(void);	//デストラクタ
public:
	static void Create();		//自身の実態を作成
	static void Delete();		//自身の実態を削除
	static CItemWindowCursor* GetPointer();	//自身のポインタを渡す

	void Draw();				//描画
	void Update();				//更新

	void SetVertex ();			//ポリゴン情報を埋める

	void SetPos();				//ポリゴンの位置情報を設定する

	int GetItemNum();			//選択しているアイテムの情報を返却する。

	//メンバ変数のポインタを設定する
	void SetPointer();
};

