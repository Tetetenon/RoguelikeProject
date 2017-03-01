#pragma once

#include "2DWindow.h"
#include "Inventory.h"

class CItemCommandWindow;
class CItemWindowCursor;
class CItemDescriptionFrame;

class CItemWindow:
	public C2DWindow
{
private:
	//シングルトン
	static CItemWindow* m_pItemWindow;
	LPD3DXFONT			m_Font;					//描画用フォント
	RECT				m_Pos[ITEM_NUM_MAX];	//ウィンドウ表示位置
	bool				m_bDrawFlg;				//描画フラグ
	bool				m_bUpdateFlg;				//更新フラグ

	VERTEX_2D	m_aVertex[ITEM_NUM_MAX][NUM_VERTEX];	//ポリゴン頂点情報格納用

	CItemCommandWindow*		m_pCommandWindow;	//コマンドウインドウの描画フラグ変更用
	CItemWindowCursor*		m_pIItemWindowCursor;	//選択しているアイテムウインドウの取得
	CItemDescriptionFrame*	m_pDescription;		//アイテム説明文
	CInventory*				m_pPlayerInventory;	//プレイヤーの所持アイテムポインタ

	int						m_nInterval;		//入力経過時間

	CItemWindow(void);							//コンストラクタ
	~CItemWindow(void);							//デストラクタ
public:
	static void Create();						//実体を作成
	static void Delete();						//実体の削除
	static CItemWindow*	GetPointer();			//ポインタを渡す

	void UpDate();								//更新部
	void Draw();								//描画

	void DrawFlgChange(bool);				//描画フラグをON/OFFする
	void UpdateFlgChange(bool);					//更新フラグのON/OFF

	void SetVertex();							//ポリゴン情報を埋める
	void SetFontPos();							//フォント描画位置設定

	//描画のフラグ状況を取得
	bool GetDrawFlg()	{return m_bDrawFlg;}
	bool GetUpdateFlg() { return m_bUpdateFlg; }

	//メンバ変数のポインタを設定する
	void SetPoiner();
};

