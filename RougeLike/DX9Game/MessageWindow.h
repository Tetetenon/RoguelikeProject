#pragma once


#include "Structure.h"
#include <tchar.h>

#define DRAW_NUM 5
#define FONT_NUM 41

class MessageWindow
{
private:
	LPD3DXFONT			m_pFont;						//フォントへのポインタ
	RECT				m_DrawFontPos[DRAW_NUM];		//フォントの描画位置

	static _TCHAR		m_Message[DRAW_NUM][FONT_NUM];	//格納するメッセージ(文字数30文字,行数5)

	VERTEX_2D			m_aVertex[DRAW_NUM][NUM_VERTEX];	//ポリゴン頂点情報格納用

	static bool			m_bDrawflg;						//描画フラグ
	static float		m_fDrawTime;					//描画継続時間
public:
	MessageWindow(void);								//コンストラクタ
	~MessageWindow(void);								//デストラクタ

	void Init ();										//初期化
	void Fin	();										//終了
	void Update();										//更新
	void Draw();										//描画

	void SetVertex ();							//ポリゴン情報の中身を埋める

	void SetFontPos ();							//フォント描画位置を設定
	
	static void SetMassege(_TCHAR String[], ...);		//文字列をセットする
};

