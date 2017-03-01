#pragma once

#include <tchar.h>
#include"2DWindow.h"
#include "define.h"

#define FONT_MAX 10

class CTurn;
class CItemWindow;
class CUnit; 
class CMenuWindow;

class CItemCommandWindow:
	public C2DWindow
{
	//シングルトン
	static CItemCommandWindow* m_pItemCommandWindow;
	CUnit*			m_pPlayer;								//プレイヤーのポインタ
	_TCHAR			m_CommandName[COMMAND_MAX][FONT_MAX];	//コマンド名
	LPD3DXFONT		m_Font;									//描画用フォント
	RECT			m_Pos[COMMAND_MAX];						//ウィンドウ表示位置
	bool			m_bDrawFlg;								//描画フラグ
	VERTEX_2D		m_aVertex[COMMAND_MAX][NUM_VERTEX];		//ポリゴン頂点情報格納用
	CTurn*			m_pTurn;								//ステート変更
	CItemWindow*	m_pItemWindow;							//インベントリの描画フラグ変更用
	CMenuWindow*	m_pMenuWindow;							//メニューウィンドウへのポインタ
	int				m_EnterInterval;						//アイテム選択時にエンターキーをクリックしてから経った時間を計測する(連続でTriggerが反応することを避けるため)


	CItemCommandWindow(void);						//コンストラクタ
	~CItemCommandWindow(void);						//デストラクタ
public:
	static void Create();						//実体の作成
	static void Delete();						//実体の削除
	static CItemCommandWindow* GetPointer();	//自身のポインタを渡す

	void UpDate();								//更新部
	void Draw();								//描画

	void DrawFlgChange();						//描画フラグをON/OFFする

	void SetVertex();							//ポリゴン情報を埋める
	void SetFontPos();							//フォント描画位置設定

	void SetCommand();							//ウィンドウのコマンドを埋める

	//描画のフラグ状況を取得
	bool GetDrawFlg()	{return m_bDrawFlg;}

	//メンバ変数のポインタを設定する
	void SetPointer();
};

