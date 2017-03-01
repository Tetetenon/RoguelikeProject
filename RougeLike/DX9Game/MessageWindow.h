#pragma once


#include "Structure.h"
#include <tchar.h>

#define DRAW_NUM 5
#define FONT_NUM 41

class CMessageWindow
{
private:
	//シングルトン
	static CMessageWindow* m_pMessageWindow;

	LPD3DXFONT			m_pFont;						//フォントへのポインタ
	RECT				m_DrawFontPos[DRAW_NUM];		//フォントの描画位置

	_TCHAR		m_Message[DRAW_NUM][FONT_NUM];	//格納するメッセージ(文字数30文字,行数5)

	VERTEX_2D			m_aVertex[DRAW_NUM][NUM_VERTEX];	//ポリゴン頂点情報格納用

	bool			m_bDrawflg;						//描画フラグ
	float		m_fDrawTime;					//描画継続時間

	CMessageWindow(void);					//コンストラクタ
	~CMessageWindow(void);					//デストラクタ
public:
	static void Create();					//実体の作成
	static void Delete();					//実体の削除
	static CMessageWindow* GetPointer();	//実体のポインタを渡す

	void Update();							//更新
	void Draw();							//描画

	void SetVertex ();						//ポリゴン情報の中身を埋める

	void InitFontData();					//フォントのデータを初期化する

	void SetFontPos ();						//フォント描画位置を設定
	
	void SetMassege(_TCHAR String[], ...);	//文字列をセットする
};

