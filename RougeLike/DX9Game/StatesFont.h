#pragma once

//ステータス画面の項目を描画する

#include "C2DTexture.h"
#include "StatesDefine.h"

class CStatesFont :
	public C2DTexture
{
private:
	//使用テクスチャ番号格納用
	static int			m_nTextureNumber[STATES_FONT_MAX];		
	//ポリゴン情報格納用
	static	VERTEX_2D	m_aVertex[STATES_FONT_MAX][NUM_VERTEX];
public:
	CStatesFont(void);		//コンストラクタ
	~CStatesFont(void);		//デストラクタ

	void Draw();			//描画

	void SetVertex ();		//ポリゴン情報の設定
};