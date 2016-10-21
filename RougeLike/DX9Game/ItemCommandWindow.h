#pragma once

#include <tchar.h>
#include"2DWindow.h"
#include "define.h"

#define FONT_MAX 10

class CTurn;
class CInventory;

class CCommandWindow:
	public C2DWindow
{
	static _TCHAR				m_CommandName[COMMAND_MAX][FONT_MAX];			//コマンド名
	static LPD3DXFONT			m_Font;											//描画用フォント
	static RECT					m_Pos[COMMAND_MAX];								//ウィンドウ表示位置

	static bool					m_bDrawFlg;										//描画フラグ

	static VERTEX_2D			m_aVertex[COMMAND_MAX][NUM_VERTEX];				//ポリゴン頂点情報格納用

	static CTurn				m_Turn;											//ステート変更

	static CInventory			m_Inbentory;									//インベントリの描画フラグ変更用

	int							m_EnterInterval;		//アイテム選択時にエンターキーをクリックしてから経った時間を計測する(連続でTriggerが反応することを避けるため)
public:
	CCommandWindow(void);						//コンストラクタ
	~CCommandWindow(void);						//デストラクタ

	void Init();								//初期化
	void Fin();									//終了処理

	void UpDate();								//更新部
	void Draw();								//描画

	void DrawFlgChange();						//描画フラグをON/OFFする

	void SetVertex();							//ポリゴン情報を埋める
	void SetFontPos();							//フォント描画位置設定

	void SetCommand();							//ウィンドウのコマンドを埋める

	//描画のフラグ状況を取得
	static bool GetDrawFlg()	{return m_bDrawFlg;}
};

