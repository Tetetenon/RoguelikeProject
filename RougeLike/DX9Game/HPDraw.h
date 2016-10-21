#pragma once

//プレイヤーの情報を描画する

#include "Structure.h"
#include <tchar.h>

class CHPDraw
{
private:
	static int					m_nHP;					//描画するユニットの現在のHP

	static LPD3DXFONT			m_pFont;					//描画フォントの設定
	static RECT					m_FontDrawPos;				//フォントの描画位置を設定する

	static char				m_States[256];	//ステータス(HP情報)を格納する

	static VERTEX_2D			m_aVertex[NUM_VERTEX];		//テクスチャの描画位置

	static int					m_nMaxHP;					//描画するユニットの最大HP

public:
	CHPDraw(void);										//コンストラクタ
	~CHPDraw(void);										//デストラクタ

	void Init();											//初期化
	void Fin();												//終了処理

	void Update();											//更新
	void Draw();											//描画処理

	static void SetVertex();										//ポリゴン各種情報を設定

	static void SetPosition();										//ポリゴンの位置を再設定

	static void SetFontPos();										//文字描画位置を設定

	static void SetHP (int nHP);							//描画するHP数値をセット

	static void SetMaxHP (int nMaxHP);						//描画するHPの最大HPをセット

};

